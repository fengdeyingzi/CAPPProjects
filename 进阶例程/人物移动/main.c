#include<base.h>
#include<graphics.h>
#include<android.h>
#include"map.h"
#include"people.h"
int nx=400;
int ny=230;//������
int x=400;
int y=230;//������
int time=2;//����
int fang=2;;//�ϸ�����
int32 sp;//ˢ��
int32 timerrun=0;//�ƶ��߳�
int32 zb;//�����߳�
int z=1;//�������
int gx=900;//�������ƶ�����
int v=0;
int zhuang=0;

void exitxuan(void)//�˳�ѡ��
{
     int a=dlgcreate("\x90\x0\x51\xfa\xff\x1f\x0\x0","\x66\x2f\x54\x26\x90\x0\x51\xfa\xff\x1f\x0\x0",1);
}

int f(void)//����ѡ��
{
        int a=2;
        //����
        if(nx>=x)
        {
        if(ny>y)
        {           
           if(nx-x>=ny-y)
           a=3;
           else
           a=1;
        }
        else
        {
            if(nx-x>=y-ny)
            a=3;
            else
            a=2;
        }
        }
        if(nx<x)
        {
        if(ny>y)
        {
            if(x-nx>=ny-y)
            a=4;
            else
            a=1;
        }
        else
        {
             if(x-nx>=y-ny)
             a=4;
             else
             a=2;
        }
        }
        if(nx==x&&ny==y)
        a=fang;
        else
        fang=a;
        return a;
}

void run(int date)//�ƶ�
{
    if(nx==x&&ny==y)
    timerdel(timerrun);
    
    if(x>nx)
    nx++;
    if(x<nx)
    nx--;
    if(x==nx)
    nx=x;
    
    if(y>ny)
    ny++;
    if(y<ny)
    ny--;
    if(y==ny)
    ny=y;
}

void gun(int date)
{
    dtext("�����ƶ����˵���״̬",gx,0,0,0,0,0,2);
    if(gx==-300)
    gx=900;
    else
    gx-=5;
}

void shua(int date)//ˢ��
{
    cls(255,255,255);
    map1();
    int v=1;
    if((nx!=x)||(ny!=y))
    {
    if(time%2==0)
    v=0;
    else
    v=2;
    time++;
    }
    bmap(f(),v,nx,ny);
    zmap1();
    gun(0);
    ref(0,0,SCRW,SCRH);
}

int init()
{
   sp=timercreate();
   zb=timercreate();
   bmap(2,1,nx,ny);
   timerstart(sp,200,341,"shua",1);
   return 0;
}





//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        //���·��ؼ������˳�
        case _SRIGHT:
            exitxuan();
            break;
        case _MENU:
            timerstop(sp);
            cls(0,0,0);
            setContextView("1.xml");
            ref(0,0,SCRW,SCRH);
            break;
        }
    }
    if(type==MS_DOWN)
    {
        if(timerrun!=0)
        timerdel(timerrun);
        x=p1;
        y=p2;
        
        v=1;
        timerrun=timercreate();
        timerstart(timerrun,50,1,"run",1);
    }
    
    if(type==MR_DIALOG)//�˳�ѡ��
    {
        if(p1==DLG_OK)
        {
           timerdel(sp);
           exit();
        }
        if(p1==DLG_CANCEL)
        {}
    }
    if(type==VIEW_DOWN)
    {
       if(p1==01&&zhuang==0)
       {
        int text1=findViewById(101);
        int text2=findViewById(102);
        int text3=findViewById(103);
        int text4=findViewById(104);
        view_setText(text1,"\x54\xd\x5b\x57\x0\x3a\x4e\x8c\x7e\xf4\x0\x20\x0\x20\x0\x20\x7b\x49\x7e\xa7\x0\x3a\x0\x31\x0\x30\x0\x30\x0\x0");
        view_setText(text2,"\x5c\x5e\x60\x27\x4e\x0\x0\x3a\x0\x31\x0\x30\x0\x30\x0\x0");
        view_setText(text3,"\x5c\x5e\x60\x27\x4e\x8c\x0\x3a\x0\x31\x0\x30\x0\x30\x0\x0");
        view_setText(text4,"\x5c\x5e\x60\x27\x4e\x9\x0\x3a\x0\x31\x0\x30\x0\x30\x0\x0");
        zhuang=1;
       }
       else
       {
        int text1=findViewById(101);
        int text2=findViewById(102);
        int text3=findViewById(103);
        int text4=findViewById(104);
        view_setText(text1,"\x0\x0");
        view_setText(text2,"\x0\x0");
        view_setText(text3,"\x0\x0");
        view_setText(text4,"\x0\x0");
        zhuang=0;
       }
       
       if(p1==9)
       {
       timerstart(sp,200,341,"shua",1);
       clearView();
       }
    }

    return 0;
}

//Ӧ����ͣ������������̨���Ϊ���ɼ�ʱ����ô˺���
int pause()
{
    timerstop(sp);
    timerdel(sp);
    sp=timercreate();
    return 0;
}

//Ӧ�ûָ��������Ϊ�ɼ�ʱ���ô˺���
int resume()
{
    timerstart(sp,200,341,"shua",1);
    return 0;
}
 