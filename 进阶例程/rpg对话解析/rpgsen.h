/*
������
2015.08.29
*/



#include <exb.h>
#include <android.h>
#include <ex_math.h>
#define RPGSEN_SHOW_TRIGGER_MAX 20

typedef struct _RpgsenSen
{
 char *name;
 char *sen;
}RpgsenSen;

typedef struct _RpgsenSenPeople
{
 char *name;
 char *nameTrue;
}RpgsenSenPeople;


typedef struct _Rpgsen
{
 //������Ŀ
 struct _RpgsenSenPeople people[16];
 
 //�Ի���Ŀ
 struct _RpgsenSen sen[64];
 
 //������Ŀ
 int peopleSum;
 
 //�Ի���Ŀ
 int sumNow;
 int sum;
 
 //��ǰ��ʾ���뵭��
 int fadeNow;
 
 //��������
 int triggerSum;
 int triggerSumNow;
 
 //��ǰ�Ի�����ָ��
 char *senName;
 char *senSen;
 
 //��ť
 int flagPass;
 int flagNext;
 
}Rpgsen;


void rpgsenInit(Rpgsen *r)
{
 r->peopleSum= 0;
 r->sumNow = 0;
 r->sum = 0;
 r->fadeNow = 0;
 r->triggerSum = 0;
 r->triggerSumNow = 0;
 r->flagPass = 0;
 r->flagNext = 0;
 
}

void rpgsenRead(Rpgsen *r, char *filename)
{
 //�ļ�����
 int l;
 //�����ļ�����
 char *s = readFileFromAssets(filename,&l);
 //ȡ�õ�Ԫ�ĳ���
 int lOne = 0;
 int i,j;
 //��������ݵ�ָ��
 char *s1;    /*����*/
 int s2;    /*����*/
 printf("����: %d\n", l);
 printf("%s\n", s);
 //����
 for(i = 0; i < l;)
 {
  
  if(s[i] == '[')
  {
   i ++;
   //ȡ��һС�����ݵģ�����ȡ�õĳ���
   lOne = rpgsenReadOne(s, i, l - i);
   
   //�����ɴ�������
   if(strncmp(s + i, "triggerSum", lOne) == 0)
   {
    i += lOne;
    i ++;
    
    lOne = rpgsenReadOne(s, i, l - i);
    s2 = atoi(s + i);
    i += lOne;
    i ++;
    
    r-> triggerSum = s2;
    printf("(%d)triggerSum:%d\n", i, s2);
   }
   //����people(����)
   else if(strncmp(s + i, "people", lOne) == 0)
   {
    i += lOne;
    i ++;
    
    //��ȡ����
    lOne = rpgsenReadOne(s, i, l - i);
    s1 = (char *)malloc(lOne + 1);
    memcpy(s1, s + i, lOne);
    s1[lOne] = '\0';
    r->people[r->peopleSum].name = s1;
    printf("(%d.%d)people:%s\n", i, lOne, s1);
    i += lOne;
    i ++;
    
    //��ȡ����
    lOne = rpgsenReadOne(s, i, l - i);
    s1 = (char *)malloc(lOne + 1);
    memcpy(s1, s + i, lOne);
    s1[lOne] = '\0';
    r->people[r->peopleSum].nameTrue = s1;
    printf("(%d.%d)peopleTrue:%s\n", i, lOne, s1);
    i += lOne;
    i ++;
    
    //people��ȡ�ɹ�
    r->peopleSum ++;
   }
   //����sen(�Ի�)
   else if(strncmp(s + i, "sen", lOne) == 0)
   {
    i += lOne;
    i ++;
        
    //��ȡ����
    lOne = rpgsenReadOne(s, i, l - i);
    s1 = (char *)malloc(lOne + 1);
    memcpy(s1, s + i, lOne);
    s1[lOne] = '\0';
    r->sen[r->sum].name = s1;
    printf("(%d.%d)name:%s\n", i, lOne, s1);
    i += lOne;
    i ++;
    
    //��ȡ����
    lOne = rpgsenReadOne(s, i, l - i);
    s1 = (char *)malloc(lOne + 1);
    memcpy(s1, s + i, lOne);
    s1[lOne] = '\0';
    r->sen[r->sum].sen = s1;
    printf("(%d.%d)sen:%s\n", i, lOne, s1);
    i += lOne;
    i ++;
    
    //sen��ȡ�ɹ�
    r->sum ++;
   }
   
  }
  else i ++;    
 }
 free(s);
 //���õ�һ���Ի�
 rpgsenDrawRel(r);
}

static int rpgsenReadOne(char *s, int from, int remain)
{
 int len = 0;
 while((s[from + len] != ' ') && (s[from + len] != ']') && (len <= remain))
 {
  len ++;
 }
 return len;
}


void rpgsenDispose(Rpgsen *r)
{
 int i;
 for(i = 0; i < r->peopleSum; i ++)
 {
  free(r->people[i].name);
  free(r->people[i].nameTrue);
 }
 for(i = 0; i < r->sum; i ++)
 {
  free(r->sen[i].name);
  free(r->sen[i].sen);
 }
}



void rpgsenDraw(Rpgsen *r)
{
 if(r->sumNow <= r->sum)
 {
  rectst rec;
  rec.x = 40;//40;
  rec.y = 0;
  rec.w = SCRW - 80 ;
  rec.h = SCRH + 100 ;
  colorst col;
  col.r = 190;
  col.g = 190;
  col.b = 160;
 
 
  drect(10, SCRH - 230, SCRW -20, 230, 60, 60, 60);
  drect(20, SCRH - 220, SCRW -40, 210, 40, 40, 40);

  setTextSize(1,30);
  dtext(r->senName,40, SCRH - 210, 230,220,180, 0, 1);
  setTextSize(1,24);
  dtextex(r->senSen, 100, SCRH - 180 , &rec, &col, 0, 1);
 
  //����ť
  setTextSize(1,20);
  if(r->flagNext)setTextSize(1,28);
  dtext("ȷ��", SCRH / 2 - 40, SCRH - 65, 180, 180, 180, 0, 1);
 }
}

//�����Ի�����Ϊ�Ѷ�
static void rpgsenDrawRel(Rpgsen *r)
{
 int ok = 0;
 if(r->sumNow < r->sum )
 {
  for(int i = 0; i < r->peopleSum; i ++)
  {
   if(strcmp(r->people[i].name, r->sen[r->sumNow].name) == 0)
   {
    r->senName = r->people[i].nameTrue;
    ok = 1;
    break;
   }
  }
  if(ok == 0)
  {
   r->senName = NULL;
  }
  r->senSen = r->sen[r->sumNow].sen;
  r->sumNow ++;
 }
}


int rpgsenEvent(Rpgsen *r, int s, int p1, int p2)
{
 if(r->sumNow < r->sum)
 {
  if(isPointCollRect(p1,p2, SCRH / 2 - 30 , SCRH - 70, 60, 50))
  {
   if(s == MS_DOWN)
   {
    if(r->flagNext == 0)
    r->flagNext = 1;
   }
   else if(s == MS_UP)
   {
    if(r->flagNext == 1)
    {
     r->flagNext = 0;
     rpgsenDrawRel(r);
    }
   }  
  }
  return 1;
  }
  else 
  {
   r->sumNow = r->sum + 1;
   return 0;
  }
}

//�����Ի��¼�
void rpgsenInto(Rpgsen *r)
{
 if(r->triggerSumNow < r->triggerSum)
 {
  r->triggerSumNow ++;
  r->sumNow = 0;
  rpgsenDrawRel(r);
 }
 
}