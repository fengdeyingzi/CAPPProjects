
#ifndef _DRAW_H_
#define _DRAW_H_


//»æÖÆ±ß¿ò
void nrect(int x,int y,int w,int
h,int color)
{
 int n=2;
 drawRect(x+n,y+n,w-n*2,h-n*2, 0xa0ffffff);
 drawRect(x,y,w,n,color);
 drawRect(x,y+h-n,w,n,color);
 drawRect(x,y+2,n,h-n*2,color);
 drawRect(x+w-n,y+2,n,h-n*2,color);
 
}


#endif


