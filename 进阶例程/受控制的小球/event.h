
/*����ȫ�ֱ������ڴ������¼�*/
int ex, ey;

/*��������*/
void Down(int x,int y)
{
  /*��¼�����µ�λ��*/
  ex=x;
  ey=y;
  
  ball.r+=10;
  draw();
}

/*�����ͷ�*/
void Up(int x,int y)
{
  ball.r-=10;
  draw();
}

/*������Ļ*/
void Move(int x,int y)
{
  /*��ʵ���˶�*/
  ball.x+=x-ex;
  ball.y+=y-ey;
  draw();
  
  /*���������Ǳ�������Ļ��*/
  run(0);
  
  ex=x;
  ey=y;
}


/*������Ϣ*/
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