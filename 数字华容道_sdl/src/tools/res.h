#ifndef _RES_H_
#define _RES_H_
#include "../api/base.h"
#include "../api/graphics.h"

/******资源类型********
*图片，字体，声音，定时器*
**********************/
typedef enum resType
{
 tImg = 0,
 tFnt,
 tSnd,
 tTim,
 tStr,
 tSpr,
 tJsn,
 tObj
}ResType;

//资源
typedef struct res
{
 int32 id;
 char*path;
 ResType type;
}Res;

//资源链
struct
{
 Res res[300];
 int num;
}ResList;

//载入资源
extern  void*loadRes(char*path,ResType type);
extern void freeOneRes(Res*res,
 ResType type);
//释放资源资源
extern void freeRes();
//获取资源
extern Res*getRes(char*path,ResType type);

#endif


