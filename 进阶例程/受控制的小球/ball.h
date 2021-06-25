

/*小球结构体*用于储存小球的信息*/
typedef struct
{
  int x;
  int y;
  int dx;  //用于控制小球横向移动
  int dy;  //用于控制小球纵向移动
  int r;
  int32 color;
}Ball;


/*绘图函数*本例中用于绘制小球并刷新屏幕*/
void draw()
{
  /*********************************
  *drawCir函数共四个参数* x,y,r,color*
  ****x,y代表圆的圆心，r代表圆的半径****
  ********color代表绘制圆的颜色*******
  *********************************/
  /*指定颜色清屏*/
  cls(0,0,0);
  
  drawCir(ball.x,ball.y,ball.r,ball.color);
  
  /*刷新一个矩形区域* SCRW,SCRH分别代表屏幕宽，高*/
  ref(0,0,SCRW,SCRH);
}


void run(int data)
{
  /*************
  *到边界了咋办?**
  **************/
  
  /*左*/
  if(ball.x<=ball.r)
  {
     ball.x=ball.r;
     /*换方向咯*/
     ball.dx=-ball.dx;
  }
  
  /*右*/
  if(ball.x>=SCRW-ball.r)
  {
     ball.x=SCRW-ball.r;
     /*换方向咯*/
     ball.dx=-ball.dx;
  }
  
  /*上*/
  if(ball.y<=ball.r)
  {
     ball.y=ball.r;
     /*换方向咯*/
     ball.dy=-ball.dy;
  }
  
  /*下*/
  if(ball.y>=SCRH-ball.r)
  {
     ball.y=SCRH-ball.r;
     /*换方向咯*/
     ball.dy=-ball.dy;
  }
  
}



