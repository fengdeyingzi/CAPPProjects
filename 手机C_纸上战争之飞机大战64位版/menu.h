
#ifndef _MENU_H_
#define _MENU_H_
#include <graphics.h>
#include "draw.h"
#include "ex_game.h"
#include "win.h"
#include "rclist.h"

typedef struct
{
 int type; //��ǰ�˵���
 int isDrawWindow; //�Ƿ���ʾ����
 char *text;
 int32 world; //����
 int32 camera;
 int32 sp_text; //���� ����
 int32 sp_btn_left;
 int32 sp_btn_right;
 int32 bitmap_back; //����ͼƬ
 int32 bitmap_text; //ͼƬ����
 int32 bitmap_left;
 int32 bitmap_right;
 int32 bitmap_winleft;
 int32 bitmap_winright;
 int32 sp_winleft;
 int32 sp_winright;
} MENU;

#ifdef TCC
extern int32 rc;
#endif

//�����˵�
MENU *menu_create()
{
printf("%s\n","menu_create");
 MENU *menu = malloc(sizeof(MENU));
 memset(menu,0,sizeof(_MENU));
 printf("%s\n","����");
 menu->camera=ca_create(0,0,480,800);
 //��ȡbitmap
 printf("%s\n","����");
 menu->bitmap_back=readBitmapFromAssets("menu_background1.png");
 menu->bitmap_text=readBitmapFromAssets("text_menu.png");
 menu->bitmap_left=readBitmapFromAssets("btn_left.png");
 menu->bitmap_right=readBitmapFromAssets("btn_right.png");
 menu->bitmap_winleft=readBitmapFromAssets("win_left.png");
 menu->bitmap_winright=readBitmapFromAssets("win_right.png");
 //��ȡ����
 printf("%s %x\n","���� sp_read",menu->bitmap_winleft);
 menu->sp_winleft=sp_read("win_left.sprite",menu->bitmap_winleft);
 menu->sp_winright=sp_read("win_right.sprite",menu->bitmap_winright);
 menu->sp_text=sp_read("text_menu.sprite",menu->bitmap_text);
 menu->sp_btn_left=sp_read("btn_left.sprite", menu->bitmap_left);
 menu->sp_btn_right=sp_read("btn_right.sprite",menu->bitmap_right);
 printf("%s\n","����");
 menu->world=world_create();
 printf("%s %x %x\n","addsprite",menu->world,menu->sp_text);
 world_addSprite(menu->world,menu->sp_text);
 printf("%s\n","����");
 world_addSprite(menu->world,menu->sp_btn_left);
 printf("%s\n","����");
 world_addSprite(menu->world,menu->sp_btn_right);
 printf("%s\n","����");
 world_setCamera(menu->world,menu->camera);
 sp_setxy(menu->sp_text,(SCRW-140)/2,SCRH*3/4);
 sp_setxy(menu->sp_btn_left,SCRW/2-80-32,SCRH*3/4);
 sp_setxy(menu->sp_btn_right,SCRW/2+80,SCRH*3/4);
 printf("%s\n","����");
 sp_setxy(menu->sp_winleft,4,SCRH-100);
 sp_setxy(menu->sp_winright,SCRW-4-100,SCRH-100);
 menu->isDrawWindow=0;
 printf("%s\n","create ok");
 return menu;
};

//��ʾ�˵�
void menu_draw(MENU *menu)
{
printf("%s\n","menu_draw");
 cls(0,0,0);
 //��������
 printf("%s\n","��������");
 drawBitmap(menu->bitmap_back,0,(SCRH-854)/2);
 if(menu->isDrawWindow)
 {
 printf("%s\n","nrect");
  nrect(4,(SCRH-600)/2,SCRW-8,600,0xfff0a070);
  sp_draw(menu->sp_winleft,NULL);
  sp_draw(menu->sp_winright,NULL);
  rectst rect;
  colorst color;
  rect.x=10;
  rect.y=(SCRH-600)/2;
  rect.w=SCRW-20;
  rect.h=600;
  color.r=20;
  color.g=20;
  color.b=20;
  dtextex(menu->text,rect.x,rect.y,&rect,&color,3,1);
 }
 else
 {
 printf("%s\n","world_draw");
 world_draw(menu->world);
 }
 ref(0,0,SCRW,SCRH);
 
}
//��ʾ����
void menu_drawHelp(MENU *menu)
{
 menu->isDrawWindow=TRUE;
 menu->text=rc_getText(rc,11);
}
//��ʾ����
void menu_drawAbout(MENU *menu)
{
 menu->isDrawWindow=TRUE;
 menu->text = rc_getText(rc,13);
}

//�˵�event�¼�
int menu_event(MENU *menu, int type,int p1,int p2)
{
 if(type==KY_UP)
 {
  if(p1==_BACK)
  {
  exitApp();
  exit();
  }
  return 0;
 }
 if(type==MS_UP)
 {
  if(sp_impact(menu->sp_btn_left,p1,p2))
  {
   menu->type--;
   if(menu->type<0)
   menu->type=0;
   sp_setAction(menu->sp_text,menu->type);
  }
  if(sp_impact(menu->sp_btn_right,p1,p2))
  {
   menu->type++;
   if(menu->type>5)
   menu->type=5;
   sp_setAction(menu->sp_text,menu->type);
  }
  if(sp_impact(menu->sp_text,p1,p2))
  {
   
   if(menu->type == 0)
   {
    win_set(WIN_GAME);
   }
   if(menu->type==1) //ѡ��ؿ�
   {
    //menu->isDrawWindow=1;
    //win_set(WIN_HELP);
   }
   if(menu->type==2) //����˵��
   {
    menu->isDrawWindow=1;
    menu_drawHelp(menu);
    //win_set(WIN_ABOUT);
   }
   if(menu->type==4) //����
   {
    menu->isDrawWindow=1;
    menu_drawAbout(menu);
   }
   if(menu->type==4)
   {
    
   }
   if(menu->type==5)
   {
    exitApp();
    exit();
   }
   
  }
  else if(menu->isDrawWindow)
  {
  if(sp_impact(menu->sp_winleft,p1,p2))
  {
   menu->isDrawWindow=0;
  }
  if(sp_impact(menu->sp_winright,p1,p2))
  {
   menu->isDrawWindow=0;
  }
  }
 }
 
 
 return 0;
}
 
//�ͷŲ˵�
int menu_free(MENU *menu)
{
  //�ͷ�bitmap
 bitmapFree(menu->bitmap_back);
 bitmapFree(menu->bitmap_text);
 bitmapFree(menu->bitmap_left);
 bitmapFree(menu->bitmap_right);
 bitmapFree(menu->bitmap_winleft);
 bitmapFree(menu->bitmap_winright);
  //�ͷž���
  
 sp_free(menu->sp_text);
 sp_free(menu->sp_btn_left);
 sp_free(menu->sp_btn_right);
 sp_free(menu->sp_winleft);
 sp_free(menu->sp_winright);
 //�ͷ�����
 world_free(menu->world);
 
 ca_free(menu->camera);
 
 free(menu);
 
 return 0;
}







#endif