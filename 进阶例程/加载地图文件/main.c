/************************
**加载地图文件**作者：小蟀**
*请查看地图assets/map.max*
*************************/
#include <base.h>

int map[10][10];

void readMap(char* mapName)
{
  /*只读读取地图文件句柄*/
  int Map=open(mapName,1);
  char* text=malloc(1);
  memset(text,0,2);
 
  printf("%s\n\n",mapName);
  
  int i=0,j=0;
  
  while(1)
  {
    /*读取到text*/
    int len=read(Map,text,1);
    printf("内容：%s，长度：%d\n",text,len);
     
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
  readMap("CIDE/进阶例程/加载地图文件/assets/map.max");
  printMap();
  return 0;
}



//event函数，接收消息事件
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

//应用暂停，当程序进入后台或变为不可见时会调用此函数
int pause()
{
    return 0;
}

//应用恢复，程序变为可见时调用此函数
int resume()
{
    return 0;
}
 