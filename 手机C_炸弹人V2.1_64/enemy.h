#include <base.h>
#include <ex_game.h>
#include "map.h"

enum
{
 SP_DOWN,
 SP_LEFT,
 SP_RIGHT,
 SP_UP
 };

int en_impact(int32 bomb,int32 enemy)
{
 int itemx=sp_getx(bomb)/40;
 int itemy=sp_gety(bomb)/40;
    int ix,iy;
  ix=itemx*40+20;
  iy=itemy*40+20;
  //判断是否炸到怪物
  
   if(sp_getAction(enemy)<4)
   {
    if(sp_impact(enemy,ix,iy))
    {
     //sp_setDraw(enemy,FALSE);
     return TRUE;
    }
   }
  
  
  ix=(itemx-1)*40+20;
  iy=itemy*40+20;
  //判断是否炸到怪物
  
   if(sp_getAction(enemy)<4)
   {
    if(sp_impact(enemy,ix,iy))
    {
     //sp_setDraw(enemy,FALSE);
     return TRUE;
    }
   }
  
  
  ix=(itemx+1)*40+20;
  iy=itemy*40+20;
  //判断是否炸到怪物
  
   if(sp_getAction(enemy)<4)
   {
    if(sp_impact(enemy,ix,iy))
    {
     //sp_setDraw(enemy,FALSE);
     return TRUE;
    }
   }
  
  
  ix=itemx*40+20;
  iy=(itemy-1)*40+20;
  //判断是否炸到怪物
 
   if(sp_getAction(enemy)<4)
   {
    if(sp_impact(enemy,ix,iy))
    {
     //sp_setDraw(enemy,FALSE);
     return TRUE;
    }
   }
  
  
  ix=itemx*40+20;
  iy=(itemy+1)*40+20;
  //判断是否炸到怪物
  
   if(sp_getAction(enemy)<4)
   {
    if(sp_impact(enemy,ix,iy))
    {
     //sp_setDraw(enemy,FALSE);
     return TRUE;
    }
   }
  
  return 0;
}



//敌人移动事件
int en_run(int32 enemy)
{
 int x,y;
 int32 action=sp_getAction(enemy);
 //printf("开始移动%d \n",action);
 if(action==SP_UP)
 {
  
 sp_move(enemy, 0,-2);
x=sp_getx(enemy);
y=sp_gety(enemy); 
if(map_getData(map,x/40,y/40))
 {
  sp_move(enemy, 0,2);
  
 }
else if(map_getData(map,(x+39)/40,y/40) || y<0)
{
 sp_move(enemy, 0,2);
}
// printf("移动人物\n");
 //sp_run(enemy);
 
 }
 //////////
 else if(action==SP_DOWN)
 {
 sp_move(enemy, 0,2);
 //sp_run(enemy);
 x=sp_getx(enemy);
y=sp_gety(enemy);
 if(map_getData(map,x/40,(y+39)/40))
 {
  sp_move(enemy, 0,-2);
 }
else if(map_getData(map,(x+39)/40,(y+39)/40))
{
 sp_move(enemy, 0,-2);
}
 
 }
 //////////
 else if(action==SP_LEFT)
 {
 sp_move(enemy, -2,0);
 //sp_run(enemy);
 x=sp_getx(enemy);
y=sp_gety(enemy);
 if(map_getData(map,x/40,y/40))
 {
  sp_move(enemy, 2,0);
 }
else if(map_getData(map,x/40,(y+39)/40) || x<0)
{
 sp_move(enemy, 2,0);
}
 
 }
 /////////////////
 else if(action==SP_RIGHT)
 {
 sp_move(enemy, 2,0);
 //sp_run(enemy);
 x=sp_getx(enemy);
y=sp_gety(enemy);
 if(map_getData(map,(x+39)/40,y/40))
 {
  sp_move(enemy,-2,0);
 }
else if(map_getData(map,(x+39)/40,(y+39)/40))
{
 sp_move(enemy,-2,0);
}
 
 }
 

// char text[30];
// sprintf(text,"%d",action);
// dtext(text,0,0,240,240,240,0,1);
// ref(0,0,SCRW,SCRH);
 return 0;
}


