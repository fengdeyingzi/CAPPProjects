#include <base.h>
#include <math.h>
/*
*��Բ����
*by:�޺�
*/
int r=90;
int x=100;
int y=150;
void huaYuan(int r1,int ax,int by,int r,int g,int b)
//huaYuan(�뾶,Բ�ĺ�����,Բ��������,rɫֵ,gɫֵ,bɫֵ);
	{
		int a1=r1,b1=r1;
		int y,y2;
		for(int x=a1-r1/4*3;x<a1+r1/4*3;x++)
		{
			y=(int)(sqrt(r1*r1-(x-a1)*(x-a1)))+b1;
			y2=(int)(-sqrt(r1*r1-(x-a1)*(x-a1)))+b1;
	   dpointex(x+ax-r1,y+by-r1,r,g,b);
			 dpointex(x+ax-r1,y2+by-r1,r,g,b);
			 dpointex(y+ax-r1,x+by-r1,r,g,b);
			 dpointex(y2+ax-r1,x+by-r1,r,g,b);
		}
	}
int init()
{
    //����
    cls(0,0,0);
    huaYuan(r,x,y,255,255,0);
    
    //ˢ����Ļ
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
 