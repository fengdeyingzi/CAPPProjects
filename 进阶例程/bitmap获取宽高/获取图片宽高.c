//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <exb.h>
#include <graphics.h>
//�����Զ���ͷ�ļ�
#include "uptime.h"

setpadtype(2);

//��ں�������������ʱ��ʼִ��
int init()
{

  
  getTime();
  cls(240,240,240);
  ref(0,0,500,500);
  getTime();
   
 int32 bitmap= readBitmapFromAssets ("1.png");
BITMAPINFO picinfo;
bitmapGetInfo(bitmap,&picinfo);
 printf("ͼƬ��ȣ�%d �߶ȣ�%d",picinfo.width,picinfo.height);
drawBitmap(bitmap,0,0);
bitmapFree(bitmap);
    ref(0,0,SCRW,SCRH);
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
            exit();
            break;
        case _1:
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
 