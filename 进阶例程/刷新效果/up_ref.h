


//由下至上 方格刷新


typedef struct
{
 int load;//刷新进度
 int size; //刷新次数
 int line; //方格行数
 int w; //方格宽度
 int h; //方格高度
} UP_REF;


int up_create()
{
 UP_REF *up=malloc(sizeof(UP_REF));
 up->w=SCRW/10;
 up->h=SCRW/10;
 up->line=10;
 up->load=0;
 up->size=SCRH/up->h+1+10;
 return (int)up;
}

int up_ref(int id)
{
 UP_REF *up=(void*)id;
 int load=up->load;
 int size=up->size;
 int w=up->w;
 int h=up->h;
 int y=SCRH-h*load;
 int line=up->line;
 for(int x=0;x<SCRW;x+=w)
// for(int y=SCRH;y>=0;y-=h)
 {
  for(int l=line;l>=0;l--)
  {
  int lw=w*l/line;
  int lh=h*l/line;
  ref(x+(w-lw)/2,y+l*h+(h-lh)/2,lw,lh);
  }
 }
 up->load++;
 if(up->load>up->size)
  return TRUE;
 
 return 0;
}


int up_free(int id)
{
 UP_REF *up=(void*)id;
 free(up);
 
 return 0;
}


