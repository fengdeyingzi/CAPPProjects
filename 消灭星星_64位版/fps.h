
#ifndef _FPS_H_
#define _FPS_H_

//帧率检测

typedef struct
{
 int time; //时间
 int size; //帧数
} FPS;

FPS *fps_create()
{
 FPS *fps=malloc(sizeof(FPS));
 memset(fps,0,sizeof(FPS));
 fps->time=getuptime();
 fps->size=1;
 return fps;
}

void fps_run(FPS *ftp)
{
 ftp->size++;
 
}

int fps_get(FPS *ftp)
{
 
 int time=getuptime();
 //printf("%d\n",time);
 if(time-ftp->time >0)
 return 1000/ ((time - ftp->time)/ftp->size);
 return 0;
}


int fps_free(FPS *ftp)
{
 free(ftp);
 return 0;
}


#endif
