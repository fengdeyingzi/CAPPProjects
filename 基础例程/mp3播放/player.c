#include <base.h>
#include <sound.h>

//�뽫Ҫ���ŵ�mp3����Ϊ1.mp3���ŵ������ļ���
#define FILENAME "c/����/1.mp3"

#define _MP3 3//mp3�豸������ֵ�ο�sound.h�е�enum��

int init(void)
{
    cls(0,0,0);
    if(soundinit(_MP3))
    {
        dtext("��֧��",0,0,255,255,255,FALSE,1);
    }
    else
    {
        dtext("���ڲ���",0,0,255,255,255,FALSE,1);
        soundloadfile(_MP3,FILENAME);
        soundplay(_MP3,0,FALSE);
    }
    ref(0,0,SCRW,SCRH);
    return 0;
}

int event(int type, int p1, int p2)
{
    if(KY_DOWN == type)
    {
        switch(p1)
        {
        case _SRIGHT:
            exitapp();
            break;
        case _1:
            break;
        }
    }

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

int exitapp(void)
{
    soundstop(_MP3);
    soundclose(_MP3);
    exit();
    return 0;
}