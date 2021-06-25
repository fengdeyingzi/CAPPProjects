#include "mrc_base.h"
#include "android.h"

#include "6502.c"
#include "debug.h"
#include "JoyPad.c"
#include "nes_main.c"
#include "PPU.c"
#define SIM_MOD

#define _FILELIST 1
/**
  ******************************************************************************
  
  * @nes模拟器移植：风的影子
  * 请使用tcc运行器运行
  * 需要手机C语言3.0及以上版本
  ******************************************************************************
  * @说明:源码来源于网络,作者佚名,属开源共享资源,目前在真机上的速度很慢且只能模拟40K
  * 以下的ROM,望各路高手共同优化,共享之.
  * 
  ******************************************************************************
  */  
/* SKYSDK version:AF02.04.07 */

/*初始化按键扫描模块，在应用入口被调用一次*/
extern int32 mrc_keyScan_init(void);
/*判断某个底层按键索引值的按键是否被按下*/
extern int32 mrc_keyScan_KeyPressed(int32 keyIndex);
/*获取当前被按下按键的索引值*/
extern int32 mrc_keyScan_getPressedKeyIndex(void);

extern void nes_main(void);
extern void startopcodetable(void);
extern int32 nesloop;
extern void mrc_sleep(uint32 ms);
extern int exitApp();
int32 KEYCODE[8];//键盘值
extern int8  KEY[8];   //按键逻辑 1:按下 其他:没按
uint8 _index;
int32 ROM_len;
unsigned char *rom_file;

void drawTxt(char* txt)
{

	  mrc_drawRect(0,0,240,320,0,0,0);
	  mrc_drawText(txt,0,0,200,0,0,0,0);
	  mrc_refreshScreen(0, 0, 240, 320);

}
void  keyinit(void)
{   
#ifdef SIM_MOD
    _index=8;
#else
    mrc_keyScan_init();
    _index=0;
#endif
    mrc_memset(KEYCODE,0,sizeof(KEYCODE));
    mrc_memset(KEY,0,sizeof(KEY));
}
void setkey(void)
{
int32 f,len;
  len=mrc_getLen("mynes.ini");
  if(len==sizeof(KEYCODE))
  {  
	f=mrc_open("mynes.ini",12);
	mrc_read(f,&KEYCODE,len);
	mrc_close(f);
	_index=8;
  }
}
void Start()
{
    drawTxt("加载中...");
    mrc_sleep(100);
    nes_main();
}
#ifdef _FILELIST

//打开nes
void open_nes(char *filename)
{
 ROM_len=getlen(filename);
 if(ROM_len<=0)return ;
 rom_file=malloc(ROM_len);
 int f=open(filename,1);
 read(f,rom_file,ROM_len);
 close(f);
 if(rom_file!=NULL&&ROM_len>1024&&ROM_len<=90*1024)
	{
	  startopcodetable();
      setkey();
	  if(_index==8)
	  { 
	    Start();
	  }
	  else
	  {
		drawTxt("设置按键: 右");
	  }
	}
	else
	{
	drawTxt("内存不足...");
	mrc_exit();
	}
 
}


int init(void)
{   
	setscrsize(256,256 *SCRH/SCRW);
 setContextView("pad.xml");
setpadtype(2);
	keyinit();
	ROM_len=0;
    nesloop=0;
	rom_file=NULL;
  fv_init(0);
  fv_settype(".nes|.NES",TRUE);
  fv_begin("C");
	return MR_SUCCESS;
}


#else




int init(void)
{   
	setscrsize(256,256 *SCRH/SCRW);
 setContextView("pad.xml");
setpadtype(2);
	keyinit();
	ROM_len=0;
    nesloop=0;
	rom_file=NULL;
    rom_file=(unsigned char *)readFileFromAssets("nes.nes",&ROM_len);
	
	if(rom_file!=NULL&&ROM_len>1024&&ROM_len<=43*1024)
	{
	  startopcodetable();
      setkey();
	  if(_index==8)
	  { 
	    Start();
	  }
	  else
	  {
		drawTxt("设置按键: 右");
	  }
	}
	else
	{
	drawTxt("内存不足...");
	mrc_exit();
	}
	return MR_SUCCESS;
}

#endif

int pause(void)
{
	return 0;
}
int resume(void)
{
	return 0;
}
int exitApp(void)
{	
	if( nesloop!=0)
	{
	  
		mrc_timerDelete(nesloop);
	 
	}
	if(rom_file!=NULL)
	{
	    mrc_free(rom_file);
	}
	return 0;
}
#ifdef SIM_MOD
void keyscan(void)
{


}
int event(int code, int p0, int p1)
{
  if(MR_KEY_PRESS == code)
	{
		switch(p0)
		{
		case MR_KEY_SOFTRIGHT:
    exitApp();
			 mrc_exit();
			 break;
		case MR_KEY_SELECT:
			 KEY[4]=1;
			 break;
  case MR_KEY_SOFTLEFT:  
			 KEY[5]=1;
			 break;
		case MR_KEY_LEFT:
			 KEY[1]=1;
			 break;
		case MR_KEY_RIGHT:
			 KEY[0]=1;
			 break;
		case MR_KEY_UP:
    KEY[3]=1;
			 break;
  case MR_KEY_DOWN:
			 KEY[2]=1;
			 break;
		case MR_KEY_1:
			 KEY[6]=1;
			 break;
		case MR_KEY_2:
			 break;
		case MR_KEY_3:
		  KEY[7]=1;
			 break;
  case MR_KEY_STAR:
  KEY[6]=1;
  break;
  case MR_KEY_POUND:
  KEY[7]=1;
  break;
		}
	}
 else if(code == 21)
 {
  if(p0==17)
  {
   KEY[5]=1;
  }
  else if(p0==20)
  {
   KEY[4]=1;
   
  }
  
 }
 else if(code==10)
 {
  if(p0==DLG_OK)
  {
   open_nes(fv_getpath());
   fv_end();
  }
  
 }
	else 
	{
      keyinit();
	}
	
return MR_SUCCESS;

}
#else
int32 mrc_extRecvAppEvent(int32 app, int32 code, int32 param0, int32 param1)
{
return MR_SUCCESS;
}
int32 mrc_extRecvAppEventEx(int32 code, int32 p0, int32 p1, int32 p2, int32 p3, int32 p4,int32 p5)
{
return MR_SUCCESS;
}
void keyscan(void)
    {  
	   int8 i;
       for(i=0;i<8;i++)
        {
          KEY[i]=(int8)mrc_keyScan_KeyPressed(KEYCODE[i]);
        }
     }
void SetKeyCode(uint8 k)
{   
	int32 f;
	KEYCODE[k]=mrc_keyScan_getPressedKeyIndex();
    _index++;
	if(_index==8)
	{
	   f=mrc_open("mynes.ini",12);
       mrc_write(f,&KEYCODE,sizeof(KEYCODE));
	   mrc_close(f);
	}
}
void NEXT(char* txt)
{
     SetKeyCode(_index);
     drawTxt(txt);
}
int32 mrc_event(int32 code, int32 p0, int32 p1)
     {   
		// uint32 memA,memB;
         if(_index < 8&&code==MR_KEY_PRESS&&p0!=MR_KEY_SOFTRIGHT)
		 {
		    switch(_index)
		    {
			case 7:
			    SetKeyCode(_index);
				Start();
				break;
			case 6:
				NEXT("设置按键: B");
				break;
			case 5:
				NEXT("设置按键: A");
				break;
			case 4:
				NEXT("设置按键: 选择");
				break;
			case 3:
				NEXT("设置按键: 确认");
				break;
			case 2:
				NEXT("设置按键: 上");
				break;
			case 1:
				NEXT("设置按键: 下");
				break;
			case 0:
				NEXT("设置按键: 左");
				break;
		    }
		 }
		 else
		 {
		   if(MR_KEY_PRESS == code&&p0==MR_KEY_SOFTRIGHT)
		   {
		    /* memA=mrc_getSysMem();
			 memB=mrc_getMemoryRemain();
			 memB=memA-memB;
		     FPRINTF("内存花费: %d B,%d Kb",memB,memB/1024);*/
		     mrc_exit();
		   }
		 }
	 return MR_SUCCESS;
     }
#endif
