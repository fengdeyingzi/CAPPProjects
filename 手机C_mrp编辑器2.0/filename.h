
/*
�ж��ļ���׺��
�ɹ�����TRUE
ʧ��FALSE
*/


int impactName(char *filename,char *hz)
{
 char *temp=strrchr(filename,'.');
 if(strcmp(temp,hz)==0)
 {
  printf("��mrp");
  return 1;
 }
 return FALSE;
}




