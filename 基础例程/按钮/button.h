/*
  按钮控件
　by：风的影子
*/

//按钮结构体

typedef struct 
{
int id; //按钮id
int type;//按钮状态，按下1，释放0，隐藏-1
char *text; //按钮文字
int textx; //文字x坐标
int texty; //文字y坐标
int x; //按钮位置x
int y; //按钮位置y
int w; //按钮宽度
int h; //按钮高度
}button;
int id=0;

//新增按钮
//参数分别是 按钮文字 按钮x坐标 y坐标 宽度 高度 
void* new_button(char *text,int x,int y,int w,int h)
{
int fw,fh;
 button *btn;
btn=malloc(sizeof(button));
btn->text=text;
btn->x=x; 
btn->y=y;
btn->w=w;
btn->h=h;
btn->type=0;
btn->id=id;id++;
textwh(text,0,1,&fw,&fh);
btn->textx=x+(w-fw)/2;
btn->texty=y+(h-fh)/2;
return btn;
}

//显示按钮 参数：按钮结构体指针
void button_draw(button *btn)
{

if(btn->type!=-1)
  {
   //绘制一个矩形
drect(btn->x+2,btn->y+2,btn->w-4,btn->h-4,68-btn->type*40,168-btn->type*40,240-btn->type*40);
drect(btn->x+4,btn->y+4,btn->w-8,btn->h-8,230,238,245);
  //绘制文字
dtext(btn->text,btn->textx,btn->texty,50,50,50,0,1);
  }
}

//设置按钮文字 参数：按钮结构体指针 新的按钮文字
void button_settext(button *btn,char *text)
{
btn->text=text;
draw_button(btn);
ref(btn->x,btn->y,btn->w,btn->h);
}


//判断按钮点击事件 参数：按钮指针 触屏x坐标 触屏y坐标
//返回值：TRUE(1)成功 FALSE(0)失败
int button_impact(button *btn,int x,int y)
{
if(x>btn->x && x<btn->x+btn->w && y>btn->y && y<btn->y+btn->h)
return 1;
else return 0;


}

//释放按钮内存
void button_free(button *btn)
{
 free(btn);
}


