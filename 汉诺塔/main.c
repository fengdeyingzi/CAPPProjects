#include "def.h"
#include "libs/xgui/ToolBar.h"

/*
作者：蟋蟀蝈蝈蛐蛐
Q  Q：1126390395
*/

//菜单
Button*title = NULL;
Button*start = NULL;
Button*about = NULL;
Button*tuichu = NULL;

//游戏背景
View*one = NULL;
View*two = NULL;
View*three = NULL;

//游戏UI
Button*score = NULL;

//游戏数据
int max = 3,select = 0,point = 0;
int o[10],oo[10],ooo[10];

//退出app
void exitUi()
{
 btn_free(title);
 btn_free(start);
 btn_free(about);
 btn_free(tuichu);
 
 view_free(one);
 view_free(two);
 view_free(three);
 exit();
}

void showMenu()
{
 cls(0x80,0x60,0x90);
 view_hide(one);
 view_hide(two);
 view_hide(three);
 
 btn_show(tuichu);
 btn_show(about);
 btn_show(start);
 btn_show(title);
 
 btn_draw(tuichu);
 btn_draw(about);
 btn_draw(start);
 btn_draw(title);
 ref(0,0,SW,SH);
}

//隐藏菜单
void hideMenu()
{
 btn_hide(tuichu);
 btn_hide(about);
 btn_hide(start);
 // btn_hide(title);
}

//游戏数据
void gameData(int n)
{
 max = n+2;
 for(int i = 0;i<10;i++)
 {
  o[i] = 0;
  oo[i] = 0;
  ooo[i] = 0;
 }
 for(int i = 0;i<n+2;i++)
 	o[i] = i+1;
}

//绘制汉诺塔
void drawGame()
{
 if(point==0)
  return ;
  
 char text[50];
 if(!btn_isshow(start))
 {
  drawRect(one->x+one->w/2-10,one->y,20,one->h,0xff805060);
  dtext("起点", one->x+one->w/2-50, one->y+one->h+50, 0xff, 0xff, 0xff, 0, 1);
  drawRect(two->x+one->w/2-10,two->y,20,two->h,0xff805060);
  drawRect(three->x+one->w/2-10,three->y,20,three->h,0xff805060);
  dtext("终点", three->x+three->w/2-50, three->y+three->h+50, 0xff, 0xff, 0xff, 0, 1);
  sprintf(text, "关卡：%d", point);
  dtext(text, title->x+title->w+100, title->y+10, 0xff, 0xff, 0xff, 0, 1);
 }
 
 for(int i = 0;i<max;i++)
 {
  if(o[i]!=0)
  {
   drawRect(one->x+2+(one->w/max*(max-o[i])/2),one->y+one->h/max*i+2,one->w/max*o[i]-4,one->h/max-4,0x80000000);
  }
  
  if(oo[i]!=0)
  {
   drawRect(two->x+2+(one->w/max*(max-oo[i])/2),two->y+two->h/max*i+2,one->w/max*oo[i]-4,two->h/max-4,0x80000000);
  }
  
  if(ooo[i]!=0)
  {
   drawRect(three->x+2+(one->w/max*(max-ooo[i])/2),three->y+three->h/max*i+2,three->w/max*ooo[i]-4,three->h/max-4,0x80000000);
  }
 }
 
 //绘制选中
 for(int i = 0;i<max;i++)
 {
  if(o[i]!=0&&select==1)
  {
   drawRect(one->x+2+(one->w/max*(max-o[i])/2),one->y+one->h/max*i+2,one->w/max*o[i]-4,one->h/max-4,0x80f05060);
   break;
  }
  if(oo[i]!=0&&select==2)
  {
   drawRect(two->x+2+(one->w/max*(max-oo[i])/2),two->y+two->h/max*i+2,one->w/max*oo[i]-4,two->h/max-4,0x80f05060);
   break;
  }
  if(ooo[i]!=0&&select==3)
  {
   drawRect(three->x+2+(one->w/max*(max-ooo[i])/2),three->y+three->h/max*i+2,three->w/max*ooo[i]-4,three->h/max-4,0x80f05060);
   break;
  }
 }
}


//显示游戏
void showGame()
{
 cls(0x80,0x60,0x90);
 btn_draw(tuichu);
 btn_draw(about);
 btn_draw(start);
 btn_draw(title);

 view_show(one);
 view_show(two);
 view_show(three);
 
 gameData(point);
 drawGame();
}

//游戏升级
void gameWin()
{
 if(o[max-1]==0&&oo[max-1]==0&&ooo[max-1]!=0)
 {
  if(point<8)
    point++;
  showGame();
 }
}

//设置
int setNum(int select,int num)
{
 switch(select)
 {
  case 1:
  for(int i = 1;i<max;i++)
  	if(o[i]>num)
  {
   o[i-1] = num;
   return o[i];
  }
  else if(o[max-1]==0)
  	o[max-1] = num;
  break;
  
  case 2:
  for(int i = 1;i<max;i++)
  	if(oo[i]>num)
  {
   oo[i-1] = num;
   return oo[i];
  }
  else if(oo[max-1]==0)
  	oo[max-1] = num;
  break;
  
  case 3:
  for(int i = 1;i<max;i++)
  	if(ooo[i]>num)
  {
   ooo[i-1] = num;
   return ooo[i];
  }
  else if(ooo[max-1]==0)
  	ooo[max-1] = num;
  break;
 }
 return-1;
}

//获取
int delNum(int select)
{
 switch(select)
 {
  case 1:
  for(int i = 0;i<max;i++)
  	if(o[i]!=0)
  {
   o[i] = 0;
   return 0;
  }
  break;
  case 2:
  for(int i = 0;i<max;i++)
  	if(oo[i]!=0)
  {
   oo[i] = 0;
   return 0;
  }
  break;
  case 3:
  for(int i = 0;i<max;i++)
  	if(ooo[i]!=0)
  {
   ooo[i] = 0;
   return 0;
  }
  break;
 }
 return 0;
}

//获取
int getNum(int select)
{
 switch(select)
 {
  case 1:
  for(int i = 0;i<max;i++)
  	if(o[i]!=0)
  	return o[i];
  break;
  case 2:
  for(int i = 0;i<max;i++)
  	if(oo[i]!=0)
  	return oo[i];
  break;
  case 3:
  for(int i = 0;i<max;i++)
  	if(ooo[i]!=0)
  	return ooo[i];
  break;
 }
 return 0;
}

//app监听
void appClick(int id)
{
 cls(0x80,0x60,0x90);
 //printf("%d,%d:",select,id);
 switch(id)
 {
  case 1:
  point=1;
  hideMenu();
  showGame();
  break;
  
  case 2:
  dlgcreate(A_title,A_content,2);
  break;
  
  case 11:
  if(select==0)
  {
   if(getNum(1)!=0)
   	select = 1;
  }
  else if(select==1)
  	select = 0;
  else
  {
   if(getNum(select)<getNum(1)||getNum(1)==0)
   {
    setNum(1,getNum(select));
    delNum(select);
    select = 0;
   }
  }
  break;
  
  case 12:
  if(select==0)
  {
   if(getNum(2)!=0)
   	select = 2;
  }
  else if(select==2)
  	select = 0;
  else
  {
   if(getNum(select)<getNum(2)||getNum(2)==0)
   {
    setNum(2,getNum(select));
    delNum(select);
    select = 0;
   }
  }
  break;
  
  case 13:
  if(select==0)
  {
   if(getNum(3)!=0)
   	select = 3;
  }
  else if(select==3)
  	select = 0;
  else
  {
   if(getNum(select)<getNum(3)||getNum(3)==0)
   {
    setNum(3,getNum(select));
    delNum(select);
    select = 0;
   }
  }
  break;
 }
 //printf("%d,%d\n",select,id);
 
 btn_draw(tuichu);
 btn_draw(about);
 btn_draw(start);
 btn_draw(title);
 view_draw(one);
 view_draw(two);
 view_draw(three);
 
 drawGame();
 gameWin();
 
 if(id==3)
 	exitUi();
 ref(0,0,SW,SH);
}

//初始化app
void initApp()
{
 //菜单
 title = btn_create("汉诺塔",10,10,200-20,100-20);
 start = btn_create("START",300,100,SW-600,150);
 about = btn_create("ABOUT",300,300,SW-600,150);
 tuichu = btn_create("EXIT",300,500,SW-600,150);
 
 btn_setid(title,0);
 btn_setid(start,1);
 btn_setid(about,2);
 btn_setid(tuichu,3);
 
 //btn_setonclick(title, appClick);
 btn_setonclick(start,appClick);
 btn_setonclick(about,appClick);
 btn_setonclick(tuichu,appClick);
 
 btn_draw(tuichu);
 btn_draw(about);
 btn_draw(start);
 btn_draw(title);
 
 //游戏
 one = view_create(50,200,SW/3-100,SH-400);
 two = view_create(SW/3+50,200,SW/3-100,SH-400);
 three = view_create(SW/3*2+50,200,SW/3-100,SH-400);
 view_setid(one,11);
 view_setid(two,12);
 view_setid(three,13);
 view_hide(one);
 view_hide(two);
 view_hide(three);
 view_setonclick(one,appClick);
 view_setonclick(two,appClick);
 view_setonclick(three,appClick);
}

//app事件
void appEvent(int type,int p1,int p2)
{
 //btn_event(title, type, p1, p2);
 btn_event(start,type,p1,p2);
 btn_event(about,type,p1,p2);
 btn_event(tuichu,type,p1,p2);
 
 view_event(one,type,p1,p2);
 view_event(two,type,p1,p2);
 view_event(three,type,p1,p2);
 
 if(KY_UP==type)
 {
  switch(p1)
  {
   case _BACK:
   if(btn_isshow(start))
   exitUi();
   else
   {
   showMenu();
   point=0;
   }
   break;
   case _MENU:
   break;
  }
 }
}

//入口函数
int init()
{
 cls(0x80,0x60,0x90);
 setscrsize(1280,1280*SH/SW);
 //set_statusBarColor(0x80806090);
 
 initApp();
 
 ref(0,0,SW,SH);
 return 0;
}

//event函数
int event(int type,int p1,int p2)
{
 //app事件
 appEvent(type,p1,p2);
 return 0;
}

//应用暂停
int pause()
{
 return 0;
}

//应用恢复
int resume()
{
 return 0;
}
