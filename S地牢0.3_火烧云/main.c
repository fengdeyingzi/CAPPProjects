/*
��� ��������S����
��� ��ɶȣ�40%
��� ��  ����0.3
��� ��  �ߣ�������(Culosic)
��� ��  �ͣ�̽�ա����ء����ԡ��غ��ơ�ս��
��� ��  ��ѧϰ���������Ρ����ص��Ρ�������
       ��ʹ��ͼƬ����ͼ������ɣ�����
       ���ᡢҩƷʹ�ã�����װ�������зḻ��
       �ܣ�ǿ��boss������ս��
��� �������裺
       1.�����ͼ������
       2.�����ս��غ����
       3.װ������Ʒ��ʹ��
       4.�����Ż�
��� ����˵����
       ����ͼ�ꡰͼ���򿪻�ر�С��ͼ
       ����ͼ�ꡰ��򿪻�رձ���
       ������ͼ�����ƶ��򹥻�
       �������ؼ��˳���Ϸ

��� ��ӭ��Ϸ�����߼���
       ��[��Ϸ����]Ӱ�Ӿ��ֲ�
       ��Ⱥ���룺496717720

��� �ֻ�c�����߾ۼ���
       ��Ӱ�Ӿ��ֲ�
       ��Ⱥ���룺370468001

��� �ҵ�QQ
       ���Һ��ѽ��٣�ֻ��ͬ��
       �ﰮ��Ϸ��������ҳ�����ļ�
       ��2268881308

��� ����
       ��������� 2500����
       �ﲻһ���ã������ο�
       ��A*Ҳ�Ǽٵġ��������£�

2017/2/6-2017/2/12 by ������

*/

#include <base.h>
#include "base.h"
#include <exb.h>
#include <android.h>
#include <graphics.h>

#include "map.h"
#include "aStar.h"
#include "role.h"
#include "wupin.h"
#include "game.h"

void helloworld(){
 int _SCRW,_SCRH;
 _SCRW = 720*2;
 _SCRH = _SCRW * SCRH / SCRW;
 setscrsize(_SCRW, _SCRH);
 
 Map map;
 mapInit(&map);
 
 cls(0,0,0);
 mapDraw(&map, 0, 0);
 ref(0,0,SCRW,SCRH);
}


int init(){
 gameInit();
 toast("��������Ʒ(v0.2)", 1);
 gameStart(80);
 return 0;
}


int event(int type, int p1, int p2){
 gameEvent(type,p1,p2);
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
 