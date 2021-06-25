/*
 * 文件浏览头文件
 * 版权所有 (C) 2011-2012 eleqian
 * [6/4/2012]
 */

#ifndef __FILEVIEW_H__
#define __FILEVIEW_H__

#define FILEVIEW_FLAG_FILE   0x1
#define FILEVIEW_FLAG_FOLDER 0x2
#define FILEVIEW_FLAG_RECENT 0x4

typedef int32 (*FV_CB)(const char *dir, const char *name);

int32 FileView_Init(void);
int32 FileView_End(void);
int32 FileView_Draw(uint8 refresh);
int32 FileView_Event(int32 type, int32 p1, int32 p2);

// 显示文件浏览窗口
// 参数：标题，指定路径(为NULL表示所有磁盘)，标志，回调
int32 FileView_Show(char *sTitle, char *sPath, int32 flag, FV_CB cbFunc);

// 刷新文件列表
int32 FileView_Refresh(void);

#endif // __FILEVIEW_H__
