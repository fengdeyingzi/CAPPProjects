

//�����Сˢ��Ч��

typedef struct
{
 int load; //����
 int interval; //���
 int size; //ˢ�´���
 int w; //������
 int h; //����߶�
} RECT_REF;

int rf_create()
{
 RECT_REF *rect_ref=malloc(sizeof(RECT_REF));
 rect_ref->load=0;
 rect_ref->size=10;
 rect_ref->w=SCRW/12;
 rect_ref->h=SCRW/12;
 return (int)rect_ref;
}

int rf_ref(int id)
{
 RECT_REF *rect_ref=(void*)id;
 int w=rect_ref->w;
 int h=rect_ref->h;
 int rw=rect_ref->w* rect_ref->load/rect_ref->size;
 int rh=rect_ref->h* rect_ref->load/rect_ref->size;
 for(int x=(w-rw)/2;x<SCRW;x+=w)
 ref(x,0,rw,SCRH);
 for(int y=(h-rh)/2;y<SCRH;y+=h)
 ref(0,y,SCRW,rh);

 if(rect_ref->load>=rect_ref->size) return TRUE;
 else
 rect_ref->load++;

return 0;
}



int rf_free(int id)
{
 RECT_REF *rect_ref=(void*)id;
 free(rect_ref);

return 0;
}


