

/*С��ṹ��*���ڴ���С�����Ϣ*/
typedef struct
{
  int x;
  int y;
  int dx;  //���ڿ���С������ƶ�
  int dy;  //���ڿ���С�������ƶ�
  int r;
  int32 color;
}Ball;


/*��ͼ����*���������ڻ���С��ˢ����Ļ*/
void draw()
{
  /*********************************
  *drawCir�������ĸ�����* x,y,r,color*
  ****x,y����Բ��Բ�ģ�r����Բ�İ뾶****
  ********color�������Բ����ɫ*******
  *********************************/
  /*ָ����ɫ����*/
  cls(0,0,0);
  
  drawCir(ball.x,ball.y,ball.r,ball.color);
  
  /*ˢ��һ����������* SCRW,SCRH�ֱ������Ļ����*/
  ref(0,0,SCRW,SCRH);
}


void run(int data)
{
  /*************
  *���߽���զ��?**
  **************/
  
  /*��*/
  if(ball.x<=ball.r)
  {
     ball.x=ball.r;
     /*������*/
     ball.dx=-ball.dx;
  }
  
  /*��*/
  if(ball.x>=SCRW-ball.r)
  {
     ball.x=SCRW-ball.r;
     /*������*/
     ball.dx=-ball.dx;
  }
  
  /*��*/
  if(ball.y<=ball.r)
  {
     ball.y=ball.r;
     /*������*/
     ball.dy=-ball.dy;
  }
  
  /*��*/
  if(ball.y>=SCRH-ball.r)
  {
     ball.y=SCRH-ball.r;
     /*������*/
     ball.dy=-ball.dy;
  }
  
}



