#ifndef _WUPIN_H_
#define _WUPIN_H_
#include <base.h>
#include <android.h>
#include <graphics.h>
#include "role.h"

/*
Mdzz, 没流量百度下物品英文名
   ←_←
PS：其实物品没那么多
还没写buff效果
所以写这么多物品就是写着过过瘾:-)
*/

#define WUPIN_BAG_MAX 20
#define WUPIN_EQUIP_MAX 5
#define WUPIN_GROUND_MAX 50


// 物品效果
typedef struct _WupinEf{
 int a;     // 提升的属性 <0特定效果 0无 1生命 2攻击 3速度 4攻速 5格挡
 int s;     // 提升值
 int time;    // 0永久 其他：持续时长
}_Wupin;

// 物品模型
typedef struct _Wupin{
 char *name;
 char *detail;
 int type;    // 0废物 1药水 2卷轴 3装备
 struct _WupinEf ef[10];
 int efSum;
}Wupin;

// 物品堆积实例
typedef struct _WupinL{
 struct _Wupin *wupin;
 int sum;
}WupinL;

// 物品堆积在地上的示例
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

struct _Wupin wupin_med_icec;  // 草药冰淇淋
struct _Wupin wupin_med_hp;    // 治疗药水
struct _Wupin wupin_med_mad;   // 暴怒药水
struct _Wupin wupin_med_swift; // 迅捷药水
struct _Wupin wupin_med_speed; // 速度药水
struct _Wupin wupin_med_def;   // 镇定药水
struct _Wupin wupin_w_tp;      // 星空裂震图
struct _Wupin wupin_w_boom;    // 龙之惩戒符咒
struct _Wupin wupin_w_shaka;   // 圣光卷轴
struct _Wupin wupin_w_laka;    // 暗影卷轴
struct _Wupin wupin_equip_swordwooden; // 木剑
struct _Wupin wupin_equip_chiiron;     // 铁尺
struct _Wupin wupin_equip_swordleft;   // 劳伦兹左手剑
struct _Wupin wupin_equip_swordfly;    // 飞仙者残剑
struct _Wupin wupin_equip_rentera;     // 地狱兵刃（和上面的组合起来得到神明护符）
struct _Wupin wupin_equip_knifelight;  // 流光快刀
struct _Wupin wupin_equip_renreg;      // 规则末刃
struct _Wupin wupin_equip_fugod;       // 神明护符（+全属性）
struct _Wupin wupin_equip_fupower;     // 力量护符
struct _Wupin wupin_equip_fuspeed;     // 速度护符
struct _Wupin wupin_equip_dfwooden;    // 木盾
struct _Wupin wupin_equip_dfleather;   // 皮革盾牌
struct _Wupin wupin_equip_dflight;     // 神奇光盾
struct _Wupin wupin_equip_jmamoru;     // 守护者铠甲
struct _Wupin wupin_equip_jwin;        // 胜利之心
struct _Wupin wupin_equip_falight;     // 光元素放大器
struct _Wupin wupin_equip_fayuking;    // 悠之王者权杖
struct _Wupin wupin_equip_falife;      // 奇迹宝石核心

void wupinInitAll(){
 wupin_med_icec.name = "草药冰淇淋";
 wupin_med_icec.detail = "呜呜，在看我吗？我很没用的……话说地牢里哪来的冰淇淋……";
 wupin_med_icec.type = 1;
 wupin_med_icec.efSum = 1;
 wupin_med_icec.ef[0].a = 1;
 wupin_med_icec.ef[0].s = 5;
 
 wupin_med_hp.name = "治疗药水";
 wupin_med_hp.detail = "强力的恢复药水，他可以消除任何伤痛，贴心的药，良心的药，放心的药，火烧云制造:-)";
 wupin_med_hp.type = 1;
 wupin_med_hp.efSum = 1;
 wupin_med_hp.ef[0].a = 1;
 wupin_med_hp.ef[0].s = 99999;
 
 wupin_w_tp.name = "星空裂震图";
 wupin_w_tp.detail = "让你拥有一次穿越空间的能力，该图纸为消耗品";
 wupin_w_tp.type = 2;
 wupin_w_tp.efSum = 1;
 wupin_w_tp.ef[0].a = -1;
 wupin_w_tp.ef[0].s = 0;
 
 wupin_equip_swordwooden.name = "木剑";
 wupin_equip_swordwooden.detail = "普通的剑我们普通的砍～别看我只是木头做的！";
 wupin_equip_swordwooden.type = 3;
 wupin_equip_swordwooden.efSum = 1;
 wupin_equip_swordwooden.ef[0].a = 2;
 wupin_equip_swordwooden.ef[0].s = 3;

 
 wupin_equip_dfwooden.name = "木盾";
 wupin_equip_dfwooden.detail = "总算有个盾牌挡一挡了，人可不是靶子，不喜欢被人殴打到。";
 wupin_equip_dfwooden.type = 3;
 wupin_equip_dfwooden.efSum = 2;
 wupin_equip_dfwooden.ef[0].a = 5;
 wupin_equip_dfwooden.ef[0].s = 3;
 wupin_equip_dfwooden.ef[1].a = 1;
 wupin_equip_dfwooden.ef[1].s = 2;
 
 wupin_equip_chiiron.name = "铁尺";
 wupin_equip_chiiron.detail = "一个重量级的武器，萧炎用过的？";
 wupin_equip_chiiron.type = 3;
 wupin_equip_chiiron.efSum = 2;
 wupin_equip_chiiron.ef[0].a = 2;
 wupin_equip_chiiron.ef[0].s = 4;
 wupin_equip_chiiron.ef[1].a = 1;
 wupin_equip_chiiron.ef[1].s = 8;
 
 wupin_equip_swordfly.name = "飞仙者断剑";
 wupin_equip_swordfly.detail = "上面刻划着难懂的符文，使用你的力量驾驭他！";
 wupin_equip_swordfly.type = 3;
 wupin_equip_swordfly.efSum = 3;
 wupin_equip_swordfly.ef[0].a = 2;
 wupin_equip_swordfly.ef[0].s = 6;
 wupin_equip_swordfly.ef[1].a = 1;
 wupin_equip_swordfly.ef[1].s = 10;
 wupin_equip_swordfly.ef[2].a = 4;
 wupin_equip_swordfly.ef[2].s = 3;
 
 wupin_equip_fuspeed.name = "速度护符";
 wupin_equip_fuspeed.detail = "低于阻力，让你的敏捷和攻击速度小幅度提升。";
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
 char *b = "未知属性";
 switch(a){
  case 1:
   b = "生命上限";
   break;
  case 2:
   b = "攻击力";
   break;
  case 3:
   b = "敏捷";
   break;
  case 4:
   b = "攻击速度";
   break;
  case 5:
   b = "格挡";
   break;
 }
 return b;
}

int wupinAdd(struct _WupinL* wl){
 int ok = 0;
 int i;
 // 只找同类的物品（叠加）
 for(i = 0; !ok && i < WUPIN_BAG_MAX; i ++){
  if(wupins[i].sum > 0){
   if(wupins[i].wupin == wl->wupin){
    wupins[i].sum += wl->sum;
    wl->sum = 0;
    ok = 1;
   }
  }
 }
 // 还不行就放入空的格子（嘿嘿，简单为妙）
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


// 重新计算武器的效益（戴上或者卸下装备时触发）
void wupinEqReCalcu(){
 Role *r = &main_role;
 int i, j, s;
 // 主角自身属性
 r->hp = main_role_self_hp;
 r->atk = main_role_self_atk;
 r->def = main_role_self_def;
 r->moveCost = main_role_self_moveCost;
 r->attackCost = main_role_self_attackCost;
 // 穷举收益
 for(i = 0; i < WUPIN_EQUIP_MAX ; i ++){
  if(wupin_eq[i].sum > 0){
   for(j = 0; j < wupin_eq[i].wupin->efSum; j ++){
    s = wupin_eq[i].wupin->ef[j].s;
    switch(wupin_eq[i].wupin->ef[j].a){
     case 1: // "生命值";
      r->hp += s;
      break;
     case 2: // "攻击力";
      r->atk += s;
      break;
     case 3: // "敏捷";
      r->moveCost -= s;
      break;
     case 4: // "攻击速度";
      r->attackCost -= s;
      break;
     case 5: // "格挡";
      r->def += s;
      break;
    }
   }
  }
 }
 // 去掉不合法参数
 if(r->moveCost < 1) r->moveCost = 1;
 if(r->attackCost < 1) r->attackCost = 1;
 if(r->hpNow > r->hp) r->hp = r->hpNow;
}

// 物品使用
void wupinSetEf(struct _WupinL* wl){
 Role *r = &main_role;
 int ds;
 char dc[100];
 // 使用和添加能力
 for(int i = 0; i < wl->wupin->efSum; i ++){
  switch(wl->wupin->ef[i].a){
  case 1: // "生命值";
   ds = wl->wupin->ef[i].s;
   if(r->hpNow + ds > r->hp){
    ds = r->hp - r->hpNow;
   }
   r->hpNow += ds;
   sprintf(dc, "治疗%d生命值！", ds);
   toast(dc, 0);
   break;
  case 2: // "攻击力";
   break;
  case 3: // "敏捷";
   break;
  case 4: // "攻击速度";
   break;
  case 5: // "格挡";
   break;
  default: // 特定效果
   static int ifk = 0;
   if(wl->wupin == &(wupin_w_tp)){
    if(ifk < 3){
     ifk ++;
     toast("暂未开发（哎呀！本来想带你飞的～）", 0);
    }else if(ifk < 10){
     ifk ++;
     toast("都说了没开发，你还点使用", 0);
    }else{
     ifk ++;
     toast("你赢了……得，您继续点吧……", 0);
    }
    
   }
   break;
  }
 }
 // 物品损耗
 wl->sum --;
}

// 根据点击的xy获取wupin的索引
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
 // 名称
 setTextSize(1, 45);
 dtext(wl->wupin->name, x + 30, y + 10, 250, 250, 250, 0, 1);
 // 介绍，如果是武器会给出额外信息
 if(wl->wupin->type ==3){
  setTextSize(1, 30);
  for(i = 0; i < wl->wupin->efSum; i ++){
   sprintf(de, "+ %d点 %s", wl->wupin->ef[i].s, wupinGetEfName(wl->wupin->ef[i].a));
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
 dtext(wl->wupin->type != 3 ? "使用" : (equiped?"卸下":"装备"), x + 20, y + h - 60, 250, 250, 250 ,0,1);
 dtext("丢弃", x + 150, y + h - 60, 250, 250, 250 ,0,1);
 dtext("返回", x + w - 100, y + h - 60, 250, 250, 250 ,0,1);
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
        sc = "药";
        break;
       case 2:
        sc = "纸";
        break;
       case 3:
        sc = "器";
        break;
       default:
       sc = "？";
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
  // 详细信息
  int equiped = (wupin_eq_sel != -1);
  if(equiped){
   wl = &(wupin_eq[wupin_eq_sel]);
  }else{
   wl = &(wupins[wupins_sel]);
  }
  wupinDrawDetail(wl,equiped,dx-10, dy-10-d, d*xs+20, d*ys+d+20);
 }
}


// 画在地上的物品
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
     sc = "药";
     break;
    case 2:
     sc = "纸";
     break;
    case 3:
     sc = "器";
     break;
    default:
     sc = "？";
     break;
   }
   setTextSize(1, d/2);
   drect(x + d/5, y + d/5, d*3/5, d*3/5, 200, 200, 0);
   dtext(sc, x + d/4, y + d/4, 0, 0, 180, 0, 1);
  }
 }
}

// 添加地上的物品
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

// 随机产生地上的物品
void wupinGroundRand(int level, int sum, struct _Wupin* w){
 Room *r;
 int sc = 0;
 for(int i = 0; i < sum; i ++){
  r = mapFindRoomRand(&(game_now.map), level);
  if(r != NULL){
   if(sc > WUPIN_GROUND_MAX){
    printf("ERROR 地上物品过多，请修改宏或者减少物品");
    exit();
   }
   wupinAddGround(w, r->x + 1 + rand()%(r->w - 2), r->y + 1 + rand()%(r->h - 2));
   sc ++;
  }else{
   break;
  }
 }
 printf("○ 产生[%s]物品%d个\n", w->name, sc);
}

// 捡物品
void wupinGroundGet(){
 char cs[100];
 for(int i = 0; i < WUPIN_GROUND_MAX; i ++){
  if(wupin_ground[i].wl.sum > 0){
   if((main_role.x == wupin_ground[i].x) * (main_role.y == wupin_ground[i].y)){
    if(wupinAdd(&(wupin_ground[i].wl))){
      sprintf(cs, "你得到了%s", wupin_ground[i].wl.wupin->name);
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
    // 卸下装备
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