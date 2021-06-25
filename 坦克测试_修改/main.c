
#include <base.h>
#include <ex_game.h>
#include <exb.h>
#include <graphics.h>

/*
修改绘制逻辑
  init函数
  map_cj函数

退出时要释放内存
  exit_free函数


*/

int32 world, camera, bitmap, hero_em, bitmap_d, hero_map, hero_map1;
int32 x, y, m;
int32 timer;
int map_data[169] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
    1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0,
    0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0,
    0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0,
    0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};

int32 *sp;
int num() {
  int j = 0;
  for (int i = 0; i < 169; i++) {
    if (map_data[i] == 1) j++;
  }
  sp = malloc(sizeof(int) * j);
  return j;
}

void map_cj(int32 j) {
  world_draw(world);
  for (int i = 0; i < 169; i++) {
    if (map_data[i] == 1) {
      // sp[j-1]=sp_read("map.sprite",bitmap_d);
      //  world_addSprite(world,sp[j-1]);
      // sp_setxy(sp[j-1],i%13*34+10,i/13*34+10);
      // sp_draw(sp[j-1],camera);
      j--;
    }
  }
}

int pengzhuangyou(int x, int y) {
  if ((y - 10) % 34 == 0)
    if (map_data[(x - 10) / 34 + (y - 10) / 34 * 13 + 1] == 1)
      return 0;
    else
      return 1;
  if (map_data[(x - 10 + 2) / 34 + (y - 10) / 34 * 13 + 13 + 1] == 1) return 0;
  if (map_data[(x - 10 + 2) / 34 + (y - 10) / 34 * 13 + 1] == 1) return 0;
  return 1;
}

int pengzhuangzuo(int x, int y) {
  if ((y - 10) % 34 == 0)
    if (map_data[(x - 10 - 2) / 34 + (y - 10) / 34 * 13] == 1)
      return 0;
    else
      return 1;
  if (map_data[(x - 10 - 2) / 34 + (y - 10) / 34 * 13 + 13] == 1) return 0;
  if (map_data[(x - 10 - 2) / 34 + (y - 10) / 34 * 13] == 1) return 0;
  return 1;
}

int pengzhuangshang(int x, int y) {
  if ((x - 10) % 34 == 0)
    if (map_data[(x - 10) / 34 + (y - 10 - 2) / 34 * 13] == 1)
      return 0;
    else
      return 1;
  if (map_data[(x - 10) / 34 + (y - 10 - 2) / 34 * 13] == 1) return 0;
  if (map_data[(x - 10) / 34 + (y - 10 - 2) / 34 * 13 + 1] == 1) return 0;
  return 1;
}

int pengzhuangxia(int x, int y) {
  if ((x - 10) % 34 == 0)
    if (map_data[(x - 10) / 34 + (y - 10) / 34 * 13 + 13] == 1)
      return 0;
    else
      return 1;
  if (map_data[(x - 10) / 34 + (y - 10 + 2) / 34 * 13 + 13] == 1) return 0;
  if (map_data[(x - 10) / 34 + (y + 2 - 10) / 34 * 13 + 13 + 1] == 1) return 0;
  return 1;
}

void logoc(int data) {
  int32 k;
  cls(0, 0, 0);
  printf("logoc\n");
  if (getkeypressed(_UP) == 0 && getkeypressed(_DOWN) != 0 &&
      getkeypressed(_LEFT) != 0 && getkeypressed(_RIGHT) != 0) {
    sp_setAction(hero_em, 0);
    if (pengzhuangshang(sp_getx(hero_em), sp_gety(hero_em)) &&
        sp_gety(hero_em) > 10) {
      sp_move(hero_em, 0, -2);
    }
  }
  if (getkeypressed(_UP) != 0 && getkeypressed(_DOWN) == 0 &&
      getkeypressed(_LEFT) != 0 && getkeypressed(_RIGHT) != 0) {
    sp_setAction(hero_em, 2);
    if (pengzhuangxia(sp_getx(hero_em), sp_gety(hero_em)) &&
        sp_gety(hero_em) < 408) {
      sp_move(hero_em, 0, 2);
    }
  }
  if (getkeypressed(_LEFT) == 0) {
    sp_setAction(hero_em, 3);
    if (pengzhuangzuo(sp_getx(hero_em), sp_gety(hero_em)) &&
        sp_getx(hero_em) > 10) {
      sp_move(hero_em, -2, 0);
    }
  }
  if (getkeypressed(_RIGHT) == 0) {
    sp_setAction(hero_em, 1);
    if (pengzhuangyou(sp_getx(hero_em), sp_gety(hero_em)) &&
        sp_getx(hero_em) < 408) {
      sp_move(hero_em, 2, 0);
    }
  }
  drect(1, 1, 452, 10, 150, 150, 150);
  drect(1, 1, 10, 452, 150, 150, 150);
  drect(452, 1, 10, 452, 150, 150, 150);
  drect(1, 452, 462, 10, 150, 150, 150);
  printf("sp_draw %d %d\n",hero_em,camera);
  sp_draw(hero_em, camera);
  k = m;
  printf("map_cj\n");
  map_cj(k);
  printf("setpadtype\n");
  

  printf("%d,%d\n", sp_getx(hero_em), sp_gety(hero_em));
  ref(0, 0, SCRW, SCRH);
}

//入口函数，程序启动时开始执行
int init() {
  //调用函数helloworld

  //设置屏幕缓冲区setscrsize(442,450*SCRH/SCRW);
  setscrsize(462, 462);
  //创建世界
  m = num();
  printf("%d", m);
  world = world_create();
  printf("world_create");
  //创建相机
  camera = ca_create(0, 0, SCRW, SCRH);
printf("ca_create");
  //加载坦克和地图的图片
  bitmap = readBitmapFromAssets("tank.png");
  printf("readBitmap\n");
  //读取精灵
  hero_em = sp_read("tank.sprite", bitmap);
printf("sp_read\n");
  bitmap_d = readBitmapFromAssets("map.png");
  //世界添加精灵
  world_addSprite(world, hero_em);
  printf("addSprite\n");
  //设置世界照相机
  world_setCamera(world, camera);
printf("world_setCamera\n");
  cls(0, 0, 0);
  //显示世界
  world_draw(world);
  printf("world_draw\n");
  sp_move(hero_em, 10, 180);
  printf("sp_move\n");
  int j = 0;
  for (int i = 0; i < 169; i++) {
    if (map_data[i] == 1) {
      sp[j - 1] = sp_read("map.sprite", bitmap_d);
      world_addSprite(world, sp[j - 1]);
      sp_setxy(sp[j - 1], i % 13 * 34 + 10, i / 13 * 34 + 10);
      // sp_draw(sp[j-1],camera);
      j--;
    }
  }
printf("timercreate");
setpadtype(2);
  timer = timercreate();
  printf("timerstart");
  timerstart(timer, 30, 1, "logoc", TRUE);

  return 0;
}

// event函数，接收消息事件
int event(int type, int p1, int p2) {
  if (KY_UP == type) {
    switch (p1) {
      case _BACK:
        exit_free();
        exit();
        break;
      case _MENU:
        break;
    }
  }

  return 0;
}

//应用暂停，当程序进入后台或变为不可见时会调用此函数
int pause() { return 0; }

//应用恢复，程序变为可见时调用此函数
int resume() { return 0; }

int exit_free() {
  //释放主角
  sp_free(hero_em);
  //释放地图
  int j = 0;
  for (int i = 0; i < 169; i++) {
    if (map_data[i] == 1) {
      sp_free(sp[j - 1]);
      j--;
    }
  }
  //释放世界
  world_free(world);
  //释放相机
  ca_free(camera);
  if(timer!=0) timerdel(timer);
  //释放bitmap
  bitmapFree(bitmap_d);
  return 0;
}
