#ifndef MRC_BASE_H
#define MRC_BASE_H


#define MR_IS_FILE     1      //文件
#define MR_IS_DIR      2      //目录
#define MR_IS_INVALID  8  //无效(非文件、非目录)

#define MR_FILE_RDONLY         1//以只读的方式打开文件。
#define MR_FILE_WRONLY        2//以只写的方式打开文件。
#define MR_FILE_RDWR             4//以读写的方式打开文件。
#define MR_FILE_CREATE          8//如果文件不存在，创建该文件。

void *mrc_malloc(int32 size);

void mrc_free(void* ptr);

void mrc_exit(void);

void mrc_printf(const char *format, ...);

#endif
