//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <android.h>
#include <graphics.h>

 void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    //dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}

int list;
int bitmap;
//��ں�������������ʱ��ʼִ��
int init()
{
    //���ú���helloworld
    helloworld();
    
    bitmap = readBitmapFromAssets("icon_music.png");
    //���ز���
    setContextView("list.xml");
    //��ȡlistView�ؼ�
    list=findViewById(100);
    //��listView�������Ŀ
    for(int i=0;i<10;i++)
    list_add(list,0,bitmap,"\x98\xce\x76\x84\x5f\x71\x5b\x50\x0\x0","\x66\x2f\x59\x29\x62\x4d\x0\x0");
   // printf("%d",list);
    //ˢ��listView
    list_notifyData(list);
    
    return 0;
}



//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
        bitmapFree(bitmap);
            exit();
            break;
        case _MENU:
            break;
        }
    }
    
    if(type==19)//ListView��event�¼�
    {
     int id=view_getId(list);
     //printf(" p1=%d p2=%d\n",p1,p2);
     if(id==p1)
     {
      //ɾ��һ������
     list_remove(list,p2);
     //ˢ��listView
     list_notifyData(list);
     }
    }

printf("%d %d %d \n",type,p1,p2);
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
 