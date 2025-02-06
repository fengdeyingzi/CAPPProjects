//
//  dsm.c
//  CAPP
//
//  Created by mac on 2020/1/28.
//  Copyright © 2020 capp. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <malloc.h>
#endif
// #include "platform.h"
//#include "mpcrun.h"
#include "dsm.h"
#include "log.h"
char SDPath[DSM_MAX_FILE_LEN] = "mnt/sdcard"; //内存卡目录(需要初始化) 以后考虑弃用
//char *SystemPath = "system";  //系统盘目录
//char *DataPath = "data/data";  //data目录
//char *AllPath = "";   //系统根目录
// char dsmWorkPath[DSM_MAX_FILE_LEN]; //平台目录 暂时不用管
static char ProjectPath[DSM_MAX_FILE_LEN]; //运行文件路径 工程路径(绝对路径)
static char RUN_NAME[DSM_MAX_FILE_LEN]; //运行的文件名
static char PlatDir[DSM_MAX_FILE_LEN]; //平台路径
static char SDCard[DSM_MAX_FILE_LEN]; //SD卡路径
static char DocDir[DSM_MAX_FILE_LEN]; //doc文档路径
static char CacheDir[DSM_MAX_FILE_LEN]; //应用缓存路径
static char FilesDir[DSM_MAX_FILE_LEN]; //files目录
int IS_RUN = 0; //true运行器模式 false打包模式


int32 SCREEN_WIDTH,SCREEN_HEIGHT;

/*
 * 整理路径，将分隔符统一为sep，并清除连续的多个
 *
 * 参数：路径(必须可读写)
 */
char *FormatPathString(char *path, char sep) {
    char *p, *q;
    int flag = 0;

    if (NULL == path)
        return NULL;

    for (p = q = path; '\0' != *p; p++) {
        if ('\\' == *p || '/' == *p) {
            if (0 == flag)
                *q++ = sep;
            flag = 1;
        }
        else {
            *q++ = *p;
            flag = 0;
        }
    }

    *q = '\0';

    return path;
}



//获取c文件的路径 并设置运行文件名 需要释放

// char *xl_getFilePath(char *filename) {
//     char *ptr;
// //    char *path;
//     //格式化
//     FormatPathString(filename, '/');
//     LOGI("getFilePath %s", filename);
//     //搜索末尾处的'/'
//     ptr = strrchr(filename, '/');
//     if(ptr){
//     strncpy(ProjectPath, filename, (int) (ptr - filename));
//     strncpy(ProjectPath, filename, (int) (ptr - filename));
//     strcpy(run_name,ptr+1);
//     //替换为0
//     ProjectPath[(int) (ptr - filename)] = 0;
//     }
//     else{
//         strcpy(run_name, filename);
//         strcpy(ProjectPath,"");
//     }
// // path= malloc((int)(ptr-filename)+1);


//     return ProjectPath;
// }



//设置工程文件夹
int dsm_setProjectPath(char* dir){
//    strcpy(run_path, dir);
    strcpy(ProjectPath, dir);
    return 0;
}

//设置运行的C文件
void dsm_setRunC(char *path,char *name){
    strcpy(ProjectPath,path);
    strcpy(RUN_NAME,name);
}

//获取工程路径文件夹
char *dsm_getProjectPath(void){
    return ProjectPath;
}

//获取运行的C文件
char *dsm_getRunName(void){
    return RUN_NAME;
}

//获取平台目录
char *dsm_getPlatDir(void){
    return PlatDir;
}

//设置平台目录
void dsm_setPlatDir(char *dir){
    strcpy(PlatDir, dir);
}

//获取文档目录
char *dsm_getDocDir(void){
    return DocDir;
}

//设置文档目录
void dsm_setDocDir(char *dir){
    strcpy(DocDir, dir);
}

//获取缓存目录
char *dsm_getCacheDir(void){
    return CacheDir;
}

//设置缓存目录
void dsm_setCacheDir(char *dir){
    strcpy(CacheDir, dir);
}




/*

设置读取路径
 
 a盘 系统盘
 b 手机盘
 c 内存卡
 d 其它
 e mythroad目录
 doc doc文档目录
 cache 应用缓存目录
 files Files目录
*/
void SwitchPath(char *c) {
    if(strcmp(c,"b")==0){
        strcpy(PlatDir,SDCard);
    }
    if(strcmp(c,"c")==0){
        strcpy(PlatDir,SDCard);
    }
    else if(strcmp(c,"d")==0){
        sprintf(PlatDir,"%s",ProjectPath);
    }
    else if(strcmp(c,"e")==0){
        sprintf(PlatDir,"%s%s",SDCard,"mythroad/");
    }
    else if(strcmp(c,"files")==0){
        sprintf(PlatDir,"%s",FilesDir);
    }
    else if(strcmp(c,"doc")==0){
        sprintf(PlatDir,"%s",DocDir);
    }
    else if(strcmp(c,"cache")==0){
        sprintf(PlatDir,"%s",CacheDir);
    }
}

//解析参数 配置各目录
void dsm_parseArgs(int argc, char *argv[]){
    int i=0;
    memset(SDCard,0,sizeof(SDCard));
    memset(PlatDir,0,sizeof(PlatDir));
    memset(ProjectPath,0,sizeof(ProjectPath));
    memset(RUN_NAME,0,sizeof(RUN_NAME));
    memset(CacheDir,0,sizeof(CacheDir));
    memset(FilesDir,0,sizeof(FilesDir));
    memset(DocDir,0,sizeof(DocDir));
    strcpy(RUN_NAME,"temp.c");
    for(i=0;i<argc;i++){
        printf("%s\n",argv[i]);
        if(strcmp(argv[i],"-cache_dir")==0){
            strcpy(CacheDir,argv[i+1]);
        }
        if(strcmp(argv[i],"-extern_dir")==0){
            strcpy(SDCard,argv[i+1]);
        }
        if(strcmp(argv[i],"-extern_filesdir")==0){
            strcpy(DocDir,argv[i+1]);
        }
        if(strcmp(argv[i],"-files_dir")==0){
            strcpy(FilesDir,argv[i+1]);
        }
        if(strcmp(argv[i],"-extern_cache_dir")==0){
            // strcpy(CacheDir,argv[i+1]);
        }
        if(strcmp(argv[i],"-plat_dir")==0){
            strcpy(PlatDir,argv[i+1]);
        }
        if(strcmp(argv[i],"-run_name")==0){
            strcpy(RUN_NAME,argv[i+1]);
        }
        if(strcmp(argv[i],"-project_dir")==0){
            strcpy(ProjectPath,argv[i+1]);
        }
        if(strcmp(argv[i],"-is_run")==0){
            IS_RUN = 1;
        }
        
    }
    FormatPathString(SDCard,'/');
    FormatPathString(PlatDir,'/');
    FormatPathString(ProjectPath,'/');
    FormatPathString(RUN_NAME,'/');
    FormatPathString(CacheDir,'/');
    FormatPathString(FilesDir,'/');
    FormatPathString(DocDir,'/');

}

