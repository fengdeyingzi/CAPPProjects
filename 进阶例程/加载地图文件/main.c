/************************
**���ص�ͼ�ļ�**���ߣ�С�**
*��鿴��ͼassets/map.max*
*************************/
#include <base.h>

int map[10][10];

void readMap(char* mapName)
{
  /*ֻ����ȡ��ͼ�ļ����*/
  int Map=open(mapName,1);
  char* text=malloc(1);
  memset(text,0,2);
 
  printf("%s\n\n",mapName);
  
  int i=0,j=0;
  
  while(1)
  {
    /*��ȡ��text*/
    int len=read(Map,text,1);
    printf("���ݣ�%s�����ȣ�%d\n",text,len);
     
    if(len==1)
    {
      map[i][j]=atoi(text);
      j++;
    
      if(strcmp(text,"\n")==0)
      {
        i++;
        j=0;
      }
    }
    else
    {
      break;
    }
    
  }
  
  close(Map);
}

void printMap()
{
  cls(0,0,0);
  int i,j;
  for(i=0;i<10;i++)
  {
    for(j=0;j<10;j++)
    {
      printf("%2d",map[i][j]);
      if(map[i][j]==1)
      drect(j*50+1,i*50+1,50-2,50-2,100,100,100);
    }
    printf("\n");
  }
  ref(0,0,SCRW,SCRH);
}

int init()
{
  readMap("CIDE/��������/���ص�ͼ�ļ�/assets/map.max");
  printMap();
  return 0;
}



//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
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
 