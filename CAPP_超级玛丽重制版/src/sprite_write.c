/*
精灵文件输出

编写：风的影子

*/


//坦克图块 34*34
//图片大小 1088*374
#include "base.h"
#include "sprite_write.h"

//输出rectflip(纵向计算rectflip坐标)

void printf_rectf(int x,int y,int width,int height,int movex,int movey)
{
 int i;
 int ix=0,iy=0;
 while(ix<width)
 {
 while(iy<height)
 {
 printf("   <picture>"
        "      <rectflip"
        "      x=\"%d\""
        "      y=\"%d\""
        "      width=\"%d\""
        "      height=\"%d\""
        "      px=\"%d\""
        "      py=\"%d\""
        "      />"
        "   </picture>\n",
        0,0,movex,movey,x+ix,y+iy);
 iy+=movey;
 }
 ix+=movex;
 }
}

//快速生成精灵文件
//图片上每一行为一个动作
//参数：图片资源宽度 高度，图块宽度 高度
void printf_sprite(int width,int height,int itemw,int itemh)
{
 int ix=0,iy=0;
 if(itemw<=0 || itemh<=0)
 return ;
 printf("<sprite"
        " bitmap=\"\""
        " width=\"%d\""
        " height=\"%d\""
        ">\n",itemw,itemh);
 for(iy=0;iy<=height-itemh;iy+=itemh)
 {
  printf("  <action"
         "  name=\"\""
         "  mode=\"1\">\n");
  
  for(ix=0;ix<=width-itemw;ix+=itemw)
  {
   printf("   <picture>"
          "      <rectflip"
          "      x=\"%d\""
          "      y=\"%d\""
          "      width=\"%d\""
          "      height=\"%d\""
          "      px=\"%d\""
          "      py=\"%d\""
          "      />"
          "   </picture>\n",
          0,0,itemw,itemh,ix,iy);
   
  }
  printf("  </action>\n");
 }
 
 printf("</sprite>\n");
}

//快速生成地图图块精灵文件
//参数：图片资源宽度 高度，图块宽度 高度
void printf_mapsprite(int width,int height,int itemw,int itemh)
{
 int ix=0,iy=0;
 if(itemw<=0 || itemh<=0)
 return;
 printf("<sprite"
        " bitmap=\"\""
        " width=\"%d\""
        " height=\"%d\""
        ">\n",itemw,itemh);
 
 for(iy=0;iy<=height-itemh;iy+=itemh)
 for(ix=0;ix<=width-itemw;ix+=itemw)
 {
  printf("  <action"
         "  name=\"\""
         ">\n");
  
  
  {
   printf("   <picture>"
          "      <rectflip"
          "      x=\"%d\""
          "      y=\"%d\""
          "      width=\"%d\""
          "      height=\"%d\""
          "      px=\"%d\""
          "      py=\"%d\""
          "      />"
          "   </picture>\n",
          0,0,itemw,itemh,ix,iy);
   
  }
  printf("  </action>\n");
 }
 
 printf("</sprite>\n");
}

//获取图块精灵，需要手动释放内存
char *getMapsprite(int width,int height,int itemw,int itemh)
{
 int ix=0,iy=0;
 if(itemw<=0 || itemh<=0)
 return NULL;
 char *text=malloc(50*1024);
 memset(text,0,50*1024);
 char buf[200];
 sprintf(buf,"<sprite"
             " bitmap=\"\""
             " width=\"%d\""
             " height=\"%d\""
             ">\n"
             " <action"
             "  name=\"0\""
             "  >"
             "  <picture>"
             "  </picture>"
             "  </action>",
             itemw,itemh);
 strcat(text,buf);
 for(iy=0;iy<=height-itemh;iy+=itemh)
 for(ix=0;ix<=width-itemw;ix+=itemw)
 {
  sprintf(buf,"  <action"
              "  name=\"\""
              ">\n");
  strcat(text,buf);
  
  {
   sprintf(buf,"   <picture>"
               "      <rectflip"
               "      x=\"%d\""
               "      y=\"%d\""
               "      width=\"%d\""
               "      height=\"%d\""
               "      px=\"%d\""
               "      py=\"%d\""
               "      />"
               "   </picture>\n",
               0,0,itemw,itemh,ix,iy);
   strcat(text,buf);
  }
  sprintf(buf,"  </action>\n");
  strcat(text,buf);
 }
 
 sprintf(buf,"</sprite>\n");
 strcat(text,buf);
 
 return text;
}


void printf_xml()
{
 //坦克1
//printf_rectf(0,34*3,1088,34,34,0);
printf_rectf(0,34*3,34*2,34, 34,34);

}


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

