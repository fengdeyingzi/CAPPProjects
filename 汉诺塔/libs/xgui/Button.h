#ifndef XGUI_BUTTON_H
#define XGUI_BUTTON_H

//��ť�ṹ��
typedef struct
{
 char*name;//�ؼ�����
 int id;//��ťid
 
 int type;//��ť״̬������1���ͷ�0������-1
 int isshow;//�Ƿ���ʾ
 int isdown;//�Ƿ���
 
 int x;//��ťλ��x
 int y;//��ťλ��y
 int w;//��ť���
 int h;//��ť�߶�
 
 char*text;//��ť����
 int textx;//����x����
 int texty;//����y����
 int textc;//������ɫ
 
 int bkgc;//��ť������ɫ
 int fram;//��ť��Ե��ɫ
 
 int bkgc2;//����
 int fram2;//����
 int32 timer;//�ص���ʱ��
 int draw_mode;//ˢ��ģʽ
 void*onclick;//�����ص�
}Button;

int id = 0;
//������ť
void*btn_create(char*text,int x,int y,int w,int h);
//���ð�ťid
void btn_setid(Button*btn,int id);
//��ȡ��ťid
int btn_getid(Button*btn);
//���ư�ť
void btn_draw(Button*btn);
//���ð�ť�ı�
void btn_settext(Button*btn,char*text);
//����ģʽ
void btn_setref(Button*btn,int mode);
//���ûص�����
void btn_setonclick(Button*btn,void*click);
//��ʾ��ť
int btn_show(Button*btn);
//���ذ�ť
int btn_hide(Button*btn);
//��ť�Ƿ���ʾ
int btn_isshow(Button*btn);
//��ťevent�¼�
void btn_event(Button*btn,int type,int p1,int p2);
//��ť����ж�
int btn_impact(Button*btn,int x,int y);
//�ͷŰ�ť
void btn_free(Button*btn);

/*-----------------------------------*/

//������ť
void*btn_create(char*text,int x,int y,int w,int h)
{
 int32 fw,fh;
 Button*btn;
 btn = malloc(sizeof(Button));
 memset(btn,0,sizeof(Button));
 btn->name = "Button";
 btn->text = NULL;
 btn_settext(btn,text);
 btn->x = x;
 btn->y = y;
 btn->w = w;
 btn->h = h;
 btn->type = 0;
 btn->id = -1;
 btn->fram = 0x8044A8F0;
 btn->bkgc = 0x80E6EEF5;
 btn->fram2 = 0xF0A8A8A8;
 btn->bkgc2 = 0xA044A8F0;
 id++;
 textwh(text,0,1,&fw,&fh);
 btn->textx = x+(w-fw)/2;
 btn->texty = y+(h-fh)/2;
 btn->textc = 0xffffffff;
 btn->timer = timercreate();
 btn->isdown = 0;
 btn->isshow = 1;
 btn->draw_mode = 0;
 return btn;
}

//���ð�ťid
void btn_setid(Button*btn,int id)
{
 btn->id = id;
}

//��ȡ��ťid
int btn_getid(Button*btn)
{
 return btn->id;
}

//��ʾ��ť ��������ť�ṹ��ָ��
void btn_draw(Button*btn)
{
 if(btn->isshow)
 {
  if(btn->isdown)
  {
   //����һ������
   drawRect(btn->x,btn->y,btn->w,btn->h,btn->fram2);
   drawRect(btn->x+4,btn->y+4,btn->w-8,btn->h-8,btn->bkgc2);
  }
  else
  {
   //����һ������
   drawRect(btn->x,btn->y,btn->w,btn->h,btn->fram);
   drawRect(btn->x+4,btn->y+4,btn->w-8,btn->h-8,btn->bkgc);
  }
  //��������
  dtext(btn->text,btn->textx,btn->texty,btn->textc>>16&0xff,btn->textc>>8&0xff,btn->textc&0xff,0,1);
 }
}

//���ð�ť���� ��������ť�ṹ��ָ�� �µİ�ť����
void btn_settext(Button*btn,char*text)
{
 //�����ڴ�
 int len=sizeof(char)*strlen(text)+1;
 char*txt = malloc(len);
// memset(txt, '\0', len);
 sprintf(txt,"%s",text);
 if(btn->text!=NULL)
 	free(btn->text);
 btn->text = txt;
 txt=NULL;
 
 int32 fw,fh;
 textwh(text,0,1,&fw,&fh);
 //������������
 btn->textx = btn->x+(btn->w-fw)/2;
 btn->texty = btn->y+(btn->h-fh)/2;
 //����ˢ��
 if(btn->draw_mode==0)
 {
  btn_draw(btn);
  ref(btn->x,btn->y,btn->w,btn->h);
 }
}

//���ö�ʱ��ˢ��ģʽ 0�Ƕ�ʱ��ˢ�� 1��ʱ��ˢ��
void btn_setref(Button*btn,int mode)
{
 btn->draw_mode = mode;
}

//��ʾ��ť
int btn_show(Button*btn)
{
 btn->isshow = 1;
 if(btn->draw_mode==1)
 {
  btn_draw(btn);
  ref(btn->x,btn->y,btn->w,btn->h);
 }
 return 0;
}

//���ذ�ť
int btn_hide(Button*btn)
{
 btn->isshow = 0;
 btn->isdown = 0;
 return 0;
}

//��ť�Ƿ���ʾ
int btn_isshow(Button*btn)
{
 return btn->isshow;
}

//���õ���ص����� �����ֻ�C��֧�ֺ���ָ�룬���Բ���char*������ԭ��Ϊ��ʱ���Ļص�����void click_ok(int id)
void btn_setonclick(Button*btn,void*click)
{
 btn->onclick = click;
}

//��ťevent�¼�
void btn_event(Button*btn,int type,int p1,int p2)
{
 if(type==MS_DOWN)
 {
  if(btn_impact(btn,p1,p2))
  {
   btn->isdown = 1;
   if(btn->draw_mode==0)
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
    btn->isdown = 0;
    if(btn->draw_mode==0)
    {
     btn_draw(btn);
     ref(btn->x,btn->y,btn->w,btn->h);
    }
    if(btn->onclick!=NULL)
    {
     // printf("click");
     timerstart(btn->timer,10,btn->id,btn->onclick,0);
    }
   }
  }
 }
}


//�жϰ�ť����¼� ��������ťָ�� ����x���� ����y����
//����ֵ��TRUE(1)�ɹ� FALSE(0)ʧ��
int btn_impact(Button*btn,int x,int y)
{
 if(btn->isshow)
 {
  if(x>btn->x&&x<btn->x+btn->w&&y>btn->y&&y<btn->y+btn->h)
  	return 1;
 }
 return 0;
}

//�ͷŰ�ť�ڴ�
void btn_free(Button*btn)
{
 if(btn->text!=NULL)
 	free(btn->text);
 free(btn);
}

#endif

