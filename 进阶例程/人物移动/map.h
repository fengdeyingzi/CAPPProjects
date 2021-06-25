
void map1(void)
{
   int32 ditu=readBitmapFromAssets("map01.png");
   for(int i=0;i<9*95;i+=95)
   {
   drawBitmap(ditu,i,0);
   drawBitmap(ditu,i,125);
   drawBitmap(ditu,i,250);
   drawBitmap(ditu,i,375);
   }
   bitmapFree(ditu);
}

void zmap1(void)
{
   int32 zhangai=readBitmapFromAssets("map02.png");
   int32 shu1=clipBitmap(zhangai,0,160,120,160);
   int32 shu2=clipBitmap(zhangai,130,160,120,160);
   drawBitmap(shu1,0,0);
   drawBitmap(shu1,100,300);
   drawBitmap(shu1,500,20);
   drawBitmap(shu2,450,300);
   drawBitmap(shu2,520,150);
   bitmapFree(zhangai);
   bitmapFree(shu1);
   bitmapFree(shu2);
   
}
     

void peng(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2)
{
   if((jue(x1-x2)<(w1+w2))&&(jue(y1-y2)<(h1+h2)))
   {
      return TRUE;
   }
   else
      return FALSE;
}

int jue(int a)
{
   if(a>=0)
   return a;
   if(a<0)
   return (-1*a);
}