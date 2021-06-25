#include "base.h"
//链表定义，为了简单，除Prev,Next外只定义一个成员
typedef struct List
{
 char* Text;
 struct List* Prev;
 struct List* Next;
}ListSt;
//在末尾增加一个结点
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
//删除除头、尾以外所有结点
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
//字体宽高
int fontw,fonth;
int init(void)
{
 ListSt *j,*k,*t;
 textwh("子",0,1,&fontw,&fonth);
 
 int size = sizeof(ListSt);
 j = malloc(size);
 memset(j,0,size);
 k = malloc(size);
 memset(k,0,size);
 j->Next = k;
 k->Prev = j;//上面将链头链尾初始化，并将其连接起来
 AddList(k,"第一个");
 AddList(k,"第二个");
 AddList(k,"第三个");
 AddList(k,"第四个");
 AddList(k,"BY TSC");
 cls(255,255,255);
//正向
 t = j->Next;
 int y = 0;
 while(t->Next != NULL)
 {
  dtext(t->Text,0,y,255,0,0,0,1);
  y += fonth;
  t = t->Next;
 }
//反向
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
