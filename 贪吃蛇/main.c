//加载系统头文件base.h
#include <base.h>
#include <exb.h>
#include <android.h>
#include <ex_math.h>
//蛇宽高
#define SWH 30

int32 timer;//定时器句柄
int kzfx;//控制方向

int foodx;//食物坐标
int foody;
int score;//分数
typedef struct Node
{
    int x;
    int y;
    int w;
    int h;
    int r;
    int g;
    int b;
    struct Node* Prior;//指向前驱节点指针域
    struct Node* Next;//指向后继节点指针域
}NODE;

NODE* headnode;

void headnodeinit(NODE** );
void add_list(NODE*);
struct Node fz(NODE* );
void she(NODE* );
void food();
void start_timer(int);
void shescore();
void delte_list(NODE* );
void traverse_list(NODE* );

//初始化蛇头
void headnodeinit(NODE** p)
{
    *p = (struct Node* )malloc(sizeof(struct Node));
    memset(*p, 0, sizeof(struct Node));
    (*p)->Prior = (*p)->Next = *p;
    
    NODE* q = *p;
    int i = 0;
    for(i = 0; i < 3; i++)
    {
        add_list(q);
     
    }

}
//遍历
void traverse_list(NODE* p)
{
    if(p->Next == p)
    {
        return;
    }
    else
    {
        NODE* q = p->Next;
        NODE per;
        per = fz(q);
        NODE t;
        
        if(kzfx == 0)
        {   
            q->x += SWH;
        }
        else if(kzfx == 1)
        {
            
            q->x -= SWH;
        }
        else if(kzfx == 2)
        {
            q->y += SWH;
        }
        else
        {
            q->y -= SWH;
        }
        char j = 0;
        int x = q->x;
        int y = q->y;     
        q->r = 120;
        while(q != p)
        { 
           if(j)
           {
               t = fz(q);
               q->x = per.x;
               q->y = per.y;
               if(x == q->x && y == q->y || x >= SCRW || -1 > x || 
               y >= SCRH || -1 > y)
               {
                  cls(0, 0, 0);
                  delte_list(q);
                  headnodeinit(&headnode);
                  traverse_list(headnode);
                  timerdel(timer);
                  timer = 0;
                  score = 0;
                  return;
               }
               per = t;
           }
           
           she(q);
           q = q->Next;
           j = 1;
        }
        shescore();
        food();
        if(isCollRect(x, y, SWH, SWH, foodx, foody ,SWH, SWH))
        {
           foodx = rand()%(SCRW - (SWH+SWH));
           foody = rand()%(SCRH - (SWH+SWH));
           add_list(p);
           score += 10;
        }   
        ref(0, 0, SCRW, SCRH);
    }
 
}
struct Node fz(NODE* p)
{
    struct Node per;
    per.x = p->x;
    per.y = p->y;
    return per;
}
//清空链表
void delte_list(NODE* head)
{
    if(head->Next == head)
    {
     
        return;
    }
    else
    {
        NODE* p = head->Next;
        NODE* q = NULL;  
        while(p != head)
        {
            q = p->Next;
            free(p);
            p = q;
           
        }
        
        free(head);
    }
 
}
void she(NODE* p)
{
    if(p != NULL)
    {     
       drect(p->x, p->y, p->w, p->h, p->r, p->g, p->b);   
    }
}
//添加一节到尾部
void add_list(NODE* p)
{  
    NODE* Pnew = (struct Node* )malloc(sizeof(struct Node));

    Pnew->x = SCRW/2;
    Pnew->y = SCRH/2;
    Pnew->w = SWH;
    Pnew->h = SWH;
    Pnew->r = 255;
    Pnew->g = 255;
    Pnew->b = 255;

    p->Prior->Next = Pnew;
    Pnew->Next = p;
    Pnew->Prior = p->Prior;
    p->Prior = Pnew;
}
//食物
void food()
{
    drect(foodx, foody, SWH, SWH, 250, 0, 0);
 
}

void start_timer(int data)
{
    cls(0, 0, 0); 
    traverse_list(headnode);
  
}
//分数
void shescore()
{
    char buf[20];
    sprintf(buf, "得分:%d", score);
    //显示GBK编码
    char *text = ex_coding(buf,strlen(buf),"UTF-8","GBK");
    dtext(text, 0, 0, 255, 230, 0, 0, 1);
    free(text);
}
//入口函数，程序启动时开始执行
int init()
{
    cls(0, 0, 0);
    ref(0, 0, SCRW, SCRH);
    timer = 0;
    kzfx = 0;
    score = 0;
    headnodeinit(&headnode);
    foodx = rand()%(SCRW - SWH);
    foody = rand()%(SCRH - SWH);    
    traverse_list(headnode);
    setpadtype(2);
    char *temp = "点击屏幕开始游戏";
    char *text = ex_coding(temp,strlen(temp),"UTF-8","GBK");
    dtext(text,10,100,255,255,255,0,1);
    free(text);
    ref(0,0,SCRW,SCRH);
    return 0;
}




//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
        delte_list(headnode);
        if(timer)
        {timerdel(timer);}
            exit();
            break;
        case _MENU:
            break;
        }
        
        if(_UP == p1)//上
        {
            if(headnode->Next->x != headnode->Next->Next->x)
            {kzfx = 3;}
        }
        if(_DOWN == p1)//下
        {
            if(headnode->Next->x != headnode->Next->Next->x)
            {kzfx = 2;}
        }
        if(_LEFT == p1)//左
        {
            if(headnode->Next->y != headnode->Next->Next->y)
            {kzfx = 1;}
        }
        if(_RIGHT == p1)//右
        {
            if(headnode->Next->y != headnode->Next->Next->y)
            {kzfx = 0;}
        }
    }
    
    if(MS_UP == type)//点击屏幕开始
    {
        if(!timer)
        {
            timer = timercreate();
            timerstart(timer, 100, 1234, "start_timer", TRUE);
            
        }
    }

    return 0;
}

//应用暂停，当程序进入后台或变为不可见时会调用此函数
int pause()
{
    return 0;
}

//应用恢复，程序变为可见时调用此函数
int resume()
{
    return 0;
}
 