
#ifndef _BAOZHA_H_
#define _BAOZHA_H_

typedef struct
{
 int32 sprite; //����
 int x;
 int y;
} _BAOZHA;

//��������
_BAOZHA *bao_create(int bitmap)
{
 _BAOZHA *baozha = malloc(sizeof(_BAOZHA));
 memset(baozha,0,sizeof(_BAOZHA));
 baozha->sprite= sp_read("guang.sprite",bitmap);
 
 return baozha;
};

//����
_BAOZHA *bao_copy(_BAOZHA *bao)
{
 _BAOZHA *temp = malloc(sizeof(_BAOZHA));
 memcpy(temp,bao,sizeof(_BAOZHA));
 temp->sprite=sp_copy(bao->sprite);
 return temp;
};

//��������
int bao_setxy(_BAOZHA *bao,int x,int y)
{
 bao->x=x;
 bao->y=y;
 sp_setxy(bao->sprite,x-78,y-78);
 return 0;
}
//��ȡ����
int bao_getx(_BAOZHA *bao)
{
 return bao->x;
}

int bao_gety(_BAOZHA *bao)
{
 return bao->y;
}

//����
int bao_run(_BAOZHA *bao)
{
 sp_run(bao->sprite);
 return 0;
}

//����Ƿ����
int bao_isDestory(_BAOZHA *bao)
{
 if(sp_getFrame(bao->sprite)>=6)
 return TRUE;
 else
 return FALSE;
}

//����
int bao_draw(_BAOZHA *bao)
{
 sp_draw(bao->sprite,NULL);
 return 0;
}

//�ͷ�
int bao_free(_BAOZHA *bao)
{
 sp_free(bao->sprite);
 free(bao);
 return 0;
}
















#endif
