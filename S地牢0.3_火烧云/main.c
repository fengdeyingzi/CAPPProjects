/*
★★ 程序名：S地牢
★★ 完成度：40%
★★ 版  本：0.3
★★ 作  者：火烧云(Culosic)
★★ 类  型：探险、闯关、策略、回合制、战棋
★★ 需  求：学习、仿照手游《像素地牢》，但是
       不使用图片。地图随机生成，各种
       卷轴、药品使用，各种装备，还有丰富技
       能，强大boss等你来战。
★★ 开发步骤：
       1.随机地图的制作
       2.人物和战棋回合设计
       3.装备和物品的使用
       4.界面优化
★★ 操作说明：
       ★点击图标“图”打开或关闭小地图
       ★点击图标“物”打开或关闭背包
       ★点击地图即可移动或攻击
       ★点击返回键退出游戏

★★ 欢迎游戏爱好者加入
       ★[游戏开发]影子俱乐部
       ★群号码：496717720

★★ 手机c爱好者聚集地
       ★影子俱乐部
       ★群号码：370468001

★★ 我的QQ
       ★我好友较少，只加同好
       ★爱游戏制作、网页制作的加
       ★2268881308

★★ 代码
       ★代码量： 2500左右
       ★不一定好，仅供参考
       ★A*也是假的。。（害怕）

2017/2/6-2017/2/12 by 火烧云

*/

#include <base.h>
#include "base.h"
#include <exb.h>
#include <android.h>
#include <graphics.h>

#include "map.h"
#include "aStar.h"
#include "role.h"
#include "wupin.h"
#include "game.h"

void helloworld(){
 int _SCRW,_SCRH;
 _SCRW = 720*2;
 _SCRH = _SCRW * SCRH / SCRW;
 setscrsize(_SCRW, _SCRH);
 
 Map map;
 mapInit(&map);
 
 cls(0,0,0);
 mapDraw(&map, 0, 0);
 ref(0,0,SCRW,SCRH);
}


int init(){
 gameInit();
 toast("火烧云作品(v0.2)", 1);
 gameStart(80);
 return 0;
}


int event(int type, int p1, int p2){
 gameEvent(type,p1,p2);
 return 0;
}

int pause()
{
    return 0;
}

int resume()
{
    return 0;
}
 