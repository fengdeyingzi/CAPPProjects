#ifndef _STAGE_H_
#define _STAGE_H_

#include "base.h"
#include "graphics.h"

/*
世界  场景
做游戏专用
风的影子 制作
*/

typedef struct BODY {
    int type; //类型 0图片 1精灵 2主角 3地图 4按钮 5文本 6菜单 7进度条  6窗口
    long sprite;
    struct BODY *next;
    int32 value;
} BODY;


typedef struct {
    struct BODY *head; //世界中的物体
    struct BODY *end; //最后一个物体
    long int camera;//照相机
    int32 value; //排序值
} WORLD;



//创建世界
int32 world_create();
/*
//为世界设置摄像机
int world_setCamera(int id,int camera)
{
 WORLD *world=(void*)id;
 world->camera=(void*)camera;
 
 return 0;
}
*/

//在世界里添加一个物体
int world_addBody(int32 id, int32 body);

int world_addSprite(int32 id, int32 sprite);

//刷新世界end参数
static int world_ref(WORLD *world);

//删除一个精灵
int world_removeSprite(int32 id, int32 sprite);
int world_setCamera(long int id, long int camera);

//显示世界
int world_draw(long int id);

//设置世界显示方式

int world_rank(long int id, int type);
//世界逻辑
int world_run(long int id);


//检测x y 坐标是否点中世界里的物体，如果点中，返回被点中的物体

//检测世界内精灵是否与指定精灵发生碰撞，如果发生碰撞，返回碰撞的物体

//销毁世界
//销毁世界并不会销毁摄像机，精灵，它们需要单独销毁
int world_free(long int id);

#endif
