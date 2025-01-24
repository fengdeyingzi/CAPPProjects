/*
精灵文件输出

编写：风的影子

*/
#ifndef _SPRITE_WRITE_H_
#define _SPRITE_WRITE_H_

//坦克图块 34*34
//图片大小 1088*374


//输出rectflip(纵向计算rectflip坐标)

void printf_rectf(int x,int y,int width,int height,int movex,int movey);

//快速生成精灵文件
//图片上每一行为一个动作
//参数：图片资源宽度 高度，图块宽度 高度
void printf_sprite(int width,int height,int itemw,int itemh);

//快速生成地图图块精灵文件
//参数：图片资源宽度 高度，图块宽度 高度
void printf_mapsprite(int width,int height,int itemw,int itemh);

//获取图块精灵，需要手动释放内存
char *getMapsprite(int width,int height,int itemw,int itemh);


void printf_xml();

/*
void printf_tmx(char *filename)
{
 int len=getlen(filename);
 char *buf=malloc(len+1);
 int f=open(filename,1);
 read(f,buf,len);
 buf[len]=0;
 char *head;
 char *word;
 int type;
 int i=0;
 char c;
 int item=0;
 while(c=buf[i])
 {
  switch(type)
  {
   case 0:
   if(c=='<')
   {
    head=buf+i+1;
    type=1;
   }
   break;
   case 1:
   if(c=='=')
   {
    type=2;
   }
   else if(c=='>')
   {
    type=0;
   }
   break;
   case 2:
   if(c=='\"')
   {
    word=buf+i+1;
    type=3;
   }
   break;
   case 3:
   if(c=='\"')
   {
    if(strncmp(head,"tile ",5)==0)
    {
     
     printf("%d,",atoi(word));
     if(atoi(word)<10)
     printf(" ");
     item++;
     
     if(item%20==0)
     printf("\n");
    }
    type=4;
   }
   break;
   case 4:
   if(c=='>')
   {
    type=0;
   }
   break;
   case 5:
   break;
   case 6:
   break;
   
   
  }
  i++;
  
 }
 
}

*/

#endif