#ifndef XGUI_BUTTON_H
#define XGUI_BUTTON_H

//按钮结构体
typedef struct
{
 char*name;//控件名字
 int id;//按钮id
 
 int type;//按钮状态，按下1，释放0，隐藏-1
 int isshow;//是否显示
 int isdown;//是否按下
 
 int x;//按钮位置x
 int y;//按钮位置y
 int w;//按钮宽度
 int h;//按钮高度
 
 char*text;//按钮文字
 int textx;//文字x坐标
 int texty;//文字y坐标
 int textc;//文字颜色
 
 int bkgc;//按钮背景颜色
 int fram;//按钮边缘颜色
 
 int bkgc2;//按下
 int fram2;//按下
 int32 timer;//回调定时器
 int draw_mode;//刷新模式
 void*onclick;//函数回调
}Button;

int id = 0;
//新增按钮
void*btn_create(char*text,int x,int y,int w,int h);
//设置按钮id
void btn_setid(Button*btn,int id);
//获取按钮id
int btn_getid(Button*btn);
//绘制按钮
void btn_draw(Button*btn);
//设置按钮文本
void btn_settext(Button*btn,char*text);
//设置模式
void btn_setref(Button*btn,int mode);
//设置回调函数
void btn_setonclick(Button*btn,void*click);
//显示按钮
int btn_show(Button*btn);
//隐藏按钮
int btn_hide(Button*btn);
//按钮是否显示
int btn_isshow(Button*btn);
//按钮event事件
void btn_event(Button*btn,int type,int p1,int p2);
//按钮点击判断
int btn_impact(Button*btn,int x,int y);
//释放按钮
void btn_free(Button*btn);

/*-----------------------------------*/

//新增按钮
void*btn_create(char*text,int x,int y,int w,int h)
{
 int32 fw,fh;
 Button*btn;
 btn = malloc(sizeof(Button));
 memset(btn,0,sizeof(Button));
 btn->name = "Button";
 btn->text = NULL;
 btn_settext(btn,text);
 btn->x = x;
 btn->y = y;
 btn->w = w;
 btn->h = h;
 btn->type = 0;
 btn->id = -1;
 btn->fram = 0x8044A8F0;
 btn->bkgc = 0x80E6EEF5;
 btn->fram2 = 0xF0A8A8A8;
 btn->bkgc2 = 0xA044A8F0;
 id++;
 textwh(text,0,1,&fw,&fh);
 btn->textx = x+(w-fw)/2;
 btn->texty = y+(h-fh)/2;
 btn->textc = 0xffffffff;
 btn->timer = timercreate();
 btn->isdown = 0;
 btn->isshow = 1;
 btn->draw_mode = 0;
 return btn;
}

//设置按钮id
void btn_setid(Button*btn,int id)
{
 btn->id = id;
}

//获取按钮id
int btn_getid(Button*btn)
{
 return btn->id;
}

//显示按钮 参数：按钮结构体指针
void btn_draw(Button*btn)
{
 if(btn->isshow)
 {
  if(btn->isdown)
  {
   //绘制一个矩形
   drawRect(btn->x,btn->y,btn->w,btn->h,btn->fram2);
   drawRect(btn->x+4,btn->y+4,btn->w-8,btn->h-8,btn->bkgc2);
  }
  else
  {
   //绘制一个矩形
   drawRect(btn->x,btn->y,btn->w,btn->h,btn->fram);
   drawRect(btn->x+4,btn->y+4,btn->w-8,btn->h-8,btn->bkgc);
  }
  //绘制文字
  dtext(btn->text,btn->textx,btn->texty,btn->textc>>16&0xff,btn->textc>>8&0xff,btn->textc&0xff,0,1);
 }
}

//设置按钮文字 参数：按钮结构体指针 新的按钮文字
void btn_settext(Button*btn,char*text)
{
 //申请内存
 int len=sizeof(char)*strlen(text)+1;
 char*txt = malloc(len);
// memset(txt, '\0', len);
 sprintf(txt,"%s",text);
 if(btn->text!=NULL)
 	free(btn->text);
 btn->text = txt;
 txt=NULL;
 
 int32 fw,fh;
 textwh(text,0,1,&fw,&fh);
 //更新文字坐标
 btn->textx = btn->x+(btn->w-fw)/2;
 btn->texty = btn->y+(btn->h-fh)/2;
 //绘制刷新
 if(btn->draw_mode==0)
 {
  btn_draw(btn);
  ref(btn->x,btn->y,btn->w,btn->h);
 }
}

//设置定时器刷新模式 0非定时器刷新 1定时器刷新
void btn_setref(Button*btn,int mode)
{
 btn->draw_mode = mode;
}

//显示按钮
int btn_show(Button*btn)
{
 btn->isshow = 1;
 if(btn->draw_mode==1)
 {
  btn_draw(btn);
  ref(btn->x,btn->y,btn->w,btn->h);
 }
 return 0;
}

//隐藏按钮
int btn_hide(Button*btn)
{
 btn->isshow = 0;
 btn->isdown = 0;
 return 0;
}

//按钮是否显示
int btn_isshow(Button*btn)
{
 return btn->isshow;
}

//设置点击回调函数 由于手机C不支持函数指针，所以采用char*，函数原型为定时器的回调函数void click_ok(int id)
void btn_setonclick(Button*btn,void*click)
{
 btn->onclick = click;
}

//按钮event事件
void btn_event(Button*btn,int type,int p1,int p2)
{
 if(type==MS_DOWN)
 {
  if(btn_impact(btn,p1,p2))
  {
   btn->isdown = 1;
   if(btn->draw_mode==0)
   {
    btn_draw(btn);
    ref(btn->x,btn->y,btn->w,btn->h);
   }
   //printf("down");
  }
 }
 if(type==MS_UP)
 {
  //if(btn_impact(btn,p1,p2))
  {
   if(btn->isdown)
   {
    btn->isdown = 0;
    if(btn->draw_mode==0)
    {
     btn_draw(btn);
     ref(btn->x,btn->y,btn->w,btn->h);
    }
    if(btn->onclick!=NULL)
    {
     // printf("click");
     timerstart(btn->timer,10,btn->id,btn->onclick,0);
    }
   }
  }
 }
}


//判断按钮点击事件 参数：按钮指针 触屏x坐标 触屏y坐标
//返回值：TRUE(1)成功 FALSE(0)失败
int btn_impact(Button*btn,int x,int y)
{
 if(btn->isshow)
 {
  if(x>btn->x&&x<btn->x+btn->w&&y>btn->y&&y<btn->y+btn->h)
  	return 1;
 }
 return 0;
}

//释放按钮内存
void btn_free(Button*btn)
{
 if(btn->text!=NULL)
 	free(btn->text);
 free(btn);
}

#endif

