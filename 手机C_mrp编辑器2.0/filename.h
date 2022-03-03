
/*
判断文件后缀，
成功返回TRUE
失败FALSE
*/


int impactName(char *filename,char *hz)
{
 char *temp=strrchr(filename,'.');
 if(strcmp(temp,hz)==0)
 {
  printf("是mrp");
  return 1;
 }
 return FALSE;
}




