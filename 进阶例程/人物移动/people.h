//人物图片
void bmap(int a,int b,int x,int y)
{
    //从assets目录读取bitmap
    int32 zong = readBitmapFromAssets ("zhu.png");
    
    int32 up[3];
    int32 down[3];
    int32 left[3];
    int32 right[3];
    down[0]=clipBitmap(zong,97,0,32,32);
    down[1]=clipBitmap(zong,129,0,32,32);
    down[2]=clipBitmap(zong,161,0,32,32);
    left[0]=clipBitmap(zong,97,32,32,32);
    left[1]=clipBitmap(zong,129,32,32,32);
    left[2]=clipBitmap(zong,161,32,32,32);
    right[0]=clipBitmap(zong,97,64,32,32);
    right[1]=clipBitmap(zong,129,64,32,32);
    right[2]=clipBitmap(zong,161,64,32,32);
    up[0]=clipBitmap(zong,97,96,32,32);
    up[1]=clipBitmap(zong,129,96,32,32);
    up[2]=clipBitmap(zong,161,96,32,32);
    switch(a)
    {
       case 1:
       drawBitmap(up[b],x,y);
       break;
       case 2:
       drawBitmap(down[b],x,y);
       break;
       case 3:
       drawBitmap(left[b],x,y);
       break;
       case 4:
       drawBitmap(right[b],x,y);
       break;
    }
    bitmapFree(zong);
    
    for(int i=0;i<3;i++)
    bitmapFree(up[i]);
    
    for(int j=0;j<3;j++)
    bitmapFree(down[j]);
    
    for(int k=0;k<3;k++)
    bitmapFree(left[k]);
    
    for(int l=0;l<3;l++)
    bitmapFree(right[l]);
}