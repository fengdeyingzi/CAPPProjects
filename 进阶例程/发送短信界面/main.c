/***********************
**���Ͷ��Ž���**���ߣ�С�
************************/

#include <base.h>
#include <android.h>

/*****************
*unicode����תgb
*���ֶ��ͷŷ����ڴ�
*���� ���Ӱ��
******************/
char *unToGb(char *text)
{
 char *input= text;
int input_len= wstrlen(input);
 char *output= malloc(input_len+2);
 int output_len;
 u2c( input, input_len, &output, &output_len);
 return output;
}


/***********************
*����һ����ť�����ذ�ť���
************************/
int addBtn(char* name)
{
  /*����һ����ť*����Button*/
  int btn=createView("Button");
  char* text=malloc(100);
  
  sprintf(text,"
  android:id=\"0\"
  ");
  
  /*���ÿؼ�����*/
  setView(btn,text);
  
  /*���ÿؼ�����*/
  view_setText(btn,name); 
  
  free(text);
  return btn;
}

/***************
*�û�������Ͱ�ť
***************/
void go(int id)
{
  if(id == 3)
  {
    char* temp=malloc(100);
    char* gbNum=malloc(100);
    char* Text=malloc(100);
    
    //��ȡ����
    int num=findViewById(1);
    temp=view_getText(num);
    gbNum=unToGb(temp);

    //��ȡ����
    int text=findViewById(2);
    Text=view_getText(text);
    
    /*���Ͷ��ţ�un�������ݣ�*/
    sms(gbNum,Text,1);
    
    /*����һ����ť���ɻ�������*/
    int see=findViewById(4);
    int btn=addBtn(Text);
    addView(see,btn);
    
    free(temp);
    free(gbNum);
    free(Text);
  }
}



//��ں�������������ʱ��ʼִ��
int init()
{
  cls(0,0,0);
  setContextView("sms.xml");
  ref(0,0,SCRW,SCRH);
  return 0;
}


//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
  if(VIEW_DOWN == type)
  {
    go(p1);
  }
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            clearView();
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
 