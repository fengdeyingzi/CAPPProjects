/*
  ��ť�ؼ�
��by�����Ӱ��
*/

//��ť�ṹ��

typedef struct 
{
int id; //��ťid
int type;//��ť״̬������1���ͷ�0������-1
char *text; //��ť����
int textx; //����x����
int texty; //����y����
int x; //��ťλ��x
int y; //��ťλ��y
int w; //��ť���
int h; //��ť�߶�
}button;
int id=0;

//������ť
//�����ֱ��� ��ť���� ��ťx���� y���� ��� �߶� 
void* new_button(char *text,int x,int y,int w,int h)
{
int fw,fh;
 button *btn;
btn=malloc(sizeof(button));
btn->text=text;
btn->x=x; 
btn->y=y;
btn->w=w;
btn->h=h;
btn->type=0;
btn->id=id;id++;
textwh(text,0,1,&fw,&fh);
btn->textx=x+(w-fw)/2;
btn->texty=y+(h-fh)/2;
return btn;
}

//��ʾ��ť ��������ť�ṹ��ָ��
void button_draw(button *btn)
{

if(btn->type!=-1)
  {
   //����һ������
drect(btn->x+2,btn->y+2,btn->w-4,btn->h-4,68-btn->type*40,168-btn->type*40,240-btn->type*40);
drect(btn->x+4,btn->y+4,btn->w-8,btn->h-8,230,238,245);
  //��������
dtext(btn->text,btn->textx,btn->texty,50,50,50,0,1);
  }
}

//���ð�ť���� ��������ť�ṹ��ָ�� �µİ�ť����
void button_settext(button *btn,char *text)
{
btn->text=text;
draw_button(btn);
ref(btn->x,btn->y,btn->w,btn->h);
}


//�жϰ�ť����¼� ��������ťָ�� ����x���� ����y����
//����ֵ��TRUE(1)�ɹ� FALSE(0)ʧ��
int button_impact(button *btn,int x,int y)
{
if(x>btn->x && x<btn->x+btn->w && y>btn->y && y<btn->y+btn->h)
return 1;
else return 0;


}

//�ͷŰ�ť�ڴ�
void button_free(button *btn)
{
 free(btn);
}


