

#include "./objsen.h"

//绘制ObjSen内obj
void drawSenObj(ObjSen*link)
{
 ObjSen*temp = link;
 while(TRUE)
 {
  if(temp==NULL)
  	return;
  (*temp->obj->draw)(temp->obj);
  temp = temp->next;
 }
}

void drawSenObjCam(ObjSen*link,Cam*cam)
{
 ObjSen*temp = link;
 while(TRUE)
 {
  if(temp==NULL)
  	return;
  if(temp->obj!=NULL)
  {
   if(temp->obj->draw==NULL) 
    drawObjCam(temp->obj,cam);
   else
    (*temp->obj->draw)(temp->obj);
  }
  temp = temp->next;
 }
}

//向ObjSen添加obj
void addSenObj(ObjSen*link,
Obj*obj)
{
 ObjSen*last = NULL;
 ObjSen*temp = link;
 //添加第一个
 if(temp->obj==NULL)
 {
  temp->obj = obj;
  return;
 }
 //循环遍历
 while(TRUE)
 {
  //第一次
  if(last==NULL)
  {
   //一个元素
   if(temp->next==NULL)
   {
    temp->next = 
    malloc(sizeof(ObjSen));
    temp = temp->next;
    break;
   }
   else
   {
    last = temp;
    temp = temp->next;
    continue;
   }
  }
  //遍历结束
  if(temp==NULL)
  {
   last->next = 
   malloc(sizeof(ObjSen));
   temp = last->next;
   break;
  }
  last = temp;
  temp = temp->next;
 }
 temp->obj = obj;
 temp->next = NULL;
}

//检测链接中数目
int getSenObjNum(ObjSen*link,int group)
{
 int index=0;
 ObjSen*temp = link;
 while(TRUE)
 {
  if(temp==NULL)
  	return index;
  //检测碰撞
  if(temp->obj!=NULL
  &&temp->obj->group==group)
   index++;
  else if(group==-1)
   index++;
  temp = temp->next;
 }
 return index;
}

//运行ObjSen
void runObjSen(ObjSen*link)
{
 ObjSen*temp = link;
 while(TRUE)
 {
  if(temp==NULL)
  	return;
  runObj(temp->obj);
  temp = temp->next;
 }
}

//检测点碰撞
Obj* pointSenObj(ObjSen*link,
int x,int y)
{
 Obj*result=NULL;
 ObjSen*temp = link;
 while(TRUE)
 {
  if(temp==NULL)
  	return result;
  	else 
  if(_posCollObj(x,y,temp->obj))
  {
   result=temp->obj;
  }
  temp = temp->next;
 }
 return result;
}

//检测链接中全部碰撞
void collAllSenObj(ObjSen*link)
{
 ObjSen*temp = link;
 while(TRUE)
 {
  if(temp==NULL)
  	return;
  //检测碰撞
  if(temp->obj!=NULL)
  collSenObj(link,temp->obj);
  temp = temp->next;
 }
}

//检测ObjSen碰撞
void collSenObj(ObjSen*link,
 Obj*obj)
{
 ObjSen*temp = link;
 while(TRUE)
 {
  if(temp==NULL)
  	return;
  //过滤自己和同组元素
  if(obj!=temp->obj)
  	if(obj->group!=
    temp->obj->group)
  	if(_objCollObj(obj,temp->obj))
  {
   if(obj->coll!=NULL)
   (*obj->coll)(obj,temp->obj);
  }
  temp = temp->next;
 }
}

//删除ObjSen内一个obj
void delSenOne(ObjSen**link,
 Obj*obj)
{
 int index=0;
 ObjSen*last = NULL;
 ObjSen*temp = *link;
 while(TRUE)
 {
  if(temp==NULL)
  	return;
  
  //释放
  if(temp->obj==obj)
  {
   if(last!=NULL)
   	 last->next = temp->next;
   else
    *link = temp->next;
    
   freeObj(temp->obj);
   free(temp);
   temp=NULL;
   
   printf("delSenOne:%d\n",index);
   return;
  }
  index++;
  last = temp;
  temp = temp->next;
 }
}

//删除ObjSen内全部obj
void delSenAll(ObjSen*link)
{
 int index=0;
 ObjSen*fSen = link;
 ObjSen*temp = link;
 while(TRUE)
 {
  if(temp==NULL)
  	return;
  
  freeObj(temp->obj);
  fSen = temp->next;
  free(temp);
  temp = fSen;
  
  printf("delSenAll:%d\n",index++);
 }
}



