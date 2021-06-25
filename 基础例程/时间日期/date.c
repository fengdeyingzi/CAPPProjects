#include <base.h>


int event(int type, int p1, int p2)
{
    if(KY_DOWN == type)
    {
        switch(p1)
        {
         //按返回键退出
        case _SRIGHT:
            exit();
            break;
        }
    }

    return 0;
}

//设置时间日期结构体
typedef struct
{
    uint16 year;                 //年
    uint8  month;                //月
    uint8  day;                  //日
    uint8  hour;                 //时，24小时制
    uint8  minute;               //分
    uint8  second;               //秒
}mr_datetime;

int init(void)
{
    mr_datetime date;
    char text[300];
    getdatetime(&date);
    sprintf(text, "%d年%d月%d日%d时%d分%d秒", date.year, date.month, date.day, date.hour, date.minute, date.second);
        printf("当前日期：%d年%d月%d日%d时%d分%d秒",date.year,date.month,date.day,date.hour,date.minute,date.second);
    
    cls(0,0,0);
    dtext(text,0,0,75,195,245,0,2);
    dtext("已输出到printf",0,100,75,195,245,0,2);
    ref(0,0,SCRW,SCRH);
    return 0;
}


int pause(void)
{
    return 0;
}

int resume(void)
{
    return 0;
}
