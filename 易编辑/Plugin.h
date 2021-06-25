/*
 * 插件接口头文件
 * 版权所有 (C) 2011-2012 eleqian
 * [6/4/2012]
 */

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include <mrc_base.h>
//#include <aps_main.h>

#define PLUGIN_FOLDER "eles/plugins"  // 插件文件夹
#define PLUGIN_EXT_NAME "plugin.ext"  // 插件ext名称

/*
 *	一级消息
 */

// 主程序消息
enum
{
    MAIN_EXT_FUNC_RETURN,  // 插件返回
    MAIN_EXT_FUNC_QUERY,   // 查询信息
    MAIN_EXT_FUNC_CONTROL, // 主程序控制
    MAIN_EXT_FUNC_DRAW,    // 图像库调用
    MAIN_EXT_FUNC_STRING,  // 字符串函数
    MAIN_EXT_FUNC_UTILE,   // 实用函数

    // 窗口部件
    MAIN_EXT_FUNC_INPUTBOX,  // 输入框
    MAIN_EXT_FUNC_MENU,      // 菜单
    MAIN_EXT_FUNC_FILEVIEW,  // 文件浏览
    MAIN_EXT_FUNC_INFOPAGE,  // 信息页

    MAIN_EXT_FUNC_INIFILE,   // ini文件操作模块

    MAIN_EXT_FUNC_MAX
};

// 插件消息
enum
{
    PLUGIN_EXT_MSG_REDRAW,   // 插件重绘界面
    PLUGIN_EXT_MSG_INPUT,    // 插件编辑框通知
    PLUGIN_EXT_MSG_MENU,     // 插件菜单通知
    PLUGIN_EXT_MSG_FILEVIEW, // 插件文件浏览通知
    PLUGIN_EXT_MSG_INFOPAGE, // 插件信息页通知

    PLUGIN_EXT_MSG_MAX
};

/*
 *	二级消息
 */

// 信息查询枚举
enum
{
    EXT_FUNC_QUERY_PLUGIN_ID,     // 查询插件加载ID

    EXT_FUNC_QUERY_MAIN_VERSION,  // 查询主程序版本
    EXT_FUNC_QUERY_MAIN_NAME,     // 查询主程序路径

    EXT_FUNC_QUERY_ARG_FILENAME,  // 目标文件名
    EXT_FUNC_QUERY_ARG_FILEPATH,  // 目标文件绝对路径
    EXT_FUNC_QUERY_ARG_FILESIZE,  // 当前文件大小
    EXT_FUNC_QUERY_ARG_FILEOFFET, // 当前文件偏移

    EXT_FUNC_QUERY_SKIN_TYPE,     // 程序界面配色模式
    EXT_FUNC_QUERY_SKIN_COLOR,    // 程序界面颜色
    EXT_FUNC_QUERY_FONT,          // 程序界面字体

    EXT_FUNC_QUERY_APP_ID,        // 程序id
    EXT_FUNC_QUERY_PLGUIN_NAME,   // 插件路径

    EXT_FUNC_QUERY_MAX
};

// 主程序控制枚举
enum
{
    EXT_FUNC_CONTROL_OPENFILE,      // 打开文件
    EXT_FUNC_CONTROL_CLOSEFILE,     // 关闭当前打开文件
    EXT_FUNC_CONTROL_SWITCH_WINDOW, // 切换显示窗口
    EXT_FUNC_CONTROL_GOTO_OFFSET,   // 转到文件偏移
    EXT_FUNC_CONTROL_FIND_DATA,     // 查找数据
    EXT_FUNC_CONTROL_SAVE_DATA,     // 保存数据
    EXT_FUNC_CONTROL_INSTERT_DATA,  // 插入数据
    EXT_FUNC_CONTROL_DELETE_DATA,   // 删除数据
    EXT_FUNC_CONTROL_REDRAW,        // 重绘界面

    EXT_FUNC_CONTROL_MAX
};

// 绘图函数库枚举
enum
{
    EXT_FUNC_DRAW_CLS,              // 清除全屏
    EXT_FUNC_DRAW_REFRESH,          // 刷新全屏
    EXT_FUNC_DRAW_CLEAR_RECT,       // 清除区域
    EXT_FUNC_DRAW_REFRESH_RECT,     // 刷新区域

    EXT_FUNC_DRAW_HLINE,            // 绘制水平线段
    EXT_FUNC_DRAW_VLINE,            // 绘制垂直线段
    EXT_FUNC_DRAW_ROUND_BORDER,     // 圆角边框
    EXT_FUNC_DRAW_SHADE_RECT,       // 从上至下渐变填充区域
    EXT_FUNC_DRAW_FILL_RECT,        // 绘制填充区域

    EXT_FUNC_DRAW_TEXT_SCREENW,     // 在屏幕范围绘制文字
    EXT_FUNC_DRAW_TEXT_SCREENA,
    EXT_FUNC_DRAW_TEXT_LINESW,      // 在区域绘制文字
    EXT_FUNC_DRAW_TEXT_LINESA,
    EXT_FUNC_DRAW_TEXT_MIDW,        // 在区域水平和竖直中心绘制文字
    EXT_FUNC_DRAW_TEXT_MIDA,
    EXT_FUNC_DRAW_TEXT_MID_LEFTW,   // 在区域竖直中心水平靠左绘制文字
    EXT_FUNC_DRAW_TEXT_MID_LEFTA,
    EXT_FUNC_DRAW_TEXT_MID_RIGHTW,  // 在区域竖直中心水平靠右绘制文字
    EXT_FUNC_DRAW_TEXT_MID_RIGHTA,

    EXT_FUNC_DRAW_TITLEBARW,        // 标题栏
    EXT_FUNC_DRAW_TOOLBARW,         // 工具栏

    EXT_FUNC_DRAW_MAX
};

// 字符串函数枚举
enum
{
    EXT_FUNC_STR_GB2UNI,    // gb转unicode
    EXT_FUNC_STR_UNI2GB,    // unicode转gb
    EXT_FUNC_STR_UNI2UTF8,  // unicode转utf-8
    EXT_FUNC_STR_UTF82UNI,  // utf-8转unicode

    EXT_FUNC_STR_STRICMP,   // 忽略大小写比较字符串
    EXT_FUNC_STR_STRNICMP,  // 忽略大小写比较字符串前n个字符
    EXT_FUNC_STR_STRDUP,    // 新建并复制字符串到新串
    EXT_FUNC_STR_STRRCHR,   // 从字符串末尾查找
    EXT_FUNC_STR_UCASE,     // 将字符串转换为大写
    EXT_FUNC_STR_LCASE,     // 将字符串转换为小写

    EXT_FUNC_STR_WSTRLEN,   // unicode字符串长度计算
    EXT_FUNC_STR_WSTRCPY,   // unicode字符串复制
    EXT_FUNC_STR_WSTRNCPY,  // unicode字符串复制前n个字符
    EXT_FUNC_STR_WSTRCAT,   // unicode字符串连接
    EXT_FUNC_STR_WSTRCMP,   // unicode字符串比较
    EXT_FUNC_STR_WSTRDUP,   // unicode字符串新建

    EXT_FUNC_STR_WITOA,     // 数值转换为unicode
    EXT_FUNC_STR_WATOI,     // unicode转换为数值

    EXT_FUNC_STR_BMH,       // BMH字符串匹配

    // 以下两个函数比支持gb的效率更高
    EXT_FUNC_STR_ASC2UNI,   // ascii转unicode
    EXT_FUNC_STR_UNI2ASC,   // unicode转ascii

    EXT_FUNC_STR_STRC2U,    // 类似strdup，同时转换gb为unicode
    EXT_FUNC_STR_STRU2C,    // 类似strdup，同时转换unicode为gb

    EXT_FUNC_STR_MAX
};

// 实用函数枚举
enum
{
    EXT_FUNC_ULTILE_GETCURDIR,        // 获取当前环境路径
    EXT_FUNC_ULTILE_SWITCHDIR,        // 设置环境路径

    EXT_FUNC_ULTILE_COPYFILE,         // 普通复制文件
    EXT_FUNC_ULTILE_COPYFILE_PATH,    // 绝对路径复制文件
    EXT_FUNC_ULTILE_COPYFILE_HANDLE,  // 根据文件句柄复制文件

    EXT_FUNC_ULTILE_FINDFROM_HANDLE,  //根据文件句柄查找数据位置

    EXT_FUNC_ULTILE_HEX2DATA,         // 转换HEX字符串为数据
    EXT_FUNC_ULTILE_DATA2HEX,         // 转换数据为HEX字符串

    EXT_FUNC_ULTILE_CHECK_VERSION,    // 检查版本
    EXT_FUNC_ULTILE_REG_EVENT_FUNC,   // 注册消息入口

    EXT_FUNC_ULTILE_MAKE_DIR,         // 创建多级目录
    EXT_FUNC_ULTILE_REMOVE_DIR,       // 删除目录及其子目录和文件
    EXT_FUNC_ULTILE_FIX_DIR,          // 调整路径分隔符
    EXT_FUNC_ULTILE_CONV_DIR2SYS,     // 转换绝对路径为相对mythroad路径

    EXT_FUNC_ULTILE_LOG,              // 写LOG

    EXT_FUNC_ULTILE_MAX
};

// ini文件操作函数枚举
enum
{
    EXT_FUNC_INIFILE_OPEN,          // 打开ini文件
    EXT_FUNC_INIFILE_CLOSE,         // 关闭ini文件
    EXT_FUNC_INIFILE_GET_STRING,    // 读取字符串
    EXT_FUNC_INIFILE_GET_INT,       // 读取整型数据
    EXT_FUNC_INIFILE_GET_BOOL,      // 读取布尔型数据
    EXT_FUNC_INIFILE_SET_STRING,    // 保存字符串数据
    EXT_FUNC_INIFILE_SET_INT,       // 保存整型数据
    EXT_FUNC_INIFILE_SET_BOOL,      // 保存布尔型数据
    EXT_FUNC_INIFILE_CLEAR,         // 清除ini配置内容

    EXT_FUNC_INIFILE_MAX
};

// 菜单函数枚举
enum
{
    /* 插件调用，主程序实现 */
    EXT_FUNC_MENU_ADD,      // 添加菜单项
    EXT_FUNC_MENU_SHOW,     // 显示菜单
    EXT_FUNC_MENU_DESTROY,  // 释放菜单

    /* 主程序调用，插件实现 */
    EXT_FUNC_MENU_SELECT,   // 选择菜单项
    EXT_FUNC_MENU_DRAWBACK, // 绘制菜单背景
    EXT_FUNC_MENU_CANCLE,   // 菜单关闭

    EXT_FUNC_MENU_MAX
};

// 信息显示函数枚举
enum
{
    EXT_FUNC_INFOPAGE_SHOW,         // 显示
    EXT_FUNC_INFOPAGE_SET_TOOLBAR,  // 设置工具栏

    EXT_FUNC_INFOPAGE_MAX
};

/*
 *	其它枚举
 */

// 界面颜色类型枚举
enum
{
    SKIN_COLOR_BACK_MORMAL,
    SKIN_COLOR_BACK_LIGHT,
    SKIN_COLOR_BACK_DEEP,
    SKIN_COLOR_TEXT_NORMAL,
    SKIN_COLOR_TEXT_LIGHT,
    SKIN_COLOR_TEXT_FOCUS,
    SKIN_COLOR_TEXT_DISABLE,

    SKIN_COLOR_MAX
};

// 查找和写入数据类型枚举
enum
{
    EXT_HE_INPUT_DATA_TYPE_LAST,
    EXT_HE_INPUT_DATA_TYPE_HEX,
    EXT_HE_INPUT_DATA_TYPE_UCS2BE,
    EXT_HE_INPUT_DATA_TYPE_UCS2LE,
    EXT_HE_INPUT_DATA_TYPE_GB2312,
    EXT_HE_INPUT_DATA_TYPE_UTF8,
    EXT_HE_INPUT_DATA_TYPE_NUM,
    EXT_HE_INPUT_DATA_TYPE_DATA,

    EXT_HE_INPUT_DATA_TYPE_MAX
};

// 通用消息
enum
{
    EXT_MSG_OK,      // 确定
    EXT_MSG_CANCLE,  // 取消

    EXT_MSG_MAX
};

// 菜单样式标志设置
#define EXT_MENU_FLAG_ENABLE   0x1  // 有效
#define EXT_MENU_FLAG_CHECK    0x2  // 选中
#define EXT_MENU_FLAG_AUTOFOLD 0x4  // 自动关闭
#define EXT_MENU_FLAG_UNICODE  0x8  // 文本为unicode(默认gb2312)
#define EXT_MENU_FLAG_NORMAL   (EXT_MENU_FLAG_ENABLE | EXT_MENU_FLAG_AUTOFOLD)  // 普通(有效+自动关闭)

// 菜单显示标志设置
#define EXT_MENU_SHOW_FLAG_NO_TOOLBAR  0x1  // 不显示工具栏
#define EXT_MENU_SHOW_FLAG_INDEX       0x2  // 显示菜单序号

// 文件浏览标志设置
#define EXT_FILEVIEW_FLAG_FILE   0x1  // 选择文件
#define EXT_FILEVIEW_FLAG_FOLDER 0x2  // 选择文件夹
#define EXT_FILEVIEW_FLAG_RECENT 0x4  // 使用上次浏览位置，忽略path设置

// 信息页标记位
#define EXT_INFOPAGE_FLAG_BUTTON_OK    0x1  // 有确定按钮
#define EXT_INFOPAGE_FLAG_FREE_TITLE   0x2  // 需要释放标题数据
#define EXT_INFOPAGE_FLAG_FREE_CONTENT 0x4  // 需要释放文本数据
#define EXT_INFOPAGE_FLAG_CONTENT_GB   0x8  // 文本数据为GB编码

/*
 *	供插件调用的函数
 */

// 插件调用以返回主程序
#define ext_PluginReturn(ret) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_RETURN, (int32)(ret), 0, 0, 0, 0)

/*---------------------------*/

// 查询当前加载插件的ID
#define ext_GetPluginExtID() \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_QUERY, EXT_FUNC_QUERY_PLUGIN_ID, 0, 0, 0, 0)

// 查询主程序的ID
#define ext_GetAppId() \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_QUERY, EXT_FUNC_QUERY_APP_ID, 0, 0, 0, 0)

// 查询主程序的版本号
#define ext_GetMainVersion() \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_QUERY, EXT_FUNC_QUERY_MAIN_VERSION, 0, 0, 0, 0)

// 查询主程序的mrp路径
#define ext_GetMainMrpName() \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_QUERY, EXT_FUNC_QUERY_MAIN_NAME, 0, 0, 0, 0)

// 查询当前插件mrp路径
#define ext_GetPluginMrpName() \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_QUERY, EXT_FUNC_QUERY_PLGUIN_NAME, 0, 0, 0, 0)

// 查询目标文件名称
#define ext_GetArgFileName() \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_QUERY, EXT_FUNC_QUERY_ARG_FILENAME, 0, 0, 0, 0)

// 查询目标文件路径
#define ext_GetArgFilePath() \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_QUERY, EXT_FUNC_QUERY_ARG_FILEPATH, 0, 0, 0, 0)

// 查询当前打开文件大小
#define ext_GetCurFileSize() \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_QUERY, EXT_FUNC_QUERY_ARG_FILESIZE, 0, 0, 0, 0)

// 查询当前打开文件偏移
#define ext_GetCurFileOffset() \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_QUERY, EXT_FUNC_QUERY_ARG_FILEOFFET, 0, 0, 0, 0)

// 查询当前程序皮肤模式
#define ext_GetAppSkinType() \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_QUERY, EXT_FUNC_QUERY_SKIN_TYPE, 0, 0, 0, 0)

// 查询当前程序皮肤颜色
#define ext_GetAppSkinColor(type) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_QUERY, EXT_FUNC_QUERY_SKIN_COLOR, (int32)(type), 0, 0, 0)

// 查询当前程序字体
#define ext_GetAppFont() \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_QUERY, EXT_FUNC_QUERY_FONT, 0, 0, 0, 0)

/*---------------------------*/

// 打开文件
#define ext_HV_OpenFile(path, name) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_CONTROL, EXT_FUNC_CONTROL_OPENFILE, (int32)(path), (int32)(name), 0, 0)

// 关闭文件
#define ext_HV_CloseFile() \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_CONTROL, EXT_FUNC_CONTROL_CLOSEFILE, 0, 0, 0, 0)

// 切换窗口
#define ext_HV_SwitchWindow(index) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_CONTROL, EXT_FUNC_CONTROL_SWITCH_WINDOW, (int32)(index), 0, 0, 0)

// 转到位置
#define ext_HV_GotoOffset(offset) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_CONTROL, EXT_FUNC_CONTROL_GOTO_OFFSET, (int32)(offet), 0, 0, 0)

// 查找数据
#define ext_HE_FindData(type, data, size) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_CONTROL, EXT_FUNC_CONTROL_FIND_DATA, (int32)(type),(int32)(data), (int32)(size), 0)

// 保存数据
#define ext_HE_SaveData(type, data, size) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_CONTROL, EXT_FUNC_CONTROL_SAVE_DATA, (int32)(type),(int32)(data), (int32)(size), 0)

// 插入数据
#define ext_HE_InstertData(data, size) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_CONTROL, EXT_FUNC_CONTROL_INSTERT_DATA, (int32)(data), (int32)(size), 0, 0)

// 删除数据
#define ext_HE_DeleteData(size) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_CONTROL, EXT_FUNC_CONTROL_DELETE_DATA, (int32)(size), 0, 0, 0)

// 重绘界面
#define ext_UI_Redraw(refresh) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_CONTROL, EXT_FUNC_CONTROL_REDRAW, (int32)(refresh), 0, 0, 0)

/*---------------------------*/

// 清除屏幕
#define ext_ClearScreen() \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_CLS, 0, 0, 0, 0)

// 刷新屏幕
#define ext_RefreshScreen() \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_REFRESH, 0, 0, 0, 0)

// 清除区域
#define ext_ClearRect(prect) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_CLEAR_RECT, (int32)(prect), 0, 0, 0)

// 刷新区域
#define ext_RefreshRect(prect) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_REFRESH_RECT, (int32)(prect), 0, 0, 0)

// 绘制水平线段
#define ext_DrawHLine(x1, x2, y, color) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_HLINE, (int32)(x1), (int32)(x2), (int32)(y), (int32)(color))

// 绘制垂直线段
#define ext_DrawVLine(x, y1, y2, color) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_VLINE, (int32)(x), (int32)(y1), (int32)(y2), (int32)(color))

// 圆角边框
#define ext_DrawRoundBorder(prect,color) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_ROUND_BORDER, (int32)(prect), (int32)(color), 0, 0)

// 填充区域
#define ext_DrawFillRect(prect, color) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_FILL_RECT, (int32)(prect), (int32)(color), 0, 0)

// 从上至下渐变填充区域
#define ext_DrawShadeRect(prect) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_SHADE_RECT, (int32)(prect), 0, 0, 0)

// 在屏幕范围绘制文字-unicode
#define ext_DrawTextScreenW(text, x, y) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_TEXT_SCREENW, (int32)(text), (int32)(x), (int32)(y), 0)

// 在屏幕范围绘制文字-gb2312
#define ext_DrawTextScreenA(text, x, y) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_TEXT_SCREENA, (int32)(text), (int32)(x), (int32)(y), 0)

// 在区域绘制文字-unicode
#define ext_DrawTextLinesW(prect, text, color) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_TEXT_LINESW, (int32)(prect), (int32)(text), (int32)(color), 0)

// 在区域绘制文字-gb2312
#define ext_DrawTextLinesA(prect, text, color) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_TEXT_LINESA, (int32)(prect), (int32)(text), (int32)(color), 0)

// 在区域水平和竖直中心绘制文字-unicode
#define ext_DrawTextMidW(prect, text, color) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_TEXT_MIDW, (int32)(prect), (int32)(text), (int32)(color), 0)

// 在区域水平和竖直中心绘制文字-gb2312
#define ext_DrawTextMidA(prect, text, color) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_TEXT_MIDA, (int32)(prect), (int32)(text), (int32)(color), 0)

// 在区域竖直中心水平靠左绘制文字-unicode
#define ext_DrawTextMidLeftW(prect, text, color) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_TEXT_MID_LEFTW, (int32)(prect), (int32)(text), (int32)(color), 0)

// 在区域竖直中心水平靠左绘制文字-gb2312
#define ext_DrawTextMidLeftA(prect, text, color) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_TEXT_MID_LEFTA, (int32)(prect), (int32)(text), (int32)(color), 0)

// 在区域竖直中心水平靠右绘制文字-unicode
#define ext_DrawTextMidRightW(prect, text, color) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_TEXT_MID_RIGHTW, (int32)(prect), (int32)(text), (int32)(color), 0)

// 在区域竖直中心水平靠右绘制文字-gb2312
#define ext_DrawTextMidRightA(prect, text, color) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_TEXT_MID_RIGHTA, (int32)(prect), (int32)(text), (int32)(color), 0)

// 绘制普通标题栏-unicode
#define ext_DrawTitleBarW(prect, text) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_TITLEBARW, (int32)(prect), (int32)(text), 0, 0)

// 绘制普通工具栏-unicode
#define ext_DrawToolBarW(prect, ltext, rtext, state) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_DRAW, EXT_FUNC_DRAW_TOOLBARW, (int32)(prect), (int32)(ltext), (int32)(rtext), (int32)(state))

/*---------------------------*/

// 转换gb为unicode
#define ext_GB2UCSBE(gb, buf, len) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_GB2UNI, (int32)(gb), (int32)(buf), (int32)(len), 0)

// 转换unicode为gb
#define ext_UCSBE2GB(uni, buf, len) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_UNI2GB, (int32)(uni), (int32)(buf), (int32)(len), 0)

// 转换utf-8为unicode
#define ext_UTF82UCSBE(utf, buf, len) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_UTF82UNI, (int32)(utf), (int32)(buf), (int32)(len), 0)

// 转换unicode为utf-8
#define ext_UCSBE2UTF8(uni, buf, len) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_UNI2UTF8, (int32)(uni), (int32)(buf), (int32)(len), 0)

// 将字符串转换为大写
#define ext_strupr(str) \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_UCASE, (int32)(str), 0, 0, 0)

// 将字符串转换为小写
#define ext_strlwr(str) \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_LCASE, (int32)(str), 0, 0, 0)

// 查找字符串中最后出现字符位置
#define ext_strrchr(s1, ch) \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_STRRCHR, (int32)(s1), (int32)(ch), 0, 0)

// 忽略大小写比较字符串
#define ext_stricmp(s1, s2) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_STRICMP, (int32)(s1), (int32)(s2), 0, 0)

// 忽略大小写比较字符串前n个字符
#define ext_strnicmp(s1, s2, n) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_STRNICMP, (int32)(s1), (int32)(s2), (int32)(n), 0)

// 复制字符串到新串
#define ext_strdup(str) \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_STRDUP, (int32)(str), 0, 0, 0)

// 复制字符串到新串，同时转换gb为unicode
#define ext_strc2u(str) \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_STRC2U, (int32)(str), 0, 0, 0)

// 复制字符串到新串，同时转换unicode为gb
#define ext_stru2c(str) \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_STRU2C, (int32)(str), 0, 0, 0)

// unicode字符串长度
#define ext_wstrlen(str) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_WSTRLEN, (int32)(str), 0, 0, 0)

// unicode字符串比较
#define ext_wstrcmp(s1, s2) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_WSTRCMP, (int32)(s1), (int32)(s2), 0, 0)

// unicode字符串新建并复制
#define ext_wstrdup(s1) \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_WSTRDUP, (int32)(s1), 0, 0, 0)

// unicode字符串复制
#define ext_wstrcpy(s1, s2) \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_WSTRCPY, (int32)(s1), (int32)(s2), 0, 0)

// unicode字符串复制n个字符
#define ext_wstrncpy(s1, s2, n) \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_WSTRNCPY, (int32)(s1), (int32)(s2), (int32)(n), 0)

// unicode字符串连接
#define ext_wstrcat(s1, s2) \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_WSTRCAT, (int32)(s1), (int32)(s2), 0, 0)

// unicode转换为数值
#define ext_watoi(str) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_WATOI, (int32)(str), 0, 0, 0)

// 数值转换为unicode
#define ext_witoa(num) \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_WITOA, (int32)(num), 0, 0, 0)

// 转换ascii为unicode
#define ext_Asc2UniBE(asc, buf, len) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_ASC2UNI, (int32)(asc), (int32)(buf), (int32)(len), 0)

// 转换unicode为ascii
#define ext_UniBE2Asc(uni, buf, len) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_UNI2ASC, (int32)(uni), (int32)(buf), (int32)(len), 0)

// BMH字符串匹配
#define ext_BMH(data, dlen, s, slen) \
    (void*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_STRING, EXT_FUNC_STR_BMH, (int32)(data), (int32)(dlen), (int32)(s), (int32)(slen))

/*---------------------------*/

// 获取当前环境路径
#define ext_GetCurDir(buf) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_GETCURDIR, (int32)(buf), 0, 0, 0)

// 设置环境路径
#define ext_SwitchDir(dir) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_SWITCHDIR, (int32)(dir), 0, 0, 0)

// 普通复制文件
#define ext_CopyFile(srcfile, destfile) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_COPYFILE, (int32)(srcfile), (int32)(destfile), 0, 0)

// 绝对路径复制文件
#define ext_CopyFileFullPath(srcpath, destpath, srcfile, destfile) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_COPYFILE_PATH, (int32)(srcpath), (int32)(destpath), (int32)(srcfile), (int32)(destfile))

// 根据句柄复制文件
#define ext_CopyFileHandle(srcfd, destfd, cpysize) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_COPYFILE_HANDLE, (int32)(srcfd), (int32)(destfd), (int32)(cpysize), 0)

// 根据文件句柄查找数据位置
#define ext_FindFromFileHandle(fd, offset, data, size) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_FINDFROM_HANDLE, (int32)(fd), (int32)(offset), (int32)(data), (int32)(size))

// 转换HEX字符串为数据
#define ext_ConvHex2Data(hex, hszie, data, dsize) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_HEX2DATA, (int32)(hex), (int32)(hszie), (int32)(data), (int32)(dsize))

// 转换数据为HEX字符串
#define ext_ConvData2Hex(data, dsize, hex, hszie) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_DATA2HEX, (int32)(data), (int32)(dsize), (int32)(hex), (int32)(hszie))

// 创建多级目录
#define ext_MakeDir(dir) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_MAKE_DIR, (int32)(dir), 0, 0, 0)

// 删除多级目录
#define ext_RemoveDir(dir) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_REMOVE_DIR, (int32)(dir), 0, 0, 0)

// 转换绝对路径为相对mythroad目录
#define ext_ConvPath2Sys(path, name, out) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_CONV_DIR2SYS, (int32)(path), (int32)(name), (int32)(out), 0)

// 调整路径分隔符
#define ext_FixPath(path, sep) \
    (char*)mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_MAKE_DIR, (int32)(path), (int32)(sep), 0, 0)

// 检查版本(检查插件与主程序兼容性)
#define ext_CheckVersion(version) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_CHECK_VERSION, (int32)(version), 0, 0, 0)

// 注册消息入口(和aps_main_regEntry类似)
#define ext_RegEventFunc(func) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_REG_EVENT_FUNC, (int32)(func), 0, 0, 0)

// LOG
#define ext_Log(str, num) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_LOG, (int32)(str), (int32)(num), 0, 0)

// LOG当前位置
#define ext_LogPos() \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_UTILE, EXT_FUNC_ULTILE_LOG, (int32)(__FILE__), (int32)(__LINE__), 0, 0)

/*---------------------------*/

// 打开ini文件
#define ext_IniOpenFile(file) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_INIFILE, EXT_FUNC_INIFILE_OPEN, (int32)(file), 0, 0, 0)

// 关闭ini文件
#define ext_IniCloseFile() \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_INIFILE, EXT_FUNC_INIFILE_CLOSE, 0, 0, 0, 0)

// 清除ini内容
#define ext_IniClearContent() \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_INIFILE, EXT_FUNC_INIFILE_CLEAR, 0, 0, 0, 0)

// 读取字符串值
#define ext_IniGetString(section, key, value) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_INIFILE, EXT_FUNC_INIFILE_GET_STRING, (int32)(section), (int32)(key), (int32)(value), 0)

// 保存字符串值
#define ext_IniSetString(section, key, value) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_INIFILE, EXT_FUNC_INIFILE_SET_STRING, (int32)(section), (int32)(key), (int32)(value), 0)

// 读取整型值
#define ext_IniGetInt(section, key, default) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_INIFILE, EXT_FUNC_INIFILE_GET_INT, (int32)(section), (int32)(key), (int32)(default), 0)

// 保存整型值
#define ext_IniSetInt(section, key, value) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_INIFILE, EXT_FUNC_INIFILE_SET_INT, (int32)(section), (int32)(key), (int32)(value), 0)

// 读取布尔型值
#define ext_IniGetBool(section, key, default) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_INIFILE, EXT_FUNC_INIFILE_GET_BOOL, (int32)(section), (int32)(key), (int32)(default), 0)

// 保存布尔型值
#define ext_IniSetBool(section, key, value) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_INIFILE, EXT_FUNC_INIFILE_SET_BOOL, (int32)(section), (int32)(key), (int32)(value), 0)

/*---------------------------*/

// 调用信息显示页面
#define ext_InfoPage(title, content, flag) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_INFOPAGE, EXT_FUNC_INFOPAGE_SHOW, (int32)(title), (int32)(content), (int32)(flag), 0)

// 设置信息显示工具栏文本
#define ext_InfoPag_SetToolBar(wstr_l, wstr_r) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, EXT_FUNC_INFOPAGE_SET_TOOLBAR, EXT_FUNC_INFOPAGE_SHOW, (int32)(wstr_l), (int32)(wstr_r), 0, 0)

// 调用菜单
#define ext_MenuShow(menu, x, y, flag) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_MENU, EXT_FUNC_MENU_SHOW, (int32)(menu), (int32)(x), (int32)(y), (int32)(flag))

// 添加菜单
#define ext_MenuAdd(menu, title, id, flag) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_MENU, EXT_FUNC_MENU_ADD, (int32)(menu), (int32)(title), (int32)(id), (int32)(flag))

// 销毁菜单
#define ext_MenuDestory(menu) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_MENU, EXT_FUNC_MENU_DESTROY, (int32)(menu), 0, 0, 0)

// 调用文件浏览器
#define ext_FileView(title, path, flag) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_FILEVIEW, (int32)(title), (int32)(path), (int32)(flag), 0, 0)

// 调用文本编辑框
#define ext_InputBox(id, title, content, type, size) \
    mrc_extSendAppEventEx(APS_EXT_ID_APP, MAIN_EXT_FUNC_INPUTBOX, (int32)(id), (int32)(title), (int32)(content), (int32)(type), (int32)(size))

#endif // __PLUGIN_H__
