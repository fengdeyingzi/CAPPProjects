#include "base.h"
#include "ex_math.h"
#include <math.h>

/*
��shell��ϣ��������
shell����һ���� shell ����������1969�귢���ġ������Ȱ����k(k>=1)���Ǽ���Ԫ���ź�������Сkֵ��һ��ȡ��һ�룩��������ֱ��k=1ʱ���������������������������룺
*/
void shell(int *a,int n)
{
int i,j,k,x;
k=n/2; /*���ֵ*/
while(k>=1) {
for(i=k;i<n;i++) {
x=a[i];
j=i-k;
while(j>=0&&x<a[j]) {
a[j+k]=a[j];
j-=k;
}
a[j+k]=x;
}
k/=2; /*��С���ֵ*/
}
}



//�жϵ�(x,y)�Ƿ��ھ�������(rectx,recty,rectw,recth)��
int isPointCollRect(int x,int y,int rectx,int recty,int rectw,int recth)
{
	if(x>=rectx && x<rectx+rectw && y>=recty && y<recty+recth)
	{
		return TRUE;
	}
	return FALSE;
}


// ���κ�Բ����ײ���
int isCirCollRect(float circleXPos, float circleYPos, float radius, float rectX, float rectY, float rectW, float rectH)
{
    float arcR  = radius;
    float arcOx = circleXPos;
    float arcOy = circleYPos;

    //�ֱ��жϾ���4��������Բ�ĵľ����Ƿ�<=Բ�뾶�����<=��˵����ײ�ɹ�   
    if(((rectX-arcOx) * (rectX-arcOx) + (rectY-arcOy) * (rectY-arcOy)) <= arcR * arcR)   
        return TRUE;   
    if(((rectX+rectW-arcOx) * (rectX+rectW-arcOx) + (rectY-arcOy) * (rectY-arcOy)) <= arcR * arcR)   
        return TRUE;   
    if(((rectX-arcOx) * (rectX-arcOx) + (rectY+rectH-arcOy) * (rectY+rectH-arcOy)) <= arcR * arcR)   
        return TRUE;   
    if(((rectX+rectW-arcOx) * (rectX+rectW-arcOx) + (rectY+rectH-arcOy) * (rectY+rectH-arcOy)) <= arcR * arcR)   
        return TRUE;

    //�жϵ�Բ�ĵ�Y������������ʱX��λ�ã����X��(rectX-arcR)��(rectX+rectW+arcR)�����Χ�ڣ�����ײ�ɹ�   
    float minDisX = 0;   
    if(arcOy >= rectY && arcOy <= rectY + rectH)
    {   
        if(arcOx < rectX)   
            minDisX = rectX - arcOx;   
        else if(arcOx > rectX + rectW)   
            minDisX = arcOx - rectX - rectW;   
        else    
            return TRUE;   
        if(minDisX <= arcR)   
            return TRUE;   
    }

    //�жϵ�Բ�ĵ�X������������ʱY��λ�ã����X��(rectY-arcR)��(rectY+rectH+arcR)�����Χ�ڣ�����ײ�ɹ�
    float minDisY = 0;   
    if(arcOx >= rectX && arcOx <= rectX + rectW)
    {   
        if(arcOy < rectY)   
            minDisY = rectY - arcOy;   
        else if(arcOy > rectY + rectH)   
            minDisY = arcOy - rectY - rectH;   
        else  
            return TRUE;   
        if(minDisY <= arcR)   
            return TRUE;   
    }

    return FALSE; 
}

// �߶κ��߶���ײ���
/*
int IsLineCollisionLine(int p1, int p2, int p3, int p4)
{
    float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) 
        return FALSE;

    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

    // Check if the x and y coordinates are within both lines
    if ( x < MIN(x1, x2) || x > MAX(x1, x2) ||
        x < MIN(x3, x4) || x > MAX(x3, x4) )
        return FALSE;

    if ( y < MIN(y1, y2) || y > MAX(y1, y2) ||
        y < MIN(y3, y4) || y > MAX(y3, y4) ) 
        return FALSE;

    return TURE;
}
*/


int isCollRect(int x1, int y1, int w1, int h1, int x2, int  y2, int w2, int h2) 
		{  
			//Logcat.e(""+x1 + " " + y1 + " " + w1+ " "  + h1+ " "  + x2+ " "  + y2+ " "  + w2+ " "  + h2);
		
		//������1 λ�ھ���2 �����  
		if (x1 > x2 && x1 >= x2 + w2)
		{  
		return FALSE;  
		//������1 λ�ھ���2 ���Ҳ�  
		} 
		else if (x1 < x2 && x1 + w1 <= x2)
		{ 
		return FALSE;  
		//������1 λ�ھ���2 ���Ϸ�  
		} 
		else if (y1 > y2 && y1 >= y2+ h2) 
		{  
		return FALSE;  
		//������1 λ�ھ���2 ���·�  
		} 
		else if (y1 < y2 && y1 + h1 <= y2) 
		{  
		return FALSE;  
		}  
		
		//���в��ᷢ����ײ��������ʱ���϶�������ײ��  
		return TRUE;  
		}
	
	
	static float ex_toRad(float a)
	{
		return (a*3.14159265f)/180;
	}
	
	
		//��(x,y)��תָ������r���õ���ת�������
	//��תһ��ˮƽ�ߣ��õ���ת�������
//��������ת���ĵ�(px,py)����ת����뾶rx����ת����뾶ry�� ��ת������ָ��(*x,*y)
	void toSpin(int px,int py,int rx,int ry,int r,int* x,int* y)
	{
		
		*x=(int)( px+(rx)*cos(ex_toRad(r)));
		*y=(int)( py+(ry)*sin(ex_toRad(r)));

		
	}
	
	//������֮����� �����ڼ���Բ��Բ����ײ(������Բ��Բ�ľ���������ǵİ뾶ֻ�ͣ���ô��ײ�ɹ�)
	float getLineSize(int x,int y,int x2,int y2)
	{
		
		return sqrt( (x2-x)*(x2-x)+ (y2-y)*(y2-y));
	}
	
	
	
	//������֮�仡��
	float getRadiam(float x,float y,float rx,float ry)
	{float dx,dy;
		dx=rx-x;
		dy=ry-y;
		float r=(atan((dy) / (dx))*180/3.14159265f);

		//���½�
		if(dx>=0 && dy>=0)
			r=r;
		//���½�
		else if(dx<=0&& dy>=0)
			r=90+r+90;
		//���Ͻ�
		else if(dx<=0&&dy<=0)
			r=180+r;
		//���Ͻ�
		else if(dx>=0 && dy<=0)
			r=90+r+270;

		return r;
	}

	