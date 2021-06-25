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

// ȫ��Game
Game game_now;

// ��ť 0δ���� 1����
int button_map = 0;
int button_bag = 0;
int button_mr = 0;

// 0���� 1��С��ͼ 2�򿪱��� 3�򿪸�����Ϣ
int screen = 0;

// ������ʱ
int t_over = 10;
// �˳��������
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
  big = "��Ϸ���أ�";
  txt1 = "��ϲ�㰡�����ǲ�û�еڶ��ء�����";
  txt2 = "�������𡣡���ͼ̫���ˣ����ͼ��1200�λ�ͼ";
 }else{
  big = "�㱻ɱ�ˣ������ˣ�";
  txt1 = "���氲׿���Ρ����ص��Ρ��ɣ�ͦ����ġ�";
  txt2 = "�� �ٿ�һ������İ�����������";
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
  textwh("�����ؼ��˳�", 0, 1, &w, &h);
  dtext("�����ؼ��˳�", SCRW-w-30, 600, 255, 80, 30, 0, 1);
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

// �������
void gameDrawMR(){
 char txt[100];
 Role *r = &main_role;
 int a1, a2, a3;
 int b1, b2, b3;
 
 setTextSize(1, 35);
 dtext("����ֵ", 50, SCRH/4, 255, 255, 255, 0, 1);
 dtext("������", 50, SCRH/4 + 100, 255, 255, 255, 0, 1);
 dtext("����", 50, SCRH/4 + 150, 255, 255, 255, 0, 1);
 dtext("�����ٶ�", 50, SCRH/4 + 200, 255, 255, 255, 0, 1);
 dtext("��", 50, SCRH/4 + 250, 255, 255, 255, 0, 1);
 
 
 
 setTextSize(1, 30);
 sprintf(txt, "%d/%d  (����%d+����%d)", r->hpNow, r->hp, main_role_self_hp, r->hp - main_role_self_hp);
 dtext(txt, 300, SCRH/4, 230, 250, 230, 0, 1);
 sprintf(txt, "%d  (����%d+����%d)", r->atk, main_role_self_atk, r->atk - main_role_self_atk);
 dtext(txt, 300, SCRH/4 + 100, 250, 240, 240, 0, 1);
 
 gameGetCost(r->moveCost, &a1, &b1);
 gameGetCost(main_role_self_moveCost, &a2, &b2);
 gameGetCostA(10 - main_role_self_moveCost + r->moveCost, &a3, &b3);
 sprintf(txt, "%d.%d  (����%d.%d+����%d.%d)", a1, b1, a2, b2, a3, b3);
 dtext(txt, 300, SCRH/4 + 150, 220, 220, 220, 0, 1);
 
 gameGetCost(r->attackCost, &a1, &b1);
 gameGetCost(main_role_self_attackCost, &a2, &b2);
 gameGetCostA(10 - main_role_self_attackCost + r->attackCost, &a3, &b3);
 sprintf(txt, "%d.%d  (����%d.%d+����%d.%d)", a1, b1, a2, b2, a3, b3);
 dtext(txt, 300, SCRH/4 + 200, 240, 220, 240, 0, 1);
 
 sprintf(txt, "%d  (����%d+����%d ��%d%%�˺�)", r->def, main_role_self_def, r->def - main_role_self_def, (r->def*1000)/(r->def*10 + 100));
 dtext(txt, 300, SCRH/4 + 250, 250, 250, 230, 0, 1);
 
}

// �� �ؼ���UI
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
 
 // ��ť
 drawRect(0, SCRH-100, SCRW, 100, 0x88335577);
 drawRect(30, SCRH-120, 100, 100, 0xff335577);
 drawRect(160, SCRH-120, 100, 100, 0xff335577);
 drawRect(290, SCRH-120, 100, 100, 0xff335577);

 setTextSize(1, 60);
 dtext((screen==1||screen==2||screen==3)?"��":"ͼ", 50, SCRH-110, 160, 210, 250, 0, 1);
 dtext((screen==1||screen==2||screen==3)?"��":"��", 180, SCRH-110, 160, 210, 250, 0, 1);
 dtext((screen==1||screen==2||screen==3)?"��":"��", 310, SCRH-110, 160, 210, 250, 0, 1);

 // ����
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
 
 // ��Ϸ��ʼ����
 if(game_now.start < 255){ 
  effsetcon(0, 0, SCRW, SCRH, game_now.start, game_now.start, game_now.start);
  game_now.start += 25;
 }
}

// ��ʾ��Ϸ����
static void gameShowSets(){
 char p[100];
 setTextSize(1, SCRW/30);
 sprintf(p, "SCR��%d*%d", SCRW, SCRH);
 dtext(p, 500, 0, 200, 230, 255, 0, 1);
 sprintf(p, "FPS��%d", 1000/(getuptime() - game_now.t));
 dtext(p, 500, 30, 200, 230, 255, 0, 1);
 game_now.t = getuptime();
}

// �ж���Ϸ�Ƿ����
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
  // ͼ
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
  // ��
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
  // ��
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
  dz = 0; // ����
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
 
 // ��ʼ����Ʒ
 wupinInitAll();
 
 // ��ʼ������
 wupinInit();
 
 int isError;
 do{
  isError = 0;
  // ��ʼ����ͼ
  mapInit(&game_now.map);
  // ��ʼ��Ѱ·
  aStarInit(&game_now.aStar,&game_now.map,MAP_WIDTH,MAP_HEIGHT);
  // ��������
  Room *r = mapGetRoom(&game_now.map, 0, 0);
  if(r != NULL){//  ���� ���� ���� ���� ��
   roleMainInit(r->x + 1, r->y + 1, 10, 10, 15, 4, 0, "��");
  }else{
   toast("���´���������",0);
   isError = 1;
  }
  int level, sum;
 
  // �����������
  mapMakeDraw("���������ò�ͬǿ�ȵĵ���");
 
  level = 1;
  sum = mapGetRoomSum(&(game_now.map),level);
  roleMakeRand(game_now.enemy, &(game_now.enemySum), level, sum, 12, 10, 8, 2, 0, "��");
  
  level = 2;
  sum = mapGetRoomSum(&(game_now.map),level);
  roleMakeRand(game_now.enemy, &(game_now.enemySum), level, sum, 10, 9, 10, 3, 1, "��");
  
  level = 3;
  sum = mapGetRoomSum(&(game_now.map),level)/2;
  roleMakeRand(game_now.enemy, &(game_now.enemySum), level, sum, 8, 4, 20, 5, -4, "��");
  
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
   roleMakeRand(game_now.enemy, &(game_now.enemySum), level, 1, 10, 9, 35, 10, 5, "ʥ");
  }
  
  //���������Ʒ
  Wupin *w;
  mapMakeDraw("����ҩˮ����ֽ������");
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
 
 // ��λ����
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