/*
程序名：S水面
作者：火烧云
说明：模仿水面物理，硬币掉入水中，拖动硬币也可以和水面交互。

    之前玩了steam游戏《GRIS》，下雨的那关印象深刻，于是就自己弄了下水面效果。。。
    开始是直接用正弦波做的，弄出来中间位置很奇怪。（由于用的对称的正弦波，在触发位置的左边和右边的速度变化不平滑）
    后面看了教程，也是很迷糊，最后弄出个小程序，虽然没啥意义，但还可以吧，动了次手，嘿嘿。

2020-6-26 早上
*/

#include <base.h>
#include <graphics.h>
#include <math.h>

// 预期帧率
#define EFPS 60
// 画布宽度
#define CCRW 800
// 水面单元宽度
#define WATER_PX 5
#define WATER_SURFACE_H 10
// 硬币大小
#define COIN_R 80

// 物理、材质参数。
const float gravity = 5000;        // 重力加速度
const float coin_bounce = -0.4;    // 硬币反弹的动量系数
const float coin_resist = -0.002;  // 硬币在水里的阻力加速度
const float water_fill = 0.5;      // 入水动量系数
const float water_spread = 0.25;   // 水浪传播系数(0-0.5)
const float water_bounce = -0.03;  // 水浪弹力系数
const float water_resist = -1;     // 水浪阻力系数
const float water_stick = 0.3;     // 水浪传播范围

// 定时器相关。
int32 timer;
int32 currentT;

// 硬币相关。
float coin_x = CCRW / 2;
float coin_y = COIN_R * 2 + 10;
float coin_vx = 0;
float coin_vy = 0;
float coin_dragging = 0;

// 用于存储所有“水柱”的实时动量，计算各个水柱之间的相互作用。
int part_count = CCRW / WATER_PX;
float part_v[CCRW / WATER_PX];
float part_y[CCRW / WATER_PX];
float part_left[CCRW / WATER_PX];
float part_right[CCRW / WATER_PX];

// 帧率相关
const float fps_gap = 2; // 刷新间隔，单位：秒
float fps_t = -1;
char fps[100];

// 逐帧计算并渲染水面。
void draw(int32 data)
{
  int drawT = getuptime();
  float center_y = SCRH / 2;
  float delta_time = (drawT - currentT) / 1000.0;
  currentT = drawT;

  // 计算硬币位置、速度。
  if (!coin_dragging)
  {
    coin_x += coin_vx * delta_time;
    coin_y += coin_vy * delta_time;
  }
  if (!coin_dragging)
  {
    coin_vy += gravity * delta_time;
  }

  // 水中阻力
  int coll_i = coin_x / WATER_PX;
  if (coin_vy != 0 && coin_y + COIN_R > center_y + part_y[coll_i])
  {
    float delta_x = (coin_vy > 0 ? coin_resist : -coin_resist) * coin_vx * coin_vx * delta_time;
    float delta_y = (coin_vy > 0 ? coin_resist : -coin_resist) * coin_vy * coin_vy * delta_time;
    coin_vx = abs(coin_vx) > abs(delta_x) ? coin_vx + delta_x : 0;
    coin_vy = abs(coin_vy) > abs(delta_y) ? coin_vy + delta_y : 0;
    if (coin_y - COIN_R < center_y && coin_y + COIN_R > center_y)
    {
      part_y[coll_i] += coin_vy * water_fill;
    }
  }

  // 碰撞
  if (coin_x - COIN_R < 0)
  {
    coin_x = COIN_R;
    coin_vx *= coin_bounce;
    if (abs(coin_vx) < 10)
    {
      coin_vx = 0;
    }
  }
  else if (coin_x + COIN_R > SCRW)
  {
    coin_x = SCRW - COIN_R;
    coin_vx *= coin_bounce;
    if (abs(coin_vx) < 10)
    {
      coin_vx = 0;
    }
  }
  if (coin_y - COIN_R < 0)
  {
    coin_y = COIN_R;
    coin_vy *= coin_bounce;
    if (abs(coin_vy) < 10)
    {
      coin_vy = 0;
    }
  }
  else if (coin_y + COIN_R > SCRH)
  {
    coin_y = SCRH - COIN_R;
    coin_vy *= coin_bounce;
    if (abs(coin_vy) < 100)
    {
      coin_vy = 0;
    }
  }

  // 计算水面位置、速度。
  for (int i = 0; i < part_count; i++)
  {

    part_v[i] += water_bounce * part_y[i] * delta_time;
    part_v[i] += water_resist * part_v[i] * delta_time;
    part_y[i] += part_v[i];
  }

  // 参考：https://gamedevelopment.tutsplus.com/tutorials/make-a-splash-with-dynamic-2d-water-effects--gamedev-236
  // 计算各个水柱之间的相互作用。具体算法我还是没搞懂。。。
  for (int j = 0; j < part_count * water_stick; j++)
  {
    for (int i = 0; i < part_count; i++)
    {
      if (i - 1 >= 0)
      {
        part_left[i] = water_spread * (part_y[i] - part_y[i - 1]);
        part_v[i - 1] += part_left[i];
      }
      if (i + 1 < part_count)
      {
        part_right[i] = water_spread * (part_y[i] - part_y[i + 1]);
        part_v[i + 1] += part_right[i];
      }
    }
    for (int i = 0; i < part_count; i++)
    {
      if (i - 1 >= 0)
      {
        part_y[i - 1] += part_left[i];
      }
      if (i + 1 < part_count)
      {
        part_y[i + 1] += part_right[i];
      }
    }
  }

  cls(60, 60, 60);

  // 画硬币。
  drawCir(coin_x, coin_y, COIN_R, 0xffffffff);
  drawCir(coin_x, coin_y, COIN_R - 7, 0xffcccccc);
  drawCir(coin_x, coin_y, COIN_R - 10, 0xfff3f3f3);

  // 画水柱，形成水面。
  for (int i = 0; i < part_count; i++)
  {
    float x = i * WATER_PX;
    float y = part_y[i];
    drawRect(x, center_y + y, WATER_PX, center_y - y, 0x445f99ee);
    drawRect(x, center_y + y - WATER_SURFACE_H, WATER_PX, WATER_SURFACE_H, 0xaa5faaff);
  }

  // FPS
  if (fps_t == -1 || fps_t > fps_gap)
  {
    sprintf(fps, "FPS:%d", (int)(1 / delta_time + 0.5));
    fps_t = 0;
  }
  else
  {
    fps_t += delta_time;
  }
  dtext(fps, 30, 30, 255, 255, 255, 0, 1);

  ref(0, 0, SCRW, SCRH);
}

void coin_event(int type, int p1, int p2)
{
  if (type == MS_DOWN)
  {
    if ((p1 - coin_x) * (p1 - coin_x) + (p2 - coin_y) * (p2 - coin_y) < COIN_R * COIN_R)
    {
      coin_dragging = 1;
    }
  }
  else if (type == MS_MOVE)
  {
    if (coin_dragging)
    {
      float coin_x_old = coin_x;
      float coin_y_old = coin_y;
      coin_x = p1;
      coin_y = p2;
      coin_vy = (coin_y - coin_y_old) / 60 * 1000.0;
      coin_vx = (coin_x - coin_x_old) / 60 * 1000.0;
    }
  }
  else if (type == MS_UP)
  {
    coin_dragging = 0;
  }
}

///////////////////////// 系统回调 //////////////////////////////
int startApp()
{
  currentT = getuptime();
  timerstart(timer, 1000.0 / EFPS, 1000.0 / EFPS, &draw, 1);
  return 0;
}

int exitApp()
{
  timerstop(timer);
  timerdel(timer);
  return 0;
}

int init()
{
  setscrsize(CCRW, CCRW * SCRH / SCRW);

  timer = timercreate();
  startApp();
  return 0;
}

int event(int type, int p1, int p2)
{
  if (type == KY_UP && p1 == _BACK)
  {
    exit();
  }
  coin_event(type, p1, p2);
  return 0;
}

int pause()
{
  timerstop(timer);
  return 0;
}

int resume()
{
  startApp();
  return 0;
}
