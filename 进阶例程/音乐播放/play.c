
#include <base.h>
#include <sound.h>

//�뽫Ҫ���ŵ�mp3����Ϊ1.mp3���ŵ������ļ���
#define FILENAME "assets://yx.mid"

#define _MP3 3
//mp3�豸������ֵ�ο�sound.h�е�enum��


 //��ʱ�����
int32 timer,vol=5,data;

//����ͳ�ƶ�ʱ��ִ�д���

int a=0,s=300;


void timerCD(int data)
{
    char text[20];
   sand(getuptime());
    cls(205,155,155);
    //��a��ֵת�����ַ���
    sprintf (text, "%d", a);
    //�������ֵ���Ļ��
    dtext (text, 10, 10, 20, 20, 20, 0, 2);
     drect(80,20,350,26,100,255,220); //��������
   
   drect(80,23,a*2,20,250,255,152);//�����ƶ���
    drect(5,500,60,50,125,160,175);//����
    dtext("��",20,505,12,12,12,0,2);
drect(SCRW-80,500,55,50,120,161,175);//���� 
dtext("��",SCRW-68,505,12,12,12,0,2);
drect(73,510,320,30,50,190,120);//������ʾ��
drect(80,513,s,23,200,190,120);//������С��ʾ��
drect(80,600,68,58,125,255,220);//play
drect(107,618,18,24,125,125,220);
drect(105,620,22,20,125,125,220);//play
drect(150,600,68,58,125,255,220);//VOL-
drect(280,600,68,58,125,255,220);//vol+ 
drect(5,600,68,58,125,210,250);//pause
 dtext("||",28,610,12,12,12,0,0);
    dtext("VOL-",158,610,12,12,12,0,0);
  dtext("VOL+",285,610,12,12,12,0,0);
   
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
   a++;
    
}
int init(void)
{
 
   cls(180,150,200);
//������ʱ��
    timer=timercreate();
    //������ʱ�� 
   timerCD(0);
   timerstart (timer, 1000, 1234, "timerCD", TRUE);
 
    
    if(soundinit(_MP3))
    {
        dtext("��֧��",0,0,255,255,255,FALSE,1);
    }
    else
    {
        dtext("���ڲ���",0,0,255,255,255,FALSE,1);
  /*drect(5,300,60,50,125,160,150);*/      soundloadfile(_MP3,FILENAME);
        soundplay(_MP3,0,FALSE);
    
    setvolume(vol);
    }
    ref(0,0,SCRW,SCRH);
    return 0;
}

int event(int type, int p1, int p2)
{
    //��ͣ����
    if(MS_DOWN==type)
   { if(p1<=50&&p2<650&&p2>600)
   {
    soundpause(_MP3);
drect(5,600,68,58,125,210,250);
   ref(0,600,70,650);
   
   timerstop(timer);
   //����ʱΪ�β���ֹͣ��
   }
if(p1>=80&&p1<=148&&p2<650&&p2>600)
 soundresume(_MP3);
 timerstart(timer,1000,1234,"timerCD",TRUE);
      

    }
    
   if(MS_DOWN==type)
   {
   int _s; if(p1>=150&&p1<=218&&p2<=658&&p2>600)
    {if(s>0)s-=50;if(vol>0)vol-=1;
   
   drect(150,600,69,99,125,251,220);//��������-
    //drect(75,513,320,29,50,190,120);//��ʾ��
    //drect(78,513,s,23,220,190,120);//��ʾ������С
    ref(5,302,SCRW-53,SCRH-350);
    }
   if(p1>=280&&p1<=348&&p2<=658&&p2>600)
    {
     if(s<300)s+=50;if(vol<6){
     vol+=1;
   }
   drect(285,600,60,58,125,251,220);//��������+
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
    //�˳�ʱɾ����ʱ��
    timerdel(timer);
    exit();
    return 0;
}