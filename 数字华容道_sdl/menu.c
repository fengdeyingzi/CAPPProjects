#include "game.h"

void drawBtn(void*ob)
{
 Obj*obj = ob;
 char data[100];
 
 Cam*cam = &(_room->cam);
 drawObjCam(obj,&(_room->cam));
 
 if(obj->data[0]!=0)
 {
  sprintf(data,
  "%dX%d",obj->data[0],obj->data[0]);
  fnt_drawline(GM.fnt,
   data,obj->x+cam->x-40,
   obj->y+cam->y-25);
 }
}

//房间创建
void menuCreate(void*rm)
{
 Spr*spr = NULL;
 Obj*obj = NULL;
 Room*room = rm;
 //载入资源
 GM.fnt = (_FNT*)
 getRes("fnt/font.fnt",tFnt)->id;
 spr = (Spr*)
 getRes("spr/btn.spr",tSpr)->id;
 
 obj = newObj(SW/2,SH-300,spr);
 obj->draw=drawBtn;
 obj->data[0]=5;
 roomAddObj(room,obj);
 
 obj = newObj(SW/2,SH-450,spr);
 obj->draw=drawBtn;
 obj->data[0]=4;
 roomAddObj(room,obj);
 
 obj = newObj(SW/2,SH-600,spr);
 obj->draw=drawBtn;
 obj->data[0]=3;
 roomAddObj(room,obj);
}

//绘制房间
void menuDraw(void*rm)
{
 Room*room = rm;
 drawSenObjCam(room->sen,
  &(room->cam));
 img("assets://logo.png",49,0);
}

void menuEvent(int type,int p1,int p2)
{
 Obj*obj=NULL;
 if(MS_DOWN==type)
 {
  obj = 
  pointSenObj(_room->sen,p1,p2);
  if(obj!=NULL)
  {
   NUM=obj->data[0];
   exitRoom(_room);
   GM.rmMenu = NULL;
   gotoHome();
  }
 }
 
 if(KY_UP==type)
 {
  switch(p1)
  {
   case _BACK:
   exitRoom(_room);
   GM.rmMenu = NULL;
   capp_exit();
   break;
  }
 }
}

//跳转房间
int gotoMenu()
{
 if(GM.rmMenu==NULL)
 {
  GM.rmMenu = 
  newRoom(640,640*SH/SW,100);
 }
 GM.rmMenu->create = menuCreate;
 GM.rmMenu->draw = menuDraw;
 GM.rmMenu->event = menuEvent;
 gotoRoom(GM.rmMenu);
 return 0;
}

