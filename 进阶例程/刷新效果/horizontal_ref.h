
//横向刷新屏幕

typedef struct
{
 int load;
 int interval;
} HOR_REF;


int hor_create()
{
 HOR_REF *_ref=malloc(sizeof(HOR_REF));
 _ref->load=0;
 _ref->interval=SCRW/20;
 return (int)_ref;
}

int hor_ref(int id)
{
 HOR_REF *_ref=(void*)id;
 //绘制与间距相等的线段，间隔为间距-1
 int w=_ref->interval;
 int x=_ref->load;
 _ref->load+=w-1;
 for(int i=0;i<w;i++)
 {
  if(x>i*w)
  ref(x-i*w,0,1,SCRH*5);
 }
 
 if(_ref->load>SCRW+w*w)return TRUE;
 
 return 0;
}

int hor_free(int id)
{
 HOR_REF *_ref=(void*)id;
 free(_ref);
 
 return 0;
}









