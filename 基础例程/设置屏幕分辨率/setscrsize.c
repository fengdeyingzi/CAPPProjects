#include <base.h>

/*
设置屏幕分辨率

调用函数setscrsize设置分辨率
该函数将重新初始化屏幕
SCRW SCRH 的值也会随之改变

建议在init函数里调用此函数

*/
char text[300];

int init()
{
    //设置屏幕分辨率为480*800
    setscrsize(480,800);
    cls(0,0,0);
    
    sprintf(text,"屏幕宽度：%d",SCRW);
    printf("屏幕缓存区宽高 %d %d",SCRW,SCRH);
    
    
    dtext(text, 30,30,255,255,255,0,1);
    ref(0,0,SCRW,SCRH);
    
    return 0;
}




int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        
        case _SRIGHT:
            exit();
            break;
        case _1:
            break;
        }
    }
    
    

    return 0;
}

int pause()
{
    return 0;
}

int resume()
{
    return 0;
}
 