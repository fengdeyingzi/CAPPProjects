
#include <base.h>
#include <sound.h>

//请将要播放的mp3改名为1.mp3并放到例程文件夹
#define FILENAME "assets://yx.mid"

#define _MP3 3
//mp3设备（类型值参考sound.h中的enum）


 //定时器句柄
int32 timer,vol=5,data;

//用来统计定时器执行次数

int a=0,s=300;


void timerCD(int data)
{
    char text[20];
   sand(getuptime());
    cls(205,155,155);
    //将a的值转换成字符串
    sprintf (text, "%d", a);
    //绘制文字到屏幕上
    dtext (text, 10, 10, 20, 20, 20, 0, 2);
     drect(80,20,350,26,100,255,220); //进度条框
   
   drect(80,23,a*2,20,250,255,152);//进度移动条
    drect(5,500,60,50,125,160,175);//音响
    dtext("⊙",20,505,12,12,12,0,2);
drect(SCRW-80,500,55,50,120,161,175);//音响 
dtext("⊙",SCRW-68,505,12,12,12,0,2);
drect(73,510,320,30,50,190,120);//音量显示框
drect(80,513,s,23,200,190,120);//音量大小显示条
drect(80,600,68,58,125,255,220);//play
drect(107,618,18,24,125,125,220);
drect(105,620,22,20,125,125,220);//play
drect(150,600,68,58,125,255,220);//VOL-
drect(280,600,68,58,125,255,220);//vol+ 
drect(5,600,68,58,125,210,250);//pause
 dtext("||",28,610,12,12,12,0,0);
    dtext("VOL-",158,610,12,12,12,0,0);
  dtext("VOL+",285,610,12,12,12,0,0);
   
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
   a++;
    
}
int init(void)
{
 
   cls(180,150,200);
//创建定时器
    timer=timercreate();
    //启动定时器 
   timerCD(0);
   timerstart (timer, 1000, 1234, "timerCD", TRUE);
 
    
    if(soundinit(_MP3))
    {
        dtext("不支持",0,0,255,255,255,FALSE,1);
    }
    else
    {
        dtext("正在播放",0,0,255,255,255,FALSE,1);
  /*drect(5,300,60,50,125,160,150);*/      soundloadfile(_MP3,FILENAME);
        soundplay(_MP3,0,FALSE);
    
    setvolume(vol);
    }
    ref(0,0,SCRW,SCRH);
    return 0;
}

int event(int type, int p1, int p2)
{
    //暂停放音
    if(MS_DOWN==type)
   { if(p1<=50&&p2<650&&p2>600)
   {
    soundpause(_MP3);
drect(5,600,68,58,125,210,250);
   ref(0,600,70,650);
   
   timerstop(timer);
   //〖定时为何不能停止〗
   }
if(p1>=80&&p1<=148&&p2<650&&p2>600)
 soundresume(_MP3);
 timerstart(timer,1000,1234,"timerCD",TRUE);
      

    }
    
   if(MS_DOWN==type)
   {
   int _s; if(p1>=150&&p1<=218&&p2<=658&&p2>600)
    {if(s>0)s-=50;if(vol>0)vol-=1;
   
   drect(150,600,69,99,125,251,220);//音量按键-
    //drect(75,513,320,29,50,190,120);//显示框
    //drect(78,513,s,23,220,190,120);//显示音量大小
    ref(5,302,SCRW-53,SCRH-350);
    }
   if(p1>=280&&p1<=348&&p2<=658&&p2>600)
    {
     if(s<300)s+=50;if(vol<6){
     vol+=1;
   }
   drect(285,600,60,58,125,251,220);//音量按键+
    //drect(70,310,350,30,120,150,180);
    //drect(73,313,SCRW-350+vol,23,250,190,120);
    ref(5,302,SCRW,SCRH-350);
    }
    setvolume(vol);
     } 
    if(KY_DOWN == type)
    {
        switch(p1)
        {
        case _SRIGHT:
            exitapp();
            break;
        case _1:
            break;
        }
    }

    return 0;
}

int pause(void)
{
    return 0;
}

int resume(void)
{
    return 0;
}

int exitapp(void)
{
    soundstop(_MP3);
    soundclose(_MP3);
    //退出时删除定时器
    timerdel(timer);
    exit();
    return 0;
}