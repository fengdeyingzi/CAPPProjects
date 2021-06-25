#include "./room.h"

Room*_room = NULL;

//创建room
Room*newRoom(int w,int h,int sp)
{
 Room*rm = malloc(sizeof(Room));
 rm->sen =
 malloc(sizeof(ObjSen));
 rm->sen->obj=NULL;
 rm->sen->next=NULL;
 rm->sp = sp;
 rm->tim = getuptime();
 rm->w = w;
 rm->h = h;
 rm->create = NULL;
 rm->draw = NULL;
 rm->exit = NULL;
 rm->event = NULL;
 rm->cam.x=0;
 rm->cam.y=0;
 rm->cam.w=SW;
 rm->cam.h=SH;
 setscrsize(w,h);
 printf("\n\n***newRoom*%d*%d***\n",
 w,h);
 return rm;
}

//跳转房间
void gotoRoom(Room*rm)
{
 _room = rm;
 //执行跳转
 if(_room->create!=NULL)
 	_room->create(_room);
 printf("\n\n***gotoRoom***\n");
}

//添加obj
void roomAddObj(Room*rm,Obj*obj)
{
 if(rm==NULL)
 return;
 addSenObj(rm->sen,obj);
}

void drawRoom(Room*rm)
{
 if(rm==NULL)
 return;
 if(rm->draw!=NULL)
  rm->draw(rm);
 else
  drawSenObjCam(rm->sen,&(rm->cam));
}

void drawCurRoom()
{
 drawRoom(_room);
}

//运行房间
void runRoom(Room*rm)
{
 if(rm==NULL)
 return;
 if(getuptime()-rm->tim>=rm->sp)
 {
  rm->tim=getuptime();
  runObjSen(rm->sen);
  collAllSenObj(rm->sen);
 }
}

//运行当前房间
void runCurRoom()
{
 runRoom(_room);
}


//退出房间
void exitRoom(Room*rm)
{
 if(rm==NULL)
 return;
 if(rm->exit!=NULL)
 	rm->exit(rm);
 else
  delSenAll(rm->sen);
 rm = NULL;
 printf("\n\n***exitRoom***\n");
}



