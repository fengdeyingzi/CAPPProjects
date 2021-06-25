#ifndef CHECK_H_INCLUDED
#define CHECK_H_INCLUDED

#include <graphics.h>
#include <game_math.h>


//�ؼ��ṹ��
typedef struct {
  char *name;
  int isCheck;         //�ؼ�״̬
  int x;          //�ؼ�x����
  int y;          //�ؼ�y����
  int32 down;     //�ؼ�������ͼ
  int32 b0;       //�ؼ��ǹ�ѡ��ͼ
  int32 b1;       //�ؼ���ѡ��ͼ
}Check;

/*�ؼ���С�ǹ̶���,�޸���Ļ��С�ؼ���С����Ÿı�*/


/*  ����BOX
    x  �ؼ�x����
    y  �ؼ�y����
    ����ֵ:
      ʧ��  NULL
      �ɹ�  �ؼ����*/
void *checkbox_create(int x,int y){
  Check * New = malloc(sizeof(Check));
  //�����ڴ�
  
  if((New->down = readBitmapFromAssets("check/down-box.png")) <= 0){
    printf("Draw_box[check/down-box.png]\n");
    free(New);
    return NULL;}
  if((New->b0 = readBitmapFromAssets("check/Box-0.png")) <= 0){
    printf("Draw_box[check/Box-0.png]\n");
    free(New);
    return NULL;}
  if((New->b1 = readBitmapFromAssets("check/Box-1.png")) <= 0){
    printf("Draw_box[check/Box-1.png]\n");
    free(New);
    return NULL;}
  //����Ҫ����ͼʧ���ͷ��ڴ沢����NULL
  
  New->isCheck = 0;  //��ʼ��Ϊδ��ѡ״̬
  New->x = x;   //��ʼ��x����
  New->y = y;   //��ʼ��y����
  return New;   //����
}


/*  ����CIR
    x  �ؼ�x����
    y  �ؼ�y����
    ����ֵ:
      ʧ��  NULL
      �ɹ�  �ؼ����*/
void * check_cir_create(int x,int y){
  Check * New = malloc(sizeof(Check));
  //�����ڴ�
  
  if((New->down = readBitmapFromAssets("check/down-Cir.png")) <= 0){
    printf("Draw_box[check/down-Cir.png]\n");
    free(New);
    return NULL;}
  if((New->b0 = readBitmapFromAssets("check/Cir-0.png")) <= 0){
    printf("Draw_box[check/Cir-0.png]\n");
    free(New);
    return NULL;}
  if((New->b1 = readBitmapFromAssets("check/Cir-1.png")) <= 0){
    printf("Draw_box[check/Cir-1.png]\n");
    free(New);
    return NULL;}
  //����Ҫ����ͼʧ���ͷ��ڴ沢����NULL
  
  New->isCheck = 0;   //��ʼ��Ϊδ��ѡ״̬
  New->x = x;    //��ʼ��x����
  New->y = y;    //��ʼ��y����
  return New;    //����
}


/*  ����BUTTON
    x  �ؼ�x����
    y  �ؼ�y����
    ����ֵ:
      ʧ��  NULL
      �ɹ�  �ؼ����*/
void * check_button_create(int x,int y){
  Check * New = malloc(sizeof(Check));
  //�����ڴ�
  
  if((New->down = readBitmapFromAssets("check/down-Rect.png")) <= 0){
    printf("Draw_box[check/down-Rect.png]\n");
    free(New);
    return NULL;}
  if((New->b0 = readBitmapFromAssets("check/Rect-0.png")) <= 0){
    printf("Draw_box[check/Rect-0.png]\n");
    free(New);
    return NULL;}
  if((New->b1 = readBitmapFromAssets("check/Rect-1.png")) <= 0){
    printf("Draw_box[check/Rect-1.png]\n");
    free(New);
    return NULL;}
  //����Ҫ����ͼʧ���ͷ��ڴ沢����NULL
  
  New->isCheck = 0;  //��ʼ��Ϊδ��ѡ״̬
  New->x = x;   //��ʼ��x����
  New->y = y;   //��ʼ��y����
  return New;   //����
}



/*  ���ƿؼ�ALL
    id  �ؼ����*/
void check_draw(Check * id){
  if(id == NULL)
    return;
  //�ؼ�����NULLֱ�ӷ���
  
  if(id->id == 0)  //���ƿؼ�������ͼ
    drawBitmap(id->b0,id->x,id->y);
  if(id->id == 1){ //���ƿؼ������빴ѡ��ͼ
    drawBitmap(id->b0,id->x,id->y);
    drawBitmap(id->b1,id->x,id->y);
  }
}



/*  ��ؿؼ�BOX
    id  �ؼ����
    type  Ӧ���¼������¼�
    x     Ӧ���¼�������Ļx����
    y     Ӧ���¼�������Ļy����
    ����ֵ:
      ��ť��ɾ�� -1
      �ǹ�ѡ     0
      ��ѡ       1*/
int checkbox_event(Check * id,int type,int x,int y){
   if(id == NULL)
      return -1;
   //�ؼ�����NULL����-1

   if(game_rect(x,y,id->x+10,id->y+10,60,60)){
   //x y���ڿؼ�������
      if(type == MS_DOWN){
         drawBitmap(id->down,id->x,id->y);
         ref(id->x,id->y,80,80);
      }
      //������ʾ����Ч��
      if(type == MS_UP)id->id=(id->id==0)?1:0;
      //�ͷŸ���״̬
   }
   return id->id;//���ؿؼ�״̬
}


/*����дע���ˣ�ÿ�����ж��ǲ��ǵ���NULL����Ϊ��ɾ���˿ؼ�֮����ʾ���߼�س���������Ϊ�ڴ��ͷ��ˣ��������ж��ǲ���ɾ���ˣ����о����õ�ʱ��Ҫע�⣬-1�ǲ����� 0�ǹر� 1�Ǵ�*/





/*  ��ؿؼ�CIR
    id  �ؼ����
    type  Ӧ���¼������¼�
    x     Ӧ���¼�������Ļx����
    y     Ӧ���¼�������Ļy����
    ����ֵ:
      ��ť��ɾ�� -1
      �ǹ�ѡ     0
      ��ѡ       1*/
int checkcir_event(Check * id,int type,int x,int y){
  
   if(id == NULL)
     return -1;
   if(game_cir(x,y,id->x+40,id->y+40,20)){
      if(type == MS_DOWN){
         drawBitmap(id->down,id->x,id->y);
         ref(id->x,id->y,80,80);
      }
      if(type == MS_UP)id->isCheck=(id->isCheck==0)?1:0;
   }
   
   return id->id;
}


/*  ��ؿؼ�BUTTON
    id  �ؼ����
    type  Ӧ���¼������¼�
    x     Ӧ���¼�������Ļx����
    y     Ӧ���¼�������Ļy����
    ����ֵ:
      ��ť��ɾ�� -1
      �ǹ�ѡ     0
      ��ѡ       1*/
int check_button_event(Check * id,int type,int x,int y){
   if(id == NULL)
     return -1;
   
   if(game_rect(x,y,id->x,id->y,100,60)){
      if(type == MS_DOWN){
         drawBitmap(id->down,id->x,id->y);
         ref(id->x,id->y,100,60);
      }
      if(type == MS_UP)id->isCheck=(id->isCheck==0)?1:0;
   }
   
   return id->id;
}



/*  ɾ���ؼ�
    id  �ؼ����
    ����ֵ:
      �յ�ַ*/
void *check_free(Check * id){
  if(id == NULL)
    return id;
  bitmapFree(id->down);
  bitmapFree(id->b0);
  bitmapFree(id->b1);
  free(id);
  return NULL;
}




#endif