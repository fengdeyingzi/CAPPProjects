#ifndef _GAME_H_
#define _GAME_H_
#include <base.h>
#include <android.h>
#include <graphics.h>
#include <exb.h>

#include "map.h"
#include "aStar.h"
#include "role.h"
#include "wupin.h"

#define GAME_MAX_ENEMY 100

int _SCRW;
int _SCRH;

typedef struct _Game{
 int32 timerF;
 int32 t;
 int32 deltaT;
 
 Role enemy[GAME_MAX_ENEMY];
 int enemySum;
 Map map;
 AStar aStar;
 int start;
 int gameOver;
 int gameOverLt;
}Game;

// 全局Game
Game game_now;

// 按钮 0未按下 1按下
int button_map = 0;
int button_bag = 0;
int button_mr = 0;

// 0正常 1打开小地图 2打开背包 3打开个人信息
int screen = 0;

// 结束计时
int t_over = 10;
// 退出警告框句柄
int32 exit_dialog;

///// private ////////////

static int isPointInRect(int p, int q, int x, int y, int w, int h){
 return p >= x && q >= y && p < x + w && q < y + h;
}

static void gameDispose(){
 timerstop(game_now.timerF);
 timerdel(game_now.timerF);
}

void gameDrawMohu(){
 drawRect(0, 100, SCRW, SCRH-200, 0x88335577);
 ref(0, 0, SCRW, SCRH);
}

void gameDrawOver(){
 int w, h;
 char *big, *txt1, *txt2;
 if(game_now.gameOver == 1){
  big = "游戏过关！";
  txt1 = "恭喜你啊，但是并没有第二关。。。";
  txt2 = "贼卡是吗。。地图太大了，光地图就1200次绘图";
 }else{
  big = "你被杀了！结束了！";
  txt1 = "玩玩安卓手游《像素地牢》吧，挺好玩的。";
  txt2 = "↑ 再看一次上面的安利（滑稽）";
 }
 setTextSize(1, 60);
 textwh(big, 0, 1, &w, &h);
 dtext(big, (SCRW-w)/2, 300, 255, 255, 255, 0, 1);

 setTextSize(1, 30);
 textwh(txt1, 0, 1, &w, &h);
 dtext(txt1, (SCRW-w)/2, 400, 255, 255, 255, 0, 1);
 
 textwh(txt2, 0, 1, &w, &h);
 dtext(txt2, (SCRW-w)/2, 500, 255, 255, 255, 0, 1);

 if(t_over > 0){
  t_over --;
 }else{
  textwh("按返回键退出", 0, 1, &w, &h);
  dtext("按返回键退出", SCRW-w-30, 600, 255, 80, 30, 0, 1);
 }
}

static void gameGetCost(int cost, int *a, int *b){
 if(cost==0){
  *a = 0;
  *b = 0;
 }else{
  *a = 10/cost;
  *b = 100/cost - (*a) * 10;
 }
}

static void gameGetCostA(int cost, int *a, int *b){
 if(cost==10){
  *a = 0;
  *b = 0;
 }else{
  *a = 10/cost;
  *b = 100/cost - (*a) * 10;
  *a = *a - 1;
 }
}

// 个人情况
void gameDrawMR(){
 char txt[100];
 Role *r = &main_role;
 int a1, a2, a3;
 int b1, b2, b3;
 
 setTextSize(1, 35);
 dtext("生命值", 50, SCRH/4, 255, 255, 255, 0, 1);
 dtext("攻击力", 50, SCRH/4 + 100, 255, 255, 255, 0, 1);
 dtext("敏捷", 50, SCRH/4 + 150, 255, 255, 255, 0, 1);
 dtext("攻击速度", 50, SCRH/4 + 200, 255, 255, 255, 0, 1);
 dtext("格挡", 50, SCRH/4 + 250, 255, 255, 255, 0, 1);
 
 
 
 setTextSize(1, 30);
 sprintf(txt, "%d/%d  (基础%d+额外%d)", r->hpNow, r->hp, main_role_self_hp, r->hp - main_role_self_hp);
 dtext(txt, 300, SCRH/4, 230, 250, 230, 0, 1);
 sprintf(txt, "%d  (基础%d+额外%d)", r->atk, main_role_self_atk, r->atk - main_role_self_atk);
 dtext(txt, 300, SCRH/4 + 100, 250, 240, 240, 0, 1);
 
 gameGetCost(r->moveCost, &a1, &b1);
 gameGetCost(main_role_self_moveCost, &a2, &b2);
 gameGetCostA(10 - main_role_self_moveCost + r->moveCost, &a3, &b3);
 sprintf(txt, "%d.%d  (基础%d.%d+额外%d.%d)", a1, b1, a2, b2, a3, b3);
 dtext(txt, 300, SCRH/4 + 150, 220, 220, 220, 0, 1);
 
 gameGetCost(r->attackCost, &a1, &b1);
 gameGetCost(main_role_self_attackCost, &a2, &b2);
 gameGetCostA(10 - main_role_self_attackCost + r->attackCost, &a3, &b3);
 sprintf(txt, "%d.%d  (基础%d.%d+额外%d.%d)", a1, b1, a2, b2, a3, b3);
 dtext(txt, 300, SCRH/4 + 200, 240, 220, 240, 0, 1);
 
 sprintf(txt, "%d  (基础%d+额外%d 格挡%d%%伤害)", r->def, main_role_self_def, r->def - main_role_self_def, (r->def*1000)/(r->def*10 + 100));
 dtext(txt, 300, SCRH/4 + 250, 250, 250, 230, 0, 1);
 
}

// 画 控件、UI
void gameDrawUI(){
 char s[100];
 drawRect(0, 0, SCRW, 100, 0x88335577);
 drawRect(0, 0, 420, 60, 0xff335577);
 drawCir(420, 0, 60, 0xff335577);
 drawRect(0, 0, 100, 60, 0xff335577);
 drawRect(60, 9, 300, 13, 0xff112233);
 drawRect(60, 9, 30 + 270*main_role.hpNow/main_role.hp, 13, 0xff66aa99);
 drawRect(60, 39, 270, 13, 0xff112233);
 drawRect(60, 39, 30 + 240*main_role_wait/ROLE_PER_ROUND_WAIT, 13, 0xffbbbb99);
 drawCir(60, 60, 60, 0xff335577);
 drawCir(60, 60, 32, 0xff66ccff);
 setTextSize(1, 24);
 dtext("99", 10, 10, 160, 210, 250, 0, 1);
 sprintf(s, "%d/%d", main_role.hpNow, main_role.hp);
 dtext(s, 370, 0, 160, 210, 250, 0, 1);
 dtext("ACT", 360, 30, 160, 210, 250, 0, 1);
 
 setTextSize(1, 48);
 dtext(main_role.name, 34, 30, 0,0,0,0,1);
 
 // 按钮
 drawRect(0, SCRH-100, SCRW, 100, 0x88335577);
 drawRect(30, SCRH-120, 100, 100, 0xff335577);
 drawRect(160, SCRH-120, 100, 100, 0xff335577);
 drawRect(290, SCRH-120, 100, 100, 0xff335577);

 setTextSize(1, 60);
 dtext((screen==1||screen==2||screen==3)?"返":"图", 50, SCRH-110, 160, 210, 250, 0, 1);
 dtext((screen==1||screen==2||screen==3)?"返":"物", 180, SCRH-110, 160, 210, 250, 0, 1);
 dtext((screen==1||screen==2||screen==3)?"返":"况", 310, SCRH-110, 160, 210, 250, 0, 1);

 // 弹窗
 if(screen){
  if(screen == 1){
   mapDrawMini(&game_now.map, main_role.x, main_role.y);
  }else if(screen == 2){
   wupinDrawBag();
  }else if(screen == 3){
   gameDrawMR();
  }else if(screen == 10){
   gameDrawOver();
  }
 }
 
 // 游戏开始笼罩
 if(game_now.start < 255){ 
  effsetcon(0, 0, SCRW, SCRH, game_now.start, game_now.start, game_now.start);
  game_now.start += 25;
 }
}

// 显示游戏参数
static void gameShowSets(){
 char p[100];
 setTextSize(1, SCRW/30);
 sprintf(p, "SCR：%d*%d", SCRW, SCRH);
 dtext(p, 500, 0, 200, 230, 255, 0, 1);
 sprintf(p, "FPS：%d", 1000/(getuptime() - game_now.t));
 dtext(p, 500, 30, 200, 230, 255, 0, 1);
 game_now.t = getuptime();
}

// 判断游戏是否结束
static void gameOverHl(){
 if(game_now.gameOver == 0){
  if(enemy_die_sum >= game_now.enemySum){
   game_now.gameOver = 1;
   game_now.gameOverLt ++;
  }
  if(main_role.hpNow <= 0){
   game_now.gameOver = -1;
   game_now.gameOverLt ++;
  }
  if(game_now.gameOver != 0){
   screen = 10;
   gameDrawMohu();
  }
 }
}

static void gameRunTimer(int data){
 if(!screen){
  cls(140, 140, 140);
  mapDraw(&game_now.map);
  wupinDrawOnGround();
  wupinAct();
  roleAllAct(game_now.enemy, game_now.enemySum);
  roleAllDraw(game_now.enemy, game_now.enemySum, TILED_D);
  gameOverHl();
 }
 gameDrawUI();
 gameShowSets();
 ref(0, 0, SCRW, SCRH);
}

static int gameEventUI(int s, int p, int q){
 int have = 0;
 if(isPointInRect(p, q, 30, SCRH-120, 100, 100)){
  // 图
  if(s == MS_DOWN){
   button_map = 1;
   have = 1;
  }else if(s == MS_UP){
   screen = (screen?0:1);
   button_map = 0;
   have = 1;
   if(screen)gameDrawMohu();
  }else if(s == MS_MOVE){
   have = 1;
  }
 }else if(isPointInRect(p, q, 160, SCRH-120, 100, 100)){
  // 包
  if(s == MS_DOWN){
   button_bag = 1;
   have = 1;
  }else if(s == MS_UP){
   screen = (screen?0:2);
   button_bag = 0;
   have = 1;
   if(screen)gameDrawMohu();
  }else if(s == MS_MOVE){
   have = 1;
  }
 }else if(isPointInRect(p, q, 290, SCRH-120, 100, 100)){
  // 况
  if(s == MS_DOWN){
   button_mr = 1;
   have = 1;
  }else if(s == MS_UP){
   screen = (screen?0:3);
   button_mr = 0;
   have = 1;
   if(screen)gameDrawMohu();
  }else if(s == MS_MOVE){
   have = 1;
  }
 }else if(screen == 2){
  wupinEvent(s, p, q);
 }
 if(screen)have = 1;
 return have;
}

static void gameEventOver(int s, int p, int q){
 if(s == KY_DOWN)
 {
  switch(p)
  {
   case _SRIGHT:
    gameDispose();
    exit();
    break;
  }
 }
}

static void gameEventExit(int s, int p, int q){
 
 if(s == KY_DOWN && p == _SRIGHT){
  exit_dialog = 
      dlgcreate("\x90\x0\x51\xfa\x0\x0"
      , "\x90\x0\x51\xfa\x6e\x38\x62\xf\xff\x1f\x0\x0"
      , 1);
 } else if(s == MR_DIALOG)
 {
  dlgdel(exit_dialog);
  switch(p)
  {
   case 0:
    gameDispose();
    exit();
    break;
   case 1:
    break;
  }
 }
}

static void gameEventMapMove(int s, int p, int q){
 static int x=0,y=0,dot=1, dz;
 if(s == MS_DOWN){
  x = p;
  y = q;
  dot = 1;
  dz = 0; // 防振
 }
 if(s == MS_MOVE){
  if((dz != 0) || ((x>p?x-p:p-x) + (y>q?y-q:q-y) > TILED_D/2)){
   dot = 0;
   dz = 1;
   game_now.map.x += p - x;
   game_now.map.y += q - y;
   x = p;
   y = q;
  }
 }
 if(s == MS_UP){
  if(dot){
   int xt = (p - game_now.map.x)/TILED_D;
   int yt = (q - game_now.map.y)/TILED_D;
   roleMainDo(game_now.enemy, game_now.enemySum,xt, yt);
  }
 }
}

////////////////////////


void gameInit(){
 getscrsize(&_SCRW, &_SCRH);
 setscrsize(720, 720 * SCRH / SCRW);
 game_now.start = 0;
 game_now.gameOver = 0;
 game_now.gameOverLt = 0;
 game_now.t = 0;
 game_now.deltaT = 1;
 game_now.timerF = timercreate();
 
 // 初始化物品
 wupinInitAll();
 
 // 初始化背包
 wupinInit();
 
 int isError;
 do{
  isError = 0;
  // 初始化地图
  mapInit(&game_now.map);
  // 初始化寻路
  aStarInit(&game_now.aStar,&game_now.map,MAP_WIDTH,MAP_HEIGHT);
  // 创建主角
  Room *r = mapGetRoom(&game_now.map, 0, 0);
  if(r != NULL){//  敏捷 攻速 生命 攻击 格挡
   roleMainInit(r->x + 1, r->y + 1, 10, 10, 15, 4, 0, "我");
  }else{
   toast("重新创建主房间",0);
   isError = 1;
  }
  int level, sum;
 
  // 随机创建敌人
  mapMakeDraw("产生并放置不同强度的敌人");
 
  level = 1;
  sum = mapGetRoomSum(&(game_now.map),level);
  roleMakeRand(game_now.enemy, &(game_now.enemySum), level, sum, 12, 10, 8, 2, 0, "兵");
  
  level = 2;
  sum = mapGetRoomSum(&(game_now.map),level);
  roleMakeRand(game_now.enemy, &(game_now.enemySum), level, sum, 10, 9, 10, 3, 1, "者");
  
  level = 3;
  sum = mapGetRoomSum(&(game_now.map),level)/2;
  roleMakeRand(game_now.enemy, &(game_now.enemySum), level, sum, 8, 4, 20, 5, -4, "斗");
  
  level = 5;
  do{
   sum = mapGetRoomSum(&(game_now.map),level);
   if(sum <= 0){
    level --;
   }
  }while(sum <= 0);
  if(level <= 0){
   isError = 1;
  }else{
   roleMakeRand(game_now.enemy, &(game_now.enemySum), level, 1, 10, 9, 35, 10, 5, "圣");
  }
  
  //随机放入物品
  Wupin *w;
  mapMakeDraw("播撒药水、符纸、武器");
  level = -1;
  sum = game_now.enemySum;
  wupinGroundRand(level, sum, &wupin_med_icec);
  
  level = -1;
  sum = 1;
  wupinGroundRand(level, sum, &wupin_med_hp);
  wupinGroundRand(level, sum, &wupin_equip_fuspeed);
 
  level = 1;
  sum = 2;
  wupinGroundRand(level, sum, &wupin_equip_swordwooden);
 
  level = 2;
  sum = 1;
  do{
   sum = mapGetRoomSum(&(game_now.map),level);
   if(sum <= 0){
    level ++;
   }
  }while(sum <= 0 && level <= 5);
  wupinGroundRand(level, sum, &wupin_equip_dfwooden);
  
  level = 4;
  do{
   sum = mapGetRoomSum(&(game_now.map),level);
   if(sum <= 0){
    level --;
   }
  }while(sum <= 0);
  if(level <= 0){
   isError = 1;
  }else{
   if(rand()%6){
    wupinGroundRand(level, sum, &wupin_equip_chiiron);
   }else{
    wupinGroundRand(level, sum, &wupin_equip_swordfly);
   }
  }
  
 }while(isError);
 
 // 定位主角
 game_now.map.x -= main_role.x * TILED_D - SCRW/2;
 game_now.map.y -= main_role.y * TILED_D - SCRH/2;

}


void gameStart(int deltaT){
 game_now.deltaT = deltaT;
#ifdef TCC
 timerstart(game_now.timerF, deltaT, deltaT, gameRunTimer, 1);
#else
 timerstart(game_now.timerF, deltaT, deltaT, "gameRunTimer", 1);
#endif
}

void gameEvent(int s, int p, int q){
 if(game_now.gameOver == 0){
  if(!gameEventUI(s, p, q)){
   gameEventMapMove(s, p, q);
  }
  gameEventExit(s, p, q);
 }else{
  gameEventOver(s, p, q);
 }
}

/////
#endif