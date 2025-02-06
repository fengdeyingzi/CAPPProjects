
#ifndef _TILED_H_
#define _TILED_H_

#include <base.h>
#include "sprite_write.h"

extern char *readtiledToSprite(char *text);


//��ȡ�ı�����
char *readText(char *filename)
{
 int len;
 char *text;
 len=getlen(filename);
 if(len<=0)return NULL;
 text=malloc(len+1);
 int f=open(filename,1);
 if(f)
 {
 read(f,text,len);
 text[len]=0;
 close(f);
 }
 return text;
}

//д���ı�����
int writeText(char *filename,void *data,int len)
{
 remove(filename);
 int f=open(filename,2+8);
 if(f>0)
 {
  write(f,data,len);
  close(f);
 }
 else 
 {
  return -1;
 }
 
 return 0;
}

//��tmx�ļ�ת��Ϊ�����ļ�
int readTiledToSpriteFile(char *tilefilename,char* spritefilename)
{
 char *text=readText(tilefilename);
 char *sp_text=readtiledToSprite(text);
 writeText(spritefilename,sp_text,strlen(sp_text));
 free(text);
 free(sp_text);
 return 0;
}


//��tmx��ͼת��Ϊ����
char *readtiledToSprite(char *text)
{
 int i=0;
 char c;
 int type=0;
 char *buf;
 char *head;
 char *item;
 char *word;
 int width,height;
 int item_width,item_height;
 while(*text)
 {
  
  c=*text;
  //printf("%d %c\n",type,c);
  switch(type)
  {
   case 0:
   if(c=='<')
   type=1;
   break;
   case 1: //����ͷ��Ϣ
   head=text;
    
    type=2;
   
 
   break;
   case 2: //�����ո�
   if(c==' ')
   type=3;
   else if(c=='>')
   type=0;
   break;
   case 3: //��������
   item=text;
   type=4;
   if(c=='>')
   type=0;
   
   if(c=='>')
   type=0;
   if(c=='/')
   type=9;
   
   break;
   case 4: //����
   if(c=='=')
   type=5;
   break;
   case 5: //��������
   if(c=='"')
   {
    type=6;
    word=text+1;
   // printf("head %c \n",*head);
    if(strncmp(head,"map",3)==0)
   {
   printf("map\n"); if(strncmp(item,"tilewidth",5+4)==0)
    {
     item_width=atoi(word);
    }
    else if(strncmp(item,"tileheight",6+4)==0)
    {
     item_height=atoi(word);
    }
   }
   else if(strncmp(head,"image",5)==0)
   {
    printf("layer\n");
    if ( strncmp (item,"width",5)==0)
    {
     width=atoi(word);
    }
    else if(strncmp(item,"height",6)==0)
    {
     height=atoi(word);
    }
   }
   }
   break;
   case 6: //����������
   if(c=='"')
   {
    type=2;
   }
   break;
   case 7:
   if(c=='>')
   {
    type=0;
   }
   else if(c=='/')
   {
    type=9;
   }
   break;
   case 9:
   if(c=='>')
   type=0;
   break;
  }
  text++;
 }
printf("width=%d height=%d itemw=%d height=%d\n",width,height,item_width,item_height);
 buf=getMapsprite( width,height,item_width,item_height);

return buf;
}




//��ȡtmx��ͼ��ת��Ϊ����
void printf_tmx(char *filename)
{
 
 char *buf=readText(filename);
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


//��ȡtmx��ͼ��� �߶� ͼ���� �߶�
//���ص�ͼdata����Ҫ�ֶ��ͷ��ڴ�
int *readtiledInfo(char *text,int *width,int *height,int *item_width,int *item_height)
{
 int i=0;
 char c;
 int type=0;
 int img_width,img_height;
 char *buf;
 char *head;
 char *item;
 char *word;
 int *data=NULL;
 int offset=0;
 
 while(text[i])
 {
  
  c=text[i];
  //printf("%d %c\n",type,c);
  switch(type)
  {
   case 0:
   if(c=='<')
   type=1;
   break;
   case 1: //����ͷ��Ϣ
   head=text+i;
    
    type=2;
   
 
   break;
   case 2: //�����ո�
   if(c==' ')
   type=3;
   else if(c=='>')
   type=0;
   break;
   case 3: //��������
   item=text+i;
   type=4;
   if(c=='>')
   type=0;
   
   if(c=='>')
   type=0;
   if(c=='/')
   type=9;
   
   break;
   case 4: //����
   if(c=='=')
   type=5;
   break;
   case 5: //��������
   if(c=='"')
   {
    type=6;
    word=text+i+1;
    //printf("head %c item %c\n",*head,*item);
    if(strncmp(head,"map",3)==0)
   {
   printf("map\n"); if(strncmp(item,"tilewidth",5+4)==0)
    {
     *item_width=atoi(word);
    }
    else if(strncmp(item,"tileheight",6+4)==0)
    {
     *item_height=atoi(word);
    }
   }////////////////
   else if(strncmp(head,"image",5)==0)
   {
    printf("layer\n");
    if ( strncmp (item,"width",5)==0)
    {
     img_width=atoi(word);
     
    }
    else if(strncmp(item,"height",6)==0)
    {
     img_height=atoi(word);
     
     
    }
   }//////////
   else if(strncmp(head,"layer",5)==0)
   {
    if(strncmp(item,"width",5)==0)
    {
     *width=atoi(word);
     printf("width=%d\n",*width);
    }
    else if(strncmp(item,"height",6)==0)
    {
     *height=atoi(word);
     printf("height=%d\n",*height);
    }
    if( *width!=0 && *height!=0)
    {
     data=malloc(*width * (*height) *4);
     printf("malloc width%d height%d\n",*width,*height);
    }
   }//////////
   else if(strncmp(head,"tile ",5)==0)
    {
     if(strncmp(item,"gid",3)==0)
     data[offset++]=atoi(word);
    }
   }
   break;
   case 6: //����������
   if(c=='"')
   {
    type=2;
   }
   break;
   case 7:
   if(c=='>')
   {
    type=0;
   }
   else if(c=='/')
   {
    type=9;
   }
   break;
   case 9:
   if(c=='>')
   type=0;
   break;
  }
  i++;
 }


 printf("width=%d height=%d itemw=%d itemh=%d\n",*width,*height,*item_width,*item_height);

return data;
}


int *readTextInfo(char *text,int *width,int *height,int *item_width,int *item_height)
{
 
 int *data=NULL;
 int offset =0;
 char *head;
 char *item;
 char *word;
 int i=0;
 int type=0;
 char c;
 while(c=text[i])
 {
  //printf("%c",c);
  switch(type)
  {
   case 0:
   if(c=='[')
   type=1;
   break;
   case 1:
   head=text+i;
   type=2;
   break;
   case 2:
   if(c==']')
   type=3;
   break;
   case 3:
   if(c>='a' && c<='z')
   {
    item=text+i;
    type=4;
   }
   
   else if(c=='[')
   type=1;
   
   break;
   case 4:
   if(c=='=')
   {
    word=text+i+1;
    //printf("\nhead=%c item=%c word=%c\n",*head,*item,*word);
    if (strncmp(head,"header",6)==0)
   {
    if (strncmp(item,"width",5)==0)
    {
     *width=atoi(word);
    }
    else if(strncmp(item,"height", 6)==0)
    {
     *height=atoi(word);
     if( *width !=0 && *height!=0)
    {
     data=malloc(*width *(*height)*4);
     printf("\ndata�����ڴ�\n");
    }
    }
    else if(strncmp(item,"tilewidth",9)==0)
    {
     *item_width=atoi(word);
    }
    else if(strncmp(item,"tileheight",10)==0)
    {
     *item_height=atoi(word);
    }
    
   }
   else if(strncmp(head,"layer",5)==0)
   {
    if(strncmp(item,"data",4)==0)
    {
     char id;
     int type2=0;
     while(id=(*word))
     {
      switch(type2)
      {
       case 0:
       if(id>='0' && id<='9')
       {
        data[offset++]=atoi(word);
        type2=1;
       }
       break;
       case 1:
       if(id==',')
       type2=0;
       break;
       
      }
      word++;
     }
    }
   }
   type=3;
   }
   else if(c=='[')
   {
    type=1;
   }
   break;
   case 5:
   
   break;
   case 6:
   
   break;
   case 7:
   
   break;
   case 8:
   
   break;
   case 9:
   
   break;
   case 10:
   
   break;
   case 11://����data
   
   
   
  }
  
  i++;
  
 }
 
 
 printf("width=%d height=%d itemw=%d itemh=%d\n",*width, *height, *item_width, *item_height);

 
 
 return data;
}




#endif



