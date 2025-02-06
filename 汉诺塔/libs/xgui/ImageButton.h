#ifndef XGUI_IMAGEBUTTON_H
#define XGUI_IMAGEBUTTON_H
#include "graphics.h"
#include "ex_math.h"
#include "./bitmap.h"

typedef struct
{
 char*name;//�ؼ�����
 int id;//��ťid
 int type;//��ť״̬������1���ͷ�0������-1
 int isshow;//�Ƿ���ʾ ����ʾʱ������ִ�е���¼�
 int isdown;//�Ƿ���
 int x;//��ťλ��x
 int y;//��ťλ��y
 int w;//��ť���
 int h;//��ť�߶�
 int bitmap;//bitmap���
 int blend_color;//�����ɫ
 int img_mode;//ͼƬ��ʾģʽ 0���� 1����Ӧ 2��������ؼ�
 int32 timer;//�ص���ʱ��
 int draw_mode;//ˢ��ģʽ
 
 void*onclick;//�����ص�
 int click_mode;//�ص�ģʽ -1���ص� 0��һ�� 1���
}ImageButton;

//����ͼƬ�ؼ�
void*img_create(char*filename,int x,int y,int w,int h);
//��ȡid
int img_getid(ImageButton*img);
//���ƿؼ�
void img_draw(ImageButton*img);
//�жϿؼ��Ƿ���ʾ
int img_isshow(ImageButton*img);
//��ʾ�ؼ�
void img_show(ImageButton*img);
//���ؿؼ�
void img_hide(ImageButton*img);
//���û����ɫ
void img_setBlendColor(ImageButton*img,int color);
//����ͼƬ��ʾģʽ 0���� 1����Ӧ 2���
void img_setmode(ImageButton*img,int mode);
//��ȡ��ʾģʽ
int img_getmode(ImageButton*img);
//���õ���¼�
void img_setonclick(ImageButton*img,void*click);
//�ؼ�event�¼�
int img_event(ImageButton*img,int type,int p1,int p2);
//�ͷ�ͼƬ�ؼ�
void img_free(ImageButton*img);


//����ͼƬ�ؼ�
void*img_create(char*filename,int x,int y,int w,int h)
{
 ImageButton*img = malloc(sizeof(ImageButton));
 memset(img,0,sizeof(ImageButton));
 img->name = "ImageButton";
 if(strlen(filename)>9&&strncmp(filename,"assets://",9)==0)
 	img->bitmap = readBitmapFromAssets(filename+9);
 else
 	img->bitmap = readBitmap(filename);
 img->blend_color = 0xffffffff;
 img->x = x;
 img->y = y;
 img->w = w;
 img->h = h;
 img->isshow = 1;
 img->img_mode = 1;
 img->draw_mode = 1;
 img->click_mode = 0;
 img->timer = timercreate();
 return img;
}

//����id
void img_setid(ImageButton*img,int id)
{
 img->id = id;
}

//���û����ɫ
void img_setBlendColor(ImageButton*img,int color)
{
 img->blend_color = color;
 img_draw(img);
 ref(img->x,img->y,img->w,img->h);
}

//��ȡid
int img_getid(ImageButton*img)
{
 return img->id;
}


//���ƿؼ�
void img_draw(ImageButton*img)
{
 int bit = bitmap_blend(img->bitmap,img->blend_color);
 
 //0���� 1����Ӧ 2���
 int x,y;
 int w = bitmap_getw(bit);
 int h = bitmap_geth(bit);
 int dx,dy,dw,dh;
 if(img->isshow)
 {
  if(img->img_mode==0)
  {
   x = img->x+(img->w-w)/2;
   y = img->y+(img->h-h)/2;
   drawBitmap(bit,x,y);
   ref(img->x,img->y,img->w,img->h);
  }
  
  if(img->img_mode==1)
  {
   //�жϿ�߱�
   if(w*1000/h>img->w*1000/img->h)
   {
    dw = img->h*w/h;
    dh = img->h;
    dx = img->x+(img->w-dw)/2;
    dy = img->y+(img->h-dh)/2;
    //�Ը߶���Ϊ����
    drawBitmapEx(bit,dx,dy,dw,dh,0,0,w,h);
   }
   else
   {
    //�Կ����Ϊ����
    dw = img->w;
    dh = img->w*h/w;
    dx = img->x+(img->w-dw)/2;
    dy = img->y+(img->h-dh)/2;
    drawBitmapEx(bit,dx,dy,dw,dh,0,0,w,h);
   }
  }
  if(img->img_mode==2)
  {
   drawBitmapEx(bit,img->x,img->y,img->w,img->h,0,0,w,h);
  }
 }
 bitmapFree(bit);
}

//�жϿؼ��Ƿ���ʾ
int img_isshow(ImageButton*img)
{
 return img->isshow;
}

//��ʾ�ؼ�
void img_show(ImageButton*img)
{
 img->isshow = 1;
 if(img->draw_mode==1)
 {
  img_draw(img);
  ref(img->x,img->y,img->w,img->h);
 }
}
//���ؿؼ�
void img_hide(ImageButton*img)
{
 img->isshow = 0;
}

//����ͼƬ��ʾģʽ 0���� 1����Ӧ 2���
void img_setmode(ImageButton*img,int mode)
{
 img->img_mode = mode;
}

//��ȡ��ʾģʽ
int img_getmode(ImageButton*img)
{
 return img->img_mode;
}

//���õ���¼�
void img_setonclick(ImageButton*img,void*click)
{
 img->onclick = click;
}

//�ؼ�event�¼�
int img_event(ImageButton*img,int type,int p1,int p2)
{
 if(img->isshow)
 {
  if(type==MS_DOWN)
  {
   if(isPointCollRect(p1,p2,img->x,img->y,img->w,img->h))
   {
    img->isdown = 1;
    
    if(img->click_mode>0)
    	if(img->onclick!=NULL)
    	timerstart(img->timer,1,img->id,img->onclick,0);
    
    if(img->draw_mode==0)
    {
     img_draw(img);
     ref(img->x,img->y,img->w,img->h);
    }
   }
  }
  
  if(type==MS_UP)
  {
   if(img->isdown)
   {
    img->isdown = 0;
    
    if(img->click_mode>-1)
    	if(img->onclick!=NULL)
    	timerstart(img->timer,1,img->id,img->onclick,0);
    
    if(img->draw_mode==0)
    {
     img_draw(img);
     ref(img->x,img->y,img->w,img->h);
    }
   }
  }
 }
 return 0;
}

//�ͷ�ͼƬ�ؼ�
void img_free(ImageButton*img)
{
 if(img->bitmap)
 {
  bitmapFree(img->bitmap);
  img->bitmap = 0;
 }
 if(img->timer)
 {
  timerstop(img->timer);
  timerdel(img->timer);
  img->timer = 0;
 }
 free(img);
}

#endif
