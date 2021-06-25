#include "nes_main.h"
#include "mrc_base.h"
#include "exb.h"

int8  KEY[8];  
uint8 FrameCnt;

void NEStimer(int32 data)
{

if(getkeypressed(_UP)==0)
 {
  KEY[3]=1;
  
 }
 else
 {
  KEY[3]=0;
 }
 if(getkeypressed(_DOWN)==0)
 {
  KEY[2]=1;
  
 }
 else
 {
  KEY[2]=0;
 }
 if(getkeypressed(_LEFT)==0)
 {
  KEY[1]=1;
  
 }
 else
 {
  KEY[1]=0;
 }
 if(getkeypressed(_RIGHT)==0)
 {
  KEY[0]=1;
  
 }
 else
 {
  KEY[0]=0;
 }

 if(getkeypressed(_STAR)==0)
 {
  KEY[6]=1;
  
 }
 else
 {
  KEY[6]=0;
 }
 if(getkeypressed(_POUND)==0)
 {
  KEY[7]=1;
 }
 else
 {
  KEY[7]=0;
 }
 
 




uint32	clocks;	//CPU执行时间

FrameCnt++;		   //帧计数器


SpriteHitFlag = FALSE;	

for(PPU_scanline=0; PPU_scanline<20; PPU_scanline++)
{ 
   exec6502(CLOCKS_PER_SCANLINE);
}
exec6502(CLOCKS_PER_SCANLINE);



PPU_scanline++;	  //20++
PPU_Reg.R2 &= ~R2_SPR0_HIT;

for(PPU_scanline=21; PPU_scanline < SCAN_LINE_DISPALY_END_NUM; PPU_scanline++)
{
	if((SpriteHitFlag == TRUE) && ((PPU_Reg.R2 & R2_SPR0_HIT) == 0))
	{
	clocks = sprite[0].x * CLOCKS_PER_SCANLINE / NES_DISP_WIDTH;
	exec6502(clocks);//需重点优化
	PPU_Reg.R2 |= R2_SPR0_HIT;
	exec6502(CLOCKS_PER_SCANLINE - clocks);
	}
	else
	{
	exec6502(CLOCKS_PER_SCANLINE);//耗时大户
	}
   if(PPU_Reg.R1 & (R1_BG_VISIBLE | R1_SPR_VISIBLE))
    {					//若为假，关闭显示
         if(SpriteHitFlag == FALSE)
       {
          NES_GetSpr0HitFlag(PPU_scanline - SCAN_LINE_DISPALY_START_NUM);	
       }
   }
   FrameCnt=FrameCnt%3;
   if(FrameCnt ==0)
   {	
	 //每3帧显示一次
    //耗时大户
	NES_RenderLine(PPU_scanline - SCAN_LINE_DISPALY_START_NUM);		
   }


}
exec6502(CLOCKS_PER_SCANLINE);
PPU_Reg.R2 |= R2_VBlank_Flag;	//设置VBANK 标志
 if(PPU_Reg.R0 & R0_VB_NMI_EN)
 {
   NMI_Flag = SET1;	//完成一帧扫描，产生NMI中断	
   mrc_refreshScreen(0, 0, 256, 256);
  }

}

uint16 * w_getScreenBuffer(void);
uint16 * LCDBUF;
int32 nesloop;

void NesFrameCycle(void)
{
	FrameCnt = 0;
	nesloop=mrc_timerCreate();
	LCDBUF = w_getScreenBuffer();
    mrc_timerStart(nesloop,24,0,NEStimer,1);
}

//启动nes
void nes_main(void)
{	
	NesHeader *neshreader = (NesHeader *) rom_file;
	NES_JoyPadInit();
	init6502mem(0,0,(&rom_file[0x10]),neshreader->romnum);  
	reset6502();
	PPU_Init((&rom_file[0x10] + (neshreader->romnum * 0x4000)), (neshreader->romfeature & 0x01));	/*PPU_初始化*/	
	NesFrameCycle();
}

//退出nes
void nes_del()
{
 
 
}