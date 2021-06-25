#ifndef A_STAR_H_
#define A_STAR_H_
/*
A*寻路（可能是假的） for SDungeon
@author 火烧云
@time 2017 2月9日
*/

#include <base.h>
#include <graphics.h>
#include <android.h>
#include "map.h"

#define A_STAR_ON_DRAWno
#define A_STAR_DRAW_TILED_D 32
#define A_STAR_DRAW_SLEEP 100

typedef struct _AStarPoint{
 int x;
 int y;
 int goG; // 要去地方的得分
 int toG; // 到目标点的得分
}AStarPoint;

typedef struct _AStar{
 Map *map;
 int mapW;
 int mapH;
 int toGoSum;
 int recordSum;
 int back1Sum;
 int back2Sum;
 int nextX;
 int nextY;
 AStarPoint toGo[8];
 AStarPoint record[100];
 AStarPoint back1[100];
 AStarPoint back2[100];
}AStar;

static void aStarDrawMap(AStar *as){
 int d = A_STAR_DRAW_TILED_D;
 int yi, xi;
 cls(0,0,0);
 for(yi = 0; yi < as->mapH; yi ++){
  for(xi = 0; xi < as->mapW; xi ++){
   if(!mapIsWall(as->map,xi,yi)){
    drawRect(xi*d,yi*d,d-1,d-1,0xff666666);
   }else{
    drawRect(xi*d,yi*d,d-1,d-1,0xffeeeeee);
   }
  }
 }
}

static void aStarDrawRef(){
 ref(0,0,SCRW,SCRH);
 sleep(A_STAR_DRAW_SLEEP);
}

static void aStarDrawOld(int nowX, int nowY, int toX, int toY){
 int d = A_STAR_DRAW_TILED_D;
 drawRect(nowX*d,nowY*d,d-1,d-1,0xffeeaa99);
 drawRect(toX*d,toY*d,d-1,d-1,0xffaa99ff);
}

static void aStarDrawNewStart(int x, int y){
 int d = A_STAR_DRAW_TILED_D;
 drawRect(x*d,y*d,d-1,d-1,0x55eeaa99);
}

static void aStarDrawNewEnd(int x, int y){
 int d = A_STAR_DRAW_TILED_D;
 drawRect(x*d,y*d,d-1,d-1,0x55aa99ff);
}

int aStarCanGo(AStar *as, struct _AStarPoint* asps, int sum, struct _AStarPoint* aspsBack, int sumBack, int x, int y){
 int ok = 0;
 if(x >= 0 && y >= 0 && x < as->mapW && y < as->mapH){
  if(!mapIsWall(as->map,x,y)){
   int k = 1, i;
   if(aspsBack == NULL){
    // 出发
    for(i = 0; k && i < sum; i ++){
     if((asps[i].x == x)*(asps[i].y == y)){
      k = 0;
     }
    }
   }else{
    // 返回
    for(i = 0; k && i < sum; i ++){
     if((asps[i].x == x)*(asps[i].y == y)){
      k = 0;
     }
    }
    k = !k;
    for(i = 0; k && i < sumBack; i ++){
     if((aspsBack[i].x == x)*(aspsBack[i].y == y)){
      k = 0;
     }
    }
   }
   if(k)ok=1;
  }
 }
 return ok;
}

static int aStarDist(int x, int y, int xt, int yt){
 return 100*((x-xt>0?x-xt:xt-x) + (y-yt>0?y-yt:yt-y));
}

// 取得出发的所有可能
static int aStarGetGo(AStar *as, struct _AStarPoint* asps, int sum, struct _AStarPoint* aspsBack, int sumBack, int x, int y, int xto, int yto){
 int ftg = 141;
 as->toGoSum = 0;
 if(aStarCanGo(as, asps, sum, aspsBack, sumBack, x-1, y-1)){//1
  as->toGo[as->toGoSum].x = x-1;
  as->toGo[as->toGoSum].y = y-1;
  as->toGo[as->toGoSum].goG = ftg;
  as->toGo[as->toGoSum].toG = aStarDist(x-1,y-1,xto,yto);
  as->toGoSum ++;
 }
 if(aStarCanGo(as, asps, sum, aspsBack, sumBack, x, y-1)){//2
  as->toGo[as->toGoSum].x = x;
  as->toGo[as->toGoSum].y = y-1;
  as->toGo[as->toGoSum].goG = 100;
  as->toGo[as->toGoSum].toG = aStarDist(x,y-1,xto,yto);
  as->toGoSum ++;
 }
 if(aStarCanGo(as, asps, sum, aspsBack, sumBack, x+1, y-1)){//3
  as->toGo[as->toGoSum].x = x+1;
  as->toGo[as->toGoSum].y = y-1;
  as->toGo[as->toGoSum].goG = ftg;
  as->toGo[as->toGoSum].toG = aStarDist(x+1,y-1,xto,yto);
  as->toGoSum ++;
 }
 if(aStarCanGo(as, asps, sum, aspsBack, sumBack, x-1, y)){//4
  as->toGo[as->toGoSum].x = x-1;
  as->toGo[as->toGoSum].y = y;
  as->toGo[as->toGoSum].goG = 100;
  as->toGo[as->toGoSum].toG = aStarDist(x-1,y,xto,yto);
  as->toGoSum ++;
 }
 if(aStarCanGo(as, asps, sum, aspsBack, sumBack, x+1, y)){//6
  as->toGo[as->toGoSum].x = x+1;
  as->toGo[as->toGoSum].y = y;
  as->toGo[as->toGoSum].goG = 100;
  as->toGo[as->toGoSum].toG = aStarDist(x+1,y,xto,yto);
  as->toGoSum ++;
 }
 if(aStarCanGo(as, asps, sum, aspsBack, sumBack, x-1, y+1)){//7
  as->toGo[as->toGoSum].x = x-1;
  as->toGo[as->toGoSum].y = y+1;
  as->toGo[as->toGoSum].goG = ftg;
  as->toGo[as->toGoSum].toG = aStarDist(x-1,y+1,xto,yto);
  as->toGoSum ++;
 }
 if(aStarCanGo(as, asps, sum, aspsBack, sumBack, x, y+1)){//8
  as->toGo[as->toGoSum].x = x;
  as->toGo[as->toGoSum].y = y+1;
  as->toGo[as->toGoSum].goG = 100;
  as->toGo[as->toGoSum].toG = aStarDist(x,y+1,xto,yto);
  as->toGoSum ++;
 }
 if(aStarCanGo(as, asps, sum, aspsBack, sumBack, x+1, y+1)){//9
  as->toGo[as->toGoSum].x = x+1;
  as->toGo[as->toGoSum].y = y+1;
  as->toGo[as->toGoSum].goG = ftg;
  as->toGo[as->toGoSum].toG = aStarDist(x+1,y+1,xto,yto);
  as->toGoSum ++;
 }
 return as->toGoSum;
}

// 找出评分最低的，也就是最优秀的
static struct _AStarPoint aStarFindBest(AStar *as){
 int g = -1;
 int which = -1;
 for(int i = as->toGoSum - 1; i >= 0; i --){
  //printf("   search(%d,%d) togo=%d\n", as->toGo[i].x, as->toGo[i].y, as->toGo[i].toG+as->toGo[i].goG);
  if((g == -1) + (as->toGo[i].goG + as->toGo[i].toG < g)){
   g = as->toGo[i].goG + as->toGo[i].toG;
   which = i;
  }
 }
 //printf("best(%d,%d) %d/%d\n", as->toGo[which].x, as->toGo[which].y, which, as->toGoSum);
 return as->toGo[which];
}


int aStarToPoint(AStar *as, int nowX, int nowY, int toX, int toY){
 if(nowX == toX && nowY == toY){
  return 0;
 }
 int jk, find1=1,find2=1, s1=0, s2=0;
 int x, y;
 int maxjk = as->mapW*as->mapH; //极限查找步数
 /////// 从起点到终点 //////
 as->recordSum = 1;
 as->record[0].x = nowX;
 as->record[0].y = nowY;
 as->record[0].goG = 0;
 as->record[0].toG = 0;
 jk = maxjk;
 x = nowX;
 y = nowY;
 #ifdef A_STAR_ON_DRAW;
 aStarDrawMap(as);
 aStarDrawOld(nowX,nowY,toX,toY);
 aStarDrawRef();
 #endif;
 while(find1 && (--jk)>=0){
  if(!aStarGetGo(as, as->record, as->recordSum, NULL, 0, x, y, toX, toY)){
   find1 = 0;
  }else{
   as->record[as->recordSum] = aStarFindBest(as);
   x = as->record[as->recordSum].x;
   y = as->record[as->recordSum].y;
   as->recordSum ++;
   #ifdef A_STAR_ON_DRAW;
   aStarDrawNewStart(x,y);
   aStarDrawRef();
   #endif;
   // 到达
   if(x == toX && y == toY){
    break;
   }
  }
 }
 ////// 返回 //////
 as->back1Sum = 1;
 as->back1[0].x = toX;
 as->back1[0].y = toY;
 as->back1[0].goG = 0;
 as->back1[0].toG = 0;
 jk = maxjk;
 x = toX;
 y = toY;
 #ifdef A_STAR_ON_DRAW;
 aStarDrawOld(nowX,nowY,toX,toY);
 aStarDrawRef();
 #endif;
 while(find1 && (--jk)>=0){
  if(!aStarGetGo(as, as->record, as->recordSum, as->back1, as->back1Sum, x, y, nowX, nowY)){
   find1 = 0;
  }else{
   s1++;
   as->back1[as->back1Sum] = aStarFindBest(as);
   x = as->back1[as->back1Sum].x;
   y = as->back1[as->back1Sum].y;
   as->back1Sum ++;
   #ifdef A_STAR_ON_DRAW;
   aStarDrawNewEnd(x,y);
   aStarDrawRef();
   #endif;
   // 到达
   if(x == nowX && y == nowY){
    break;
   }
  }
 }
 
  /////// 从终点到起点 //////
 as->recordSum = 1;
 as->record[0].x = toX;
 as->record[0].y = toY;
 as->record[0].goG = 0;
 as->record[0].toG = 0;
 jk = maxjk;
 x = toX;
 y = toY;
 #ifdef A_STAR_ON_DRAW;
 aStarDrawMap(as);
 aStarDrawOld(nowX,nowY,toX,toY);
 aStarDrawRef();
 #endif;
 while(find2 && (--jk)>=0){
  if(!aStarGetGo(as, as->record, as->recordSum, NULL, 0, x, y, nowX, nowY)){
   find2 = 0;
  }else{
   as->record[as->recordSum] = aStarFindBest(as);
   x = as->record[as->recordSum].x;
   y = as->record[as->recordSum].y;
   as->recordSum ++;
   #ifdef A_STAR_ON_DRAW;
   aStarDrawNewEnd(x,y);
   aStarDrawRef();
   #endif;
   // 到达
   if(x == nowX && y == nowY){
    break;
   }
  }
 }
 
 ////// 返回 //////
 as->back2Sum = 1;
 as->back2[0].x = nowX;
 as->back2[0].y = nowY;
 as->back2[0].goG = 0;
 as->back2[0].toG = 0;
 jk = maxjk;
 x = nowX;
 y = nowY;
 #ifdef A_STAR_ON_DRAW;
 aStarDrawOld(nowX,nowY,toX,toY);
 aStarDrawRef();
 #endif;
 while(find2 && (--jk)>=0){
  s2++;
  if(!aStarGetGo(as, as->record, as->recordSum, as->back2, as->back2Sum, x, y, toX, toY)){
   find2 = 0;
  }else{
   as->back2[as->back2Sum] = aStarFindBest(as);
   x = as->back2[as->back2Sum].x;
   y = as->back2[as->back2Sum].y;
   as->back2Sum ++;
   #ifdef A_STAR_ON_DRAW;
   aStarDrawNewStart(x,y);
   aStarDrawRef();
   #endif;
   // 到达
   if(x == toX && y == toY){
    break;
   }
  }
 }
 
 int ok = 1;
 int s = 0;
 if(!find1 && !find2){
  ok = 0;
 }else if(find1 && !find2){
  as->nextX = as->back1[as->back1Sum-2].x;
  as->nextY = as->back1[as->back1Sum-2].y;
  s = s1;
 }else if(!find1 && find2){
  as->nextX = as->back2[1].x;
  as->nextY = as->back2[1].y;
  s = s2;
 }else{
  if(s1<s2){
   as->nextX = as->back1[as->back1Sum-2].x;
   as->nextY = as->back1[as->back1Sum-2].y;
   s = s1;
  }else{
   as->nextX = as->back2[1].x;
   as->nextY = as->back2[1].y;
   s = s2;
  }
 }
 /*for(int hh = 0; hh < as->back2Sum; hh ++){
  printf("   [%d] (%d,%d)\n", hh, as->back2[hh].x, as->back2[hh].y);
 }
 printf("find(%d.%d/%d),site(%d,%d)\n", find1, find2, as->back2Sum, as->nextX,as->nextY );
 */
 
 #ifdef A_STAR_ON_DRAW;
 char w[100];
 if(ok){
  sprintf(w, "最短是[%d]步！按返回键退出", s);
 }else{
  sprintf(w, "未找到");
 }
 toast(w,1);
 #endif;
 
 if(!ok){
  printf("   AStar未找到\n");
 }
 
 return ok;
}


void aStarInit(AStar *as, Map *map, int mapW, int mapH){
 as->map = map;
 as->mapW = mapW;
 as->mapH = mapH;
}

#endif