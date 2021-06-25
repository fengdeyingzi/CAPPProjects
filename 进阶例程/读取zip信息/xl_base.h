

typedef struct {
   uint16            x;
   uint16            y;
   uint16            w;
   uint16            h;
}mr_screenRectSt;

typedef struct {
   uint8            r;
   uint8            g;
   uint8            b;
}mr_colourSt;



typedef struct
{
   uint16 year;                 //年
   uint8  month;                //月
   uint8  day;                  //日
   uint8  hour;                 //时，24小时制
   uint8  minute;               //分
   uint8  second;               //秒
}mr_datetime;







char *mrc_strrchr(char *start,char c)
{
return strrchr(start,c);
}

long mrc_wstrlen(char *text)
{
return wstrlen(text);
}



long mrc_open(char *filename, int mode)
{
return open(filename,mode);
}

long mrc_close(long f)
{
return close(f);

}

 long mrc_fileState(char *filename)
 {
 return filestate(filename);
 }

long mrc_write(long f,void *p,long l)
{
return write(f,p,l);
}

long mrc_read(long f,void *p,long l)
{

return read(f,p,l);
}

long mrc_seek(long f,long pos,int mod)
{

return seek(f,pos,mod);
}

long mrc_getLen(char *filename)
{

return getlen(filename);
}

long mrc_remove(char *filename)
{
return remove(filename);
}

long mrc_rename(char *oldname,char *newname)
{
return rename(oldname,newname);
}
 
long mrc_mkDir(char *name)
{
return mkdir(name);
}

long mrc_rmDir(char *name)
{
return rmdir(name);
}

long mrc_findStart(char *file,char *buffer,long len)
{
return filestart(file,buffer,len);
}

long mrc_findGetNext(long handler, char *buffer, long len)
{

return findnext(handler,buffer,len);
}
long mrc_findStop(long handler)
{
return findstop(handler);
}

/********************************绘图接口********************************/

long mrc_drawText(char *text,int x,int y,uint8 r,uint8 g,uint8 b,int is_unicode, uint16 font)
{
return dtext(text,x,y,r,g,b,is_unicode,font);
}


long mrc_drawTextEx(char* pcText, int16 x, int16 y, mr_screenRectSt mr_rect, mr_colourSt mr_color, int flag, uint16 font)
{

return dtextex(pcText,x,y,(void)mr_rect,(void)mr_color,flag,font);
}

long mrc_drawTextRight(char *pcText,int x, int y, mr_screenRectSt rect,mr_colourSt color,int flag,uint16 font)
{
return dtextright(pcText,x,y,rect,color,flag,font);
}


unsigned short *mrc_c2u(char *cp, int32 *err, int32 *size)
{

return c2u(cp,err,size);
}


long mrc_textWidthHeight(char* pcText, int is_unicode, uint16 font, int32* w, int32* h)
{
return textwh(pcText,is_unicode,font,w,h);
}


long mrc_unicodeTextRow(uint16 *pcText,uint16 font,int32 w)
{
return unitextrow(pcText,font,w);
}




void mrc_drawRect(int16 x, int16 y, int16 w, int16 h, uint8 r, uint8 g, uint8 b)
{
drect(x,y,w,h,r,g,b);
}

void mrc_drawLine(int16 x1, int16 y1, int16 x2, int16 y2, uint8 r, uint8 g, uint8 b)
{
dline(x1,y1,x2,y2,r,g,b);
}

void mrc_drawPointEx(int16 x, int16 y, int32 r, int32 g, int32 b)
{
dpoint (x,y,r,g,b);
}

void mrc_drawPoint(int16 x, int16 y, uint16 nativecolor)
{
dpointex(x,y,nativecolor);
}

void mrc_clearScreen(long r,long g,long b)
{
cls(r,g,b);
}



void mrc_refreshScreen(int16 x, int16 y, uint16 w, uint16 h)
{
ref(x,y,w,h);
}

void mrc_EffSetCon(int16 x, int16 y, int16 w, int16 h, int16 perr, int16 perg, int16 perb)
{
effsetcon(x,y,w,h,perr,perg,perb);
}



/********************************本地化UI接口********************************/
/*

#define menucreate mrc_menuCreate

#define menuset mrc_menuSetItem

#define menushow mrc_menuShow
#define menudel mrc_menuRelease

#define menuref mrc_menuRefresh
#define dlgcreate mrc_dialogCreate

#define dlgdel mrc_dialogRelease
#define dlgref mrc_dialogRefresh
#define textcreate mrc_textCreate
#define textdel mrc_textRelease
#define textref mrc_textRefresh



#define editcreate mrc_editCreate
#define editdel mrc_editRelease

#define editget mrc_editGetText
*/
int mrc_editCreate( char * title,  char * text, int32 type, int32 max_size)
{
return editcreate(title,text,type,max_size);
}

int mrc_editRelease(int32 edit)
{
return editdel(edit);
}


char* mrc_editGetText(int32 edit)
{
return editget(edit);
}

/********************************其他接口********************************/
void mrc_exit()
{
exit();
}

long mrc_getUptime()
{
return getuptime();
}




long mrc_getDatetime(mr_datetime* datetime)
{
return getdatatime((void*)datatime);
}
/*
long mrc_getMemoryRemain()
{
return getmemremain();
}
*/
long mrc_startShake(long time)
{
return shake(time);
}
long mrc_getSysMem()
{
return getsysmem();
}

//#define readfilefrommrp mrc_readFileFromMrpEx
/*
void * mrc_readFileFromMrp( char* filename, int32 *filelen, int32 lookfor)
{
readmrpfile(filename,(void *)filelen);
}
*/

//#define freefiledata mrc_freeFileData
//#define freeorigin mrc_freeOrigin

char *mrc_unicodeToGb2312(uint8* input, int32 input_len, uint8** output, int32* output_len)
{
return u2c(input,input_len,output,output_len);
}

int mrc_runMrp(char* mrp_name,char* file_name,char* parameter)
{
runmrp(mrp_name,file_name);
return 0;
}

//#define getparentpath mrc_GetParentPath

//#define sand mrc_sand

long mrc_rand()
{
return rand();
}
/*
long mrc_sendSms(char* pNumber, char *pContent, int32 flags)
{
sms(pContent,flags);
}
*/
//#define sms mrc_sendSms

void mrc_LCDCanSleep()
{
lcd();
}
long mrc_sleep(uint32 ms)
{
return sleep(ms);
}


// 以下函数定义在mrc_bmp.h文件中//////////////////////////////////////


int w_getScreenBuffer()
{
return getscrbuf();
}

//#define getscrsize mrc_getScreenSize
//#define setscrsize mrc_setScreenSize



int bitmapShowFlip(uint16* p, int16 x, int16 y, uint16 mw, uint16 w, uint16 h, uint16 rop, 
int16 sx, int16 sy, uint16 transcolor)
{
return bmpshowflip(p,x, y,mw,w,h,rop,sx,sy,transcolor);
}


//#define readall my_readAllEx
//extern void mrc_connectWAP(char* wap);
//#define wap mrc_connectWAP

/********************************定时器接口********************************/

long mrc_timerCreate()
{
return timercreate();
}

long mrc_timerDelete(long time)
{
return timerdel(time);
}

long mrc_timerStop(long time)
{
return timerstop(time);
}

//#define timerstart mrc_timerStart

long mrc_timerSetTimeEx(long t,long time)
{
return timersettime(t,time);
}
