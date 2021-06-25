
/*定义全局变量用于处理触屏事件*/
int ex, ey;

/*触屏按下*/
void Down(int x,int y)
{
  /*记录被按下的位置*/
  ex=x;
  ey=y;
  
  ball.r+=10;
  draw();
}

/*触屏释放*/
void Up(int x,int y)
{
  ball.r-=10;
  draw();
}

/*滑动屏幕*/
void Move(int x,int y)
{
  /*简单实现运动*/
  ball.x+=x-ex;
  ball.y+=y-ey;
  draw();
  
  /*哈哈，球还是被困在屏幕内*/
  run(0);
  
  ex=x;
  ey=y;
}


/*处理消息*/
void ballEvent(int type,int x,int y)
{
  
  switch(type)
  {
    case MS_DOWN:
    Down(x,y);
    break;
    
    case MS_UP:
    Up(x,y);
    break;
    
    case MS_MOVE:
    Move(x,y);
    break;
  }
}