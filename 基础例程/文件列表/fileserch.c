#include <base.h>

int32 dialogf;
/*
�ļ�����

*/



void find(void)
{
    int32 f;
    int dy;
    int fontw,fonth;
    char buffer[255];
    int i;
    textwh("��",0,1,&fontw,&fonth);
    f=findstart("",buffer,255);
    printf("\r\nget \"%s\",f=%d\r\n",buffer,f);
    for(i=0; i<30; i++)
    {
        int ret =findnext(f,buffer,255);
        printf("get \"%s\",ret=%d\r\n",buffer,ret);
       dtext(buffer,0,dy,255,255,255,0,1);
     dy+=fonth;
    }
    printf("\r\nfindstop ret=%d\r\n",findstop(f));
    ref(0, 0, SCRW, SCRH);
}


int event(int type, int p1, int p2)
{
    if(KY_DOWN == type)
    {
        switch(p1)
        {
        case _1:
        case _BACK:
            exit();
            break;
        case _MENU:
            find();
            break;
        case _3:
            dialogf=dlgcreate("\x8f\xd9\x66\x2f\x68\x7\x98\x98\0\0","\x8f\xd9\x66\x2f\x51\x85\x5b\xb9\0\0",1);
            break;
        default:
            break;
        }
    }
    if(type == MR_DIALOG)//�Ի�����Ϣ
    {
        char *text;

        dlgdel(dialogf);
        cls(0,0,0);
        switch(p1)
        {
        case DLG_OK:
            text="����ȷ��";
            break;
        case DLG_CANCEL:
            text="����ȡ��";
            break;
        }
        dtext(text,0,0,255,255,0,0,1);
        ref(0,0,SCRW,SCRH);
    }


    return 0;
}

int init(void)
{
    int32 start,i;
    
    cls(0, 0, 0);
    dtext("����ۼӼ���",0,0,255,255,0,0,1);
    ref(0, 0, SCRW, SCRH);

    start=getuptime();
    for(i=0 ; i<10000 ; i++);
    start= getuptime()-start;
    printf("���%dms\r\n",start);

    cls(0, 0, 0);
    dtext("���˵����ļ�����",0,0,255,255,0,0,1);
    ref(0, 0, SCRW, SCRH);



    return 0;
}

int pause(void)
{
    printf("pause\r\n");
    return 0;
}

int resume(void)
{
    printf("resume\r\n");
    return 0;

}
