
#include "game.h"

int NUM = 3;
#define WW 64
#define MAX 5

//记录所有卡片
Obj*cardArr[MAX*MAX];

int32 windlg = -1;
//data[0]记录卡片上的数据
//data[1]记录卡片的数组位置
void resetCard();
int reset = FALSE;
int resetNum = 0;
Obj*resetBtn = NULL;
int gameTime = 0;

//触屏操作，选中的
Obj*touch = NULL;
//0指针
Obj*one = NULL;

//绘制卡片
void drawCard(void*ob)
{
 Obj*obj = ob;
 char data[100];
 
 Cam*cam = &(_room->cam);
 drawObjCam(obj,&(_room->cam));
 
 if(obj->data[0]!=0)
 {
  sprintf(data,"%d",obj->data[0]);
  fnt_drawline(GM.fnt,
   data,obj->x+cam->x-15,
   obj->y+cam->y-20);
 }
}

//判断是否胜利
int isWin()
{
 int index = 0;
 int i,j;
 for( j = 0;j<NUM;j++)
 	for( i = 0;i<NUM;i++)
 {
  index = i+j*NUM;
  if(index==NUM*NUM-1)
  	return TRUE;
  
  if(cardArr[index]->data[0]
    !=index+1)
  	return FALSE;
 }
 return TRUE;
}

//获取卡片
Obj*getCard(int num)
{
  int i=0,j=0;
 for( j = 0;j<NUM;j++)
 	for( i = 0;i<NUM;i++)
 {
  if(cardArr[i+j*NUM]->data[0]==num)
  {
   printf("getCard%d:%d\n",
    num,i+j*NUM);
   return cardArr[i+j*NUM];
  }
 }
 return NULL;
}

//运动卡片
int runCard(int dir)
{
 int index = 0,data = -1;
 Obj*obj = getCard(0);
 if(obj!=NULL)
 	switch(dir)
 {
  //上，看下面有没有卡
  case _UP:
  index = obj->data[1]+NUM;
  if(index<NUM*NUM)
  {
   data = obj->data[0];
   obj->data[0] = 
   cardArr[index]->data[0];
   cardArr[index]->data[0] = data;
   return TRUE;
  }
  break;
  
  case _DOWN:
  index = obj->data[1]-NUM;
  if(index>=0)
  {
   data = obj->data[0];
   obj->data[0] = 
   cardArr[index]->data[0];
   cardArr[index]->data[0] = data;
   return TRUE;
  }
  break;
  
  case _LEFT:
  index = obj->data[1]+1;
  if(index<NUM*NUM)
  	if(index%NUM!=0)
  {
   data = obj->data[0];
   obj->data[0] = 
   cardArr[index]->data[0];
   cardArr[index]->data[0] = data;
   return TRUE;
  }
  break;
  
  case _RIGHT:
  index = obj->data[1]-1;
  if(index>=0)
  	if(index%NUM!=NUM-1)
  {
   data = obj->data[0];
   obj->data[0] = 
   cardArr[index]->data[0];
   cardArr[index]->data[0] = data;
   return TRUE;
  }
  break;
 }
 return FALSE;
}

//打乱卡片
void resetCard()
{
 sand(getuptime());
 int j=0;
 int i=0;
 for( j = 0;j<NUM;j++)
 	for( i = 0;i<NUM;i++)
 {
  cardArr[i+j*NUM]->data[0] = 
  (1+i+j*NUM)%(NUM*NUM);
 }
 reset = TRUE;
 resetNum = 0;
 gameTime = 0;
}

//房间创建
void homeCreate(void*rm)
{
 int dxy = 0;
 Obj*obj;
 Spr*spr;
 Room*room = rm;
 //载入资源
 GM.fnt = (_FNT*)
 getRes("fnt/font.fnt",tFnt)->id;
 
 spr = (Spr*)
 getRes("spr/reset.spr",tSpr)->id;
 obj = newObj(SW-64,SH-64,spr);
 resetBtn = obj;
 roomAddObj(room,obj);
 
 spr = (Spr*)
 getRes("spr/card.spr",tSpr)->id;
 int i=0,j=0;
 for( j = 0;j<NUM;j++)
 	for( i = 0;i<NUM;i++)
 {
  dxy = (SW-NUM*WW)/2+WW/2;
  obj = newObj(dxy+i*WW,
   dxy+j*WW+(SH-SW)/2,spr);
  roomAddObj(room,obj);
  
  obj->data[0] = 
  (1+i+j*NUM)%(NUM*NUM);
  obj->data[1] = i+j*NUM;
  obj->draw = drawCard;
  
  cardArr[i+j*NUM] = obj;
 }
 resetCard();
}

//绘制房间
void homeDraw(void*rm)
{
 char data[100];
 
 Room*room = rm;
 drawSenObjCam(room->sen,
  &(room->cam));
 
 sprintf(data,"TIME:%d",gameTime/100);
 fnt_drawline(GM.fnt,data,85,80);
 
 if(touch!=NULL)
 {
  drawRect(0,0,SW,SH,0x80ffffff);
  one = getCard(0);
  if(one!=NULL)
  	drawCard(one);
  
  drawCard(touch);
 }
 
 //打乱棋盘
 if(reset)
 {
  if(resetNum>NUM*10)
  {
   reset = FALSE;
   resetNum = 0;
  }
  else
  {
   runCard(rand()%4+12);
   resetNum++;
  }
 }
 else
  gameTime+=1;
}

//房间事件
void homeEvent(int type,int p1,int p2)
{
 //按下
 if(type==MS_UP)
 {
  if(_posCollObj(p1,p2,resetBtn))
   resetCard();
 }
 
 //复位中
 if(reset)
 	return;
 
 int yes = FALSE;
 Obj*obj = NULL;

 //按下
 if(type==MS_DOWN)
 {
  //点击且不是0
  touch = 
  pointSenObj(_room->sen,p1,p2);
  
  //判断四周
  one = getCard(0);
  obj = pointSenObj(_room->sen,
   p1-WW,p2);
  if(obj==one)
  	yes = TRUE||yes;
  
  obj = pointSenObj(_room->sen,
   p1+WW,p2);
  if(obj==one)
  	yes = TRUE||yes;
  
  obj = pointSenObj(_room->sen,
   p1,p2+WW);
  if(obj==one)
  	yes = TRUE||yes;
  
  obj = pointSenObj(_room->sen,
   p1,p2-WW);
  if(obj==one)
  	yes = TRUE||yes;
  
  if(touch!=NULL)
  	if(touch->data[0]==0||yes==FALSE)
  	touch = NULL;
  
  //记录位置
  if(touch!=NULL)
  {
   touch->data[2] = touch->x;
   touch->data[3] = touch->y;
  }
 }
 //移动
 if(type==MS_MOVE)
 {
  //移动
  if(touch!=NULL)
  {
   touch->x = p1;
   touch->y = p2;
  }
 }
 //抬起
 if(type==MS_UP)
 {
  //归位
  if(touch!=NULL)
  {
   if(_objCollObj(touch,one))
   {
    yes = touch->data[0];
    touch->data[0] = one->data[0];
    one->data[0] = yes;
   }
   
   touch->x = touch->data[2];
   touch->y = touch->data[3];
   touch = NULL;
  }
 }
 
 if(type==KY_UP||type==MS_UP)
 	if(isWin())
 {
  windlg = dlgcreate("\x6e\x38\x62\xf\x80\xdc\x52\x29\x0\x0","\x0\xa\x60\x6d\x55\x9c\x60\xa8\x90\x1a\x8f\xc7\x6e\x38\x62\xf\xff\x1\x0\xa\x6b\x22\x8f\xce\x52\xa0\x51\x65\x0\x51\x0\x51\x7f\xa4\xff\x1a\x0\x33\x0\x37\x0\x30\x0\x34\x0\x36\x0\x38\x0\x30\x0\x30\x0\x31\x0\xa\x52\xa0\x51\x65\x5f\x71\x5b\x50\x4f\xf1\x4e\x50\x90\xe8\xff\xc\x4e\x0\x8d\x77\x73\xa9\x6e\x38\x62\xf\xff\x1\x0\xa\x0\x0",0);
 }
 
 //键盘
 if(type==KY_DOWN)
 {
  runCard(p1);
 }
 
 if(type==MR_DIALOG)
 {
  dlgdel(windlg);
  resetCard();
 }
 //退出页面
 if(KY_UP==type)
 {
  switch(p1)
  {
   case _BACK:
   exitRoom(_room);
   GM.rmHome = NULL;
   gotoMenu();
   break;
  }
 }
}

//跳转房间
int gotoHome()
{
 if(GM.rmHome==NULL)
 {
  GM.rmHome = 
  newRoom(320,320*SH/SW,100);
 }
 GM.rmHome->create = homeCreate;
 GM.rmHome->draw = homeDraw;
 GM.rmHome->event = homeEvent;
 gotoRoom(GM.rmHome);
 return 0;
}




