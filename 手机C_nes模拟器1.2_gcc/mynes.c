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
  
  * @nesģ������ֲ�����Ӱ��
  * ��ʹ��tcc����������
  * ��Ҫ�ֻ�C����3.0�����ϰ汾
  ******************************************************************************
  * @˵��:Դ����Դ������,��������,����Դ������Դ,Ŀǰ������ϵ��ٶȺ�����ֻ��ģ��40K
  * ���µ�ROM,����·���ֹ�ͬ�Ż�,����֮.
  * 
  ******************************************************************************
  */  
/* SKYSDK version:AF02.04.07 */

/*��ʼ������ɨ��ģ�飬��Ӧ����ڱ�����һ��*/
extern int32 mrc_keyScan_init(void);
/*�ж�ĳ���ײ㰴������ֵ�İ����Ƿ񱻰���*/
extern int32 mrc_keyScan_KeyPressed(int32 keyIndex);
/*��ȡ��ǰ�����°���������ֵ*/
extern int32 mrc_keyScan_getPressedKeyIndex(void);

extern void nes_main(void);
extern void startopcodetable(void);
extern int32 nesloop;
extern void mrc_sleep(uint32 ms);
extern int exitApp();
int32 KEYCODE[8];//����ֵ
extern int8  KEY[8];   //�����߼� 1:���� ����:û��
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
    drawTxt("������...");
    mrc_sleep(100);
    nes_main();
}
#ifdef _FILELIST

//��nes
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
		drawTxt("���ð���: ��");
	  }
	}
	else
	{
	drawTxt("�ڴ治��...");
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
		drawTxt("���ð���: ��");
	  }
	}
	else
	{
	drawTxt("�ڴ治��...");
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
				NEXT("���ð���: B");
				break;
			case 5:
				NEXT("���ð���: A");
				break;
			case 4:
				NEXT("���ð���: ѡ��");
				break;
			case 3:
				NEXT("���ð���: ȷ��");
				break;
			case 2:
				NEXT("���ð���: ��");
				break;
			case 1:
				NEXT("���ð���: ��");
				break;
			case 0:
				NEXT("���ð���: ��");
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
		     FPRINTF("�ڴ滨��: %d B,%d Kb",memB,memB/1024);*/
		     mrc_exit();
		   }
		 }
	 return MR_SUCCESS;
     }
#endif
