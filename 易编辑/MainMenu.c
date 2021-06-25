/*
 * 程序主菜单
 * 版权所有 (C) 2011-2012 eleqian
 * [7/21/2012]
 */

#include "mrc_base.h"

#include "MainMenu.h"
#include "Menu.h"
#include "AppMain.h"
#include "HexView.h"
#include "HexEdit.h"
#include "FileView.h"
#include "PluginMgr.h"
#include "InfoPage.h"
#include "LocalUI.h"
#include "Functions.h"
#include "DrawLib.h"
#include "src/android.h"
#include "src/exb.h"

static int32 CutFileSize;             // 剪切文件数据大小

/*
 * 回调函数
 */

// 转到回调
static void GotoOffsetCb(const char *NumStr)
{
	int32 outValue = 0;

	if(NULL != NumStr)
	{
        outValue = watoi(NumStr);
        HV_GotoFileOffset(outValue);
	}
}

// 添加字节回调
static void AddDataCb(const char *num_w)
{
    int32 addsize;

    addsize = watoi(num_w);

  //  HV_ShowMsgA("正在添加，请等待……", 1);
	    HV_ShowMsgA("\xd5\xfd\xd4\xda\xcc\xed\xbc\xd3\xa3\xac\xc7\xeb\xb5\xc8\xb4\xfd\xa1\xad\xa1\xad", 1);
    HE_InsertData(NULL, addsize);
    Main_Draw(1);
   // HV_ShowMsgA("添加数据完成。", 1);
       HV_ShowMsgA("\xcc\xed\xbc\xd3\xca\xfd\xbe\xdd\xcd\xea\xb3\xc9\xa1\xa3", 1);
}

// 删除字节回调
static void DelDataCb(const char *dNumStr)
{
    int32 delNum;
    int32 fOffset = HV_GetFileOffset();
    int32 fSize = HV_GetFileSize();
 
    delNum = watoi(dNumStr);

    if (fOffset + delNum > fSize)
    {
		        HV_ShowMsgA("\xca\xe4\xc8\xeb\xd7\xd6\xbd\xda\xca\xfd\xb9\xfd\xb4\xf3\xa3\xac\xb2\xd9\xd7\xf7\xd2\xd1\xc8\xa1\xcf\xfb\xa3\xa1", 1);
      //  HV_ShowMsgA("输入字节数过大，操作已取消！", 1);
        return;
    }
    HV_ShowMsgA("\xd5\xfd\xd4\xda\xd2\xc6\xb3\xfd\xa3\xac\xc7\xeb\xb5\xc8\xb4\xfd\xa1\xad\xa1\xad", 1);
//    HV_ShowMsgA("正在移除，请等待……", 1);
    HE_DeleteData(delNum);
    Main_Draw(1);
	    HV_ShowMsgA("\xd2\xc6\xb3\xfd\xca\xfd\xbe\xdd\xcd\xea\xb3\xc9\xa1\xa3", 1);
//    HV_ShowMsgA("移除数据完成。", 1);
}

// 保存片段-写入文件回调
static void Data2FileCb2(const char *name_w)
{
    int32 fOffset = HV_GetFileOffset();
    int32 copySize = CutFileSize;
    char *name_a = NULL;
    HV_ShowMsgA("\xd5\xfd\xd4\xda\xb1\xa3\xb4\xe6\xca\xfd\xbe\xdd\xc6\xac\xb6\xce\xa1\xad\xa1\xad", 1);
//    HV_ShowMsgA("正在保存数据片段……", 1);

    Switch2Dir(AppDatas.HDataCur->FilePath);
    name_a = stru2c(name_w);
    CutDataToFile(AppDatas.HDataCur->FileNameA, name_a, fOffset, copySize);
    TRYFREE(name_a);
    Switch2Dir(NULL);
    HV_ShowMsgA("\xb1\xa3\xb4\xe6\xca\xfd\xbe\xdd\xc6\xac\xb6\xce\xcd\xea\xb3\xc9\xa1\xa3", 1);
  //  HV_ShowMsgA("保存数据片段完成。", 1);
}

// 保存片段-输入大小回调
static void Data2FileCb(const char *dNumStr)
{
    CutFileSize = watoi(dNumStr);

    if (HV_GetFileOffset() + CutFileSize > HV_GetFileSize())
    {
		        HV_ShowMsgA("\xca\xe4\xc8\xeb\xd7\xd6\xbd\xda\xca\xfd\xb9\xfd\xb4\xf3\xa3\xac\xb2\xd9\xd7\xf7\xd2\xd1\xc8\xa1\xcf\xfb\xa3\xa1", 1);
     //   HV_ShowMsgA("输入字节数过大，操作已取消！", 1);
        return;
    }
    else if (CutFileSize > 0)
    {
		        ShowInput("\xca\xfd\xbe\xdd\xc1\xed\xb4\xe6\xce\xaa", "\\x0\\x0", MR_EDIT_ANY, MAX_FILENAME_LEN_A / 2, Data2FileCb2);
    //    ShowInput("数据另存为", "\x0\x0", MR_EDIT_ANY, MAX_FILENAME_LEN_A / 2, Data2FileCb2);
    }
}

/*---------------------------------------------------------------------------*/

// 设置常用目录回调
static void SetUserDirCb(const char *path)
{
    UniToGB(path, AppDatas.UserDir, sizeof(AppDatas.UserDir));

    if (AppDatas.UserDir[0] == '\0')
    {
        memcpy(AppDatas.UserDir, "C:\\", 4);
    }
    HV_ShowMsgA("\xb3\xa3\xd3\xc3\xc4\xbf\xc2\xbc\xc9\xe8\xd6\xc3\xb3\xc9\xb9\xa6\xa1\xa3", 1);
  //  HV_ShowMsgA("常用目录设置成功。", 1);
}

/*----------------------------------------------------------------------------------*/

// 查找数值
static void FindNum(const char *sNum)
{
    HE_FindInput(HE_INPUT_DATA_TYPE_NUM, sNum);
}

// 搜索十六进制
static void FindHex(const char *sHex)
{
    HE_FindInput(HE_INPUT_DATA_TYPE_HEX, sHex);
}

// 查找文本 Uincode-B
static void FindText_UB(const char *sText)
{
    HE_FindInput(HE_INPUT_DATA_TYPE_UCS2BE, sText);
}

// 查找文本 Uincode-L
static void FindText_UL(const char *sText)
{
    HE_FindInput(HE_INPUT_DATA_TYPE_UCS2LE, sText);
}

// 查找文本 GB2312
static void FindText_GB(const char *sText)
{
    HE_FindInput(HE_INPUT_DATA_TYPE_GB2312, sText);
}

// 查找文本 UTF8
static void FindText_UTF8(const char *sText)
{
    HE_FindInput(HE_INPUT_DATA_TYPE_UTF8, sText);
}

/*----------------------------------------------------------------------------------*/

// 替换数值
static void WriteNum(const char *sNum)
{
    HE_WriteInput(HE_INPUT_DATA_TYPE_NUM, sNum);
}

// 替换十六进制
static void WriteHex(const char *sHex)
{
    HE_WriteInput(HE_INPUT_DATA_TYPE_HEX, sHex);
}

// 替换文本 Uincode-B
static void WriteText_UB(const char *sText)
{
    HE_WriteInput(HE_INPUT_DATA_TYPE_UCS2BE, sText);
}

// 替换文本 Uincode-L
static void WriteText_UL(const char *sText)
{
    HE_WriteInput(HE_INPUT_DATA_TYPE_UCS2LE, sText);
}

// 替换文本 GB2312
static void WriteText_GB(const char *sText)
{
    HE_WriteInput(HE_INPUT_DATA_TYPE_GB2312, sText);
}

// 替换文本 UTF8
static void WriteText_UTF8(const char *sText)
{
    HE_WriteInput(HE_INPUT_DATA_TYPE_UTF8, sText);
}

/*---------------------------------------------------------------------------*/
// 设置字体
void M_SetFont(int32 data)
{
    SetAppFont((uint16)data);
}

// 设置显示信息
void M_SetInfo(int32 data)
{
    SetInfoType((uint32)data);
}

// 设置颜色
void M_SetColor(int32 data)
{
    MainMenu_SetChecked(4, 4, AppColor.type + 1, 0);
    DrawLib_SetColor((uint8)data);
    MainMenu_SetChecked(4, 4, (uint8)data + 1, 1);
    Main_Draw(1);
}

// 设置字节序
void M_SetEndian(int32 data)
{
    AppDatas.BigEndian = AppDatas.BigEndian ? 0 : 1;
    MainMenu_SetChecked(4, 5, 1, AppDatas.BigEndian);
    Main_Draw(1);
}

// 设置快捷键是否弹出菜单
void M_SetPopMenu(int32 data)
{
    AppDatas.PopMenu = AppDatas.PopMenu ? 0 : 1;
    MainMenu_SetChecked(4, 5, 2, AppDatas.PopMenu);
    Main_Draw(1);
}

// 设置是否自动打开上次文件
void M_SetAutoOpen(int32 data)
{
    AppDatas.AutoOpen = AppDatas.AutoOpen ? 0 : 1;
    MainMenu_SetChecked(4, 5, 3, AppDatas.AutoOpen);
    Main_Draw(1);
}

// 设置是否显示菜单序号
void M_SetShowMenuIndex(int32 data)
{
    AppDatas.MenuIndex = AppDatas.MenuIndex ? 0 : 1;
    MainMenu_SetChecked(4, 5, 4, AppDatas.MenuIndex);
    Menu_SetShowFlag((AppDatas.MenuIndex ? MENU_SHOW_FLAG_INDEX : 0));
    Menu_Refresh(1);
}

// 设置是否显示翻页按钮
void M_SetShowPageButton(int32 data)
{
    AppDatas.PageButton = AppDatas.PageButton ? 0 : 1;
    MainMenu_SetChecked(4, 5, 5, AppDatas.PageButton);

    // 有待改进
    Menu_Hide();
    SetAppState(APPSTATE_NORMAL, 1);
	    HV_ShowMsgA("\xd0\xe8\xd2\xaa\xd6\xd8\xc6\xf4\xb3\xcc\xd0\xf2\xb2\xc5\xc4\xdc\xc9\xfa\xd0\xa7\xa3\xa1", 1);
  //  HV_ShowMsgA("需要重启程序才能生效！", 1);
}

// 设置常用目录
void M_SetUserDir(int32 data)
{
    char *uniStr = strc2u(AppDatas.UserDir);
    ShowInput("\xca\xe4\xc8\xeb\xc2\xb7\xbe\xb6", uniStr, MR_EDIT_ANY, 127, SetUserDirCb); 
   // ShowInput("输入路径", uniStr, MR_EDIT_ANY, 127, SetUserDirCb); 
    free(uniStr);
}

/*---------------------------------------------------------------------------*/

// 文件浏览
void M_FileView(int32 data)
{
    FileView_Show("\x65\x87\x4e\xf6\x6d\x4f\x89\xc8\x0\x0", NULL, FILEVIEW_FLAG_FILE, HV_OpenFile);
}

// 常用目录浏览
void M_FVUserDir(int32 data)
{
    if (AppDatas.UserDir[0] == '\0')
        memcpy(AppDatas.UserDir, "Mythroad", 4);
    FileView_Show("\x65\x87\x4e\xf6\x6d\x4f\x89\xc8\x0\x0", AppDatas.UserDir, FILEVIEW_FLAG_FILE, HV_OpenFile);
}

// 重新定位到上次文件
void M_FVRecent(int32 data)
{
	char *temp=strrchr(AppDatas.Recent,'/');
    if(temp!=NULL)*temp=0;
    FileView_Show("\x65\x87\x4e\xf6\x6d\x4f\x89\xc8\x0\x0", AppDatas.Recent, 
        FILEVIEW_FLAG_FILE | FILEVIEW_FLAG_RECENT, HV_OpenFile);
}

// 浏览文件夹
/*void M_DirView(int32 data)
{
    FV_Show("\x6d\x4f\x89\xc8\x65\x87\x4e\xf6\x59\x39\x0\x0", NULL, 0x2, OpenFile);
}*/

// 关闭文件
void M_FileClose(int32 data)
{
    HV_CloseFile();
}

// 备份文件
void M_FileBackup(int32 data)
{
    char bakfile[MAX_FILENAME_LEN_A];
    int32 ret = -1;

    sprintf(bakfile, "%s%s", AppDatas.HDataCur->FileNameA, ".bak");

    Switch2Dir(AppDatas.HDataCur->FilePath);

    // 删除已经存在的备份文件
    if (MR_IS_FILE == mrc_fileState(bakfile))
        mrc_remove(bakfile);

    ret = CopyFile(AppDatas.HDataCur->FileNameA, bakfile);

    Switch2Dir(NULL);

    if (0 == ret)
		        HV_ShowMsgA("\xce\xc4\xbc\xfe\xb1\xb8\xb7\xdd\xcd\xea\xb3\xc9\xa1\xa3", 1);
    //    HV_ShowMsgA("文件备份完成。", 1);
    else
		        HV_ShowMsgA("\xce\xc4\xbc\xfe\xb1\xb8\xb7\xdd\xca\xa7\xb0\xdc\xa3\xa1", 1);
     //   HV_ShowMsgA("文件备份失败！", 1);
}

// 删除
void M_FileDel(int32 data)
{
    int32 ret = -1;

    Switch2Dir(AppDatas.HDataCur->FilePath);
    ret = mrc_remove(AppDatas.HDataCur->FileNameA);
    Switch2Dir(NULL);

    HV_CloseFile();

    if (0 == ret)
		        HV_ShowMsgA("\xce\xc4\xbc\xfe\xc9\xbe\xb3\xfd\xcd\xea\xb3\xc9\xa1\xa3", 1);
    //    HV_ShowMsgA("文件删除完成。", 1);
    else
		        HV_ShowMsgA("\xce\xc4\xbc\xfe\xc9\xbe\xb3\xfd\xca\xa7\xb0\xdc\xa3\xa1", 1);
   //     HV_ShowMsgA("文件删除失败！", 1);
}

// 转到
void M_GotoOffset(int32 data)
{
    char *pMax = witoa(HV_GetFileSize());
    ShowInput("\xd7\xaa\xb5\xbd\xc6\xab\xd2\xc6", "\\x0\\x30", MR_EDIT_NUMERIC, wstrlen(pMax) / 2 + 1, GotoOffsetCb);
  //  ShowInput("转到偏移", "\x0\x30", MR_EDIT_NUMERIC, wstrlen(pMax) / 2 + 1, GotoOffsetCb);
    TRYFREE(pMax);
}

/*---------------------------------------------------------------------------*/
// 查找
void M_FindData(int32 type)
{
    switch (type)
    {
    case HE_INPUT_DATA_TYPE_HEX:
		        ShowInput("\xb2\xe9\xd5\xd2\x16\xbd\xf8\xd6\xc6", HE_GetLastInput(), MR_EDIT_ANY, 128, FindHex);
    //    ShowInput("查找16进制", HE_GetLastInput(), MR_EDIT_ANY, 128, FindHex);
        break;
    case HE_INPUT_DATA_TYPE_NUM:
		        ShowInput("\xb2\xe9\xd5\xd2\xca\xfd\xd6\xb5", HE_GetLastInput(), MR_EDIT_NUMERIC, 12, FindNum);
       // ShowInput("查找数值", HE_GetLastInput(), MR_EDIT_NUMERIC, 12, FindNum);
        break;
    case HE_INPUT_DATA_TYPE_UCS2BE:
		        ShowInput("\xb2\xe9\xd5\xd2\xce\xc4\xb1\xbe", HE_GetLastInput(), MR_EDIT_ANY, 128, FindText_UB);
     //   ShowInput("查找文本", HE_GetLastInput(), MR_EDIT_ANY, 128, FindText_UB);
        break;
    case HE_INPUT_DATA_TYPE_UCS2LE:
		        ShowInput("\xb2\xe9\xd5\xd2\xce\xc4\xb1\xbe", HE_GetLastInput(), MR_EDIT_ANY, 128, FindText_UL);
    //    ShowInput("查找文本", HE_GetLastInput(), MR_EDIT_ANY, 128, FindText_UL);
        break;
    case HE_INPUT_DATA_TYPE_GB2312:
		        ShowInput("\xb2\xe9\xd5\xd2\xce\xc4\xb1\xbe", HE_GetLastInput(), MR_EDIT_ANY, 128, FindText_GB);
		        LOGI("查找gb编码");
    //    ShowInput("查找文本", HE_GetLastInput(), MR_EDIT_ANY, 128, FindText_GB);
        break;
    case HE_INPUT_DATA_TYPE_UTF8:
		        ShowInput("\xb2\xe9\xd5\xd2\xce\xc4\xb1\xbe", HE_GetLastInput(), MR_EDIT_ANY, 128, FindText_UTF8);
  //      ShowInput("查找文本", HE_GetLastInput(), MR_EDIT_ANY, 128, FindText_UTF8);
        break;
    default:
        break;
    }
}

void M_FindNext(int32 data)
{
    HE_FindInput(HE_INPUT_DATA_TYPE_LAST, NULL);
}

/*---------------------------------------------------------------------------*/
// 写入
void M_WriteData(int32 type)
{
    switch (type)
    {
    case HE_INPUT_DATA_TYPE_HEX:
		        ShowInput("\xd0\xb4\xc8\xeb\x16\xbd\xf8\xd6\xc6", HE_GetLastInput(), MR_EDIT_ANY, 128, WriteHex);
   //     ShowInput("写入16进制", HE_GetLastInput(), MR_EDIT_ANY, 128, WriteHex);
        break;
    case HE_INPUT_DATA_TYPE_NUM:
		        ShowInput("\xd0\xb4\xc8\xeb\xca\xfd\xd6\xb5", HE_GetLastInput(), MR_EDIT_NUMERIC, 12, WriteNum);
    //    ShowInput("写入数值", HE_GetLastInput(), MR_EDIT_NUMERIC, 12, WriteNum);
        break;
    case HE_INPUT_DATA_TYPE_UCS2BE:
        ShowInput("\xd0\xb4\xc8\xeb\xce\xc4\xb1\xbe", HE_GetLastInput(), MR_EDIT_ANY, 128, WriteText_UB);
     //   ShowInput("写入文本", HE_GetLastInput(), MR_EDIT_ANY, 128, WriteText_UB);
        break;
    case HE_INPUT_DATA_TYPE_UCS2LE:
		        ShowInput("\xd0\xb4\xc8\xeb\xce\xc4\xb1\xbe", HE_GetLastInput(), MR_EDIT_ANY, 128, WriteText_UL);
 //       ShowInput("写入文本", HE_GetLastInput(), MR_EDIT_ANY, 128, WriteText_UL);
        break;
    case HE_INPUT_DATA_TYPE_GB2312:
		        ShowInput("\xd0\xb4\xc8\xeb\xce\xc4\xb1\xbe", HE_GetLastInput(), MR_EDIT_ANY, 128, WriteText_GB);
   //     ShowInput("写入文本", HE_GetLastInput(), MR_EDIT_ANY, 128, WriteText_GB);
        break;
    case HE_INPUT_DATA_TYPE_UTF8:
	        ShowInput("\xd0\xb4\xc8\xeb\xce\xc4\xb1\xbe", HE_GetLastInput(), MR_EDIT_ANY, 128, WriteText_UTF8);
    //    ShowInput("写入文本", HE_GetLastInput(), MR_EDIT_ANY, 128, WriteText_UTF8);
        break;
    default:
        break;
    }
}

void M_WriteNext(int32 data)
{
    HE_WriteInput(HE_INPUT_DATA_TYPE_LAST, NULL);
}

/*---------------------------------------------------------------------------*/

// 比较相同字节
void M_SetCompareMode(int32 data)
{
    HE_SetCompareMode(data);

    if (data == 1)
    {
        MainMenu_SetChecked(1, 4, 1, 0);
        MainMenu_SetChecked(1, 4, 2, 1);
    }
    else
    {
        MainMenu_SetChecked(1, 4, 1, 1);
        MainMenu_SetChecked(1, 4, 2, 0);
    }

    Menu_Draw(1);
}

// 比较下一个
void M_CompareNext(int32 data)
{
    HE_Compare();
}

/*---------------------------------------------------------------------------*/
// 改变偏移

void M_PageUp(int32 data) //上一页
{
    HV_ChangeDataOffset(OFFSET_SEEK_PAGE_UP);
}
void M_PageDown(int32 data) //下一页
{
    HV_ChangeDataOffset(OFFSET_SEEK_PAGE_DOWN);
}
void M_PageHome(int32 data) //开头
{
    HV_ChangeDataOffset(OFFSET_SEEK_BEGIN);
}
void M_PageEnd(int32 data) //末尾
{
    HV_ChangeDataOffset(OFFSET_SEEK_END);
}

/*---------------------------------------------------------------------------*/

// 插入字节
void M_AddData(int32 data)
{    ShowInput("\xb2\xe5\xc8\xeb\xd7\xd6\xbd\xda\xca\xfd", "\\x0\\x30\\x0\\x0", MR_EDIT_NUMERIC, 12, AddDataCb);
  //  ShowInput("插入字节数", "\x0\x30\x0\x0", MR_EDIT_NUMERIC, 12, AddDataCb);
}

// 删除字节
void M_DelData(int32 data)
{    ShowInput("\xc9\xbe\xb3\xfd\xd7\xd6\xbd\xda\xca\xfd", "\\x0\\x30\\x0\\x0", MR_EDIT_NUMERIC, 12, DelDataCb);
  //  ShowInput("删除字节数", "\x0\x30\x0\x0", MR_EDIT_NUMERIC, 12, DelDataCb);
}

// 保存片段
void M_Data2File(int32 data)
{    ShowInput("\xb1\xa3\xb4\xe6\xd7\xd6\xbd\xda\xca\xfd", "\\x0\\x30\\x0\\x0", MR_EDIT_NUMERIC, 12, Data2FileCb);
//    ShowInput("保存字节数", "\x0\x30\x0\x0", MR_EDIT_NUMERIC, 12, Data2FileCb);
}

/*---------------------------------------------------------------------------*/

// 插件调用
void M_PluginMgr(int32 data)
{
  //XL  PM_Show();
}

// 插件目录浏览
void M_PluginDir(int32 data)
{
    return;
    char *path;
    int32 len;
    char *p;

    path = (char*)malloc(MAX_PATH_LEN_A);

    len = GetCurDir(path);
    if (len <= 0)
    {
		        HV_ShowMsgA("\xca\xa7\xb0\xdc\xa3\xa1", 1);
    //    HV_ShowMsgA("失败！", 1);
        return;
    }
    sprintf(path + len, "%s\\", PLUGIN_FOLDER);

    for (p = path; '\0' != *p; p++)
    {
        if ('/' == *p)
            *p = '\\';
    }

    FileView_Show("\x63\xd2\x4e\xf6\x76\xee\x5f\x55\x0\x0", path, FILEVIEW_FLAG_FILE, HV_OpenFile);
    TRYFREE(path);
}

/*---------------------------------------------------------------------------*/

// 调用自带浏览器
/*void M_GotoEles(int32 data)
{
    extern void mrc_connectWAP(char* wap);
    uint8 EncodeUrl[] = "\x2d\x31\x31\x35\x7f\x6a\x6a\x20\x29\x20\x36\x6b\x32\x24\x35\x6b\x24\x2c";

    ChangeAppState(APPSTATE_NORMAL, 0);
    DecodeStr(EncodeUrl, 0x45);
    mrc_connectWAP((char*)EncodeUrl);
}*/

// 帮助
void M_ShowHelp(int32 data)
{
    char *gbstr;

    gbstr = ReadStringFromMrp("readme.txt");
    if (NULL != gbstr)
    {
		        InfoPage_Show("\xca\xb9\xd3\xc3\xb0\xef\xd6\xfa", gbstr, INFOPAGE_FLAG_CONTENT_GB, NULL);
   //     InfoPage_Show("使用帮助", gbstr, INFOPAGE_FLAG_CONTENT_GB, NULL);
        TRYFREE(gbstr);
    }
    else
    {
		        HV_ShowMsgA("\xb0\xef\xd6\xfa\xce\xc4\xbc\xfe\xb6\xaa\xca\xa7\xa3\xac\xc7\xeb\xd6\xd8\xd0\xc2\xcf\xc2\xd4\xd8\xb1\xbe\xc8\xed\xbc\xfe\xa3\xa1", 1);
      //  HV_ShowMsgA("帮助文件丢失，请重新下载本软件！", 1);
    }
}

// 更新记录
void M_ShowNew(int32 data)
{
    char *gbstr;

    gbstr = ReadStringFromMrp("new.txt");
    if (NULL != gbstr)
    {
		        InfoPage_Show("\xb8\xfc\xd0\xc2\xc0\xfa\xca\xb7", gbstr, INFOPAGE_FLAG_CONTENT_GB, NULL);
      //  InfoPage_Show("更新历史", gbstr, INFOPAGE_FLAG_CONTENT_GB, NULL);
        TRYFREE(gbstr);
    }
    else
    {        HV_ShowMsgA("\xb8\xfc\xd0\xc2\xbc\xc7\xc2\xbc\xce\xc4\xbc\xfe\xb6\xaa\xca\xa7\xa3\xac\xc7\xeb\xd6\xd8\xd0\xc2\xcf\xc2\xd4\xd8\xb1\xbe\xc8\xed\xbc\xfe\xa3\xa1", 1);
		
    //    HV_ShowMsgA("更新记录文件丢失，请重新下载本软件！", 1);
    }
}

// 关于
void M_ShowAbout(int32 data)
{
    //eleqian 设计制作
  //  uint8 EncodeChar[] = "\x22\x2b\x22\x36\x2e\x26\x29\x67\x8e\xaf\xfb\x81\x91\x81\x90\xb0";
	uint8 EncodeChar[]="\xd2\xc6\xd6\xb2\xa3\xba\xb7\xe7\xb5\xc4\xd3\xb0\xd7\xd3";
    char msgStrA[32];

  //  DecodeStr(EncodeChar, 0x47);
 //   sprintf(msgStrA, "%s\n程序版本: %d", EncodeChar, AppDatas.AppVer);
	    sprintf(msgStrA, "%s\n\xb3\xcc\xd0\xf2\xb0\xe6\xb1\xbe: %d", EncodeChar, AppDatas.AppVer);
    HV_ShowMsgA(msgStrA, 1);
    char *showtext = "风的影子 移植";
    char *totext = ex_coding(showtext,strlen(showtext),"UTF-8","GBK");
    toast( totext,0);
}

// 退出
void M_ExitApp(int32 data)
{
    SetAppState(APPSTATE_NORMAL, 1);
    app_exit();
}

/*---------------------------------------------------------------------------*/

// 初始化菜单项
/*
PMENU_LINK MainMenu_InitItems(void)
{
    PMENU_LINK rootMenu;
    PMENU_LINK tempMenu, tempMenu2;

#define JUDGE_MENU_FLAG_ENABLE(sec) \
    (MENU_FLAG_AUTOFOLD | ((sec) ? MENU_FLAG_ENABLE : 0))

#define JUDGE_MENU_FLAG_CHECK(sec) \
    (MENU_FLAG_ENABLE | ((sec) ? MENU_FLAG_CHECK : 0))

#define JUDGE_MENU_FALG_INFO(type) \
    (MENU_FLAG_ENABLE | ((AppDatas.InfoType & (type)) ? MENU_FLAG_CHECK : 0))
    rootMenu = Menu_Add(NULL, "\xb2\xcb\xb5\xa5", NULL, 0, MENU_FLAG_NORMAL);
 //   rootMenu = Menu_Add(NULL, "菜单", NULL, 0, MENU_FLAG_NORMAL);

    tempMenu = Menu_Add(rootMenu, "编辑", NULL, 0, MENU_FLAG_AUTOFOLD);
    {
        tempMenu2 = Menu_Add(tempMenu, "查找", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "GB2312", M_FindData, HE_INPUT_DATA_TYPE_GB2312, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "UCS2BE", M_FindData, HE_INPUT_DATA_TYPE_UCS2BE, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "UCS2LE", M_FindData, HE_INPUT_DATA_TYPE_UCS2LE, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "UTF-8",  M_FindData, HE_INPUT_DATA_TYPE_UTF8, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "16进制", M_FindData, HE_INPUT_DATA_TYPE_HEX, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "10进制", M_FindData, HE_INPUT_DATA_TYPE_NUM, MENU_FLAG_NORMAL);

            Menu_Add(tempMenu2, "继续查找", M_FindNext, 0, MENU_FLAG_NORMAL);
        }

        tempMenu2 = Menu_Add(tempMenu, "写入", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "GB2312", M_WriteData, HE_INPUT_DATA_TYPE_GB2312, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "UCS2BE", M_WriteData, HE_INPUT_DATA_TYPE_UCS2BE, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "UCS2LE", M_WriteData, HE_INPUT_DATA_TYPE_UCS2LE, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "UTF-8",  M_WriteData, HE_INPUT_DATA_TYPE_UTF8, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "16进制", M_WriteData, HE_INPUT_DATA_TYPE_HEX, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "10进制", M_WriteData, HE_INPUT_DATA_TYPE_NUM, MENU_FLAG_NORMAL);

            Menu_Add(tempMenu2, "继续写入", M_WriteNext, 0, MENU_FLAG_NORMAL);
        }

        tempMenu2 = Menu_Add(tempMenu, "位置", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "上页|1", M_PageUp, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "下页|4", M_PageDown, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "开头|3", M_PageHome, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "末尾|6", M_PageEnd, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "转到|2", M_GotoOffset, 0, MENU_FLAG_NORMAL);
        }

        tempMenu2 = Menu_Add(tempMenu, "比较", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "相同", M_SetCompareMode, HE_COMPARE_SAME, JUDGE_MENU_FLAG_CHECK(1));
            Menu_Add(tempMenu2, "不同", M_SetCompareMode, HE_COMPARE_DIFFERENT, JUDGE_MENU_FLAG_CHECK(0));
            Menu_Add(tempMenu2, "继续比较", M_CompareNext, 0, MENU_FLAG_NORMAL);
        }

        tempMenu2 = Menu_Add(tempMenu, "数据", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "插入", M_AddData, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "移除", M_DelData, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "截取", M_Data2File, 0, MENU_FLAG_NORMAL);
        }
    }

    tempMenu = Menu_Add(rootMenu, "文件", NULL, 0, MENU_FLAG_NORMAL);
    {
        Menu_Add(tempMenu, "历史", M_FVRecent, 0, MENU_FLAG_NORMAL);
        Menu_Add(tempMenu, "常用", M_FVUserDir, 0, MENU_FLAG_NORMAL);
        Menu_Add(tempMenu, "浏览", M_FileView, 0, MENU_FLAG_NORMAL);
        Menu_Add(tempMenu, "关闭", M_FileClose, 0, MENU_FLAG_AUTOFOLD);

        tempMenu2 = Menu_Add(tempMenu, "操作", NULL, 0, MENU_FLAG_AUTOFOLD);
        {
            //Menu_Add(tempMenu2, "改名", M_FileRename, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "备份", M_FileBackup, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "删除", M_FileDel, 0, MENU_FLAG_NORMAL);
        }
    }

    tempMenu = Menu_Add(rootMenu, "工具", NULL, 0, MENU_FLAG_NORMAL);
    {
        Menu_Add(tempMenu, "扩展插件|#", M_PluginMgr, 0, MENU_FLAG_NORMAL);
        Menu_Add(tempMenu, "插件目录", M_PluginDir, 0, MENU_FLAG_NORMAL);
    }

    tempMenu = Menu_Add(rootMenu, "设置", NULL, 0, MENU_FLAG_NORMAL);
    {
        tempMenu2 = Menu_Add(tempMenu, "数值", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "+8位", M_SetInfo, VIEWTYPE_MASK_UINT8, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_UINT8));
            Menu_Add(tempMenu2, "±8位", M_SetInfo, VIEWTYPE_MASK_INT8, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_INT8));
            Menu_Add(tempMenu2, "+16位", M_SetInfo, VIEWTYPE_MASK_UINT16, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_UINT16));
            Menu_Add(tempMenu2, "±16位", M_SetInfo, VIEWTYPE_MASK_INT16, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_INT16));
            Menu_Add(tempMenu2, "+32位", M_SetInfo, VIEWTYPE_MASK_UINT32, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_UINT32));
            Menu_Add(tempMenu2, "±32位", M_SetInfo, VIEWTYPE_MASK_INT32, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_INT32));
        }

        tempMenu2 = Menu_Add(tempMenu, "文本", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "UCS2BE", M_SetInfo, VIEWTYPE_MASK_UCS2BE, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_UCS2BE));
            Menu_Add(tempMenu2, "UCS2LE", M_SetInfo, VIEWTYPE_MASK_UCS2LE, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_UCS2LE));
            Menu_Add(tempMenu2, "GB2312", M_SetInfo, VIEWTYPE_MASK_GB2312, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_GB2312));
            Menu_Add(tempMenu2, "UTF-8", M_SetInfo, VIEWTYPE_MASK_UTF8, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_UTF8));
        }

        tempMenu2 = Menu_Add(tempMenu, "字体", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "小", M_SetFont, MR_FONT_SMALL, JUDGE_MENU_FLAG_CHECK(0 == AppDatas.AppFont));
            Menu_Add(tempMenu2, "中", M_SetFont, MR_FONT_MEDIUM, JUDGE_MENU_FLAG_CHECK(1 == AppDatas.AppFont));
            Menu_Add(tempMenu2, "大", M_SetFont, MR_FONT_BIG, JUDGE_MENU_FLAG_CHECK(2 == AppDatas.AppFont));
        }

        tempMenu2 = Menu_Add(tempMenu, "皮肤", NULL, 0, MENU_FLAG_NORMAL);
        {
            char name[16];
            int32 i;

            for (i = 0; i < 8; i++)
            {
                name[0] = '\0';

                if (DrawLib_SkinName((uint8)i, name) == MR_SUCCESS && name[0] != '\0')
                {
                    Menu_Add(tempMenu2, name, M_SetColor, i, JUDGE_MENU_FLAG_CHECK(i == AppColor.type));
                }
                else if (0 == i)
                {
                    Menu_Add(tempMenu2, "清蓝", M_SetColor, i, JUDGE_MENU_FLAG_CHECK(i == AppColor.type));
                }
                else if (1 == i)
                {
                    Menu_Add(tempMenu2, "酷黑", M_SetColor, i, JUDGE_MENU_FLAG_CHECK(i == AppColor.type));
                }
            }
        }

        tempMenu2 = Menu_Add(tempMenu, "更多", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "大端字序", M_SetEndian, 0, JUDGE_MENU_FLAG_CHECK(AppDatas.BigEndian));
            Menu_Add(tempMenu2, "快捷菜单", M_SetPopMenu, 0, JUDGE_MENU_FLAG_CHECK(AppDatas.PopMenu));
            Menu_Add(tempMenu2, "自动打开", M_SetAutoOpen, 0, JUDGE_MENU_FLAG_CHECK(AppDatas.AutoOpen));
            Menu_Add(tempMenu2, "菜单序号", M_SetShowMenuIndex, 0, JUDGE_MENU_FLAG_CHECK(AppDatas.MenuIndex));
            Menu_Add(tempMenu2, "翻页按钮", M_SetShowPageButton, 0, JUDGE_MENU_FLAG_CHECK(AppDatas.PageButton));
            Menu_Add(tempMenu2, "常用目录", M_SetUserDir, 0, MENU_FLAG_NORMAL);
        }
    }

    tempMenu = Menu_Add(rootMenu, "帮助", NULL, 0, MENU_FLAG_NORMAL);
    {
        //Menu_Add(tempMenu, "个人网站", M_GotoEles, 0, MENU_FLAG_NORMAL);
        Menu_Add(tempMenu, "使用帮助", M_ShowHelp, 0, MENU_FLAG_NORMAL);
        Menu_Add(tempMenu, "更新历史", M_ShowNew, 0, MENU_FLAG_NORMAL);
        Menu_Add(tempMenu, "关于软件", M_ShowAbout, 0, MENU_FLAG_NORMAL);
    }

    tempMenu = Menu_Add(rootMenu, "退出", M_ExitApp, 0, MENU_FLAG_NORMAL);

    return rootMenu;
}
*/
PMENU_LINK MainMenu_InitItems(void)
{
    PMENU_LINK rootMenu;
    PMENU_LINK tempMenu, tempMenu2;

#define JUDGE_MENU_FLAG_ENABLE(sec) \
    (MENU_FLAG_AUTOFOLD | ((sec) ? MENU_FLAG_ENABLE : 0))

#define JUDGE_MENU_FLAG_CHECK(sec) \
    (MENU_FLAG_ENABLE | ((sec) ? MENU_FLAG_CHECK : 0))

#define JUDGE_MENU_FALG_INFO(type) \
    (MENU_FLAG_ENABLE | ((AppDatas.InfoType & (type)) ? MENU_FLAG_CHECK : 0))
    rootMenu = Menu_Add(NULL, "\xb2\xcb\xb5\xa5", NULL, 0, MENU_FLAG_NORMAL);
 
    tempMenu = Menu_Add(rootMenu, "\xb1\xe0\xbc\xad", NULL, 0, MENU_FLAG_AUTOFOLD);
    {
        tempMenu2 = Menu_Add(tempMenu, "\xb2\xe9\xd5\xd2", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "GB2312", M_FindData, HE_INPUT_DATA_TYPE_GB2312, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "UCS2BE", M_FindData, HE_INPUT_DATA_TYPE_UCS2BE, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "UCS2LE", M_FindData, HE_INPUT_DATA_TYPE_UCS2LE, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "UTF-8",  M_FindData, HE_INPUT_DATA_TYPE_UTF8, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "16\xbd\xf8\xd6\xc6", M_FindData, HE_INPUT_DATA_TYPE_HEX, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "10\xbd\xf8\xd6\xc6", M_FindData, HE_INPUT_DATA_TYPE_NUM, MENU_FLAG_NORMAL);

            Menu_Add(tempMenu2, "\xbc\xcc\xd0\xf8\xb2\xe9\xd5\xd2", M_FindNext, 0, MENU_FLAG_NORMAL);
        }

        tempMenu2 = Menu_Add(tempMenu, "\xd0\xb4\xc8\xeb", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "GB2312", M_WriteData, HE_INPUT_DATA_TYPE_GB2312, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "UCS2BE", M_WriteData, HE_INPUT_DATA_TYPE_UCS2BE, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "UCS2LE", M_WriteData, HE_INPUT_DATA_TYPE_UCS2LE, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "UTF-8",  M_WriteData, HE_INPUT_DATA_TYPE_UTF8, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "16\xbd\xf8\xd6\xc6", M_WriteData, HE_INPUT_DATA_TYPE_HEX, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "10\xbd\xf8\xd6\xc6", M_WriteData, HE_INPUT_DATA_TYPE_NUM, MENU_FLAG_NORMAL);

            Menu_Add(tempMenu2, "\xbc\xcc\xd0\xf8\xd0\xb4\xc8\xeb", M_WriteNext, 0, MENU_FLAG_NORMAL);
        }

        tempMenu2 = Menu_Add(tempMenu, "\xce\xbb\xd6\xc3", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "\xc9\xcf\xd2\xb3|1", M_PageUp, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "\xcf\xc2\xd2\xb3|4", M_PageDown, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "\xbf\xaa\xcd\xb7|3", M_PageHome, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "\xc4\xa9\xce\xb2|6", M_PageEnd, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "\xd7\xaa\xb5\xbd|2", M_GotoOffset, 0, MENU_FLAG_NORMAL);
        }
//比较
        tempMenu2 = Menu_Add(tempMenu, "\xb1\xc8\xbd\xcf", NULL, 0, MENU_FLAG_NORMAL);
        {
Menu_Add(tempMenu2,"\xcf\xe0\xcd\xac",            M_SetCompareMode,HE_COMPARE_SAME, JUDGE_MENU_FLAG_CHECK(1));
Menu_Add(tempMenu2,"\xb2\xbb\xcd\xac",            M_SetCompareMode,HE_COMPARE_DIFFERENT, JUDGE_MENU_FLAG_CHECK(0));
            Menu_Add(tempMenu2, "\xbc\xcc\xd0\xf8\xb1\xc8\xbd\xcf", M_CompareNext, 0, MENU_FLAG_NORMAL);
        }
//数据
        tempMenu2 = Menu_Add(tempMenu, "\xca\xfd\xbe\xdd", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "\xb2\xe5\xc8\xeb", M_AddData, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "\xd2\xc6\xb3\xfd", M_DelData, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "\xbd\xd8\xc8\xa1", M_Data2File, 0, MENU_FLAG_NORMAL);
        }
    }
//文件
    tempMenu = Menu_Add(rootMenu, "\xce\xc4\xbc\xfe", NULL, 0, MENU_FLAG_NORMAL);
    {
        Menu_Add(tempMenu, "\xc0\xfa\xca\xb7", M_FVRecent, 0, MENU_FLAG_NORMAL);
        Menu_Add(tempMenu, "\xb3\xa3\xd3\xc3", M_FVUserDir, 0, MENU_FLAG_NORMAL);
        Menu_Add(tempMenu, "\xe4\xaf\xc0\xc0", M_FileView, 0, MENU_FLAG_NORMAL);
        Menu_Add(tempMenu, "\xb9\xd8\xb1\xd5", M_FileClose, 0, MENU_FLAG_AUTOFOLD);

        tempMenu2 = Menu_Add(tempMenu, "\xb2\xd9\xd7\xf7", NULL, 0, MENU_FLAG_AUTOFOLD);
        {
   //         Menu_Add(tempMenu2, "\xb8\xc4\xc3\xfb", M_FileRename, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "\xb1\xb8\xb7\xdd", M_FileBackup, 0, MENU_FLAG_NORMAL);
            Menu_Add(tempMenu2, "\xc9\xbe\xb3\xfd", M_FileDel, 0, MENU_FLAG_NORMAL);
        }
    }
//工具
    tempMenu = Menu_Add(rootMenu, "\xb9\xa4\xbe\xdf", NULL, 0, MENU_FLAG_NORMAL);
    {
        Menu_Add(tempMenu, "\xc0\xa9\xd5\xb9\xb2\xe5\xbc\xfe|#", M_PluginMgr, 0, MENU_FLAG_NORMAL);
        Menu_Add(tempMenu, "\xb2\xe5\xbc\xfe\xc4\xbf\xc2\xbc", M_PluginDir, 0, MENU_FLAG_NORMAL);
    }
//设置
    tempMenu = Menu_Add(rootMenu, "\xc9\xe8\xd6\xc3", NULL, 0, MENU_FLAG_NORMAL);
    {
        tempMenu2 = Menu_Add(tempMenu, "\xca\xfd\xd6\xb5", NULL, 0, MENU_FLAG_NORMAL);
        {
			
            Menu_Add(tempMenu2, "+8\xce\xbb", M_SetInfo, VIEWTYPE_MASK_UINT8, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_UINT8));
            Menu_Add(tempMenu2, "\xa1\xc0\x38\xce\xbb", M_SetInfo, VIEWTYPE_MASK_INT8, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_INT8));
            Menu_Add(tempMenu2, "+16\xce\xbb", M_SetInfo, VIEWTYPE_MASK_UINT16, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_UINT16));
            Menu_Add(tempMenu2, "\xa1\xc0\x31\x36\xce\xbb", M_SetInfo, VIEWTYPE_MASK_INT16, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_INT16));
            Menu_Add(tempMenu2, "+32\xce\xbb", M_SetInfo, VIEWTYPE_MASK_UINT32, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_UINT32));
			
          //  Menu_Add(tempMenu2, "\xa1\xc032\xce\xbb", M_SetInfo, VIEWTYPE_MASK_INT32, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_INT32));
        }

        tempMenu2 = Menu_Add(tempMenu, "\xce\xc4\xb1\xbe", NULL, 0, MENU_FLAG_NORMAL);
        {
           Menu_Add(tempMenu2, "UCS2BE", M_SetInfo, VIEWTYPE_MASK_UCS2BE, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_UCS2BE));
           Menu_Add(tempMenu2, "UCS2LE", M_SetInfo, VIEWTYPE_MASK_UCS2LE, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_UCS2LE));
           Menu_Add(tempMenu2, "GB2312", M_SetInfo, VIEWTYPE_MASK_GB2312, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_GB2312));
           Menu_Add(tempMenu2, "UTF-8", M_SetInfo, VIEWTYPE_MASK_UTF8, JUDGE_MENU_FALG_INFO(VIEWTYPE_MASK_UTF8));
        }

        tempMenu2 = Menu_Add(tempMenu, "\xd7\xd6\xcc\xe5", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "\xd0\xa1", M_SetFont, MR_FONT_SMALL, JUDGE_MENU_FLAG_CHECK(0 == AppDatas.AppFont));
            Menu_Add(tempMenu2, "\xd6\xd0", M_SetFont, MR_FONT_MEDIUM, JUDGE_MENU_FLAG_CHECK(1 == AppDatas.AppFont));
           Menu_Add(tempMenu2, "\xb4\xf3", M_SetFont, MR_FONT_BIG, JUDGE_MENU_FLAG_CHECK(2 == AppDatas.AppFont));
        }

        tempMenu2 = Menu_Add(tempMenu, "\xc6\xa4\xb7\xf4", NULL, 0, MENU_FLAG_NORMAL);
        {
            char name[16];
            int32 i;

            for (i = 0; i < 8; i++)
            {
                name[0] = '\\0';

                if (DrawLib_SkinName((uint8)i, name) == MR_SUCCESS && name[0] != '\\0')
                {
                    Menu_Add(tempMenu2, name, M_SetColor, i, JUDGE_MENU_FLAG_CHECK(i == AppColor.type));
                }
                else if (0 == i)
                {
                    Menu_Add(tempMenu2, "\xc7\xe5\xc0\xb6", M_SetColor, i, JUDGE_MENU_FLAG_CHECK(i == AppColor.type));
                }
                else if (1 == i)
                {
                    Menu_Add(tempMenu2, "\xbf\xe1\xba\xda", M_SetColor, i, JUDGE_MENU_FLAG_CHECK(i == AppColor.type));
                }
            }
        }

        tempMenu2 = Menu_Add(tempMenu, "\xb8\xfc\xb6\xe0", NULL, 0, MENU_FLAG_NORMAL);
        {
            Menu_Add(tempMenu2, "\xb4\xf3\xb6\xcb\xd7\xd6\xd0\xf2", M_SetEndian, 0, JUDGE_MENU_FLAG_CHECK(AppDatas.BigEndian));
            Menu_Add(tempMenu2, "\xbf\xec\xbd\xdd\xb2\xcb\xb5\xa5", M_SetPopMenu, 0, JUDGE_MENU_FLAG_CHECK(AppDatas.PopMenu));
            Menu_Add(tempMenu2, "\xd7\xd4\xb6\xaf\xb4\xf2\xbf\xaa", M_SetAutoOpen, 0, JUDGE_MENU_FLAG_CHECK(AppDatas.AutoOpen));
            Menu_Add(tempMenu2, "\xb2\xcb\xb5\xa5\xd0\xf2\xba\xc5", M_SetShowMenuIndex, 0, JUDGE_MENU_FLAG_CHECK(AppDatas.MenuIndex));
            Menu_Add(tempMenu2, "\xb7\xad\xd2\xb3\xb0\xb4\xc5\xa5", M_SetShowPageButton, 0, JUDGE_MENU_FLAG_CHECK(AppDatas.PageButton));
            Menu_Add(tempMenu2, "\xb3\xa3\xd3\xc3\xc4\xbf\xc2\xbc", M_SetUserDir, 0, MENU_FLAG_NORMAL);
        }
    }

    tempMenu = Menu_Add(rootMenu, "\xb0\xef\xd6\xfa", NULL, 0, MENU_FLAG_NORMAL);
    {
   //     Menu_Add(tempMenu, "\xb8\xf6\xc8\xcb\xcd\xf8\xd5\xbe", M_GotoEles, 0, MENU_FLAG_NORMAL);
        Menu_Add(tempMenu, "\xca\xb9\xd3\xc3\xb0\xef\xd6\xfa", M_ShowHelp, 0, MENU_FLAG_NORMAL);
        Menu_Add(tempMenu, "\xb8\xfc\xd0\xc2\xc0\xfa\xca\xb7", M_ShowNew, 0, MENU_FLAG_NORMAL);
        Menu_Add(tempMenu, "\xb9\xd8\xd3\xda\xc8\xed\xbc\xfe", M_ShowAbout, 0, MENU_FLAG_NORMAL);
    }

    tempMenu = Menu_Add(rootMenu, "\xcd\xcb\xb3\xf6", M_ExitApp, 0, MENU_FLAG_NORMAL);

    return rootMenu;
}


// 设置某些菜单是否选中
// 参数：第1层菜单序号，第2层菜单序号，第3层菜单序号，是否选中
void MainMenu_SetChecked(uint8 index1, uint8 index2, uint8 index3, uint8 isChecked)
{
    PMENU_LINK mp = NULL, mpl = NULL;

    mp = Menu_GetByIndex(AppDatas.MainMenu, index1);
    if (NULL == mp)
        return;

    mpl = mp;
    mp = Menu_GetByIndex(mp, index2);
    if (NULL == mp)
    {
        mp = mpl;
    }
    else
    {
        mpl = mp;
        mp = Menu_GetByIndex(mp, index3);
        if (NULL == mp)
        {
            mp = mpl;
        }
    }

    MENU_SET_FLAG_EX(mp, MENU_FLAG_CHECK, isChecked);
}

// 设置某些菜单是否有效
// 参数：第1层菜单序号，第2层菜单序号，第3层菜单序号，是否有效
void MainMenu_SetEnabled(uint8 index1, uint8 index2, uint8 index3, uint8 isEnabled)
{
    PMENU_LINK mp = NULL, mpl = NULL;

    mp = Menu_GetByIndex(AppDatas.MainMenu, index1);
    if (NULL == mp)
        return;

    mpl = mp;
    mp = Menu_GetByIndex(mp, index2);
    if (NULL == mp)
    {
        mp = mpl;
    }
    else
    {
        mpl = mp;
        mp = Menu_GetByIndex(mp, index3);
        if (NULL == mp)
        {
            mp = mpl;
        }
    }

    MENU_SET_FLAG_EX(mp, MENU_FLAG_ENABLE, isEnabled);
}

// 取得菜单数据
// 参数：第1层菜单序号，第2层菜单序号，第3层菜单序号
int32 MainMenu_GetData(uint8 index1, uint8 index2, uint8 index3)
{
    PMENU_LINK mp = NULL, mpl = NULL;

    mp = Menu_GetByIndex(AppDatas.MainMenu, index1);

    if (NULL == mp)
    {
        return 0;
    }

    mpl = mp;
    mp = Menu_GetByIndex(mp, index2);

    if (NULL == mp)
    {
        return mpl->Data;
    }

    mpl = mp;
    mp = Menu_GetByIndex(mp, index3);

    if (NULL == mp)
    {
        return mpl->Data; 
    }

    return mp->Data; 
}
