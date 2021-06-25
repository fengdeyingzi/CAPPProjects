
/*
����ʱ�����
��msΪ��λ

*/

#include <base.h>

typedef struct
{
 int time;
 int timer;
 int max;
} KEYTIME;

//����
int key_create()
{
 KEYTIME *keytime=malloc(sizeof(KEYTIME));
 keytime->time=0;
 keytime->max=3000;
 keytime->timer=timercreate();
 return (int)keytime;
 
}

//����
int key_start(int id)
{
 KEYTIME *keytime=(void*)id;
 timerstart(keytime->timer,1000,(int)keytime,"timerCD",TRUE);
 
 return 0;
}

//���ó���ʱ��
int key_settime(int id,int time)
{
 KEYTIME *keytime=(void*)id;
 keytime->max=time;
 
 return 0;
}

//��ȡʱ��
int key_getTime(int id)
{
 KEYTIME *keytime=(void*)id;
 return keytime->time;
}

//ֹͣ
int key_stop(int id)
{
 KEYTIME *keytime=(void*)id;
 timerstop(keytime->timer);
 return 0;
}


//����
int key_free(int id)
{
 KEYTIME *keytime=(void*)id;
 timerdel(keytime->timer);
 free(keytime);
 
 
 return 0;
}



void timerCD(int data)
{
 KEYTIME *keytime=(void*)data;
 
 keytime->time+=1000;
 
 if(keytime->time>=keytime->max)
 {
  event((int)keytime,0,0);
  timerstop(keytime->timer);
  keytime->time=0;
 }
 
 
}




