#ifndef _ROLE_H_
#define _ROLE_H_

#include <graphics.h>
#include "map.h"
#include "aStar.h"

#define ROLE_PER_ROUND_WAIT 5

// 敌人响应范围
#define ENEMY_ACTION_DST 6

typedef struct _Role{
 int roundRemain; // 回合剩余
 char *name;
 int x;
 int y;
 int moveCost;
 int attackCost;
 int hp;
 int hpNow;
 int atk;
 int def;
 int fl[20]; // 伤害飘字
 int flNow;
 int flSum;
 int die;
}Role;

void *game_role;
Role main_role;
Role *main_role_attack_goal = NULL;
int main_role_wait = ROLE_PER_ROUND_WAIT;
int main_role_state = 0; // 0等待 1行走 2攻击
int main_role_togox = 0; 
int main_role_togoy = 0; 

// 主角自身属性
int main_role_self_hp = 0;
int main_role_self_atk = 0;
int main_role_self_def = 0;
int main_role_self_moveCost = 0;
int main_role_self_attackCost = 0;


int enemy_die_sum = 0;

// role之间的街区距离
int roleDisto(Role *r, Role *r2){
 return (r->x > r2->x ? r->x - r2->x : r2->x - r->x) + (r->y > r2->y ? r->y - r2->y : r2->y - r->y);
}

// x y 位置是否存在敌人
struct _Role* roleExistEnemy(Role *enemy, int sum, int x, int y){
 Role *r = NULL;
 for(int i = 0; i < sum; i ++){
  if((!(enemy[i].die)) * (enemy[i].x == x) * (enemy[i].y == y)){
   r = &(enemy[i]);
   break;
  }
 }
 return r;
}
// r能否攻击r2（是否在攻击范围）
int roleCanAttack(Role *r, Role *r2){
 int d;
 if((r->x == r2->x) + (r->y == r2->y)){
  d = 1; 
 }else{
  d = 2;
 }
 return roleDisto(r, r2) <= d;
}

// 随机+，越接近i可能性越大，不可能离i过远
int roleGetHalfRand3(int i, int power){
 int a = rand()%i;
 int b = i - a;
 int c = i;
 int k;
 int j;
 for(k = 1; c > 0; k ++){
  c -= k/power;
 }
 for(j = 1; b > 0; j ++){
  b -= j/power;
 }
 return i + (rand()%2?(k-j):(j-k));
}

// r攻击r2
void roleAttack(Role *r, Role *r2){
 int a = roleGetHalfRand3(r->atk, 2)*100/(100+r2->def*10);
 r2->hpNow -= a;
 if(r2->hpNow <= 0){
  r2->hpNow = 0;
 
  r2->die = 1;
 }
 // 给予伤害飘字
 // patch 可能数组越间
 r2->flNow = 0;
 r2->fl[r2->flSum] = a;
 r2->flSum ++;
}


void roleEnemyAct(Role *r, Role *enemy, int sum, int roundGive){
 int enoughAttack, enoughMove;
 r->roundRemain += roundGive;
 enoughAttack = (r->roundRemain >= r->attackCost);
 enoughMove = (r->roundRemain >= r->moveCost);
 while(enoughAttack || enoughMove){
  if(roleCanAttack(r, &main_role)){
   if(enoughAttack){
    // 攻击
    roleAttack(r, &main_role);
    main_role_state = 0;
    r->roundRemain -= r->attackCost;
   }else{
    // 足够移动而不够攻击
    break;
   }
  }else{
   if(enoughMove){
    // 移动
    if(aStarToPoint(&(game_now.aStar),r->x,r->y, main_role.x, main_role.y)){
     int x = (&game_now.aStar)->nextX;
     int y = (&game_now.aStar)->nextY;
     if(roleExistEnemy(enemy,sum,x,y) == NULL){
      r->x = x;
      r->y = y;
      r->roundRemain -= r->moveCost;
     }else{
      // 避免重合
      r->roundRemain = 0;
     }
    }else{
     // 查找路径失败
     r->roundRemain = 0;
    }
   }else{
     // 足够攻击而不够移动
     break;
    }
  }
  enoughAttack = (r->roundRemain >= r->attackCost);
  enoughMove = (r->roundRemain >= r->moveCost);
  //printf("      ActEnemy r.%d,atk.%d,m.%d\n", r->roundRemain, enoughAttack, enoughMove);
 }
}

// 回合准备
void roleActPre(Role *r){
  r->flSum = 0;
}

// 所有逻辑
void roleAllAct(Role *enemy, int sum){
 int round = 0;
 int i;
 //printf("   Act Start\n");
 // 主角控制
 if(main_role_state){
  if(main_role_wait > 0){
   main_role_wait --;
  }else{
   main_role_wait = ROLE_PER_ROUND_WAIT;
   //准备
   roleActPre(&main_role);
   for(i= 0; i < sum; i ++){
    roleActPre(&(enemy[i]));
   }
   //printf("      ActMain Start\n");
   switch(main_role_state){
    case 0: // 等待
    break; 
    case 1: // 行走
     if(aStarToPoint(&game_now.aStar,main_role.x,main_role.y, main_role_togox, main_role_togoy)){
      round = main_role.moveCost;
      main_role.x = game_now.aStar.nextX;
      main_role.y = game_now.aStar.nextY;
     }else{
      // 走到了 或者根本走不到
      main_role_state = 0;
     }
     break;
    case 2: // 攻击
     if(roleCanAttack(&main_role,main_role_attack_goal)){
      round = main_role.attackCost;
      roleAttack(&main_role,main_role_attack_goal);
     }
     if(main_role_attack_goal->die){
      // 杀死了
      main_role_state = 0;
      enemy_die_sum ++;
     }
     break;
   }
  }
  //printf("      ActMain End\n");
  // 赋予敌人行动力
  for(i = 0; i < sum; i ++){
   if((!(enemy[i].die)) * (roleDisto(&main_role, &(enemy[i])) <= ENEMY_ACTION_DST)){
    roleEnemyAct(&(enemy[i]), enemy, sum, round);
   }
  }
 }
 //printf("   Act End\n");
}


static void roleDrawFx(Role *r, int d){
 int i;
 char s[100];
 setTextSize(1, d*3/4);
 // 伤害飘字
 for(i = 0; i < r->flSum; i ++){
  sprintf(s, "-%d", r->fl[i]);
  if(r->flNow - i*d/2 < d*4)dtext(s,game_now.map.x + r->x*d + d/2, game_now.map.y + r->y*d + d/2 - r->flNow - (r->flSum - i - 1)*d,220,70,60,0,1);
 }
 r->flNow += d/4;
}

static void roleAllDrawExt(Role *enemy, int sum, int d){
 int mapx = game_now.map.x;
 int mapy = game_now.map.y;
 for(int i = 0; i < sum; i ++){
  if(!(enemy[i].die)){
   // 生命栏
   drawRect(mapx + enemy[i].x*d, mapy + enemy[i].y*d, d, d/8, 0xff000000);
   drawRect(mapx + enemy[i].x*d+1,mapy + enemy[i].y*d+1, (d-2)*(enemy[i].hpNow)/(enemy[i].hp), d/8-2, 0xff66ff88);
  }
  // 特效
  roleDrawFx(&(enemy[i]), d);
 }
 drawRect(mapx + main_role.x*d, mapy + main_role.y*d, d, d/8, 0xff000000);
 drawRect(mapx + main_role.x*d+1, mapy + main_role.y*d+1, (d-2)*main_role.hpNow/main_role.hp, d/8-2, 0xff66ff88);
 roleDrawFx(&main_role, d);
}


void roleAllDraw(Role *enemy, int sum, int d){
 int mapx = game_now.map.x;
 int mapy = game_now.map.y;
 //printf("   Draw Start\n");
 setTextSize(1, d*3/4);
 for(int i = 0; i < sum; i ++){
  if(!(enemy[i].die)){
   drawCir(mapx + enemy[i].x*d+d/2, mapy + enemy[i].y*d+d/2,d/2,0xffee4433);
   dtext(enemy[i].name,mapx + enemy[i].x*d + d/8, mapy + enemy[i].y*d + d/8,0,0,0,0,1);
  }
 }
 drawCir(mapx + main_role.x*d+d/2, mapy + main_role.y*d+d/2,d/2,0xff66ccff);
 dtext(main_role.name,mapx + main_role.x*d + d/8, mapy + main_role.y*d + d/8,0,0,0,0,1);

 roleAllDrawExt(enemy, sum, d);
 //printf("   Draw End\n");
}

void roleMakeRand(Role *enemy, int *sum, int level, int s, int moveCost, int attackCost, int hp, int atk, int def, char *name){
 Room *r;
 int sc = 0;
 // ps: （滑稽）我就是喜欢随机，简单
 // patch 这里写的太多余了
 for(int i = 0; i < s; i ++){
  // 找到一间房
  r = mapFindRoomRand(&(game_now.map), level);
  if(r != NULL){
   roleInit(&(enemy[*sum]), r->x + 1 + rand()%(r->w - 2), r->y + 1 + rand()%(r->h - 2), moveCost, attackCost, hp, atk, def, name);
   *sum = *sum + 1;
   sc ++;
  }else{
   break;
  }
 }
 printf("○ 产生%d个的敌人放入%d层\n", sc, level);
}
  


void roleMainDo(Role *enemy, int sum, int x,int y){
 Role *r = roleExistEnemy(enemy, sum, x, y);
 if(r != NULL){
  if(roleCanAttack(&main_role, r)){
   main_role_attack_goal = r;
   main_role_wait = 0;
   main_role_state = 2;
   //printf("  doAttack\n");
  }else{
   // patch 超出射程未处理
   //printf("  doAttack outof range\n");
  }
 }else{
  main_role_wait = 0;
  main_role_state = 1;
  main_role_togox = x;
  main_role_togoy = y;
  //printf("  doMove\n");
 }
}

void roleInit(Role *r, int x, int y, int moveCost, int attackCost, int hp, int atk, int def, char *name){
 r->x = x;
 r->y = y;
 r->moveCost = moveCost;
 r->attackCost = attackCost;
 r->hp = hp;
 r->hpNow = hp;
 r->atk = atk;
 r->def = def;
 r->name = name;
 
 r->roundRemain = 0;
 r->flSum = 0;
 r->flNow = 0;
 r->die = 0;
}

void roleMainInit(int x, int y, int moveCost, int attackCost, int hp, int atk, int def, char *name){
 roleInit(&main_role, x, y, moveCost, attackCost, hp, atk, def, name);
 // 主角自身属性
 main_role_self_hp = main_role.hp;
 main_role_self_atk = main_role.atk;
 main_role_self_def = main_role.def;
 main_role_self_moveCost = main_role.moveCost;
 main_role_self_attackCost = main_role.attackCost;

}

#endif