#include "../picoc.h"
#include "../interpreter.h"
#include "platform.h"
#include "mrc_base.h"
#include <setjmp.h>
#include <sys/stat.h>
#include "dsm.h"
#include "android.h"


/* mark where to end the program for platforms which require this */
jmp_buf PicocExitBuf;

void PlatformInit(Picoc *pc)
{
    mrc_remove("c/print.txt");
    mrc_mkDir("c/");
    debugfile = mrc_open("c/print.txt",12);
//    mrc_write(debugfile,"start\n",6);
//    mrc_close(debugfile);
}

void PlatformCleanup(Picoc *pc)
{
    if(debugfile)
    {
        mrc_close(debugfile);
        debugfile=0;
    }
}

/* get a line of interactive input */
char *PlatformGetLine(char *Buf, int MaxLen, const char *Prompt)
{
    if (Prompt != NULL)
        printf("%s", Prompt);
        
    fflush(stdout);
    return fgets(Buf, MaxLen, stdin);
}

/* get a character of interactive input */
int PlatformGetCharacter()
{
    fflush(stdout);
    return getchar();
}

/* write a character to the console */
void PlatformPutc(unsigned char OutCh, union OutputStreamInfo *Stream)
{
    // putchar(OutCh); //xldebug
    printf("%c",OutCh);
    if(debugfile)
        mrc_write(debugfile,&OutCh,1);
    // debugfile = mrc_open("c/print.txt",12);
    // mrc_write(debugfile,"%c",OutCh);
    // mrc_close(debugfile);
}

/* //capp_readfile read a file into memory */
char *PlatformReadFile(Picoc *pc, const char *FileName)
{
    
    if(IS_RUN){
    struct stat FileInfo;
    char *ReadText;
    FILE *InFile;
    unsigned long BytesRead;
    char *p;
    char *temp_filename = malloc(600);
    sprintf(temp_filename,"%s%s",dsm_getProjectPath(),FileName);
    mrc_printf("PlatformReadFile is_run %s\n",temp_filename);
    if (stat(temp_filename, &FileInfo))
        ProgramFailNoParser(pc, "can't read file %s\n", temp_filename);
    
    ReadText = malloc(FileInfo.st_size + 1);
        memset(ReadText, 0, FileInfo.st_size);
    if (ReadText == NULL)
        ProgramFailNoParser(pc, "out of memory\n");
    
    InFile = fopen(temp_filename, "r");
    free(temp_filename);
    if (InFile == NULL)
        ProgramFailNoParser(pc, "can't read file %s\n", FileName);
    
    BytesRead = fread(ReadText, 1, (size_t)FileInfo.st_size, InFile);
    if (BytesRead == 0)
        ProgramFailNoParser(pc, "can't read file %s\n", FileName);

    ReadText[BytesRead] = '\0';
    mrc_printf("read file success %d %s\n",BytesRead,ReadText);
        for(int i=0;i<BytesRead;i++){
            if(i<4)
            mrc_printf("%02x ",ReadText[i]);
            else
                mrc_printf("%c",ReadText[i]);
        }
    fclose(InFile);
    
    // if ((ReadText[0] == '#') && (ReadText[1] == '!'))
    // {
    //     for (p = ReadText; (*p != '\r') && (*p != '\n'); ++p)
    //     {
    //         *p = ' ';
    //     }
    // }
        if(FileInfo.st_size>=2 && ReadText[0]==-1 && ReadText[1]==-2){
            
            char *p = malloc (FileInfo.st_size);
            strcpy(p, ReadText+4);
            mrc_printf("特殊解析 %s\n",p);
            free(ReadText);
            return p;
        }
    return ReadText;    
    }
    else{ //打包模式
        int32 fSize=0; //文件长度
        char *fBuf = NULL;
        int32 f=0;
		int32 len=0;
        char *text_c = readFileFromAssets(FileName,&len);
		mrc_printf("PlatformReadFile %s",FileName);
		if(text_c){
        fSize= len;
        fBuf = malloc(len + 1);
        memcpy(fBuf, text_c, len);
        free(text_c);
		if(!fBuf){
            ProgramFailNoParser(pc, "can't read file %s\n", FileName);
            return NULL;
        }
        fBuf[fSize]=0;
        return fBuf;
		}
		else{
            ProgramFailNoParser(pc, "can't read file %s\n", FileName);
            return NULL;
        }
        ProgramFailNoParser(pc, "can't read file %s\n", FileName);
        return NULL;
    }
    
}

/* read and scan a file for definitions */
void PicocPlatformScanFile(Picoc *pc, const char *FileName)
{
    char *SourceStr = PlatformReadFile(pc, FileName);
    PicocParse(pc, FileName, SourceStr, strlen(SourceStr), TRUE, FALSE, TRUE, TRUE);
}

/* exit the program */
void PlatformExit(Picoc *pc, int RetVal)
{
    pc->PicocExitValue = RetVal;
    longjmp(pc->PicocExitBuf, 1);
    printf("退出程序\n");
    exit(0);
}
