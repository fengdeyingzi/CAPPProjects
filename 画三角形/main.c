//����ϵͳͷ�ļ�base.h
#include "base.h"
#include "ex_math.h"
#include "triangle.h"



void helloworld()
{
 //��ָ����ɫ�����Ļ
 cls(0,0,0);
 int upx=SCRW,upy=SCRH/2;
 int ix,iy;
 
 int time=getuptime();
 for(int i=0;i<=360;i+=360/5)
 {
  toSpin(SCRW/2,SCRH/2,SCRW/4,SCRW/4,i,&ix,&iy);
  tri_draw(ix,iy,upx,upy,SCRW/2,SCRH/2,255,25,255);
  upx=ix;
  upy=iy;
 }

printf("%d ms\n",getuptime()-time);

 //ˢ����Ļ
 ref(0,0,SCRW,SCRH);
}


//��ں�������������ʱ��ʼִ��
int init()
{
 //���ú���helloworld
 helloworld();
 
 return 0;
}




//event������������Ϣ�¼�
int event(int type,int p1,int p2)
{
 if(KY_UP==type)
 {
  switch(p1)
  {
   case _BACK:
   exit();
   break;
   case _MENU:
   break;
  }
 }
 
 return 0;
}

//Ӧ����ͣ������������̨���Ϊ���ɼ�ʱ����ô˺���
int pause()
{
 return 0;
}

//Ӧ�ûָ��������Ϊ�ɼ�ʱ���ô˺���
int resume()
{
 return 0;
}
