#include "base.h"
//�����壬Ϊ�˼򵥣���Prev,Next��ֻ����һ����Ա
typedef struct List
{
 char* Text;
 struct List* Prev;
 struct List* Next;
}ListSt;
//��ĩβ����һ�����
void AddList(ListSt* tTail,char* Text)
{
 ListSt *t = malloc(sizeof(ListSt));
 t->Text = malloc(strlen(Text));
 strcpy(t->Text,Text);
 t->Prev = tTail->Prev;
 t->Next = tTail;
 tTail->Prev->Next = t;
 tTail->Prev = t;
}
//ɾ����ͷ��β�������н��
void DelListAll(ListSt* tHead,ListSt* tTail)
{
 ListSt *t = tTail->Prev->Prev;
 while(t != NULL)
 {
  free(t->Next->Text);
  free(t->Next);
  t = t->Prev;
 }
 tHead->Next = tTail;
 tTail->Prev = tHead; 
}
//������
int fontw,fonth;
int init(void)
{
 ListSt *j,*k,*t;
 textwh("��",0,1,&fontw,&fonth);
 
 int size = sizeof(ListSt);
 j = malloc(size);
 memset(j,0,size);
 k = malloc(size);
 memset(k,0,size);
 j->Next = k;
 k->Prev = j;//���潫��ͷ��β��ʼ������������������
 AddList(k,"��һ��");
 AddList(k,"�ڶ���");
 AddList(k,"������");
 AddList(k,"���ĸ�");
 AddList(k,"BY TSC");
 cls(255,255,255);
//����
 t = j->Next;
 int y = 0;
 while(t->Next != NULL)
 {
  dtext(t->Text,0,y,255,0,0,0,1);
  y += fonth;
  t = t->Next;
 }
//����
 y = 0;
 t = k->Prev;
 while(t->Prev != NULL)
 {
  dtext(t->Text,SCRW/2,y,255,0,0,0,1);
  y += fonth;
  t = t->Prev;
 }
 ref(0,0,SCRW,SCRH);
 DelListAll(j,k);
 free(j);
 free(k);
 return 0;
}
int event(int type, int p1, int p2)
{
 if(KY_DOWN == type)
 {
  switch(p1)
  {
   case _SEND:
   case _SRIGHT:
    exit();
    break;
   case _1:
    break;
  }
 }
 if(MS_DOWN == type)
 {
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
//BY TSC
