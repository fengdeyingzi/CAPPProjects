#ifndef CHECK_H_INCLUDED
#define CHECK_H_INCLUDED

#include <graphics.h>
#include <game_math.h>


//控件结构体
typedef struct {
  char *name;
  int isCheck;         //控件状态
  int x;          //控件x坐标
  int y;          //控件y坐标
  int32 down;     //控件按下贴图
  int32 b0;       //控件非勾选贴图
  int32 b1;       //控件勾选贴图
}Check;

/*控件大小是固定的,修改屏幕大小控件大小会跟着改变*/


/*  创建BOX
    x  控件x坐标
    y  控件y坐标
    返回值:
      失败  NULL
      成功  控件句柄*/
void *checkbox_create(int x,int y){
  Check * New = malloc(sizeof(Check));
  //分配内存
  
  if((New->down = readBitmapFromAssets("check/down-box.png")) <= 0){
    printf("Draw_box[check/down-box.png]\n");
    free(New);
    return NULL;}
  if((New->b0 = readBitmapFromAssets("check/Box-0.png")) <= 0){
    printf("Draw_box[check/Box-0.png]\n");
    free(New);
    return NULL;}
  if((New->b1 = readBitmapFromAssets("check/Box-1.png")) <= 0){
    printf("Draw_box[check/Box-1.png]\n");
    free(New);
    return NULL;}
  //打开需要的贴图失败释放内存并返回NULL
  
  New->isCheck = 0;  //初始化为未勾选状态
  New->x = x;   //初始化x坐标
  New->y = y;   //初始化y坐标
  return New;   //返回
}


/*  创建CIR
    x  控件x坐标
    y  控件y坐标
    返回值:
      失败  NULL
      成功  控件句柄*/
void * check_cir_create(int x,int y){
  Check * New = malloc(sizeof(Check));
  //分配内存
  
  if((New->down = readBitmapFromAssets("check/down-Cir.png")) <= 0){
    printf("Draw_box[check/down-Cir.png]\n");
    free(New);
    return NULL;}
  if((New->b0 = readBitmapFromAssets("check/Cir-0.png")) <= 0){
    printf("Draw_box[check/Cir-0.png]\n");
    free(New);
    return NULL;}
  if((New->b1 = readBitmapFromAssets("check/Cir-1.png")) <= 0){
    printf("Draw_box[check/Cir-1.png]\n");
    free(New);
    return NULL;}
  //打开需要的贴图失败释放内存并返回NULL
  
  New->isCheck = 0;   //初始化为未勾选状态
  New->x = x;    //初始化x坐标
  New->y = y;    //初始化y坐标
  return New;    //返回
}


/*  创建BUTTON
    x  控件x坐标
    y  控件y坐标
    返回值:
      失败  NULL
      成功  控件句柄*/
void * check_button_create(int x,int y){
  Check * New = malloc(sizeof(Check));
  //分配内存
  
  if((New->down = readBitmapFromAssets("check/down-Rect.png")) <= 0){
    printf("Draw_box[check/down-Rect.png]\n");
    free(New);
    return NULL;}
  if((New->b0 = readBitmapFromAssets("check/Rect-0.png")) <= 0){
    printf("Draw_box[check/Rect-0.png]\n");
    free(New);
    return NULL;}
  if((New->b1 = readBitmapFromAssets("check/Rect-1.png")) <= 0){
    printf("Draw_box[check/Rect-1.png]\n");
    free(New);
    return NULL;}
  //打开需要的贴图失败释放内存并返回NULL
  
  New->isCheck = 0;  //初始化为未勾选状态
  New->x = x;   //初始化x坐标
  New->y = y;   //初始化y坐标
  return New;   //返回
}



/*  绘制控件ALL
    id  控件句柄*/
void check_draw(Check * id){
  if(id == NULL)
    return;
  //控件等于NULL直接返回
  
  if(id->id == 0)  //绘制控件背景贴图
    drawBitmap(id->b0,id->x,id->y);
  if(id->id == 1){ //绘制控件背景与勾选贴图
    drawBitmap(id->b0,id->x,id->y);
    drawBitmap(id->b1,id->x,id->y);
  }
}



/*  监控控件BOX
    id  控件句柄
    type  应用事件函数事件
    x     应用事件函数屏幕x坐标
    y     应用事件函数屏幕y坐标
    返回值:
      按钮已删除 -1
      非勾选     0
      勾选       1*/
int checkbox_event(Check * id,int type,int x,int y){
   if(id == NULL)
      return -1;
   //控件等于NULL返回-1

   if(game_rect(x,y,id->x+10,id->y+10,60,60)){
   //x y点在控件矩形内
      if(type == MS_DOWN){
         drawBitmap(id->down,id->x,id->y);
         ref(id->x,id->y,80,80);
      }
      //按下显示按下效果
      if(type == MS_UP)id->id=(id->id==0)?1:0;
      //释放更改状态
   }
   return id->id;//返回控件状态
}


/*懒得写注释了，每个都判断是不是等于NULL是因为你删掉了控件之后显示或者监控程序会出错，因为内存释放了，所以先判断是不是删掉了，还有就是用的时候要注意，-1是不存在 0是关闭 1是打开*/





/*  监控控件CIR
    id  控件句柄
    type  应用事件函数事件
    x     应用事件函数屏幕x坐标
    y     应用事件函数屏幕y坐标
    返回值:
      按钮已删除 -1
      非勾选     0
      勾选       1*/
int checkcir_event(Check * id,int type,int x,int y){
  
   if(id == NULL)
     return -1;
   if(game_cir(x,y,id->x+40,id->y+40,20)){
      if(type == MS_DOWN){
         drawBitmap(id->down,id->x,id->y);
         ref(id->x,id->y,80,80);
      }
      if(type == MS_UP)id->isCheck=(id->isCheck==0)?1:0;
   }
   
   return id->id;
}


/*  监控控件BUTTON
    id  控件句柄
    type  应用事件函数事件
    x     应用事件函数屏幕x坐标
    y     应用事件函数屏幕y坐标
    返回值:
      按钮已删除 -1
      非勾选     0
      勾选       1*/
int check_button_event(Check * id,int type,int x,int y){
   if(id == NULL)
     return -1;
   
   if(game_rect(x,y,id->x,id->y,100,60)){
      if(type == MS_DOWN){
         drawBitmap(id->down,id->x,id->y);
         ref(id->x,id->y,100,60);
      }
      if(type == MS_UP)id->isCheck=(id->isCheck==0)?1:0;
   }
   
   return id->id;
}



/*  删除控件
    id  控件句柄
    返回值:
      空地址*/
void *check_free(Check * id){
  if(id == NULL)
    return id;
  bitmapFree(id->down);
  bitmapFree(id->b0);
  bitmapFree(id->b1);
  free(id);
  return NULL;
}




#endif