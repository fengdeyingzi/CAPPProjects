#ifndef _ROLE_H_
#define _ROLE_H_

#include <graphics.h>
#include "map.h"
#include "aStar.h"

#define ROLE_PER_ROUND_WAIT 5

// ������Ӧ��Χ
#define ENEMY_ACTION_DST 6

typedef struct _Role{
 int roundRemain; // �غ�ʣ��
 char *name;
 int x;
 int y;
 int moveCost;
 int attackCost;
 int hp;
 int hpNow;
 int atk;
 int def;
 int fl[20]; // �˺�Ʈ��
 int flNow;
 int flSum;
 int die;
}Role;

void *game_role;
Role main_role;
Role *main_role_attack_goal = NULL;
int main_role_wait = ROLE_PER_ROUND_WAIT;
int main_role_state = 0; // 0�ȴ� 1���� 2����
int main_role_togox = 0; 
int main_role_togoy = 0; 

// ������������
int main_role_self_hp = 0;
int main_role_self_atk = 0;
int main_role_self_def = 0;
int main_role_self_moveCost = 0;
int main_role_self_attackCost = 0;


int enemy_die_sum = 0;

// role֮��Ľ�������
int roleDisto(Role *r, Role *r2){
 return (r->x > r2->x ? r->x - r2->x : r2->x - r->x) + (r->y > r2->y ? r->y - r2->y : r2->y - r->y);
}

// x y λ���Ƿ���ڵ���
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
// r�ܷ񹥻�r2���Ƿ��ڹ�����Χ��
int roleCanAttack(Role *r, Role *r2){
 int d;
 if((r->x == r2->x) + (r->y == r2->y)){
  d = 1; 
 }else{
  d = 2;
 }
 return roleDisto(r, r2) <= d;
}

// ���+��Խ�ӽ�i������Խ�󣬲�������i��Զ
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

// r����r2
void roleAttack(Role *r, Role *r2){
 int a = roleGetHalfRand3(r->atk, 2)*100/(100+r2->def*10);
 r2->hpNow -= a;
 if(r2->hpNow <= 0){
  r2->hpNow = 0;
 
  r2->die = 1;
 }
 // �����˺�Ʈ��
 // patch ��������Խ��
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
    // ����
    roleAttack(r, &main_role);
    main_role_state = 0;
    r->roundRemain -= r->attackCost;
   }else{
    // �㹻�ƶ�����������
    break;
   }
  }else{
   if(enoughMove){
    // �ƶ�
    if(aStarToPoint(&(game_now.aStar),r->x,r->y, main_role.x, main_role.y)){
     int x = (&game_now.aStar)->nextX;
     int y = (&game_now.aStar)->nextY;
     if(roleExistEnemy(enemy,sum,x,y) == NULL){
      r->x = x;
      r->y = y;
      r->roundRemain -= r->moveCost;
     }else{
      // �����غ�
      r->roundRemain = 0;
     }
    }else{
     // ����·��ʧ��
     r->roundRemain = 0;
    }
   }else{
     // �㹻�����������ƶ�
     break;
    }
  }
  enoughAttack = (r->roundRemain >= r->attackCost);
  enoughMove = (r->roundRemain >= r->moveCost);
  //printf("      ActEnemy r.%d,atk.%d,m.%d\n", r->roundRemain, enoughAttack, enoughMove);
 }
}

// �غ�׼��
void roleActPre(Role *r){
  r->flSum = 0;
}

// �����߼�
void roleAllAct(Role *enemy, int sum){
 int round = 0;
 int i;
 //printf("   Act Start\n");
 // ���ǿ���
 if(main_role_state){
  if(main_role_wait > 0){
   main_role_wait --;
  }else{
   main_role_wait = ROLE_PER_ROUND_WAIT;
   //׼��
   roleActPre(&main_role);
   for(i= 0; i < sum; i ++){
    roleActPre(&(enemy[i]));
   }
   //printf("      ActMain Start\n");
   switch(main_role_state){
    case 0: // �ȴ�
    break; 
    case 1: // ����
     if(aStarToPoint(&game_now.aStar,main_role.x,main_role.y, main_role_togox, main_role_togoy)){
      round = main_role.moveCost;
      main_role.x = game_now.aStar.nextX;
      main_role.y = game_now.aStar.nextY;
     }else{
      // �ߵ��� ���߸����߲���
      main_role_state = 0;
     }
     break;
    case 2: // ����
     if(roleCanAttack(&main_role,main_role_attack_goal)){
      round = main_role.attackCost;
      roleAttack(&main_role,main_role_attack_goal);
     }
     if(main_role_attack_goal->die){
      // ɱ����
      main_role_state = 0;
      enemy_die_sum ++;
     }
     break;
   }
  }
  //printf("      ActMain End\n");
  // ��������ж���
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
 // �˺�Ʈ��
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
   // ������
   drawRect(mapx + enemy[i].x*d, mapy + enemy[i].y*d, d, d/8, 0xff000000);
   drawRect(mapx + enemy[i].x*d+1,mapy + enemy[i].y*d+1, (d-2)*(enemy[i].hpNow)/(enemy[i].hp), d/8-2, 0xff66ff88);
  }
  // ��Ч
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
 // ps: ���������Ҿ���ϲ���������
 // patch ����д��̫������
 for(int i = 0; i < s; i ++){
  // �ҵ�һ�䷿
  r = mapFindRoomRand(&(game_now.map), level);
  if(r != NULL){
   roleInit(&(enemy[*sum]), r->x + 1 + rand()%(r->w - 2), r->y + 1 + rand()%(r->h - 2), moveCost, attackCost, hp, atk, def, name);
   *sum = *sum + 1;
   sc ++;
  }else{
   break;
  }
 }
 printf("�� ����%d���ĵ��˷���%d��\n", sc, level);
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
   // patch �������δ����
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
 // ������������
 main_role_self_hp = main_role.hp;
 main_role_self_atk = main_role.atk;
 main_role_self_def = main_role.def;
 main_role_self_moveCost = main_role.moveCost;
 main_role_self_attackCost = main_role.attackCost;

}

#endif