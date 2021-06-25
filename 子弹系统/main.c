//加载系统头文件base.h

#include <base.h>
#include <android.h>
#include <ex_math.h>
#include <graphics.h>

#include "dex.h"

#define PADDEX "assets://keyPad.dex"
#define PADCLASS "com.xl.dex.xl_keyPad"

typedef struct {
  int x;
  int y;

  int dir;  //方向
  int sp;   //速度
} Bult;     //子弹

typedef struct LinkBult {
  Bult def;    //默认子弹属性
  Bult* bult;  //子弹
  struct LinkBult* ne;
} LinkBult;  //子弹链

//初始化链
void initLinkBult(LinkBult* link) {
  link->bult = NULL;
  link->ne = NULL;

  link->def.x = SCRW / 2;
  link->def.y = SCRH / 2;
  link->def.dir = 0;
  link->def.sp = 10;
}

//绘制单个子弹
void drawBult(Bult* bult) {
  if (bult != NULL) drawCir(bult->x, bult->y, 20, 0xff805060);
}

//绘制子弹链
void drawLinkBult(LinkBult* link) {
  LinkBult* next = link;
  while (next != NULL) {
    drawBult(next->bult);
    next = next->ne;
  }
}

//发射子弹
void shootBult(LinkBult* link) {
  //创建
  Bult* bult = malloc(sizeof(Bult));
  bult->x = link->def.x;
  bult->y = link->def.y;
  bult->dir = link->def.dir;
  bult->sp = link->def.sp;

  //套壳
  LinkBult* lb = malloc(sizeof(LinkBult));
  lb->bult = bult;
  lb->ne = NULL;

  //遍历
  LinkBult* next = link;
  while (next->ne != NULL) next = next->ne;

  //连接
  next->ne = lb;
}

//销毁子弹
void destroyBult(LinkBult* link, Bult* bult) {
  /*
  LinkBult*next = link;
  if(next->bult==bult)
  {
   link=next->ne;
   free(next->bult)
   free(next);
   return ;
  }

  while(next->ne!=NULL)
  {
         next = next->ne;
  if(next->bult==bult)
  {
   link=next->ne;
   free(next->bult)
   free(next);
   return ;
  }
  }**/
}

//释放子弹
void freeBult(Bult* bult) { free(bult); }

//释放子弹链
void freeLinkBult(LinkBult* link) {
  LinkBult* next = link;
  LinkBult* temp = NULL;
  while (next != NULL) {
    free(next->bult);
    temp = next->ne;
    free(next);
    next = temp;
  }
}

//子弹运动
void bultRun(Bult* bult) {
  if (bult != NULL) {
    int dx = bult->x;
    int dy = bult->y - bult->sp;
    toSpin(bult->x, bult->y, bult->sp, bult->sp, bult->dir, &dx, &dy);
    bult->x = dx;
    bult->y = dy;
  }
}

//子弹链运动
void linkBultRun(LinkBult* link) {
  LinkBult* next = link;
  while (next != NULL) {
    bultRun(next->bult);
    next = next->ne;
  }
}

//发射器
LinkBult* gun;
int32 timer;

_DEX* pad;

void gameRun(int data) {
  cls(0xf4, 0xf4, 0xf4);
  linkBultRun(gun);
  drawLinkBult(gun);
  ref(0, 0, SCRW, SCRH);
}

//入口函数，程序启动时开始执行
int init() {
  cls(0xf4, 0xf4, 0xf4);
  setContextView("main.xml");
  printf("setContextView\n");
  pad = dex_create(PADDEX, PADCLASS);
  printf("dex_create\n");
  
  char* text = dex_put(pad, "addView 100");
  printf("dex_put\n");
  if (text != NULL) free(text);

  //初始化
  gun = malloc(sizeof(LinkBult));
  printf("initLinkBult\n");
  initLinkBult(gun);
  printf("shootBult\n");
  shootBult(gun);
  printf("drawLinkBult\n");
  drawLinkBult(gun);
  //启动程序
  timer = timercreate();
  printf("timercreate\n");
  timerstart(timer, 50, 0, "gameRun", 1);
  ref(0, 0, SCRW, SCRH);
  return 0;
}

// event函数，接收消息事件
int event(int type, int p1, int p2) {
  if (14 == type) {
    gun->def.dir = p1;
    printf("%d\n", p1);
  }

  if (KY_DOWN == type) {
    printf("%d %d %d\n", type, p1, p2);
    if (p1 == 11) {
      shootBult(gun);
    }
  }

  if (KY_UP == type) {
    switch (p1) {
      case _BACK:
        if (pad != NULL) dex_free(pad);
        if (timer != 0) timerdel(timer);
        if(gun!=NULL)
        freeLinkBult(gun);
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
