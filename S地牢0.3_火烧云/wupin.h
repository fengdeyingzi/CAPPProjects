#ifndef _WUPIN_H_
#define _WUPIN_H_
#include <base.h>
#include <android.h>
#include <graphics.h>
#include "role.h"

/*
Mdzz, û�����ٶ�����ƷӢ����
   ��_��
PS����ʵ��Ʒû��ô��
��ûдbuffЧ��
����д��ô����Ʒ����д�Ź����:-)
*/

#define WUPIN_BAG_MAX 20
#define WUPIN_EQUIP_MAX 5
#define WUPIN_GROUND_MAX 50


// ��ƷЧ��
typedef struct _WupinEf{
 int a;     // ���������� <0�ض�Ч�� 0�� 1���� 2���� 3�ٶ� 4���� 5��
 int s;     // ����ֵ
 int time;    // 0���� ����������ʱ��
}_Wupin;

// ��Ʒģ��
typedef struct _Wupin{
 char *name;
 char *detail;
 int type;    // 0���� 1ҩˮ 2���� 3װ��
 struct _WupinEf ef[10];
 int efSum;
}Wupin;

// ��Ʒ�ѻ�ʵ��
typedef struct _WupinL{
 struct _Wupin *wupin;
 int sum;
}WupinL;

// ��Ʒ�ѻ��ڵ��ϵ�ʾ��
typedef struct _WupinLG{
 struct _WupinL wl;
 int x;
 int y;
}WupinLG;

struct _WupinL wupins[WUPIN_BAG_MAX];
struct _WupinL wupin_eq[WUPIN_EQUIP_MAX];
struct _WupinLG wupin_ground[WUPIN_GROUND_MAX];


int wupin_eq_sel = -1;
int wupins_sel = -1;
int wupins_btn_use_x = 0;
int wupins_btn_use_y = 0;
int wupins_btn_no_x = 0;
int wupins_btn_no_y = 0;
int wupins_btn_back_x = 0;
int wupins_btn_back_y = 0;

struct _Wupin wupin_med_icec;  // ��ҩ�����
struct _Wupin wupin_med_hp;    // ����ҩˮ
struct _Wupin wupin_med_mad;   // ��ŭҩˮ
struct _Wupin wupin_med_swift; // Ѹ��ҩˮ
struct _Wupin wupin_med_speed; // �ٶ�ҩˮ
struct _Wupin wupin_med_def;   // ��ҩˮ
struct _Wupin wupin_w_tp;      // �ǿ�����ͼ
struct _Wupin wupin_w_boom;    // ��֮�ͽ����
struct _Wupin wupin_w_shaka;   // ʥ�����
struct _Wupin wupin_w_laka;    // ��Ӱ����
struct _Wupin wupin_equip_swordwooden; // ľ��
struct _Wupin wupin_equip_chiiron;     // ����
struct _Wupin wupin_equip_swordleft;   // ���������ֽ�
struct _Wupin wupin_equip_swordfly;    // �����߲н�
struct _Wupin wupin_equip_rentera;     // �������У����������������õ�����������
struct _Wupin wupin_equip_knifelight;  // ����쵶
struct _Wupin wupin_equip_renreg;      // ����ĩ��
struct _Wupin wupin_equip_fugod;       // ����������+ȫ���ԣ�
struct _Wupin wupin_equip_fupower;     // ��������
struct _Wupin wupin_equip_fuspeed;     // �ٶȻ���
struct _Wupin wupin_equip_dfwooden;    // ľ��
struct _Wupin wupin_equip_dfleather;   // Ƥ�����
struct _Wupin wupin_equip_dflight;     // ������
struct _Wupin wupin_equip_jmamoru;     // �ػ�������
struct _Wupin wupin_equip_jwin;        // ʤ��֮��
struct _Wupin wupin_equip_falight;     // ��Ԫ�طŴ���
struct _Wupin wupin_equip_fayuking;    // ��֮����Ȩ��
struct _Wupin wupin_equip_falife;      // �漣��ʯ����

void wupinInitAll(){
 wupin_med_icec.name = "��ҩ�����";
 wupin_med_icec.detail = "���أ��ڿ������Һ�û�õġ�����˵�����������ı���ܡ���";
 wupin_med_icec.type = 1;
 wupin_med_icec.efSum = 1;
 wupin_med_icec.ef[0].a = 1;
 wupin_med_icec.ef[0].s = 5;
 
 wupin_med_hp.name = "����ҩˮ";
 wupin_med_hp.detail = "ǿ���Ļָ�ҩˮ�������������κ���ʹ�����ĵ�ҩ�����ĵ�ҩ�����ĵ�ҩ������������:-)";
 wupin_med_hp.type = 1;
 wupin_med_hp.efSum = 1;
 wupin_med_hp.ef[0].a = 1;
 wupin_med_hp.ef[0].s = 99999;
 
 wupin_w_tp.name = "�ǿ�����ͼ";
 wupin_w_tp.detail = "����ӵ��һ�δ�Խ�ռ����������ͼֽΪ����Ʒ";
 wupin_w_tp.type = 2;
 wupin_w_tp.efSum = 1;
 wupin_w_tp.ef[0].a = -1;
 wupin_w_tp.ef[0].s = 0;
 
 wupin_equip_swordwooden.name = "ľ��";
 wupin_equip_swordwooden.detail = "��ͨ�Ľ�������ͨ�Ŀ�������ֻ��ľͷ���ģ�";
 wupin_equip_swordwooden.type = 3;
 wupin_equip_swordwooden.efSum = 1;
 wupin_equip_swordwooden.ef[0].a = 2;
 wupin_equip_swordwooden.ef[0].s = 3;

 
 wupin_equip_dfwooden.name = "ľ��";
 wupin_equip_dfwooden.detail = "�����и����Ƶ�һ���ˣ��˿ɲ��ǰ��ӣ���ϲ������Ź�򵽡�";
 wupin_equip_dfwooden.type = 3;
 wupin_equip_dfwooden.efSum = 2;
 wupin_equip_dfwooden.ef[0].a = 5;
 wupin_equip_dfwooden.ef[0].s = 3;
 wupin_equip_dfwooden.ef[1].a = 1;
 wupin_equip_dfwooden.ef[1].s = 2;
 
 wupin_equip_chiiron.name = "����";
 wupin_equip_chiiron.detail = "һ���������������������ù��ģ�";
 wupin_equip_chiiron.type = 3;
 wupin_equip_chiiron.efSum = 2;
 wupin_equip_chiiron.ef[0].a = 2;
 wupin_equip_chiiron.ef[0].s = 4;
 wupin_equip_chiiron.ef[1].a = 1;
 wupin_equip_chiiron.ef[1].s = 8;
 
 wupin_equip_swordfly.name = "�����߶Ͻ�";
 wupin_equip_swordfly.detail = "����̻����Ѷ��ķ��ģ�ʹ�����������Ԧ����";
 wupin_equip_swordfly.type = 3;
 wupin_equip_swordfly.efSum = 3;
 wupin_equip_swordfly.ef[0].a = 2;
 wupin_equip_swordfly.ef[0].s = 6;
 wupin_equip_swordfly.ef[1].a = 1;
 wupin_equip_swordfly.ef[1].s = 10;
 wupin_equip_swordfly.ef[2].a = 4;
 wupin_equip_swordfly.ef[2].s = 3;
 
 wupin_equip_fuspeed.name = "�ٶȻ���";
 wupin_equip_fuspeed.detail = "������������������ݺ͹����ٶ�С����������";
 wupin_equip_fuspeed.type = 3;
 wupin_equip_fuspeed.efSum = 2;
 wupin_equip_fuspeed.ef[0].a = 3;
 wupin_equip_fuspeed.ef[0].s = 1;
 wupin_equip_fuspeed.ef[1].a = 4;
 wupin_equip_fuspeed.ef[1].s = 1;
}



////////


static int wupinIsPointInRect(int p, int q, int x, int y, int w, int h){
 return p >= x && q >= y && p < x + w && q < y + h;
}

char* wupinGetEfName(int a){
 char *b = "δ֪����";
 switch(a){
  case 1:
   b = "��������";
   break;
  case 2:
   b = "������";
   break;
  case 3:
   b = "����";
   break;
  case 4:
   b = "�����ٶ�";
   break;
  case 5:
   b = "��";
   break;
 }
 return b;
}

int wupinAdd(struct _WupinL* wl){
 int ok = 0;
 int i;
 // ֻ��ͬ�����Ʒ�����ӣ�
 for(i = 0; !ok && i < WUPIN_BAG_MAX; i ++){
  if(wupins[i].sum > 0){
   if(wupins[i].wupin == wl->wupin){
    wupins[i].sum += wl->sum;
    wl->sum = 0;
    ok = 1;
   }
  }
 }
 // �����оͷ���յĸ��ӣ��ٺ٣���Ϊ�
 for(i = 0; !ok && i < WUPIN_BAG_MAX; i ++){
  if(wupins[i].sum <= 0){
   wupins[i].sum = wl->sum;
   wupins[i].wupin = wl->wupin;
   wl->sum = 0;
   ok = 1;
  }
 }
 return ok;
}

int wupinEquip(struct _WupinL* wl){
 int ok = 0;
 for(int i = 0; i < WUPIN_EQUIP_MAX; i ++){
  if(wupin_eq[i].sum < 1){
    ok = 1;
    wupin_eq[i].sum = 1;
    wupin_eq[i].wupin = wl->wupin;
    break;
  }
 }
 if(ok){
  wl->sum --;
  wupinEqReCalcu();
 }
 return ok;
}

int wupinUnequip(struct _WupinL* wl){
 int ok = wupinAdd(wl);
 if(ok){
  wupinEqReCalcu();
 }
 return ok;
}


// ���¼���������Ч�棨���ϻ���ж��װ��ʱ������
void wupinEqReCalcu(){
 Role *r = &main_role;
 int i, j, s;
 // ������������
 r->hp = main_role_self_hp;
 r->atk = main_role_self_atk;
 r->def = main_role_self_def;
 r->moveCost = main_role_self_moveCost;
 r->attackCost = main_role_self_attackCost;
 // �������
 for(i = 0; i < WUPIN_EQUIP_MAX ; i ++){
  if(wupin_eq[i].sum > 0){
   for(j = 0; j < wupin_eq[i].wupin->efSum; j ++){
    s = wupin_eq[i].wupin->ef[j].s;
    switch(wupin_eq[i].wupin->ef[j].a){
     case 1: // "����ֵ";
      r->hp += s;
      break;
     case 2: // "������";
      r->atk += s;
      break;
     case 3: // "����";
      r->moveCost -= s;
      break;
     case 4: // "�����ٶ�";
      r->attackCost -= s;
      break;
     case 5: // "��";
      r->def += s;
      break;
    }
   }
  }
 }
 // ȥ�����Ϸ�����
 if(r->moveCost < 1) r->moveCost = 1;
 if(r->attackCost < 1) r->attackCost = 1;
 if(r->hpNow > r->hp) r->hp = r->hpNow;
}

// ��Ʒʹ��
void wupinSetEf(struct _WupinL* wl){
 Role *r = &main_role;
 int ds;
 char dc[100];
 // ʹ�ú��������
 for(int i = 0; i < wl->wupin->efSum; i ++){
  switch(wl->wupin->ef[i].a){
  case 1: // "����ֵ";
   ds = wl->wupin->ef[i].s;
   if(r->hpNow + ds > r->hp){
    ds = r->hp - r->hpNow;
   }
   r->hpNow += ds;
   sprintf(dc, "����%d����ֵ��", ds);
   toast(dc, 0);
   break;
  case 2: // "������";
   break;
  case 3: // "����";
   break;
  case 4: // "�����ٶ�";
   break;
  case 5: // "��";
   break;
  default: // �ض�Ч��
   static int ifk = 0;
   if(wl->wupin == &(wupin_w_tp)){
    if(ifk < 3){
     ifk ++;
     toast("��δ��������ѽ�����������ɵġ���", 0);
    }else if(ifk < 10){
     ifk ++;
     toast("��˵��û�������㻹��ʹ��", 0);
    }else{
     ifk ++;
     toast("��Ӯ�ˡ����ã���������ɡ���", 0);
    }
    
   }
   break;
  }
 }
 // ��Ʒ���
 wl->sum --;
}

// ���ݵ����xy��ȡwupin������
static int wupinSelFromScr(int x, int y){
 int d = 100;
 int xs = WUPIN_EQUIP_MAX;
 int ys = (WUPIN_BAG_MAX)/xs;
 int dx = (SCRW-xs*d)/2;
 int dy = (SCRH-ys*d)/2;
 int i, ti = -1;
 if(wupinIsPointInRect(x, y, dx, dy, xs*d, ys*d)){
  i = (y-dy)/d*xs + (x-dx)/d;
  if(i >= 0 && i < WUPIN_BAG_MAX){
   if(wupins[i].sum > 0){
    ti = i;
    wupins_sel = i;
    wupin_eq_sel = -1;
   }
  }
 }else if(wupinIsPointInRect(x, y, dx, dy-d, xs*d, d)){
  i = ((y-dy)/d*xs + (x-dx)/d);
  if(i >= 0 && i < WUPIN_BAG_MAX){
   if(wupin_eq[i].sum > 0){
    ti = i;
    wupin_eq_sel = i;
    wupins_sel = -1;
   }
  }
 }
 return ti;
}

static void wupinDrawDetail(WupinL *wl, int equiped, int x, int y, int w, int h){
 char de[100];
 int i;
 rectst rect;
 rect.x = x + w/16;
 rect.y = y + 100;
 rect.w = w*7/8;
 rect.h = h - 100;
 colorst color;
 color.r = 220;
 color.g = 220;
 color.b = 220;
 drect(x + 10, y + 10, w - 20, 60, 170, 150, 70);
 // ����
 setTextSize(1, 45);
 dtext(wl->wupin->name, x + 30, y + 10, 250, 250, 250, 0, 1);
 // ���ܣ���������������������Ϣ
 if(wl->wupin->type ==3){
  setTextSize(1, 30);
  for(i = 0; i < wl->wupin->efSum; i ++){
   sprintf(de, "+ %d�� %s", wl->wupin->ef[i].s, wupinGetEfName(wl->wupin->ef[i].a));
   dtext(de, x + 40, y + 100 + i * 40, 250, 240, 230, 0, 1);
  }
  setTextSize(1, 35);
  rect.y = y + 100 + i * 40;
  dtextex(wl->wupin->detail, rect.x + 50, rect.y, &rect,&color,0,1);
 }else{
  setTextSize(1, 35);
  dtextex(wl->wupin->detail, rect.x + 50, rect.y, &rect,&color,0,1);
 }
 drect(x + 10, y + h - 70, 100, 60, 170, 150, 70);
 drect(x + 140, y + h - 70, 100, 60, 100, 100, 100);
 drect(x + w - 110, y + h - 70, 100, 60, 170, 150, 70);
 setTextSize(1, 35);
 dtext(wl->wupin->type != 3 ? "ʹ��" : (equiped?"ж��":"װ��"), x + 20, y + h - 60, 250, 250, 250 ,0,1);
 dtext("����", x + 150, y + h - 60, 250, 250, 250 ,0,1);
 dtext("����", x + w - 100, y + h - 60, 250, 250, 250 ,0,1);
 wupins_btn_use_x = x + 10;
 wupins_btn_use_y = y + h - 70;
 wupins_btn_no_x = x + 140;
 wupins_btn_no_y = y + h - 70;
 wupins_btn_back_x = x + w - 110;
 wupins_btn_back_y = y + h - 70;
}

void wupinDrawBag(){
 int xi,yi,ok;
 int d = 100;
 int xs = WUPIN_EQUIP_MAX;
 int ys = (WUPIN_BAG_MAX)/xs;
 int dx = (SCRW-xs*d)/2;
 int dy = (SCRH-ys*d)/2;
 WupinL *wl;
 char *sc, sr[100];
 int w, h;
 ok = 1;
 drect(dx-10, dy-10-d, d*xs+20, d*ys+d+20, 150, 100, 50);
 if(wupins_sel == -1 && wupin_eq_sel == -1){
  for(yi = -1; ok; yi ++){
   for(xi = 0; ok && xi < xs; xi ++){
    if(yi * xs + xi < WUPIN_BAG_MAX){
     if(yi * xs + xi >= 0){
      drect(dx+xi*d, dy+yi*d, d-2, d-2, 80, 100, 150);
      wl = &(wupins[yi * xs + xi]);
      if((wl->sum > 0) * (wl->wupin != NULL)){
       switch(wl->wupin->type){
       case 1:
        sc = "ҩ";
        break;
       case 2:
        sc = "ֽ";
        break;
       case 3:
        sc = "��";
        break;
       default:
       sc = "��";
        break;
       }
       setTextSize(1, d/2);
       dtext(sc, dx+xi*d + d/4, dy+yi*d + d/4, 250, 250, 250, 0, 1);
       setTextSize(1, d/4);
       sprintf(sr, "x%d", wl->sum);
       textwh(sr, 0, 1, &w, &h);
       dtext(sr, dx+xi*d + d - w - 3, dy+yi*d, 230, 230, 150, 0, 1);
      }
     }else{
      drect(dx+xi*d, dy+yi*d, d-2, d-2, 100, 160, 210);
      wl = &(wupin_eq[xs + (yi * xs + xi)]);
      if(wl->sum > 0){
       setTextSize(1, d/2);
       sprintf(sr, "%c%c\0", wl->wupin->name[0], wl->wupin->name[1]);
       dtext(sr, dx+xi*d + d/4, dy+yi*d + d/4, 250, 250, 250, 0, 1);
      }
     }
    }else{
     ok = 0;
    }
   }
  }
 }else{
  // ��ϸ��Ϣ
  int equiped = (wupin_eq_sel != -1);
  if(equiped){
   wl = &(wupin_eq[wupin_eq_sel]);
  }else{
   wl = &(wupins[wupins_sel]);
  }
  wupinDrawDetail(wl,equiped,dx-10, dy-10-d, d*xs+20, d*ys+d+20);
 }
}


// ���ڵ��ϵ���Ʒ
void wupinDrawOnGround(){
 int dx = game_now.map.x;
 int dy = game_now.map.y;
 int d = TILED_D;
 int x,y;
 char *sc;
 for(int i = 0; i < WUPIN_GROUND_MAX; i ++){
  if(wupin_ground[i].wl.sum > 0){
   x = dx + wupin_ground[i].x * d;
   y = dy + wupin_ground[i].y * d;
   switch(wupin_ground[i].wl.wupin->type){
    case 1:
     sc = "ҩ";
     break;
    case 2:
     sc = "ֽ";
     break;
    case 3:
     sc = "��";
     break;
    default:
     sc = "��";
     break;
   }
   setTextSize(1, d/2);
   drect(x + d/5, y + d/5, d*3/5, d*3/5, 200, 200, 0);
   dtext(sc, x + d/4, y + d/4, 0, 0, 180, 0, 1);
  }
 }
}

// ��ӵ��ϵ���Ʒ
void wupinAddGround(struct _Wupin* w, int x, int y){
 for(int i = 0; i < WUPIN_GROUND_MAX; i ++){
  if(wupin_ground[i].wl.sum <= 0){
   wupin_ground[i].wl.wupin = w;
   wupin_ground[i].wl.sum = 1;
   wupin_ground[i].x = x;
   wupin_ground[i].y = y;
   break;
  }
 }
}

// ����������ϵ���Ʒ
void wupinGroundRand(int level, int sum, struct _Wupin* w){
 Room *r;
 int sc = 0;
 for(int i = 0; i < sum; i ++){
  r = mapFindRoomRand(&(game_now.map), level);
  if(r != NULL){
   if(sc > WUPIN_GROUND_MAX){
    printf("ERROR ������Ʒ���࣬���޸ĺ���߼�����Ʒ");
    exit();
   }
   wupinAddGround(w, r->x + 1 + rand()%(r->w - 2), r->y + 1 + rand()%(r->h - 2));
   sc ++;
  }else{
   break;
  }
 }
 printf("�� ����[%s]��Ʒ%d��\n", w->name, sc);
}

// ����Ʒ
void wupinGroundGet(){
 char cs[100];
 for(int i = 0; i < WUPIN_GROUND_MAX; i ++){
  if(wupin_ground[i].wl.sum > 0){
   if((main_role.x == wupin_ground[i].x) * (main_role.y == wupin_ground[i].y)){
    if(wupinAdd(&(wupin_ground[i].wl))){
      sprintf(cs, "��õ���%s", wupin_ground[i].wl.wupin->name);
      toast(cs, 0);
    }else{
     break;
    }
   }
  }
 }
}

void wupinAct(){
 wupinGroundGet();
}

void wupinEvent(int s, int p, int q){
 if(s == MS_UP){
  if(wupins_sel == -1 && wupin_eq_sel == -1 ){
   wupinSelFromScr(p, q);
  }else if(wupinIsPointInRect(p, q, wupins_btn_use_x, wupins_btn_use_y, 100, 60)){
   if(wupin_eq_sel == -1){
    if(wupins[wupins_sel].wupin->type != 3){
     wupinSetEf(&(wupins[wupins_sel]));
    }else{
     wupinEquip(&(wupins[wupins_sel]));
    }
   }else{
    // ж��װ��
    wupinUnequip(&(wupin_eq[wupin_eq_sel]));
   }
   wupins_sel = -1;
   wupin_eq_sel = -1;
  }else if(wupinIsPointInRect(p, q, wupins_btn_no_x, wupins_btn_no_y, 100, 60)){
   //wupins_sel = -1;
   //wupin_eq_sel = -1;
  }else if(wupinIsPointInRect(p, q, wupins_btn_back_x, wupins_btn_back_y, 100, 60)){
   wupins_sel = -1;
   wupin_eq_sel = -1;
  }
 }
}

void wupinInit(){
 int i;
 for(i = 0; i < WUPIN_BAG_MAX; i ++){
  wupins[i].sum = 0;
  wupins[i].wupin = NULL;
 }
 for(i = 0; i < WUPIN_EQUIP_MAX; i ++){
  wupin_eq[i].sum = 0;
  wupin_eq[i].wupin = NULL;
 }
 for(i = 0; i < WUPIN_GROUND_MAX; i ++){
  wupin_ground[i].wl.sum = 0;
  wupin_ground[i].wl.wupin = NULL;
 }
 
 wupins[0].sum = 99;
 wupins[0].wupin = &(wupin_w_tp);
}

#endif