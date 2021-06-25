#ifndef _XGUI_BUTTON_
#define _XGUI_BUTTON_


/*
XGUI
  ��ť�ؼ� v1.1
��by�����Ӱ��

  ���¼�¼��
  ϸ���޸�
  �޸�����¼�event����
  
  
Ӱ�Ӿ��ֲ���վ��www.yzjlb.net
�ֻ�C��̳��bbs.yzjlb.net
�ֻ�C����QQȺ��370468001
*/

//��ť�ṹ��

typedef struct 
{
 char *name; //�ؼ�����
int id; //��ťid
int type;//��ť״̬������1���ͷ�0������-1
int isshow; //�Ƿ���ʾ ����ʾʱ������ִ�е���¼�
int isdown; //�Ƿ���
char *text; //��ť����
int textx; //����x����
int texty; //����y����
int x; //��ťλ��x
int y; //��ťλ��y
int w; //��ť���
int h; //��ť�߶�
int32 timer; //�ص���ʱ��
int draw_mode; //ˢ��ģʽ
char *onclick; //�����ص�
}button;
int id=0;

//������ť
//�����ֱ��� ��ť���� ��ťx���� y���� ��� �߶� 
void *btn_create(char *text,int x,int y,int w,int h)
{
int fw,fh;
 button *btn;
btn=malloc(sizeof(button));
memset(btn,0,sizeof(button));
btn->name="Button";
btn->text=text;
btn->x=x; 
btn->y=y;
btn->w=w;
btn->h=h;
btn->type=0;
btn->id=-1;id++;
textwh(text,0,1,&fw,&fh);
btn->textx=x+(w-fw)/2;
btn->texty=y+(h-fh)/2;
btn->timer = timercreate();
btn->isdown=0;
btn->isshow = 1;
return btn;
}

//���ð�ťid
void btn_setid(button *btn,int id)
{
 btn->id=id;
}

//��ȡ��ťid
int btn_getid(button *btn)
{
 return btn->id;
}

//��ʾ��ť ��������ť�ṹ��ָ��
void btn_draw(button *btn)
{
 if(btn->isshow)
 {
  if(btn->isdown)
  {
   //����һ������
drect(btn->x,btn->y,btn->w,btn->h,68,168,240);
drect(btn->x+4,btn->y+4,btn->w-8,btn->h-8,230,238,245);
  //��������
dtext(btn->text,btn->textx,btn->texty,50,50,50,0,1);
  }
  else
  {
      //����һ������
drect(btn->x,btn->y,btn->w,btn->h,168,168,168);
drect(btn->x+4,btn->y+4,btn->w-8,btn->h-8,230,230,230);
  //��������
dtext(btn->text,btn->textx,btn->texty,50,50,50,0,1);
  }
 }
}

//���ð�ť���� ��������ť�ṹ��ָ�� �µİ�ť����
void btn_settext(button *btn,char *text)
{
 int fw,fh;
btn->text=text;
textwh(text,0,1,&fw,&fh);
btn->textx=btn->x+(btn->w-fw)/2;
btn->texty=btn->y+(btn->h-fh)/2;
button_draw(btn);
ref(btn->x,btn->y,btn->w,btn->h);
}

//���ö�ʱ��ˢ��ģʽ 0�Ƕ�ʱ��ˢ�� 1��ʱ��ˢ��
void btn_setref(button *btn,int mode)
{
 btn->draw_mode=mode;
}


//��ʾ��ť
int btn_show(button *btn)
{
 btn->isshow=1;
 btn_draw(btn);
 return 0;
}

//���ذ�ť
int btn_hide(button *btn)
{
 btn->isshow = 0;
 btn->isdown = 0;
 
 return 0;
}

//��ť�Ƿ���ʾ
int btn_isshow(button *btn)
{
 return btn->isshow;
 
}

//���õ���ص����� �����ֻ�C��֧�ֺ���ָ�룬���Բ���char*������ԭ��Ϊ��ʱ���Ļص�����void click_ok(int id)
void btn_setonclick(button *btn, char *click)
{
 btn->onclick = click;
}

//��ťevent�¼�
void btn_event(button *btn,int type,int p1,int p2)
{
 
 if(type==MS_DOWN)
 {
 if(btn_impact(btn,p1,p2))
 {
  btn->isdown=1;
  if(btn->draw_mode == 0)
  {
  btn_draw(btn);
  ref(btn->x,btn->y,btn->w,btn->h);
  }
  //printf("down");
 }
 }
 if(type==MS_UP)
 {
  //if(btn_impact(btn,p1,p2))
  {
   if(btn->isdown)
   {
    btn->isdown=0;
    if(btn->draw_mode == 0)
    {
    btn_draw(btn);
    ref(btn->x,btn->y,btn->w,btn->h);
    }
    if(btn->onclick!=NULL)
    {
    // printf("click");
    
     timerstart(btn->timer, 10, btn->id, btn->onclick, 0);
    }
   }
  }
 }
 
}


//�жϰ�ť����¼� ��������ťָ�� ����x���� ����y����
//����ֵ��TRUE(1)�ɹ� FALSE(0)ʧ��
int btn_impact(button *btn,int x,int y)
{
 if(btn->isshow)
 {
  if(x>btn->x && x<btn->x+btn->w && y>btn->y && y<btn->y+btn->h)
  return 1;
 }

return 0;
}

//�ͷŰ�ť�ڴ�
void btn_free(button *btn)
{
 free(btn);
}


#endif
