#include "base.h"
#include "android.h"


int init()
{
 
    cls(0, 0, 0);
    dtext("µã»÷ÆÁÄ»ÏÔÊ¾×ø±ê", 0, 0, 0, 255, 0, 0, 1);
    ref(0, 0, SCRW, SCRH);
       

    return 0;
}

//Ë¢ÐÂµ½ÆÁÄ»
int draw(int p0,int p1)
{
 
 char text[30];

 cls(0,0,0);
 dline(0, p1, SCRW, p1, 255, 255, 0);
 dline(p0, 0, p0, SCRH, 255, 0, 255);
 sprintf(text,"x=%d,y=%d",p0,p1);
 dtext(text, 0, 0, 255, 0, 0, 0, 1);
 ref(0, 0, SCRW, SCRH);
 return 0;
}
 


int event(int msg, int p0, int p1)
{
    if(msg==KY_DOWN && p0==_SRIGHT)
    {
        exit();
        return 0;
    }
    if(msg == MS_MOVE || msg == MS_DOWN)
    {
       draw(p0,p1);
    }
    return 0;    
}
int pause()
{
    printf("ÇÐ»»1");
    return 0;
}
int resume()
{
    printf("ÇÐ»»2");
    return 0;
}                                                                                                                                                                                       
