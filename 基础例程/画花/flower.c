#include <base.h>


int w,x,y,y1;
int init()
{
//初始化变量
w=0;x=0;y=0;y1=0;
//设置屏幕分辨率
setscrsize(240, SCRH*240/SCRW);
//执行main函数
main();
return 0;
}

int main()
{
w=80;
sr();

hp(120,400,80,255,255,0);
jing(120,100,20,320,0,255,0);
yue(120,320,80,0,255,0);
yue(120,260,80,0,255,0);
hua(120,100,80,255,0,255);
return 0;
}
void srect(int16 xx,int16 yy,int16 ww,int16 hh,uint8 rr,uint8 gg,uint8 bb,uint8 r1,uint8 g1,uint8 b1,uint8 nn)
{
int p= (rr<<16) | (gg<<8) | bb;
int q= (r1<<16 )| (g1<<8) | b1;
shaderect(xx,yy,ww,hh,p,q,nn);
}


 void refresh(int x,int y,int w,int h)
{
 ref(x,y,w,h);
 
}

                                                                //"花"
int hua(int X,int Y,int R,int r,int g,int b)
{
for(x=-R;x<=R;x=x+1)
  {
y=P(x,3)/P(R,2);
dline(X+y,Y-x+y,X+y,Y+x-y,r,g,b);
dline(X+x-y,Y+y,X-x+y,Y+y,r,g,b);
dline(X+x,Y+y,X+y,Y+x,r,g,b);
dline(X-x,Y+y,X-y,Y+x,r,g,b);


                          refresh(X-R,Y-R,R*2+1,R*2+1);
  }
return 0;
}


//"叶子"
int yue(int X,int Y,int R,int r,int g,int b)
{
for(x=0;x<=R;x=x+1)
  {
y=P(x,2)/R;
y1=P(x,4)/P(R,3);
dline(X-x,Y-y1,X-y,Y-x,r,g,b);
dline(X+y,Y-x,X+x,Y-y1,r,g,b);
refresh(X-R,Y-R,R*2+1,R+1);
  }
  return 0;
}

//    "茎"
int jing(int X,int Y,int W,int H,int r,int g,int b)
{
for(;Y<=H;Y=Y+2)
  {
dline(X-W/2,Y,X+W/2,Y,r,g,b);

  }
  return 0;
}

                                                                                                              //"花盘"
int hp(int X,int Y,int R,int r,int g,int b)
{
for(x=0;x<=R;x=x+1)
  {
y=x*x/R;
y1=P(x,4)/P(R,3);
dline(X-x,Y-y1,X,Y-y,r,g,b);
dline(X,Y-y,X+x,Y-y1,r,g,b);

  }
  ref(0,0,SCRW,SCRH);
  return 0;
}


                                                   //"价乘"
int P(int a,int b)
{
int c;
c=1;
for(;b;b=b-1)
  {
c=c*a;
  }
if( a<0)
  {
  if (c>0)
    {
  c=-c;
    }
  }
return c;
}

//"退出"
int event(int type, int p1,int p2)
{

exit();
return 0;
}

int pause()
{
return 0;
}

int resume()
{
return 0;
}
  
  
                                                                                                                    int sr()
{

srect(0,0,SCRW,SCRH,85,170,255,170,255,255,0);
refresh(0,0,SCRW,SCRH);
return 0;
}


