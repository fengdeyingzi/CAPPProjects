
typedef struct
{
  int x;
  int y;
  int w;
  int h;
  
  int isDown;
}Btn;


/*生成一个按钮，返回按钮指针*/
void* newBtn(int x,int y,int w,int h)
{
  Btn* btn=malloc(sizeof(Btn));
  btn->x=x;
  btn->y=y;
  btn->w=w;
  btn->h=h;
  btn->isDown=0;
  
  return btn;
}

/*绘制按钮*/
void drawBtn(Btn* btn)
{
  cls(0,0,0);
  /*按下效果*/
  if(btn->isDown==1)
  {
    drect(btn->x-5,btn->y-5,btn->w+10,btn->h+10,200,100,100);
  }
  /*释放效果*/
  else
  {
    drect(btn->x,btn->y,btn->w,btn->h,100,100,100);
  }
  ref(0,0,SCRW,SCRH);
}






