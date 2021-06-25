#ifndef _MAP_H_
#define _MAP_H_

#include <base.h>
#include <exb.h>
#include <graphics.h>
// 极限房间数目
#define ROOM_SUM 20
// 地图横向图块数目
#define MAP_WIDTH 30
// 地图纵向图块数目
#define MAP_HEIGHT 40
// 图块大小
#define TILED_D 64
// 图块种类
#define TILED_SPACE 0
#define TILED_WALL 1
#define TILED_WALL2 2
#define TILED_DOOR 3

typedef struct _Room{
 int x;
 int y;
 int w;
 int h;
 int t;
}Room;

typedef struct _Map{
 int id;
 int mini;
 int roomSum;
 int x;
 int y;
 uint8 data[MAP_HEIGHT][MAP_WIDTH];
 struct _Room rooms[ROOM_SUM];
}Map;


// 是否为墙壁
static int mapIsWall(Map *m, int x, int y){
 return (m->data[y][x] == TILED_WALL) + (m->data[y][x] == TILED_WALL2);
}
static int mapIsWall0(Map *m, int x, int y){
 return m->data[y][x] == TILED_WALL;
}

// 该地方在地图范围内
static int mapIsInMap(int x, int y){
 return x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT;
}

// 周围能通过的数目
static int mapCanSpace(Map *m, int x, int y, int isLt){
 int i = 0;
 if(mapIsInMap(x-1,y)){
  if(m->data[y][x-1] == TILED_SPACE) i ++;
 }
 if(mapIsInMap(x+1,y)){
  if(m->data[y][x+1] == TILED_SPACE) i ++;
 }
 if(mapIsInMap(x,y-1)){
  if(m->data[y-1][x] == TILED_SPACE) i ++;
 }
 if(mapIsInMap(x,y+1)){
  if(m->data[y+1][x] == TILED_SPACE) i ++;
 }
 if(isLt){
 // 1379
 if(mapIsInMap(x-1,y-1)){
  if(m->data[y-1][x-1] == TILED_SPACE) i ++;
 }
 if(mapIsInMap(x+1,y-1)){
  if(m->data[y-1][x+1] == TILED_SPACE) i ++;
 }
 if(mapIsInMap(x-1,y+1)){
  if(m->data[y+1][x-1] == TILED_SPACE) i ++;
 }
 if(mapIsInMap(x+1,y+1)){
  if(m->data[y+1][x+1] == TILED_SPACE) i ++;
 }
 }
 return i;
}

// 将产生的房间写入地图
static void mapMakeRoom(Map *m, Room *r){
 int k,v;
 for(k = r->y; k < r->y + r->h; k ++){
  for(v = r->x; v < r->x + r->w; v ++){
   if(k != r->y && k != r->y + r->h - 1 && v != r->x && v!= r->x + r->w - 1){
    m->data[k][v] = TILED_SPACE;
   }else{
    m->data[k][v] = TILED_WALL2;
   }
  }
 }
}

// 随机产生门
static void roomRandDoor(Map *m, Room *r, int *x, int *y, int *direction){
 for(int i = 0; i < 100; i ++){
  int ok = 1;
  *direction = (rand()%4+1)*2;
  switch(*direction){
  case 2:
   *x = r->x + 1 + rand()%(r->w - 2);
   *y = r->y;
   if(!mapIsWall(m,*x+1,*y) || !mapIsWall(m,*x-1,*y)) ok = 0;
   break;
  case 4:
   *x = r->x;
   *y = r->y + 1 + rand()%(r->h - 2);
   if(!mapIsWall(m,*x,*y+1) || !mapIsWall(m,*x,*y-1)) ok = 0;
   break;
  case 6:
   *x = r->x + r->w - 1;
   *y = r->y + 1 + rand()%(r->h - 2);
   if(!mapIsWall(m,*x,*y+1) || !mapIsWall(m,*x,*y-1)) ok = 0;
   break;
  case 8:
   *x = r->x + 1 + rand()%(r->w - 2);
   *y = r->y + r->h - 1;
   if(!mapIsWall(m,*x+1,*y) || !mapIsWall(m,*x-1,*y)) ok = 0;
   break;
  }
  if(*x == 0 || *y == 0 || *x == MAP_WIDTH-1 || *y == MAP_HEIGHT-1){
   ok = 0;
  }
  if(m->data[*y][*x] != TILED_WALL2) ok = 0;
  if(ok) break;
 }
}

// 随机挖路
static int mapDigRoad(Map*m, int *x, int *y, int *direction){
 int ok;
 for(int i = 0; i < 6; i ++){
  ok = 1;
  int xt = *x, yt = *y;
  if(!(rand()%5)){
   switch(*direction){
   case 2:
    *direction = rand()%2?4:6;
    break;
   case 4:
    *direction = rand()%2?2:8;
    break;
   case 6:
    *direction = rand()%2?2:8;
    break;
   case 8:
    *direction = rand()%2?4:6;
    break;
   }
  }
  
  switch(*direction){
  case 2:
   yt = yt - 1;
   if(!mapIsWall(m,xt+1,yt) || !mapIsWall(m,xt-1,yt)) ok = 0;
   break;
  case 4:
   xt = xt - 1;
   if(!mapIsWall(m,xt,yt+1) || !mapIsWall(m,xt,yt-1)) ok = 0;
   break;
  case 6:
   xt = xt + 1;
   if(!mapIsWall(m,xt,yt+1) || !mapIsWall(m,xt,yt-1)) ok = 0;
   break;
  case 8:
   yt = yt + 1;
   if(!mapIsWall(m,xt+1,yt) || !mapIsWall(m,xt-1,yt)) ok = 0;
   break;
  }
  if(xt == 0 || yt == 0 || xt == MAP_WIDTH-1 || yt == MAP_HEIGHT-1){
   ok = 0;
  }
  if(m->data[yt][xt] != TILED_WALL) ok = 0;
  if(ok){
   *x = xt;
   *y = yt;
   break;
  }
 }
 return ok;
}

// 挖房
static int mapDigRoom(Map*m, Room *rn, int x, int y){
 int ok;
 for(int i = 0; i < 10; i ++){
  ok = 1;
  int xt, yt, dk;
  int k,v;
  dk = rand()%4;
  switch(dk){
  case 0:// 左
   xt = x;
   yt = y - (1 + rand()%(rn->h - 2));
   break;
  case 1:// 右
   xt = x - (rn->w - 1);
   yt = y - (1 + rand()%(rn->h - 2));
   break;
  case 2:// 上
   xt = x - (1 + rand()%(rn->w - 2));
   yt = y;
   break;
  case 3:// 下
   xt = x - (1 + rand()%(rn->w - 2));
   yt = y - (rn->h - 1);
   break;
  }
  if(xt < 0 || yt < 0 || xt + rn->w >= MAP_WIDTH || yt + rn->h  >= MAP_HEIGHT){
   ok = 0;
  }
  for(k = yt; ok * (k < yt + rn->h); k ++){
   for(v = xt; ok * (v < xt + rn->w); v ++){
    if(!(k==y && v==x)){
     if(!mapIsWall(m,v,k)){
      ok = 0;
     }
    }
   }
  }
  if(ok){
   rn->x = xt;
   rn->y = yt;
   break;
  }
 }
 return ok;
}

/* 通过已知room产生下一级room
 @parm r 源Room地址
       r 新Room地址*/
static int mapMakeMoreRoom(Map *m, Room *r, Room *rn){
 int x,y,direction;
 int w, h;
 int ok = 0;
 // 起点
 roomRandDoor(m,r,&x,&y,&direction);
 m->data[y][x] = TILED_DOOR;
 // 修路或建房
 int xt = x, yt = y;
 int roi = 0;
 for(int i = 0; i < 100; i ++){
  
  int isMakeRoad = rand()%9; // >=1修路 0修房
  // 去除门对门
  if(isMakeRoad)roi ++;
  if((roi == 1) * (!isMakeRoad))continue;
  // 随机修路或者修房
  if(isMakeRoad){
   if(mapDigRoad(m,&xt,&yt,&direction)){
    m->data[yt][xt] = TILED_SPACE;
   }
  }else{
   if(mapDigRoom(m,rn,xt,yt)){
    mapMakeRoom(m,rn);
    rn->t = r->t + 1;
    m->data[yt][xt] = TILED_DOOR;
    ok = 1;
    break;
   }
  }
 }
 return ok;
}

static struct _Room * mapFindRawRoom(Map *m){
 Room *r = NULL;
 for(int i = 0; i < m->roomSum; i ++){
  if(m->rooms[i].t == -1){
   r = &(m->rooms[i]);
   break;
  }
 }
 return r;
}

int mapGetRoomSum(Map *m, int level){
 int i, ki = 0;
 for(i = 0; i < m->roomSum; i ++){
  if(m->rooms[i].t == -1)continue;
  if((m->rooms[i].t == level) + (level == -1)){
   ki ++;
  }
 }
 return ki;
}


struct _Room* mapFindRoomRand(Map *m, int level){
 // (时间换了空间，这里是划不来的……)
 Room *r = NULL;
 int i, kii = 0;
 int ki = mapGetRoomSum(m, level);
 ki = rand()%ki;
 for(i = 0; i < m->roomSum; i ++){
  if(m->rooms[i].t == -1)continue;
  if((m->rooms[i].t == level) + (level == -1)){
   if(kii < ki){
    kii ++;
   }else{
    r = &(m->rooms[i]);
    break;
   }
  }
 }
 return r;
}
// 递归修建房间 n最高级支路数目
static void mapMakeMoreRooms(Map *m, Room *r, int n){
 int success = 0;
 int sum = n - r->t + rand()%2-1;
 Room *rn;
 if(r->t > n) return;
 for(int i = 0; i < sum; i ++){
  //修建指定数目的下级房间
  rn = mapFindRawRoom(m);
  if(rn == NULL){
   // 房间用尽
  }else{
   if(mapMakeMoreRoom(m,r,rn)){
    mapMakeMoreRooms(m, rn, n);
    success ++;
   }
  }
 }
 printf("○ 制造%d级房间%d个\n", r->t + 1, success);
}

static void mapMakeDraw(char *s){
 char *c;
 int w, h;
 static int cs = rand()%9;
 switch(cs){
  case 0:
   c = "提示：“一夫当关万夫莫开”，门口是个好地方";
   break;
  case 1:
   c = "提示：创始者给予了“圣”最高能力";
   break;
  case 2:
   c = "提示：越深的房间越不详";
   break;
  case 3:
   c = "提示：谁能零装备打赢“那什男爵”？";
   break;
  case 4:
   c = "作者：假如我的代码也帮到了你，我也开心";
   break;
  case 5:
   c = "作者：做游戏最重要就是坚持、专心";
   break;
  case 6:
   c = "提示：闯入S地牢的资本就是恢复药水和格挡！";
  break;
  case 7:
   c = "提示：敌军还有两秒到达战场（不对……）";
   break;
  case 8:
   c = "作者：本作者还有其他作品（嘿）";
   break;
  case 9:
   c = "作者：我爱Java但Java不爱我（捂额状）";
   break;
 }
 cls(0, 0, 0);
 setTextSize(1, 80);
 textwh("S地牢", 0, 1, &w,&h);
 dtext("S地牢", (SCRW - w)/ 2 - 3, SCRH/5 - 30 - 3, 150, 150, 150, 0, 1);
 dtext("S地牢", (SCRW - w)/ 2, SCRH/5 - 30, 200, 200, 200, 0, 1);
 setTextSize(1, 30);
 textwh(c, 0, 1, &w,&h);
 dtext(c, (SCRW - w)/ 2, SCRH/3 - 30, 230, 0, 70, 0, 1);
 textwh(s, 0, 1, &w,&h);
 dtext(s, (SCRW - w)/ 2, SCRH/3 + 20, 230, 230, 230, 0, 1);
 ref(0, 0, SCRW, SCRH);
 sleep(300);
}

void mapMake(Map *m){
 int i, j, w, h;
 
 mapMakeDraw("产生房间");
 m->roomSum = 8 + rand()%4;
 for(i = 0; i < m->roomSum; i ++){
  m->rooms[i].w = 4 + rand()%4;
  m->rooms[i].h = 4 + rand()%4;
  m->rooms[i].t = -1;
 }
 
 mapMakeDraw("修路并递归建造房室");
 m->rooms[0].x = MAP_WIDTH/4 + rand()%(MAP_WIDTH*3/4 - m->rooms[0].w);
 m->rooms[0].y = MAP_HEIGHT/4 + rand()%(MAP_HEIGHT*3/4 - m->rooms[0].h);
 m->rooms[0].t = 0;
 mapMakeRoom(m, &(m->rooms[0]));
 mapMakeMoreRooms(m, &(m->rooms[0]), 4);
 
 mapMakeDraw("优化门、墙壁");
 for(i = 0; i < MAP_HEIGHT; i ++){
  for(j = 0; j < MAP_WIDTH; j++){
   if(m->data[i][j] == TILED_DOOR){
    if(mapCanSpace(m,j,i,0) < 2){
     m->data[i][j] = TILED_WALL2;
    }
   }else if(m->data[i][j] == TILED_WALL){
    if(mapCanSpace(m,j,i,1) > 0){
     m->data[i][j] = TILED_WALL2;
    }
   }
  }
 }
 
 printf("○ 地图生成完成\n");
}

// 获得房间
struct _Room* mapGetRoom(Map *m, int level, int is){
 Room *r = NULL;
 for(int i = is; i < m->roomSum; i ++){
  if(m->rooms[i].t == level){
   r = &(m->rooms[i]);
   break;
  }
 }
 if(r == NULL){
  printf("not f\n");
 }
 return r;
}

/////////////////////////////////

void mapInit(Map *m){
 printf("○ 初始化地图%dx%d, 图块边长=%d\n", MAP_WIDTH, MAP_HEIGHT, TILED_D);
 int i, j;
 for(i = 0; i < MAP_HEIGHT; i ++){
  for(j = 0; j < MAP_WIDTH; j++){
   m->data[i][j] = TILED_WALL;
  }
 }
 for(i = 0; i < ROOM_SUM; i ++){
  m->rooms[i].t = -1;
  m->rooms[i].x = 0;
  m->rooms[i].y = 0;
  m->rooms[i].w = 0;
  m->rooms[i].h = 0;
 }
 m->id = 0;
 m->mini = 0;
 m->roomSum = 0;
 m->x = 0;
 m->y = 0;
 mapMake(m);
}


/*
★该函数为主要的耗时
★现已尽可能优化

  其中，在我手机（1.5GHz,2G内存,红米2a）
  测试地图30*40数据：
    总共 平均90ms
    双层for 7ms
    x, y 赋值 15ms
    超出地图判断 +16ms
    switch&绘图 45到50ms
    
  下面是去掉地图超越屏幕判断的：
    总共 平均80ms
    双层for 7ms
    x, y 赋值 15ms
    switch&绘图 58ms
    
*/
void mapDraw(Map *m){
 static int d = TILED_D;
 static int mw = MAP_WIDTH;
 static int mh = MAP_HEIGHT;
 //static int mwl = MAP_WIDTH*TILED_D;
 //static int mhl = MAP_HEIGHT*TILED_D;
 static int t1, t2 = 0, ts = 0;
 int8 i, j;
 int x, y;
 int dx = m->x;
 int dy = m->y;
 
 t1 = getuptime();
 for(i = 0; i < mh; i ++){
  for(j = 0; j < mw; j ++){
   x = dx + (j<<6);
   y = dy + (i<<6);
   /*
   if(x < -d || y < -d || x > mwl -d || y > mhl -d){
    continue;
   }*/
   switch(m->data[i][j]){
    case 0:
     drect(x, y, d-1, d-1, 160,160,160);
     break;
    case 1:
     drect(x, y, d, d, 210,210,210);
     break;
    case 2:
     drect(x, y, d, d, 230,230,230);
     break;
    case 3:
     drect(x, y, d, d, 100,60,30);
     break;
   }
  }
 }
 
 t2 += getuptime() - t1;
 ts ++;
 
 //printf("  ----绘图函数平均耗时--%d\n", t2/ts);
}

void mapDrawMini(Map *m, int rx, int ry){
 static int mw = MAP_WIDTH;
 static int mh = MAP_HEIGHT;
 static int d = SCRH /2 / MAP_HEIGHT;
 static int dx = (SCRW - mw*d)/2;
 static int dy = SCRH /4;
 int i, j;
 for(i = 0; i < mh; i ++){
  for(j = 0; j < mw; j++){
   int x = j*d + dx;
   int y = i*d + dy;
   switch(m->data[i][j]){
     case 0:
      drect(x,y,d,d,160,160,160);
      break;
     case 1:
      drect(x,y,d,d,210,210,210);
      break;
     case 2:
      drect(x,y,d,d,230,230,230);
      break;
     case 3:
      drect(x,y,d,d,100,60,30);
      break;
     /*case 4:
      drect(x,y,d,d,100,60,230);
      break;*/
   }
  }
 }
 int r = (m->mini/2 - 10)*(m->mini/2 - 10);
 drawRect(rx*d+dx,ry*d+dy,d,d,0xff66ccff);
 drawCir(rx*d+d/2+dx,ry*d+d/2+dy,r,0x5566ccff & 0x0066ccff | (110-r)<<24);
 m->mini ++;
 if(m->mini < 40){
  m->mini ++;
 }else{
  m->mini = 0;
 }
}



#endif