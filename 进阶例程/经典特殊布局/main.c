/**************************
*�������Ⲽ��**���ߣ����Ӱ��
***************************/

#include <base.h>
#include <android.h>

/*�ؼ����Խṹ��*/
typedef struct
{
 int id;
 int x;
 int y;
 int w;
 int h;
} VIEW;


int init()
{
    cls(0,0,0);
    int barh=(SCRH-SCRW)/2;
    setContextView("a.xml");
    
    /*********************
    *����ṹ��ָ�벢��ֵ
    **********************/
    VIEW *view=malloc(sizeof(VIEW));
    view->id=0;
    view->x=0;
    view->y=0;
    view->w=SCRW;
    view->h=barh;
    setViewLayout(view);
    
    view->id=1;
    view->x=0;
    view->y=barh;
    view->w=SCRW*2/3;
    view->h=SCRW/3;
    setViewLayout(view);
    
    view->id=2;
    view->x=SCRW*2/3;
    view->y=barh;
    view->w=SCRW/3;
    view->h=SCRW*2/3;
    setViewLayout(view);
    
    view->id=3;
    view->x=0;
    view->y=barh+SCRW/3;
    view->w=SCRW/3;
    view->h=SCRW*2/3;
    setViewLayout(view);
    
    view->id=4;
    view->x=SCRW/3;
    view->y=barh+SCRW/3;
    view->w=SCRW/3;
    view->h=SCRW/3;
    setViewLayout(view);
    
    view->id=5;
    view->x=SCRW/3;
    view->y=barh+SCRW*2/3;
    view->w=SCRW*2/3;
    view->h=SCRW/3;
    setViewLayout(view);
    
    view->id=6;
    view->x=0;
    view->y=SCRH-barh;
    view->w=SCRW;
    view->h=barh;
    setViewLayout(view);
    free(view);
    
    ref(0,0,SCRW,SCRH);
    return 0;
}




//����view��λ��
void setViewLayout(VIEW *view)
{
 char text[300];
 sprintf(text,"
 android:layout_x=\"%d\"
 android:layout_y=\"%d\"
 android:layout_width=\"%d\"
 android:layout_height=\"%d\"
 ", view->x,view->y,view->w,view->h);
 int button=findViewById(view->id);

 if(button!=0)
 {
   /*�����ַ������ÿؼ�����*/
   setView(button,text);
 }
 
}


//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{ 
    printf("%d\n",p1);
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            exit();
            break;
        case _MENU:
            break;
        }
    }

    return 0;
}

//Ӧ����ͣ������������̨���Ϊ���ɼ�ʱ����ô˺���
int pause()
{
    return 0;
}

//Ӧ�ûָ��������Ϊ�ɼ�ʱ���ô˺���
int resume()
{
    return 0;
}
 