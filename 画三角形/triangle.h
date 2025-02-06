#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

/*
绘制三角形
检测点是否在三角形内
*/

#define MAKERGB(r, g, b) 	 (((r>>3) << 11) | ((g>>2) << 5) | ((b>>3)) )

#define Tx(x,y,x1,y1,x2,y2) ((x1-x)*(y2-y))-((y1-y)*(x2-x))
#define Ti(a,b,c) (a>0&&b>0&&c>0)||(a<0&&b<0&&c<0)||(a==0&&b==0&&c==0)


void tri_draw(int x1,int y1,int x2,int y2,int x3,int y3,int r,int g,int b){

 int A=(x1<x2)?x1:x2;
 A=(A<x3)?A:x3;
 int B=(x1>x2)?x1:x2;
 B=(B>x3)?B:x3;
 int C=(y1<y2)?y1:y2;
 C=(C<y3)?C:y3;
 int D=(y1>y2)?y1:y2;
 D=(D>y3)?D:y3;
 int color565 = MAKERGB(r,g,b);
 int Mx,My,Mz;
 int x,y;
 for(x=A;x<=B;x++){
  for(y=C;y<=D;y++){
   
   Mx=Tx(x,y,x1,y1,x2,y2);
   My=Tx(x,y,x2,y2,x3,y3);
   Mz=Tx(x,y,x3,y3,x1,y1);
   
   if(Ti(Mx,My,Mz))
    dpoint(x,y,color565);
  }
 }
}

 //求一个三角形面积
int tri_area(int x1,int y1,int x2,int y2,int x3,int y3)
{
 //return (1/2)*(x1*y2+x2*y3+x3*y1-x1*y3-x2*y1-x3*y2);
 int m =  ((x2-x1)*(y3-y2))-((x3-x2)*(y2-y1));
 return (m>0)?m:-m;
}

//判断点是否在三角形內
int tri_ispoint(int x,int y, int x1,int y1,int x2,int y2,int x3,int y3)
{
 if(tri_area(x,y,x1,y1,x2,y2)
 + tri_area(x,y,x1,y1,x3,y3)
 + tri_area(x,y,x2,y2,x3,y3) == tri_area(x1,y1,x2,y2,x3,y3))
 return TRUE;
 return FALSE;
}




#endif