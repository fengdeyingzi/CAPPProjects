#include <base.h>


int event(int type, int p1, int p2)
{
    if(KY_DOWN == type)
    {
        switch(p1)
        {
         //�����ؼ��˳�
        case _SRIGHT:
            exit();
            break;
        }
    }

    return 0;
}

//����ʱ�����ڽṹ��
typedef struct
{
    uint16 year;                 //��
    uint8  month;                //��
    uint8  day;                  //��
    uint8  hour;                 //ʱ��24Сʱ��
    uint8  minute;               //��
    uint8  second;               //��
}mr_datetime;

int init(void)
{
    mr_datetime date;
    char text[300];
    getdatetime(&date);
    sprintf(text, "%d��%d��%d��%dʱ%d��%d��", date.year, date.month, date.day, date.hour, date.minute, date.second);
        printf("��ǰ���ڣ�%d��%d��%d��%dʱ%d��%d��",date.year,date.month,date.day,date.hour,date.minute,date.second);
    
    cls(0,0,0);
    dtext(text,0,0,75,195,245,0,2);
    dtext("�������printf",0,100,75,195,245,0,2);
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
