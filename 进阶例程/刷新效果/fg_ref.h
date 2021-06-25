
#ifndef _FG_REF_H_
#define _FG_REF_H_


typedef struct
{
 int w;
 int h;
 int load; //进度
} FG_REF;

//初始化方格刷新
int fg_create()
{
 FG_REF *fg=malloc(sizeof(FG_REF));
 fg->w = SCRW/12;
 fg->h = SCRW/12;
 fg->load=0;
 return (int)fg;
 }
//刷新定时器回调
int fg_ref(int id)
{
 FG_REF *fg=(void*)id;
 int x,y;
 int w=fg->w;
 int h=fg->h;
 int i=fg->load;
 int j=w*i/10;
 if(fg->load>10)return 1;
 //printf("%d %d\n",w,h);
  for(x = 0; x<= SCRW; x += w)
    {
    for(y = 0; y<= SCRH; y += h)
      {
      
      ref(x+(w-j)/2, y+(w-j)/2, j, j);
      //printf("%d %d \n",x,y);
      }
    }
 fg->load++;

return 0;
}

int fg_free(int id)
{
 FG_REF *fg=(void*)id;
 free(fg);
 
 return 0;
}

#endif
