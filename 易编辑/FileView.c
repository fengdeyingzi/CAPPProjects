/*
 * 文件浏览器代码
 * 版权所有 (C) 2011-2012 eleqian
 * [7/21/2012]
 */

#include "mrc_base.h"
#include "src/exb.h"
#include "src/android.h"
#include "src/base.h"
#include "AppMain.h"
#include "FileView.h"
#include "KeyTimer.h"
#include "LocalUI.h"
#include "Functions.h"
#include "XString.h"
#include "DrawLib.h"

// 自定义的文件类型，不与系统类型冲突即可
#define MR_IS_DISK    16
#define MR_IS_OPEN    32

// 文件浏览操作枚举
enum
{
    FV_ACTION_ITEM_UP,
    FV_ACTION_ITEM_DOWN,
    FV_ACTION_PAGE_UP,
    FV_ACTION_PAGE_DOWN,
    FV_ACTION_PAGE_HOME,
    FV_ACTION_PAGE_END,
    FV_ACTION_PATH_OUT,
    FV_ACTION_PATH_INTO,
    FV_ACTION_SELECT,

    FV_ACTION_MAX
};

// 文件节点类型
typedef struct FileItem_st
{
    char *name;  // 名称
    int16 index; // 序号,从1开始
    int32 size;  // 大小
    uint8 type;  // 类型
    struct FileItem_st *last; // 上一节点
    struct FileItem_st *next;   // 下一节点
} FILEITEM_ST;

// 路径节点类型
typedef struct PathNode_st
{
    char *name;                  // 节点名称
    uint8 type;                  // 节点类型
    int16 topIndex;              // 显示序号,从1开始
    int16 focusIndex;            // 焦点序号,从1开始
    struct PathNode_st *last;  // 上一节点
    struct PathNode_st *next;    // 下一节点
} PATHNODE_ST;

// 文件浏览数据结构体
typedef struct
{
    char Path[MAX_PATH_LEN_A];  // 当前浏览绝对路径
    char Title[32];             // 标题栏文字
    int32 Flag;                 // 文件浏览类型参数
    FV_CB CallBack;             // 文件浏览回调函数
    int32 FileCount;            // 当前目录文件总数
    int32 VisLines;             // 列表可显示项目数
    PATHNODE_ST *PathNode;      // 绝对路径全部节点
    FILEITEM_ST *HeadItem;      // 文件链表首节点
    FILEITEM_ST *TopItem;       // 首显示节点
    FILEITEM_ST *FocusItem;     // 当前焦点节点
    
    uint16 *IconData;            // 图标数据
} FILEVIEW_DATA_ST;

static FILEVIEW_DATA_ST FVData;  // 文件浏览数据

static rectst rectTitle, rectTool;  // 标题栏，工具栏
static rectst rectInput, rectInfo;  // 路径输入框，信息栏
static rectst rectList, rectScroll; // 文件列表，滚动条

static uint16 ItemHeight;     // 列表项高度
static uint16 ButtonWidth;    // 按钮宽度(工具栏)
static uint8 IsScrolling;     // 是否滚动条在滚动
static int32 InputIndex;      // 按键输入序号
static uint8 InputState;      // 输入状态(序号或快捷键)

static void FV_ClearFileItems(void);
static void FV_ClearPathNodes(void);

static int32 FVMenu_Init(void);
static int32 FVMenu_End(void);
static int32 FVMenu_Show(void);

/*---------------------------------------------------------------------------*/

// 初始化文件浏览
int32 FileView_Init(void)
{
    int16 scnWidth, scnHeight;

    GetTextSizeW16("\x65\x87\x67\x2c\x0\x0", (int16*)&ButtonWidth, (int16*)&ItemHeight); //"文本"
    GetScreenSize16(&scnWidth, &scnHeight);

    ItemHeight += 4;
    ButtonWidth += 8;

    //设定控件位置信息
    rectTitle.x = 0; rectTitle.y = 0; rectTitle.w = scnWidth; rectTitle.h = ItemHeight;
    rectTool.x = 0; rectTool.y = scnHeight - ItemHeight; rectTool.w = scnWidth; rectTool.h = ItemHeight;
    rectInfo.x = 0; rectInfo.y = rectTitle.h; rectInfo.w = scnWidth; rectInfo.h = ItemHeight;
    rectInput.x = 0; rectInput.y = rectInfo.y + rectInfo.h + 1; rectInput.w = scnWidth; rectInput.h = ItemHeight + 2;
    rectList.x = 0; rectList.y = rectInput.y + rectInput.h + 1; rectList.w = scnWidth - 5; 
    rectList.h = scnHeight - rectTitle.h - rectTool.h - rectInfo.h - rectInput.h - 3;
    rectScroll.x = scnWidth - 5; rectScroll.y = rectList.y; rectScroll.w = 5; rectScroll.h = rectList.h;

    if (ItemHeight < 16)
        ItemHeight = 16;
    FVData.VisLines = rectList.h / ItemHeight;

    // 载入图标
    if (NULL == FVData.IconData)
    {
        uint8 *fdata;
        int32 fsize;

//        fdata = mrc_readFileFromMrp("icons.bmp", &fsize, 0); //xldebug
        fdata = readFileFromAssets("icons.bmp", &fsize); //xldebug
        if (NULL != fdata)
        {
            FVData.IconData = (uint16 *)malloc(fsize);
            memcpy(FVData.IconData, fdata, fsize);
            free(fdata);
        }
    }

    FVMenu_Init();

    return 0;
}

// 结束文件浏览，释放内存
int32 FileView_End(void)
{
    FV_ClearFileItems();
    FV_ClearPathNodes();
    TRYFREE(FVData.IconData);

    FVMenu_End();

    return 0;
}

// 绘制文件列表
static void FV_DrawList(uint8 refresh)
{
    FILEITEM_ST *fNode = NULL;
    rectst itemRect;
    rectst txtRect;
    rectst rectSpace;
    int16 picY, sclY, sclH;
    char fInfo[32] = {0};

    rectSpace.x = rectInfo.x; rectSpace.y = rectInfo.y;
    rectSpace.w = rectInfo.w; rectSpace.h = rectInfo.h + rectInput.h + rectList.h + 2;
    ClearRect(rectSpace);

    // 输入框
    DrawRoundBorder(rectInput);
    DrawTextMidLeftA(rectInput, FVData.Path, AppColor.text_normal);

    // 列表
    itemRect.x = rectList.x + 2; itemRect.y = rectList.y + 2; itemRect.w = rectList.w - 4; itemRect.h = ItemHeight;
    txtRect.x = rectList.x + 2 + 16; txtRect.y = rectList.y + 2; txtRect.w = rectList.w - 4 - 16; txtRect.h = ItemHeight;

    fNode = FVData.TopItem;

    // 绘制各个列表项
    while (NULL != fNode)
    {
        // 焦点项
        if (fNode == FVData.FocusItem) 
            DrawShadeRect(itemRect);
        DrawTextMidLeftA(txtRect, fNode->name, AppColor.text_normal);

        // 显示图标
        switch (fNode->type)
        {
        case MR_IS_DISK:
            if (-1 == fNode->size)  // 取得磁盘大小
                fNode->size = (int32)(GetDiskSize(fNode->name, 0) / 1024);
            picY = 0;
            break;
        case MR_IS_DIR:
            picY = 16;
            break;
        case MR_IS_FILE:
            if (-1 == fNode->size)  // 取得文件大小
            {
                fNode->size = FileLenInPath(FVData.Path, fNode->name);
                if (-1 == fNode->size)
                    fNode->type = MR_IS_OPEN;  // 改变类型为无法操作文件
            }

            if (MR_IS_FILE == fNode->type)
                picY = 32;
            else
                picY = 64;
            break;
        case MR_IS_OPEN:
            picY = 64;
            break;
        default:
            picY = 48;
            break;
        }
//        mrc_bitmapShowEx(FVData.IconData, 2, itemRect.y + (itemRect.h - 16) / 2, 16, 16, 16, BM_TRANSPARENT, 0, picY); //xldebug

        itemRect.y += ItemHeight;
        txtRect.y = itemRect.y;

        if (itemRect.y + itemRect.h >= rectList.y + rectList.h)
            break;

        fNode = fNode->next;
    }

    DrawRoundBorder(rectList);

    // 信息栏
    DrawFillRect(rectInfo, AppColor.back_light);
    DrawRoundBorder(rectInfo);

    // 序号
    if (FVData.FileCount <= 0)
        sprintf(fInfo, "0/0");
    else if (NULL != FVData.FocusItem)
        sprintf(fInfo, "%d/%d", FVData.FocusItem->index, FVData.FileCount);
    DrawTextMidRightA(rectInfo, fInfo, AppColor.text_normal);

    // 信息
    if (FVData.FileCount <= 0)
    {
        sprintf(fInfo, "空文件夹");
    }
    else if (NULL != FVData.FocusItem)
    {
        fNode = FVData.FocusItem;

        switch (fNode->type)
        {
        case MR_IS_DISK:
            if (fNode->size > 1024 * 1024)
                sprintf(fInfo, "%d.%dGB",  fNode->size / (1024 * 1024), (fNode->size % (1024 * 1024)) * 100 / (1024 * 1024));
            else if (fNode->size > 1024)
                sprintf(fInfo, "%d.%dMB", fNode->size / 1024, (fNode->size % 1024) * 100 / 1024);
            else
                sprintf(fInfo, "%dKB", fNode->size);
            break;
        case MR_IS_FILE:
            if (fNode->size > 1024 * 1024 * 1024)
                sprintf(fInfo, "%d.%dGB",  fNode->size / (1024 * 1024 * 1024), 
                    (fNode->size % (1024 * 1024 * 1024)) * 100 / (1024 * 1024 * 1024));
            else if (fNode->size > 1024 * 1024)
                sprintf(fInfo, "%d.%dMB",  fNode->size / (1024 * 1024), (fNode->size % (1024 * 1024)) * 100 / (1024 * 1024));
            else if (fNode->size > 1024)
                sprintf(fInfo, "%d.%dKB", fNode->size / 1024, (fNode->size % 1024) * 100 / 1024);
            else
                sprintf(fInfo, "%dB", fNode->size);
            break;
        case MR_IS_DIR:
            sprintf(fInfo, "文件夹");
            break;
        case MR_IS_OPEN:
            sprintf(fInfo, "无法操作");
            break;
        default:
            sprintf(fInfo, "错误文件");
            break;
        }
    }
    DrawTextMidLeftA(rectInfo, fInfo, AppColor.text_normal); 

    // 滚动条
    if (FVData.FileCount > FVData.VisLines)
    {
        sclY = (int16)(rectScroll.y + 1 + (rectScroll.h - 2) * (FVData.TopItem->index - 1) / FVData.FileCount);
        sclH = (int16)((rectScroll.h - 2) * FVData.VisLines / FVData.FileCount);
        DrawFillRectEx(rectScroll.x + 1, sclY, rectScroll.w - 1, sclH, AppColor.back_deep);
        DrawHLine(rectScroll.x + 2, rectScroll.x + rectScroll.w - 2, sclY - 1, AppColor.back_deep);
        DrawHLine(rectScroll.x + 2, rectScroll.x + rectScroll.w - 2, sclY + sclH, AppColor.back_deep);
    }

    if (refresh)
        RefreshRect(rectSpace);
}

// 绘制标题栏
static void FV_DrawTitleBar(char *title, uint8 refresh)
{
    DrawNormalTitleBarW(rectTitle, title);

    if (refresh)
        RefreshRect(rectTitle);
}

// 绘制底部工具栏
// 参数：状态：0 - 普通，1 - 左软键，2 - 右软键
static void FV_DrawToolBar(uint8 state, uint8 refresh)
{
    // 选项 / 取消
    DrawNormalToolBarW(rectTool, "\x90\x9\x98\x79\x0\x0", "\x53\xd6\x6d\x88\x0\x0", state);

    if (1 == InputState)
    {
        char index[12];
        char wstr[24];

        if (InputIndex > 0)
            sprintf(index, "#%d", InputIndex);
        else
            sprintf(index, "#");
        Asc2Uni(index, wstr, sizeof(wstr));
        DrawTextMidW(rectTool, wstr, AppColor.text_light);
    }

    if (refresh)
        RefreshRect(rectTool);
}

// 显示信息
static void FV_ShowInfo(const char *info, uint8 refresh)
{
    DrawFillRect(rectInfo, AppColor.back_light);
    DrawRoundBorder(rectInfo);
    DrawTextMidLeftA(rectInfo, info, AppColor.text_normal); 

    if (refresh)
        RefreshRect(rectInfo);
}

// 显示已遍历文件数
static void FV_ShowCount(int32 count)
{
    char fInfo[16] = {0};
    
    DrawFillRect(rectInfo, AppColor.back_light);
    DrawRoundBorder(rectInfo);
    DrawTextMidLeftA(rectInfo, "正在搜索……", AppColor.text_normal);
    sprintf(fInfo, ">%d", count);
    DrawTextMidRightA(rectInfo, fInfo, AppColor.text_normal);
    RefreshRect(rectInfo);
}

// 绘制全部
int32 FileView_Draw(uint8 refresh)
{
    FV_DrawTitleBar(FVData.Title, refresh);
    FV_DrawToolBar(0, refresh);
    FV_DrawList(refresh);

    return 0;
}

/*---------------------------------------------------------------------------*/

//根据序号取得文件节点
//参数：序号
//返回：节点
static FILEITEM_ST *FV_GetItemByIndex(int16 index)
{
    FILEITEM_ST *fItem = NULL;

    fItem = FVData.HeadItem;
    while (NULL != fItem && fItem->index != index)
    {
        fItem = fItem->next;
    }

    if (NULL == fItem)
        fItem = FVData.HeadItem;

    return fItem;
}

//根据名称取得文件节点
//参数：名称
//返回：节点
static FILEITEM_ST *FV_GetItemByName(const char *name)
{
    FILEITEM_ST *fItem = FVData.HeadItem;

    while (NULL != fItem && 0 != stricmp(fItem->name, name))
    {
        fItem = fItem->next;
    }

    if (NULL == fItem)
        fItem = FVData.HeadItem;

    return fItem;
}

/*---------------------------------------------------------------------------*/

//清除文件链表
void FV_ClearFileItems(void)
{
    FILEITEM_ST *fItem = NULL, *fItem2 = NULL;

    fItem = FVData.HeadItem;

    while (NULL != fItem)
    {
        if (fItem->name)
        {
            TRYFREE(fItem->name);
            fItem->name = NULL;
        }
        fItem2 = fItem->next;
        TRYFREE(fItem);
        fItem = fItem2;
    }

    FVData.HeadItem = NULL;
    FVData.FocusItem = NULL;
    FVData.TopItem = NULL;
}

// 清除路径链表
static void FV_ClearPathNodes(void)
{
    PATHNODE_ST *fNode = NULL, *fNode2 = NULL;

    fNode = FVData.PathNode;
    while (NULL != fNode)
    {
        TRYFREE(fNode->name);
        fNode2 = fNode->next;
        TRYFREE(fNode);
        fNode = fNode2;
    }

    FVData.PathNode = NULL;
}

// 构建磁盘节点
static int32 FV_MakeDiskItems(void)
{
    FILEITEM_ST *fItem = NULL;
    int32 fCount = 0;

    FV_ClearFileItems();

    fItem = (FILEITEM_ST *)malloc(sizeof(FILEITEM_ST));
    FVData.HeadItem = fItem;
    fItem->index = 1;
    fItem->type = MR_IS_DISK;
    fItem->size = -1;
    fItem->name = strdup("A:\\（系统盘）");
    fItem->last = NULL;
    fItem->next = (FILEITEM_ST *)malloc(sizeof(FILEITEM_ST));
    fItem->next->last = fItem;
    fItem = fItem->next;
    fItem->index = 2;
    fItem->type = MR_IS_DISK;
    fItem->size = -1;
    fItem->name = strdup("B:\\（手机盘）");
    fItem->next = (FILEITEM_ST *)malloc(sizeof(FILEITEM_ST));
    fItem->next->last = fItem;
    fItem = fItem->next;
    fItem->index = 3;
    fItem->type = MR_IS_DISK;
    fItem->size = -1;
    fItem->name = strdup("C:\\（内存卡）");
    fItem->next = NULL;
    fCount = 3;

    if (GetDiskSize("D", 0) > 0) //如果存在D盘
    {
        fItem->next = (FILEITEM_ST *)malloc(sizeof(FILEITEM_ST));
        fItem->next->last = fItem;
        fItem = fItem->next;
        fItem->index = 4;
        fItem->type = MR_IS_DISK;
        fItem->size = -1;
        fItem->name = strdup("D:\\（其它）");
        fItem->next = NULL;
        fCount++;
    }

    return fCount;
}

//查找当前文件夹文件并构建已排序链表
//返回：文件总数
static int32 FV_FindFiles(void)
{
    int16 i;
    int32 ret = 0;
    int32 findHwnd = 0;
    int32 fCount = 0;
    char *fBuffer = NULL;
    FILEITEM_ST *fItem = NULL, *lItem = NULL;

    if ('\0' == FVData.Path[0])
    {
        fCount = FV_MakeDiskItems();

        return fCount;
    }

    FV_ClearFileItems();

#ifndef SDK_MOD
    ret = Switch2Dir(FVData.Path);
    if (0 != ret)
    {
        FVData.HeadItem = NULL;

        return -1;
    }
#endif

    // 构建空节点，方便排序
    fItem = (FILEITEM_ST *)malloc(sizeof(FILEITEM_ST));
    FVData.HeadItem = fItem;
    fItem->type = MR_IS_DIR;
    fItem->size = -2;
    fItem->name = "";
    fItem->last = NULL;
    fItem->next = (FILEITEM_ST *)malloc(sizeof(FILEITEM_ST));
    fItem->next->last = fItem;
    fItem = fItem->next;
    fItem->type = MR_IS_FILE;
    fItem->size = -2;
    fItem->name = "";
    fItem->next = (FILEITEM_ST *)malloc(sizeof(FILEITEM_ST));
    fItem->next->last = fItem;
    fItem = fItem->next;
    fItem->type = MR_IS_INVALID;
    fItem->size = -2;
    fItem->name = "";
    fItem->next = (FILEITEM_ST *)malloc(sizeof(FILEITEM_ST));
    fItem->next->last = fItem;
    fItem = fItem->next;
    fItem->type = MR_IS_DISK;
    fItem->size = -2;
    fItem->name = "";
    fItem->next = NULL;

    fBuffer = (char*)malloc(MAX_PATH_LEN_A);
    memset(fBuffer, 0, MAX_PATH_LEN_A);


    //查找第一个
    findHwnd = findstart("", fBuffer, MAX_PATH_LEN_A);
    if (findHwnd > 0)  // 非空文件夹
    {
        // 遍历所有文件夹和文件
        do {
            // 忽略"."、".."
            if (!((fBuffer[0] == '\0')
                || (fBuffer[0] == '.' && fBuffer[1] == '\0')
                || (fBuffer[0] == '.' && fBuffer[1] == '.' && fBuffer[2] == '\0')))
            {
                if (0 == fCount % 10 && fCount > 0)
                    FV_ShowCount(fCount);

                fCount++;

                // 取得信息
                fItem = (FILEITEM_ST *)malloc(sizeof(FILEITEM_ST));
                fItem->name = strdup(fBuffer);
                fItem->type = (uint8)mrc_fileState(fBuffer);
                fItem->size = -1;

                // 查找同类型开始位置
                lItem = FVData.HeadItem;
                while (lItem->type != fItem->type)
                {
                    lItem = lItem->next;
                }

                // 按名称排序
                while (NULL != lItem) 
                {
                    if (lItem->type != fItem->type)
                        break;

                    if (stricmp(lItem->name, fItem->name) > 0)
                        break;

                    lItem = lItem->next;
                }

                // 插入
                fItem->last = lItem->last;
                fItem->next = lItem;
                lItem->last->next = fItem;
                lItem->last = fItem;
            }

            // 查找下一个
            fBuffer[0] = '\0';
        } while (MR_SUCCESS == findnext(findHwnd, fBuffer, MAX_PATH_LEN_A));

        // 结束查找
        findstop(findHwnd);
    }

    Switch2Dir(NULL);

    TRYFREE(fBuffer);

    fItem = FVData.HeadItem;
    FVData.HeadItem = NULL;
    i = 1;

    while (NULL != fItem)
    {
        if (-2 != fItem->size) // 添加序号
        {
            if (1 == i)
                FVData.HeadItem = fItem;
            fItem->index = i;
            i++;
            fItem = fItem->next;
        }
        else // 删除空节点
        {
            if (NULL != fItem->last)
                fItem->last->next = fItem->next;
            if (NULL != fItem->next)
                fItem->next->last = fItem->last;
            lItem = fItem->next;
            TRYFREE(fItem);
            fItem = lItem;
        }
    }

    return fCount;
}

// 根据路径节点生成路径字符串
static int32 FV_MakePathByNodes(void)
{
    PATHNODE_ST *fNode = NULL;

    memset(FVData.Path, 0, sizeof(FVData.Path));
    fNode = FVData.PathNode;

    while (NULL != fNode)
    {
        switch (fNode->type)
        {
        case MR_IS_DISK:  // 磁盘
            strncat(FVData.Path, fNode->name, 3);  // 构造文件夹路径
            break;
        case MR_IS_DIR:  // 文件夹
            strcat(FVData.Path, fNode->name);  // 构造文件夹路径
            strcat(FVData.Path, "\\");
            break;
        case MR_IS_FILE:  // 文件
            break;
        default:
            FVData.FileCount = 0;
            return -1;
        }

        fNode = fNode->next;
    }

    return 0;
}

// 根据名称定位焦点和显示首项
static int32 FV_LocateItemByName(const char *name)
{
    FVData.FocusItem = FV_GetItemByName(name);

    if (NULL == FVData.FocusItem)
    {
        // 不存在，定位到开头
        FVData.FocusItem = FVData.TopItem = FVData.HeadItem;
    }
    else if (FVData.FocusItem->index + FVData.VisLines <= FVData.FileCount + 1)
    {
        // 尽量把焦点项定位到第一项显示
        FVData.TopItem = FVData.FocusItem;
    } 
    else if (FVData.FileCount > FVData.VisLines)
    {
        // 保证列表项充满列表
        FVData.TopItem = FV_GetItemByIndex((int16)(FVData.FileCount - FVData.VisLines + 1));
    }
    else
    {
        // 列表项太少，从头显示
        FVData.TopItem = FVData.HeadItem;
    }

    return 0;
}

// 进入下级文件夹
static int32 FV_PathInto(void)
{
    PATHNODE_ST *fNode = NULL;

    if (NULL == FVData.PathNode)  // 添加磁盘节点
    {
        FVData.PathNode = fNode = (PATHNODE_ST *)malloc(sizeof(PATHNODE_ST));
        fNode->last = NULL;
        fNode->next = NULL;
    }
    else
    {
        fNode = FVData.PathNode;
        while (NULL != fNode->next)
        {
            fNode = fNode->next;
        }
        fNode->next = (PATHNODE_ST *)malloc(sizeof(PATHNODE_ST));
        fNode->next->last = fNode;
        fNode = fNode->next;
        fNode->next = NULL;
    }

    fNode->type = FVData.FocusItem->type;
    fNode->topIndex = FVData.TopItem->index;
    fNode->focusIndex = FVData.FocusItem->index;
    fNode->name = strdup(FVData.FocusItem->name);

    FV_MakePathByNodes();
    FVData.FileCount = FV_FindFiles();   // 查找文件
    FVData.FocusItem = FVData.HeadItem;  // 定位焦点项
    FVData.TopItem = FVData.HeadItem;    // 定位显示首项

    return 0;
}

// 返回上级文件夹
static int32 FV_PathOut(void)
{
    PATHNODE_ST *fNode = NULL;
    int16 tIndex = 1, cIndex = 1;  // 首显示节点序号，当前节点序号
    char *name;

    if (NULL == FVData.PathNode)  // 空路径
    {
        return -1;
    }
    else if (NULL == FVData.PathNode->next)  // 根目录
    {
        tIndex = FVData.PathNode->topIndex;
        cIndex = FVData.PathNode->focusIndex;
        name = strdup(FVData.PathNode->name);
        TRYFREE(FVData.PathNode->name);
        TRYFREE(FVData.PathNode);
        FVData.PathNode = NULL;
    }
    else // 其它
    {
        fNode = FVData.PathNode;
        while (NULL != fNode->next)
        {
            fNode = fNode->next;
        }
        tIndex = fNode->topIndex;
        cIndex = fNode->focusIndex;
        name = strdup(fNode->name);
        fNode->last->next = NULL;
        TRYFREE(fNode->name);
        TRYFREE(fNode);
    }

    FV_MakePathByNodes();
    FVData.FileCount = FV_FindFiles();  // 查找文件

    if (tIndex >=0 && cIndex >= 0)
    {
        // 以前浏览过，根据记录的序号定位
        FVData.TopItem = FV_GetItemByIndex(tIndex);    // 定位显示首项
        FVData.FocusItem = FV_GetItemByIndex(cIndex);  // 定位焦点项
    }
    else
    {
        // 未浏览过，根据名称定位
        FV_LocateItemByName(name);
    }

    TRYFREE(name);

    return 0;
}

// 根据路径定位文件
// 参数：路径（不含盘符）
static void FV_Locate(char *path)
{
    PATHNODE_ST *fNode = NULL;
    char *p = NULL;

    // 不允许没有磁盘节点
    if (NULL == FVData.PathNode)
        return;

    // 路径错误
    if (NULL == path)
        return;

    // 路径结束，进入目录
    if ('\0' == *path)
    {
        FV_MakePathByNodes();
        FVData.FileCount = FV_FindFiles();  // 查找文件
        FVData.FocusItem = FVData.TopItem = FVData.HeadItem;  // 定位到开头

        return;
    }

    // 查找路径分隔符
    p = (char*)strchr(path, '\\');

    if (NULL != p)
    {
        *p = '\0';

        // 添加路径节点
        fNode = FVData.PathNode;
        while (NULL != fNode->next)
        {
            fNode = fNode->next;
        }
        fNode->next = (PATHNODE_ST *)malloc(sizeof(PATHNODE_ST));
        fNode->next->last = fNode;
        fNode = fNode->next;
        fNode->next = NULL;
        fNode->type = MR_IS_DIR;
        fNode->topIndex = -1;
        fNode->focusIndex = -1;
        fNode->name = strdup(path);

        *p = '\\';

        // 递归进入下一层
        FV_Locate(p + 1);
    }
    else
    {
        // 没有下级目录
        FV_MakePathByNodes();
        FVData.FileCount = FV_FindFiles();  // 查找文件
        FV_LocateItemByName(path);          // 定位到文件名位置
    }
}

// 根据完整路径定位文件
// 参数：路径（含盘符）
static void FV_LocateFull(const char *path_in)
{
    PATHNODE_ST *fNode = NULL;
    int16 index;
    char *path;

    path = strdup(path_in);
    FixPath(path, '\\');

    memset(FVData.Path, 0, sizeof(FVData.Path));
    FV_ClearFileItems();
    FV_ClearPathNodes();

    index = *path - 'A';
    if (index > 32)
        index -= 32;

    FVData.FileCount = FV_MakeDiskItems();
    FVData.TopItem = FVData.HeadItem;
    FVData.FocusItem = FV_GetItemByIndex(index + 1);

    FVData.PathNode = fNode = (PATHNODE_ST *)malloc(sizeof(PATHNODE_ST));
    fNode->last = NULL;
    fNode->next = NULL;
    fNode->type = MR_IS_DISK;
    fNode->topIndex = FVData.TopItem->index;
    fNode->focusIndex = FVData.FocusItem->index;
    fNode->name = strdup(FVData.FocusItem->name);

    FV_ClearFileItems();
    FVData.FileCount = 0;

    FV_Locate(path + 3);

    TRYFREE(path);
}

// 显示文件浏览
int32 FileView_Show(char *sTitle, char *sPath, int32 flag, FV_CB cbFunc)
{
	fv_init(0);

	if(sPath == NULL){
	    sPath = "";
	}
    LOGI("fv_begin %s", sPath);
	fv_begin(sPath);
	LOGI("end");
	/*
    FVData.CallBack = cbFunc;
    FVData.Flag = flag;

    // 保存标题
    if (NULL != sTitle)
    {
        int32 slen;

        slen = wstrlen(sTitle);
        memcpy(FVData.Title, sTitle, slen + 2);
    }
    else
    {
        FVData.Title[0] = FVData.Title[1] = '\0';
    }

    // 使用最近浏览
    if (flag & FILEVIEW_FLAG_RECENT)
    {
        if (FVData.Path[0] != '\0')
        {
            SetAppState(APPSTATE_FILEVIEW, 1);
            return MR_SUCCESS;
        }
    }

    FV_ClearFileItems();
    FV_ClearPathNodes();

    // 根据路径选择浏览方式
    if (NULL == sPath)
    {
        memset(FVData.Path, 0, sizeof(FVData.Path));
        FVData.FileCount = FV_MakeDiskItems();
        FVData.FocusItem = FVData.HeadItem;
        FVData.TopItem = FVData.HeadItem;
    }
    else
    {
        FV_LocateFull(sPath);
    }
*/
  //  SetAppState(APPSTATE_FILEVIEW, 1);

    return 0;
}

// 结束文件浏览显示 路径 名称
int32 FileView_Hide(const char *path, const char *name)
{
    fv_end();
    SetAppState(APPSTATE_RETURN, 1);
    FVData.CallBack(path, name);

    return 0;
}

// 刷新文件列表
int32 FileView_Refresh(void)
{
    int16 tIndex, cIndex;

    cIndex = (NULL != FVData.FocusItem ? FVData.FocusItem->index : 1);
    tIndex = (NULL != FVData.TopItem ? FVData.TopItem->index : 1);

    FVData.FileCount = FV_FindFiles();             // 查找文件
    FVData.FocusItem = FV_GetItemByIndex(cIndex);  // 定位焦点项
    FVData.TopItem = FV_GetItemByIndex(tIndex);    // 定位显示首项
    FV_DrawList(1);

    return 0;
}

/*---------------------------------------------------------------------------*/

//上下改变列表行
//参数：改变行数
static void FV_ListUpDown(int16 nCount)
{
    FILEITEM_ST *fItem = NULL;
    int16 nIndex = 0;

    if (NULL == FVData.TopItem || NULL == FVData.FocusItem || 0 == nCount)
        return;

    //定位首项
    nIndex = FVData.TopItem->index + nCount;

    if (nCount < 0) //向上滚动
    {
        if (nIndex < 1)
            nIndex = 1;
    }
    else if (nCount > 0) //向下滚动
    {
        if (nIndex + FVData.VisLines > FVData.FileCount) //超出范围
        {
            if (FVData.FileCount > FVData.VisLines)
                nIndex = (int16)(FVData.FileCount - FVData.VisLines + 1);
            else
                nIndex = 1;
        }
    }

    fItem = FVData.HeadItem;
    while (NULL != fItem && fItem->index != nIndex)
        fItem = fItem->next;
    FVData.TopItem = fItem;

    //定位焦点项
    nIndex = FVData.FocusItem->index;


    if (FVData.FocusItem->index < FVData.TopItem->index)
        nIndex = FVData.TopItem->index;

    if (FVData.FocusItem->index > FVData.TopItem->index + FVData.VisLines - 1)
        nIndex = FVData.TopItem->index + (int16)FVData.VisLines - 1;

    fItem = FVData.HeadItem;
    while (NULL != fItem && fItem->index != nIndex)
    {
        fItem = fItem->next;
    }
    FVData.FocusItem = fItem;

    FV_DrawList(1);
}

// 列表上下滚动
static void FV_ListScroll(int32 lines)
{
    FILEITEM_ST *tItem;
    int32 new_index, old_index;

    if (FVData.FileCount <= 0 || 0 == lines)
        return;

    old_index = FVData.FocusItem->index;
    new_index = old_index + lines;

    if (lines < 0)  // 向上
    {
        if (new_index < 1)  // 到顶部
        {
            if (-1 == lines)  // 只滚动一行时允许循环到底部
            {
                for (tItem = FVData.HeadItem; tItem->next != NULL; tItem = tItem->next)
                    ;
                FVData.FocusItem = tItem;

                for (tItem = FVData.HeadItem; tItem->index <= FVData.FileCount - FVData.VisLines; tItem = tItem->next)
                    ;
                FVData.TopItem = tItem;
            }
            else
            {
                new_index = 1;
                FVData.TopItem = FVData.FocusItem = FVData.HeadItem;
            }
        }
        else
        {
            // 查找新焦点
            for (tItem = FVData.HeadItem;  NULL != tItem; tItem = tItem->next)
            {
                if (tItem->index == new_index)
                    break;
            }

            FVData.FocusItem = tItem;

            // 需要改变首行显示
            if (new_index < FVData.TopItem->index)
            {
                FVData.TopItem = tItem;
            }
        }
    }
    else  // 向下
    {
        if (new_index > FVData.FileCount)  // 到底部
        {
            if (1 == lines)  // 只滚动一行时允许循环到顶部
            {
                new_index = 1;
                FVData.TopItem = FVData.FocusItem = FVData.HeadItem;
            }
            else
            {
                for (tItem = FVData.HeadItem; tItem->next != NULL; tItem = tItem->next)
                    ;
                FVData.FocusItem = tItem;

                for (tItem = FVData.HeadItem; tItem->index <= FVData.FileCount - FVData.VisLines; tItem = tItem->next)
                    ;
                FVData.TopItem = tItem;
            }
        }
        else
        {
            // 查找新焦点
            for (tItem = FVData.HeadItem;  NULL != tItem; tItem = tItem->next)
            {
                if (tItem->index == new_index)
                    break;
            }

            FVData.FocusItem = tItem;

            // 需要改变首行显示
            if (new_index >= FVData.TopItem->index + FVData.VisLines)
            {
                for (tItem = FVData.HeadItem; tItem->index <= new_index - FVData.VisLines; tItem = tItem->next)
                    ;
                FVData.TopItem = tItem;
            }
        }
    }

    FV_DrawList(1);
}

/*---------------------------------------------------------------------------*/

//处理文件列表操作
//参数：操作类型
void FV_DoListEvent(uint8 action)
{
    switch (action)
    {
    case FV_ACTION_ITEM_UP:
        // 到开头
        if (FVData.FileCount > 0 && FVData.FocusItem->index == 1) 
        {
            // 停止滚动，避免滚动条循环
            if (1 == IsScrolling)
            {
                KeyTimerStop();
                IsScrolling = 0;
                break;
            }
        }
        FV_ListScroll(-1);
        break;
    case FV_ACTION_ITEM_DOWN:
        // 到末尾
        if (FVData.FileCount > 0 && FVData.FocusItem->index == FVData.FileCount)
        {
            // 停止滚动，避免滚动条循环
            if (1 == IsScrolling)
            {
                KeyTimerStop();
                IsScrolling = 0;
                break;
            }
        }
        FV_ListScroll(1);
        break;
    case FV_ACTION_PAGE_UP:
        FV_ListScroll(-FVData.VisLines);
        break;
    case FV_ACTION_PAGE_DOWN:
        FV_ListScroll(FVData.VisLines);
        break;
    case FV_ACTION_PAGE_HOME:
        FV_ListScroll(-FVData.FileCount);
        break;
    case FV_ACTION_PAGE_END:
        FV_ListScroll(FVData.FileCount);
        break;

    case FV_ACTION_PATH_OUT: //上级目录
        FV_PathOut();
        FV_DrawList(1);
        break;
    case FV_ACTION_PATH_INTO: //下级目录
        if (FVData.FileCount <= 0)
            return;

        switch (FVData.FocusItem->type)
        {
        case MR_IS_DISK:
        case MR_IS_DIR:
            FV_PathInto();
            FV_DrawList(1);
            break;
        case MR_IS_FILE:
            break;
        default:
            break;
        }
        break;
    case FV_ACTION_SELECT: //选择文件或下级目录/OK
        if (FVData.FileCount <= 0) 
            return;

        switch (FVData.FocusItem->type)
        {
        case MR_IS_DISK:
            if (FVData.Flag & FILEVIEW_FLAG_FOLDER)
            {
                char disk[4] = {0};

                memcpy(disk, FVData.FocusItem->name, 3);
                FileView_Hide(disk, "");
            }
            else
            {
                FV_PathInto();
                FV_DrawList(1);
            }
            break;
        case MR_IS_DIR:
            if (FVData.Flag & FILEVIEW_FLAG_FOLDER)
            {
                FileView_Hide(FVData.Path, FVData.FocusItem->name);
            }
            else
            {
                FV_PathInto();
                FV_DrawList(1);
            }
            break;
        case MR_IS_FILE:
            if (FVData.Flag & FILEVIEW_FLAG_FILE)
            {
                FileView_Hide(FVData.Path, FVData.FocusItem->name);
            }
            break;
        default:
            break;
        }
        break;
    }
}

/*---------------------------------------------------------------------------*/

//改变滚动条
//参数：新纵坐标，按键：0 - 按下，1 - 抬起
static void FV_ChangeScroll(int32 newY, uint8 keyCode)
{
    int16 ScrollM;

    IsScrolling = 1 - keyCode;
    ScrollM = rectScroll.y + 1 + (rectScroll.h - 2) / 2;

    if (0 == keyCode)
    {
        if (newY > ScrollM)
            FileView_Event(MR_KEY_PRESS, MR_KEY_DOWN, 0);
        else
            FileView_Event(MR_KEY_PRESS, MR_KEY_UP, 0);
    }
    else
    {
        if (newY > ScrollM)
            FileView_Event(MR_KEY_RELEASE, MR_KEY_DOWN, 0);
        else
            FileView_Event(MR_KEY_RELEASE, MR_KEY_UP, 0);
    }
}

//根据纵坐标改变列表
//参数：纵坐标
static void FV_FocusByPos(int32 Y, uint8 isUp)
{
    static uint8 IsFirstPress = 1; // 是否第一次点击，避免在点一次就进入
    FILEITEM_ST *fItem = NULL;
    int16 lIndex;

    if (NULL == FVData.TopItem)
        return;

    lIndex = (int16)(Y - rectList.y) / ItemHeight + FVData.TopItem->index;
    if (lIndex >= FVData.TopItem->index + FVData.VisLines)
        return;

    //定位焦点项
    fItem = FVData.HeadItem;
    while(fItem && fItem->index != lIndex)
    {
        fItem = fItem->next;
    }

    if (NULL != fItem)
    {
        if (FVData.FocusItem == fItem && 1 == isUp) //再次选择
        {
            if (0 == IsFirstPress)
                FV_DoListEvent(FV_ACTION_SELECT);
            else
                IsFirstPress = 0;
        }
        else if (FVData.FocusItem != fItem)
        {
            IsFirstPress = 1;
            FVData.FocusItem = fItem; //选中
            FV_DrawList(1);
        }
    }
}

// 输入目录回调
static void FVInputPathCb(const char *path)
{
    char *gbStr;

    gbStr = stru2c(path);
    FV_LocateFull(gbStr);
    TRYFREE(gbStr);

    FV_DrawList(1);
}

// 输入目录
static void FV_InputPath(void)
{
    char *uniStr;

    uniStr = strc2u(FVData.Path);
    ShowInput("输入路径", uniStr, MR_EDIT_ANY, MAX_PATH_LEN_A, FVInputPathCb);
    TRYFREE(uniStr);
}

// 连续按键回调
static void FVKeyTimerDo(int32 data)
{
    FV_DoListEvent((uint8)data);
}

/*---------------------------------------------------------------------------*/
//文件浏览事件处理
int32 FileView_Event(int32 type, int32 p1, int32 p2)
{
    static POINT_ST MousePos = {0}; // 触屏按下位置

    switch (type)
    {
    case MR_KEY_PRESS://选择列表项
        switch (p1)
        {
        case MR_KEY_UP:
            KeyTimerStart(FV_ACTION_ITEM_UP, FVKeyTimerDo);
            break;
        case MR_KEY_DOWN:
            KeyTimerStart(FV_ACTION_ITEM_DOWN, FVKeyTimerDo);
            break;
        case MR_KEY_VOLUME_UP:
            KeyTimerStart(FV_ACTION_PAGE_UP, FVKeyTimerDo);
            break;
        case MR_KEY_VOLUME_DOWN:
            KeyTimerStart(FV_ACTION_PAGE_DOWN, FVKeyTimerDo);
            break;
        case MR_KEY_1:
            if (0 == InputState)
                KeyTimerStart(FV_ACTION_PAGE_UP, FVKeyTimerDo);
            break;
        case MR_KEY_4:
            if (0 == InputState)
                KeyTimerStart(FV_ACTION_PAGE_DOWN, FVKeyTimerDo);
            break;
        case MR_KEY_SOFTLEFT:
            FV_DrawToolBar(1, 1);
            break;
        case MR_KEY_SOFTRIGHT:
            FV_DrawToolBar(2, 1);
            break;
        }
        break;
    case MR_KEY_RELEASE:
        switch (p1)
        {
        case MR_KEY_UP:
        case MR_KEY_DOWN:
        case MR_KEY_VOLUME_UP:
        case MR_KEY_VOLUME_DOWN:
            KeyTimerStop();
            break;
        case MR_KEY_LEFT: //左
            FV_DoListEvent(FV_ACTION_PATH_OUT);
            break;
        case MR_KEY_RIGHT: //右
            FV_DoListEvent(FV_ACTION_PATH_INTO);
            break;
        case MR_KEY_SOFTLEFT:
            FV_DrawToolBar(0, 1);
            //FV_DoListEvent(FV_ACTION_SELECT);
            FVMenu_Show();
            break;
        case MR_KEY_SELECT: //OK
            FV_DoListEvent(FV_ACTION_SELECT);
            break;
        case MR_KEY_SOFTRIGHT: //取消浏览
            FileView_Hide(NULL, NULL);
            break;
        case MR_KEY_STAR:
            FileView_Refresh();
            break;
        case MR_KEY_POUND:
            if (1 == InputState)
            {
                // 序号输入状态按#键确定输入
                if (InputIndex > 0 && InputIndex <= FVData.FileCount)
                {
                    FVData.TopItem = FV_GetItemByIndex((FVData.FileCount > FVData.VisLines + InputIndex) ? 
                        (int16)InputIndex : (int16)(FVData.FileCount - FVData.VisLines + 1));
                    FVData.FocusItem = FV_GetItemByIndex((int16)InputIndex);
                    FV_DrawList(1);
                }
                InputIndex = 0;
                InputState = 0;
                FV_DrawToolBar(0, 1);
            }
            else
            {
                // 快捷键状态按#键进入序号输入
                InputState = 1;
                FV_DrawToolBar(0, 1);
            }
            break;
        default:
            if (1 == InputState)
            {
                // 序号输入状态按数字键输入
                if (p1 >= MR_KEY_0 && p1 <= MR_KEY_9)
                {
                    InputIndex = InputIndex * 10 + p1;
                    if (InputIndex > FVData.FileCount)
                        InputIndex = 0;

                    FV_DrawToolBar(0, 1);
                }
            }
            else
            {
                // 快捷键状态
                switch (p1)
                {
                case MR_KEY_1:
                case MR_KEY_4:
                    KeyTimerStop();
                    break;
                case MR_KEY_3:
                    FV_DoListEvent(FV_ACTION_PAGE_HOME);
                    break;
                case MR_KEY_6:
                    FV_DoListEvent(FV_ACTION_PAGE_END);
                    break;
                case MR_KEY_2:
                    FV_InputPath();
                    break;
                case MR_KEY_5:
                    FileView_Event(type, MR_KEY_SELECT, 0);
                    break;
                }
            }
            break;
        }
        break;
    case MR_MOUSE_UP: //触屏抬起
        {
            if (1 == IsScrolling) //滚动条
            {
                FV_ChangeScroll(p2, 1);
            }
            else if (MousePos.X - p1 > (int32)rectList.w / 3) //向左滑动
            {
                FV_DoListEvent(FV_ACTION_PATH_OUT);
            }
            else if (p1 - MousePos.X > (int32)rectList.w / 3) //向右滑动
            {
                FV_DoListEvent(FV_ACTION_PATH_INTO);
            }
            else if (MousePos.Y - (int16)p2 > ItemHeight) //向上滑动
            {
                FV_ListUpDown((MousePos.Y - (int16)p2) / ItemHeight);
            }
            else if ((int16)p2 - MousePos.Y > ItemHeight) //向下滑动
            {
                FV_ListUpDown((MousePos.Y - (int16)p2) / ItemHeight);
            }
            else if (p2 >= rectInput.y && p2 < rectInput.y + rectInput.h) //路径输入框
            {
                FV_InputPath();
            }
            else if (p2 >= rectTool.y && p2 < rectTool.y + rectTool.h)
            {
                if (p1 < ButtonWidth)
                {
                    FileView_Event(MR_KEY_RELEASE, MR_KEY_SOFTLEFT, 0);
                }
                else if (p1 >= rectTool.w - ButtonWidth)
                {
                    FileView_Event(MR_KEY_RELEASE, MR_KEY_SOFTRIGHT, 0);
                }
            }
            else if (p1 < rectList.x + rectList.w - 4) //列表
            {
                FV_FocusByPos(p2, 1);
            }
        }
        break;
    case MR_MOUSE_DOWN: //触屏按下
        {
            MousePos.X = (int16)p1;
            MousePos.Y = (int16)p2;

            if (p2 >= rectTool.y && p2 < rectTool.y + rectTool.h)
            {
                if (p1 < ButtonWidth)
                {
                    FileView_Event(MR_KEY_PRESS, MR_KEY_SOFTLEFT, 0);
                }
                else if (p1 >= rectTool.w - ButtonWidth)
                {
                    FileView_Event(MR_KEY_PRESS, MR_KEY_SOFTRIGHT, 0);
                }
            }
            else if (p1 > rectScroll.x - 4 && p1 < rectScroll.x + rectScroll.w) //滚动条
            {
                FV_ChangeScroll(p2, 0);
            }
            else if (p1 < rectList.x + rectList.w - 4) //列表
            {
                FV_FocusByPos(p2, 0);
            }
        }
        break;
    case MR_MOUSE_MOVE:
        {
            int16 lines;

            lines = (int16)((p2 - MousePos.Y) / ItemHeight);

            if (0 != lines) // 滑动
            {
                FV_ListUpDown(-lines);
                MousePos.Y += lines * ItemHeight;
            }
        }
        break;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/
// 文件操作

static uint32 NewFileSize;   // 新建文件大小

// 重命名文件(夹)回调
static void FileRenameCb(const char *name_w)
{
    char *name_a;
    int32 ret;

    name_a = stru2c(name_w);

    Switch2Dir(FVData.Path);
    ret = mrc_rename(FVData.FocusItem->name, name_a);
    Switch2Dir(NULL);

    TRYFREE(name_a);

    if (0 == ret)
    {
        FileView_Refresh();
        FV_ShowInfo("重命名完成。", 1);
    }
    else
    {
        FV_ShowInfo("重命名失败！", 1);
    }
}

// 复制文件回调
static void FileCopyCb(const char *name_w)
{
    char *name_a;
    int32 ret;

    FV_ShowInfo("正在复制文件……", 1);

    name_a = stru2c(name_w);

    if (':' == name_a[1])  // 绝对路径
    {
        name_a[2] = '\0';
        ret = CopyFileFullPath(FVData.Path, name_a, FVData.FocusItem->name, name_a + 3);
        name_a[2] = '\\';

        if (MR_SUCCESS == ret)
        {
            // 源文件和目标文件在同一目录
            if (0 == strnicmp(ConvertPathSeparator(name_a), ConvertPathSeparator1(FVData.Path), strlen(FVData.Path)))
            {
                // 刷新文件列表
                FileView_Refresh();
            }

            FV_ShowInfo("文件复制完成。", 1);
        }
        else
        {
            FV_ShowInfo("文件复制失败！", 1);
        }
    }
    else
    {
        FV_ShowInfo("请输入完整路径！", 1);
    }

    TRYFREE(name_a);
}

// 新建文件回调-文件名
static void CreateFileCb2(const char *name_w)
{
    char *name_a;
    int32 fd;

    name_a = stru2c(name_w);
    fd = OpenInPath(FVData.Path, name_a, MR_FILE_RDWR | MR_FILE_CREATE);
    TRYFREE(name_a);

    if (0 != fd)
    {
        app_seek(fd, 0, MR_SEEK_END);
        WriteZeroToFile(fd, NewFileSize);
        app_close(fd);

        FileView_Refresh();
        FV_ShowInfo("新建文件完成。", 1);
    }
    else
    {
        FV_ShowInfo("新建文件失败！", 1);
    }
}

// 新建文件回调-输入大小回调
static void CreateFileCb(const char *num_w)
{
    int64 size_left;

    NewFileSize = watoi(num_w);
    size_left = GetDiskSize(FVData.Path, 1);
    if (size_left > 0 && NewFileSize > size_left)
    {
        FV_ShowInfo("磁盘空间不足！", 1);
    }
    else if (NewFileSize > 0)
    {
        // "新建文件"
        ShowInput("新建文件名", "\x65\xb0\x5e\xfa\x65\x87\x4e\xf6\x0\x0",
            MR_EDIT_ANY, MAX_PATH_LEN_A, CreateFileCb2);
    }
}

// 新建文件夹回调
static void CreatePathCb(const char *name_w)
{
    char *name_a;
    int32 ret;

    name_a = stru2c(name_w);
    ret = MakeDirEx(name_a);
    TRYFREE(name_a);

    if (0 == ret)
        FV_ShowInfo("新建文件夹完成。", 1);
    else
        FV_ShowInfo("新建文件夹失败！", 1);
}

// 删除
static void FileDel(void)
{
    int32 ret = -1;

    Switch2Dir(FVData.Path);

    if (MR_IS_FILE == FVData.FocusItem->type)  //文件
    {
        ret = mrc_remove(FVData.FocusItem->name);
    }
    else if (MR_IS_DIR == FVData.FocusItem->type)  //文件夹
    {
        FV_ShowInfo("正在删除...", 1);
        ret = RemoveDir(FVData.FocusItem->name);
    }

    Switch2Dir(NULL);

    FileView_Refresh();

    if (0 == ret)
        FV_ShowInfo("删除完成。", 1);
    else
        FV_ShowInfo("删除失败！", 1);
}

/*---------------------------------------------------------------------------*/
// 文件信息查看相关
#include "FDT.h"
#include "InfoPage.h"

static char *SearchFileNameW;
static int32 SearchState;

// 文件搜索回调
static int32 search_cb(FileInfoStruct *FileInfo)
{
    // 找到文件
    if (0 == wstrcmp((char*)FileInfo->F_Name, SearchFileNameW))
    {
        char str_attr[32];
        int32 offset = 0;
        char *info;

        info = (char *)malloc(256);
        memset(info, 0, 256);

        if (FileInfo->F_Attr & ATTR_DIRECTORY)
            offset += sprintf(str_attr + offset, " 文件夹");
        else if (FileInfo->F_Attr & ATTR_VOLUME)
            offset += sprintf(str_attr + offset, " 卷标");
        else
            offset += sprintf(str_attr + offset, " 文件");

        if (FileInfo->F_Attr & ATTR_READONLY)
            offset += sprintf(str_attr + offset, " 只读");

        if (FileInfo->F_Attr & ATTR_HIDDEN)
            offset += sprintf(str_attr + offset, " 隐藏");

        if (FileInfo->F_Attr & ATTR_SYSTEM)
            offset += sprintf(str_attr + offset, " 系统");

        if (FileInfo->F_Attr & ATTR_ARCHIVE)
            offset += sprintf(str_attr + offset, " 存档");

        sprintf(info, 
            "%s\n短名称: %s\n大小: %d Byte\n属性:%s\n创建时间: %d-%d-%d %d:%d:%d\n修改时间: %d-%d-%d %d:%d:%d\n访问日期: %d-%d-%d",
            FVData.FocusItem->name, FileInfo->F_ShortName, FileInfo->F_Size, str_attr,
            FileInfo->F_TCreate.year, FileInfo->F_TCreate.month, FileInfo->F_TCreate.day, 
            FileInfo->F_TCreate.hour, FileInfo->F_TCreate.minute, FileInfo->F_TCreate.second,
            FileInfo->F_TModify.year, FileInfo->F_TModify.month, FileInfo->F_TModify.day, 
            FileInfo->F_TModify.hour, FileInfo->F_TModify.minute, FileInfo->F_TModify.second,
            FileInfo->F_TAccess.year, FileInfo->F_TAccess.month, FileInfo->F_TAccess.day);

        InfoPage_Show("文件信息", info, INFOPAGE_FLAG_CONTENT_GB | INFOPAGE_FLAG_FREE_CONTENT, NULL);
        SearchState = 1;

        return 1;  // 退出搜索
    }

    return 0;
}

// 磁盘卷标搜索回调
static int32 search_disk_cb(FileInfoStruct *FileInfo)
{
    // 找到磁盘卷标
    if (FileInfo->F_Attr & ATTR_VOLUME)
    {
        SearchFileNameW = wstrdup((char*)FileInfo->F_Name);
        SwapBytes((uint8*)SearchFileNameW, wstrlen(SearchFileNameW));
        SearchState = 1;

        return 1;  // 退出搜索
    }

    return 0;
}

// 搜索文件并获取信息
static void ShowFileInfo(void)
{
    int32 ret = 0;

    SearchState = -1;

    switch (FVData.FocusItem->type)
    {
    case MR_IS_DISK:
        {
            int64 size;
            int32 slen = 0;
            char disk[4] = "";
            char *info;

            info = (char *)malloc(256);
            memset(info, 0, 256);

            memcpy(disk, FVData.FocusItem->name, 3);

            InfoPage_Show("磁盘信息", "查询中...", INFOPAGE_FLAG_CONTENT_GB, NULL);

            // 获取磁盘名称
            Switch2Dir(disk);
#ifdef SDK_MOD
            ret = FDT_Search("test.dat", search_disk_cb);  // 测试用
#else
            ret = FDT_Search("", search_disk_cb);
#endif
            Switch2Dir(NULL);

            slen += sprintf(info + slen, "%c盘名称:", disk[0]);
            if (1 == SearchState)
            {
                char *gbName;

                gbName = stru2c(SearchFileNameW);
                slen += sprintf(info + slen, "%s\n", gbName);
                TRYFREE(gbName);
            }
            else
            {
                if (ret < 0)
                    slen += sprintf(info + slen, "未知\n");
                else
                    slen += sprintf(info + slen, "不存在\n");
            }

            // 获取磁盘大小
            size = GetDiskSize(disk, 0);
            slen += sprintf(info + slen, "%c盘总计:%ld字节\n", disk[0], size);
            size = GetDiskSize(disk, 1);
            slen += sprintf(info + slen, "%c盘剩余:%ld字节\n", disk[0], size);

            InfoPage_Show("磁盘信息", info, INFOPAGE_FLAG_CONTENT_GB | INFOPAGE_FLAG_FREE_CONTENT, NULL);
        }
        break;
    default:
        {
            // 取得文件名
            SearchFileNameW = strc2u(FVData.FocusItem->name);
            SwapBytes((uint8*)SearchFileNameW, wstrlen(SearchFileNameW));

            Switch2Dir(FVData.Path);
            InfoPage_Show("文件信息", "查询中...", INFOPAGE_FLAG_CONTENT_GB, NULL);

#ifdef SDK_MOD
            ret = FDT_Search("test.dat", search_cb);  // 测试用
#else
            ret = FDT_Search("", search_cb);
#endif

            Switch2Dir(NULL);

            // 未找到文件
            if (-1 == SearchState)
            {
                InfoPage_Show("文件信息", "文件信息获取失败！\n可能手机不支持此功能。\n", INFOPAGE_FLAG_CONTENT_GB, NULL);
            }
        }
    }

    TRYFREE(SearchFileNameW);
}

/*---------------------------------------------------------------------------*/
// 菜单

#include "Menu.h"

// 菜单项枚举
enum
{
    FVMENU_SELECT,
    FVMENU_CREAT_FILE,
    FVMENU_CREAT_PATH,
    FVMENU_RENAME,
    FVMENU_COPY,
    FVMENU_DEL,
    FVMENU_INFO,

    FVMENU_MAX
};

static PMENU_LINK FVMenu;  // 菜单数据

// 菜单功能回调
static void FVMenu_ItemCb(int32 data)
{
    char *name_w;

    switch (data)
    {
    case FVMENU_SELECT:  // 选择
        FV_DoListEvent(FV_ACTION_SELECT);
        break;
    case FVMENU_CREAT_FILE:  // 新建文件
        // 1
        ShowInput("文件大小", "\x0\x31\x0\x0", MR_EDIT_NUMERIC, 12, CreateFileCb);
        break;
    case FVMENU_CREAT_PATH:  // 新建文件夹
        // "新建文件夹"
        ShowInput("新建文件夹名", "\x65\xb0\x5e\xfa\x65\x87\x4e\xf6\x59\x39\x0\x0", 
            MR_EDIT_ANY, MAX_PATH_LEN_A, CreatePathCb);
        break;
    case FVMENU_COPY:  // 复制文件
        {
            char *path;

            path = (char *)malloc(MAX_PATH_LEN_A);
            sprintf(path, "%s%s", FVData.Path, FVData.FocusItem->name);
            name_w = strc2u(path);
            TRYFREE(path);
            ShowInput("复制到", name_w, MR_EDIT_ANY, MAX_FILENAME_LEN_A, FileCopyCb);
            TRYFREE(name_w);
        }
        break;
    case FVMENU_RENAME:  // 重命名
        name_w = strc2u(FVData.FocusItem->name);
        ShowInput("新文件名", name_w, MR_EDIT_ANY, MAX_FILENAME_LEN_A, FileRenameCb);
        TRYFREE(name_w);
        break;
    case FVMENU_DEL:  // 删除
        FileDel();
        break;
    case FVMENU_INFO:  // 信息
        ShowFileInfo();
        break;
    default:
        break;
    }
}

// 菜单背景绘制回调
static void FVMenu_CallBack(int32 type)
{
    if (MENU_CALLBACK_DRAWBACK == type)
    {
        FV_DrawTitleBar(FVData.Title, 0);
        //FV_DrawToolBar(0, 0);
        FV_DrawList(0);
    }
    else if (MENU_CALLBACK_REFRESH == type)
    {
        FV_DrawTitleBar(FVData.Title, 1);
        //FV_DrawToolBar(0, 1);
        FV_DrawList(1);
    }
}

// 设置菜单是否可用
static void FVMenu_SetEnable(uint8 index1, uint8 index2, uint8 isEnable)
{
    PMENU_LINK mp = NULL, mpl = NULL;

    mp = Menu_GetByIndex(FVMenu, index1);

    if (NULL == mp)
        return;

    mpl = mp;
    mp = Menu_GetByIndex(mp, index2);
    if (NULL == mp)
        mp = mpl;

    MENU_SET_FLAG_EX(mp, MENU_FLAG_ENABLE, isEnable);
}

// 菜单初始化
static int32 FVMenu_Init(void)
{
    PMENU_LINK tempMenu, tempMenu2, tempMenu3;

    FVMenu = tempMenu = Menu_Add(NULL, "文件浏览", NULL, 0, MENU_FLAG_NORMAL);
    {
        Menu_Add(tempMenu, "选择", FVMenu_ItemCb, FVMENU_SELECT, MENU_FLAG_NORMAL);
        tempMenu2 = Menu_Add(tempMenu, "新建", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "文件", FVMenu_ItemCb, FVMENU_CREAT_FILE, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "文件夹", FVMenu_ItemCb, FVMENU_CREAT_PATH, MENU_FLAG_NORMAL);

        }
        tempMenu2 = Menu_Add(tempMenu, "操作", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "更名", FVMenu_ItemCb, FVMENU_RENAME, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "复制", FVMenu_ItemCb, FVMENU_COPY, MENU_FLAG_NORMAL);
            tempMenu3 = Menu_Add(tempMenu2, "删除", NULL, 0, MENU_FLAG_NORMAL);
            {
                Menu_Add(tempMenu3, "确认删除", FVMenu_ItemCb, FVMENU_DEL, MENU_FLAG_NORMAL);
            }
        }
        Menu_Add(tempMenu, "信息", FVMenu_ItemCb, FVMENU_INFO, MENU_FLAG_NORMAL);
    }

    return 0;
}

// 菜单结束
static int32 FVMenu_End(void)
{
    Menu_Destroy(FVMenu);

    return 0;
}

// 菜单显示
static int32 FVMenu_Show(void)
{
    if (NULL != FVData.FocusItem)
    {
        FVMenu_SetEnable(1, 0, 1);
        FVMenu_SetEnable(4, 0, 1);

        switch (FVData.FocusItem->type)
        {
        case MR_IS_FILE:
            FVMenu_SetEnable(2, 0, 1);
            FVMenu_SetEnable(3, 0, 1);
            FVMenu_SetEnable(3, 2, 1);
            break;
        case  MR_IS_DIR:
            FVMenu_SetEnable(2, 0, 1);
            FVMenu_SetEnable(3, 0, 1);
            FVMenu_SetEnable(3, 2, 0);
            break;
        case MR_IS_DISK:
            FVMenu_SetEnable(2, 0, 0);
            FVMenu_SetEnable(3, 0, 0);
            FVMenu_SetEnable(3, 2, 1);
            break;
        default:
            return -1;
        }
    }
    else
    {
        FVMenu_SetEnable(1, 0, 0);
        FVMenu_SetEnable(3, 0, 0);
        FVMenu_SetEnable(4, 0, 0);
    }

    Menu_Show(FVMenu, FVMenu_CallBack, rectList.x, rectTool.y, MENU_SHOW_FLAG_INDEX);

    return 0;
}
