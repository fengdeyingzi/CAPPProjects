/*
 * 公共界面绘制代码
 * 版权所有 (C) 2011-2012 eleqian
 * [6/2/2012]
 */

#include "src/base.h"
#include "mrc_base.h"
#include "src/exb.h"
#include <stdio.h>
#include <stdlib.h>
#include "src/android.h"
//#include <mrc_bmp.h>  // 获取屏幕信息的函数
//#include <mrc_skyfont.h>  // 小字体

#include "DrawLib.h"
#include "IniFile.h"
#include "XString.h"
#include "src/android.h"

COLORSET AppColor;       // 颜色配置数据

int16 ScreenWidth;       // 屏幕宽度
int16 ScreenHeight;      // 屏幕高度
uint16 *ScreenBuf;       // 屏幕缓冲区

static int16 TextFont;   // 文本字体大小

/*---------------------------------------------------------------------------*/

// 图形库初始化
int32 DrawLib_Init(void)
{
    int32 sw, sh;

    ScreenBuf = getscrbuf();
    getscrsize(&sw, &sh);
    ScreenWidth = (int16)sw;
    ScreenHeight = (int16)sh; 

    DrawLib_SetColor(0);
    DrawLib_SetFont(MR_FONT_MEDIUM);

    return 0;
}

// 图形库结束 
int32 DrawLib_End(void)
{
    return 0;
}

// 设置绘制字体
int32 DrawLib_SetFont(uint16 font)
{
    TextFont = (int16)font;

    return 0;
}

// 读取颜色配置
int32 DrawLib_LoadSkin(uint8 type)
{
    int32 ret = MR_FAILED;
    char fname[32];

    sprintf(fname, "eles/ehex/skin%d.ini", type);
    ret = IniOpenFile(fname);

    AppColor.back_normal = (uint32)IniGetInteger("Skin", "BackNormal", 0x00ffffff);
    AppColor.back_light = (uint32)IniGetInteger("Skin", "BackLight", 0x00c3d0e7);
    AppColor.back_deep = (uint32)IniGetInteger("Skin", "BackDeep", 0x002888d0);
    AppColor.text_normal = (uint32)IniGetInteger("Skin", "TextNormal", 0x00000000);
    AppColor.text_light = (uint32)IniGetInteger("Skin", "TextLight", 0x00ffffff);
    AppColor.text_focus = (uint32)IniGetInteger("Skin", "TextFocus", 0x00ff0000);
    AppColor.text_disabled = (uint32)IniGetInteger("Skin", "TextDisable", 0x00a0a0a0);

    IniCloseFile();

    return ret;
}

// 读取皮肤名称
int32 DrawLib_SkinName(uint8 type, char *name)
{
    int32 ret = MR_FAILED;
    char fname[32];

    sprintf(fname, "eles/ehex/skin%d.ini", type);
    IniOpenFile(fname);
    ret = IniGetString("Skin", "Name", name);
    IniCloseFile();

    return (ret == TRUE) ? 0 : -1;
}

//初始化绘制颜色
int32 DrawLib_SetColor(uint8 cType)
{
    AppColor.type = cType;

    // 读取配置文件成功就不使用内部设置
    if (MR_SUCCESS == DrawLib_LoadSkin(cType))
        return 0;

    if (1 == cType) //夜间
    {
        AppColor.type = 1;

        AppColor.back_normal = 0x00000000;
        AppColor.back_light = 0x002888d0;
        AppColor.back_deep = 0x00104060;
        AppColor.text_normal = 0x00d0d0d0;
        AppColor.text_light = 0x00ffffff;
        AppColor.text_focus = 0x00ffff00;
        AppColor.text_disabled = 0x00808080;
    }
    else //普通
    {
        AppColor.type = 0;

        AppColor.back_normal = 0x00ffffff;
        AppColor.back_light = 0x00c3d0e7;
        AppColor.back_deep = 0x002888d0;
        AppColor.text_normal = 0x00000000;
        AppColor.text_light = 0x00ffffff;
        AppColor.text_focus = 0x00ff0000;
        AppColor.text_disabled = 0x00a0a0a0;
    }

    return 1;
}

/*---------------------------------------------------------------------------*/

// 取得文本宽高
int32 GetTextSizeW(const char *unistr, int32 *w, int32 *h)
{
    int32 tw, th, ret;

    ret = textwh((uint16*)unistr,1, TextFont, &tw, &th);
    if (NULL != w)
        *w = tw;
    if (NULL != h)
        *h = th;

    return ret;
}

// 取得文本宽高
int32 GetTextSizeW16(const char *unistr, int16 *w, int16 *h)
{
    int32 tw, th, ret;

    ret = textwh((uint16*)unistr, 1,TextFont, &tw, &th);
    if (NULL != w)
        *w = (int16)tw;
    if (NULL != h)
        *h = (int16)th;

    return ret;
}

// 获取屏幕尺寸信息-int32
int32 GetScreenSize(int32 *w, int32 *h)
{
    int32 sw, sh;

    getscrsize(&sw, &sh);
    if (NULL != w)
        *w = sw;
    if (NULL != h)
        *h = sh;

    return 0;
}

// 获取屏幕尺寸信息-int16
int32 GetScreenSize16(int16 *w, int16 *h)
{
    int32 sw, sh;

    getscrsize(&sw, &sh);
    if (NULL != w)
        *w = (int16)sw;
    if (NULL != h)
        *h = (int16)sh;

    return 0;
}

/*---------------------------------------------------------------------------*/

// 清除区域
void ClearRect(rectst rect)
{
    drect(rect.x, rect.y, rect.w, rect.h,
        PIXEL888RED(AppColor.back_normal), PIXEL888GREEN(AppColor.back_normal), PIXEL888BLUE(AppColor.back_normal));
}

// 清屏
void ClearScreen(void)
{
    cls(PIXEL888RED(AppColor.back_normal), PIXEL888GREEN(AppColor.back_normal), PIXEL888BLUE(AppColor.back_normal));
}

static int32 RefreshTriggerCount = 0;

// 刷新区域
void RefreshRect(rectst rect)
{
    if (0 == RefreshTriggerCount)
        ref(rect.x, rect.y, rect.w, rect.h);
}

// 刷新全屏
void RefreshScreen(void)
{
    if (0 == RefreshTriggerCount)
        ref(0, 0, ScreenWidth, ScreenHeight);
}

// 阻塞屏幕刷新
// 建议少使用，以免使逻辑控制更复杂
int32 RefreshTrigger(void)
{
    RefreshTriggerCount++;

    return RefreshTriggerCount;
}

// 取消阻塞屏幕刷新
int32 RefreshUnTrigger(void)
{
    RefreshTriggerCount--;

    return RefreshTriggerCount;
}

/*---------------------------------------------------------------------------*/
// 绘制水平线段-565色
void DrawHLine565(int16 x1, int16 x2, int16 y, uint16 color16)
{
    uint16 *dest;
    uint16 *end;

    if (y < 0 || y > ScreenHeight - 1)
        return;
    if (x1 > x2)
    {
        int16 xt = x1;
        x1 = x2; x2 = xt;
    }
    if (x1 < 0)
        x1 = 0;
    if (x2 > ScreenWidth - 1)
        x2 = ScreenWidth - 1;

    dest = ScreenBuf + y * ScreenWidth + x1;
    end = dest + x2 - x1;

    while (dest <= end)
        *dest++ = color16;
}

// 绘制水平线段
void DrawHLine(int16 x1, int16 x2, int16 y, uint32 color)
{
    uint16 *dest;
    uint16 *end;
    uint16 color16;

    if (y < 0 || y > ScreenHeight - 1)
        return;
    if (x1 > x2)
    {
        int16 xt = x1;
        x1 = x2; x2 = xt;
    }
    if (x1 < 0)
        x1 = 0;
    if (x2 > ScreenWidth - 1)
        x2 = ScreenWidth - 1;

    dest = ScreenBuf + y * ScreenWidth + x1;
    end = dest + x2 - x1;
    color16 = RGB888TO565(color);

    while (dest <= end)
        *dest++ = color16;
}

// 绘制水平线段RGB
void DrawHLineEx(int16 x1, int16 x2, int16 y, uint8 r, uint8 g, uint8 b)
{
    DrawHLine(x1, x2, y, MAKERGB888(r, g, b));
}

// 绘制垂直线段
void DrawVLine(int16 x, int16 y1, int16 y2, uint32 color)
{
    int16 y;
    uint16 *dest;
    uint16 color16;

    if (x < 0 || x > ScreenWidth - 1)
        return;
    if (y1 > y2)
    {
        int16 yt = y1;
        y1 = y2; y2 = yt;
    }
    if (y1 < 0)
        y1 = 0;
    if (y2 > ScreenHeight - 1)
        y2 = ScreenHeight - 1;

    dest = ScreenBuf + y1 * ScreenWidth + x;
    color16 = RGB888TO565(color);

    for (y = y1; y <= y2; y++)
    {
        *dest = color16;
        dest += ScreenWidth;
    }
}

// 绘制垂直线段RGB
void DrawVLineEx(int16 x, int16 y1, int16 y2, uint8 r, uint8 g, uint8 b)
{
    DrawVLine(x, y1, y2, MAKERGB888(r, g, b));
}

// 绘制线段RGB
void DrawLineEx(int16 x1, int16 y1, int16 x2, int16 y2, uint8 r, uint8 g, uint8 b)
{
    dline(x1, y1, x2, y2, r, g, b);
}

// 绘制线段
void DrawLine(int16 x1, int16 y1, int16 x2, int16 y2, uint32 color)
{
    dline(x1, y1, x2, y2, PIXEL888RED(color), PIXEL888GREEN(color), PIXEL888BLUE(color));
}

/*---------------------------------------------------------------------------*/

/* 绘制圆角矩形边框
 * 参数：x,y 矩形X,Y坐标
 *		 w,h 矩形宽高
 *		 color 边框颜色
 */
void DrawRoundBorderEx(int16 x, int16 y, int16 w, int16 h, uint32 color)
{
	DrawHLine(x + 1, x + w - 2, y, color);
	DrawHLine(x + 1, x + w - 2, y + h - 1, color);
	DrawVLine(x, y + 1, y + h - 2, color);
	DrawVLine(x + w - 1, y + 1, y + h - 2, color); 
}

// 绘制圆角矩形边框-结构体版
void DrawRoundBorder(rectst rect)
{
    DrawRoundBorderEx(rect.x, rect.y, rect.w, rect.h, AppColor.back_deep);
}

/* 过渡色填充矩形区域-从上到下
 * 参数：x,y 矩形X,Y坐标
 *		 w,h 矩形宽高
 *       color1 颜色1-上方
 *       color2 颜色2-下方
 */
void DrawShadeRectEx(int16 x, int16 y, int16 w, int16 h, uint32 color1, uint32 color2)
{
	int16 i;
    int32 r1, g1, b1;
    int32 r2, g2, b2;
	int32 dr, dg, db;  // 颜色差值 << 16

	// 取得各颜色值
	r1 = PIXEL888RED(color1) << 16;
    g1 = PIXEL888GREEN(color1) << 16;
    b1 = PIXEL888BLUE(color1) << 16;
	r2 = PIXEL888RED(color2) << 16;
    g2 = PIXEL888GREEN(color2) << 16;
    b2 = PIXEL888BLUE(color2) << 16;

	dr = (r2 - r1) / h;
    dg = (g2 - g1) / h;
    db = (b2 - b1) / h;

	// 渐变绘制
	for (i = 0; i < h; i++)
	{
		DrawHLine565(x, x + w - 1, y + i, MAKERGB565((r1 >> 16), (g1 >> 16), (b1 >> 16)));
        r1 += dr;
        g1 += dg;
        b1 += db;
	}
}

// 过渡色填充矩形区域-从上到下-结构体版
void DrawShadeRect(rectst rect)
{
    DrawShadeRectEx(rect.x, rect.y, rect.w, rect.h, AppColor.back_light, AppColor.back_deep);
}

// 绘制实心矩形区域
void DrawFillRectEx(int16 x, int16 y, int16 w, int16 h, uint32 color)
{
    drect(x, y, w, h, PIXEL888RED(color), PIXEL888GREEN(color), PIXEL888BLUE(color));
}

// 绘制实心矩形区域-结构体版
void DrawFillRect(rectst rect, uint32 color)
{
    drect(rect.x, rect.y, rect.w, rect.h, PIXEL888RED(color), PIXEL888GREEN(color), PIXEL888BLUE(color));
}

/*---------------------------------------------------------------------------*/

// 文字显示函数-屏幕范围自动换行-Unicode
int32 DrawTextScreenW(const char *drawText, int16 x, int16 y)
{
    int32 ret;
    colorst tColor;
    rectst rect;

    tColor.r = PIXEL888RED(AppColor.text_normal);
    tColor.g = PIXEL888GREEN(AppColor.text_normal);
    tColor.b = PIXEL888BLUE(AppColor.text_normal);
    rect.x = 0; rect.y = 0;
    rect.w = ScreenWidth; rect.h = ScreenHeight;
    ret = dtextex((char*)drawText, x, y, &rect, &tColor, 1, TextFont);

    return ret;
}

// 文字显示扩展函数-Unicode
int32 DrawTextExW(const char *drawText, int16 x, int16 y, rectst rect, uint32 ulColor, int32 flag)
{
    int32 ret;
    colorst tColor;

    tColor.r = PIXEL888RED(ulColor);
    tColor.g = PIXEL888GREEN(ulColor);
    tColor.b = PIXEL888BLUE(ulColor);
    ret = dtextex((char*)drawText, x, y, &rect, &tColor, 1, TextFont);

    return ret;
}

//在区域显示多行Unicode文字
//参数：区域，文字，颜色
void DrawTextLinesW(rectst rect, const char *drawText, uint32 ulColor)
{
    int16 x, y;
    colorst tColor;

    tColor.r = PIXEL888RED(ulColor);
    tColor.g = PIXEL888GREEN(ulColor);
    tColor.b = PIXEL888BLUE(ulColor);
    x = (int16)(rect.x);
    y = (int16)(rect.y);
    dtextex((char*)drawText, x, y, &rect, &tColor, 1, TextFont);
    char *totext = ex_coding(drawText,wstrlen(drawText),"UTF-16BE", "UTF-8");
    LOGI("%s",totext);
}

//在区域中间显示单行Unicode文字
//参数：区域，文字，颜色
void DrawTextMidW(rectst rect, const char *drawText, uint32 ulColor)
{
    int16 x, y;
    int32 fw, fh;
    colorst tColor;

    tColor.r = PIXEL888RED(ulColor);
    tColor.g = PIXEL888GREEN(ulColor);
    tColor.b = PIXEL888BLUE(ulColor);
	textwh((uint16*)drawText, TextFont,1, &fw, &fh);
    x = (int16)(rect.x + (rect.w - fw) / 2);
    y = (int16)(rect.y + (rect.h - fh) / 2);
	dtextex((char*)drawText, x, y, &rect, &tColor, 1, TextFont);
}

//在区域中间从左显示单行Unicode文字
//参数：区域，文字，颜色
void DrawTextMidLeftW(rectst rect, const char *drawText, uint32 ulColor)
{
    int16 x, y;
    int32 fw, fh;
    colorst tColor;

    tColor.r = PIXEL888RED(ulColor);
    tColor.g = PIXEL888GREEN(ulColor);
    tColor.b = PIXEL888BLUE(ulColor);
	textwh((uint16*)drawText, TextFont,1, &fw, &fh);
    x = (int16)(rect.x);
    y = (int16)(rect.y + (rect.h - fh) / 2);
    char temp[300];
    char *retext = ex_coding(drawText, wstrlen(drawText), "UTF-16BE","GBK"); //xldebug
	dtextex((char*)retext, x, y, &rect, &tColor, 0, TextFont);
	free(retext);
}

//在区域中间从右显示单行Unicode文字
//参数：区域，文字，颜色
void DrawTextMidRightW(rectst rect, const char *drawText, uint32 ulColor)
{
    int16 x, y;
    int32 fw, fh;
    colorst tColor;

    tColor.r = PIXEL888RED(ulColor);
    tColor.g = PIXEL888GREEN(ulColor);
    tColor.b = PIXEL888BLUE(ulColor);
	textwh((uint16*)drawText, TextFont,1, &fw, &fh);
    x = (int16)(rect.x + rect.w);
    y = (int16)(rect.y + (rect.h - fh) / 2);

//	dtext((char*)drawText, x-fw, y, tColor.r, tColor.g, tColor.b,  1, TextFont);
	LOGI("dtextright x=%d fw=%d %d,%d %d %d %d %d",x, fw, x-fw, y, tColor.r, tColor.g,tColor.b,TextFont); //xldebug
    char *totext = ex_coding(drawText,wstrlen(drawText),"UTF-16BE", "UTF-8");
    LOGI("%s",totext);
    dtext(totext, x-fw, y, tColor.r, tColor.g, tColor.b,  2, TextFont);
    free(totext);
}

/*---------------------------------------------------------------------------*/

// 文字显示函数-屏幕范围自动换行-GB2312
int32 DrawTextScreenA(const char *drawText, int16 x, int16 y)
{
    int32 ret = -1;
    char *uniText = NULL;

    uniText = strc2u(drawText);
    if (NULL != uniText)
    {
        ret = DrawTextScreenW(uniText, x, y);
        free(uniText);
    }

    return ret;
}

// 文字显示扩展函数-GB2312
int32 DrawTextExA(const char *drawText, int16 x, int16 y, rectst rect, uint32 ulColor, int32 flag)
{
    int32  ret = -1;
    char *uniText = NULL;

    uniText =strc2u(drawText);
    if (NULL != uniText)
    {
        ret = DrawTextExW(uniText, x, y, rect, ulColor, flag);
        free(uniText);
    }

    return ret;
}

//在区域显示多行GB2312文字
//参数：区域，文字，颜色
void DrawTextLinesA(rectst rect, const char *drawText, uint32 ulColor)
{
    char *uniText = NULL;

    uniText = strc2u(drawText);
    if (NULL != uniText)
    {
        DrawTextLinesW(rect, uniText, ulColor);
        free(uniText);
    }
}

//在区域中间显示单行GB2312文字
//参数：区域，文字，颜色
void DrawTextMidA(rectst rect, const char *drawText, uint32 ulColor)
{
    char *uniText = NULL;

    uniText = strc2u(drawText);
    if (NULL != uniText)
    {
        DrawTextMidW(rect, uniText, ulColor);
        free(uniText);
    }
}

//在区域中间从左显示单行GB2312文字
//参数：区域，文字，颜色
void DrawTextMidLeftA(rectst rect, const char *drawText, uint32 ulColor)
{
    char *uniText = NULL;

    uniText = strc2u(drawText);
    if (NULL != uniText)
    {
        DrawTextMidLeftW(rect, uniText, ulColor);
        free(uniText);
    }
}

//在区域中间从右显示单行GB2312文字
//参数：区域，文字，颜色
void DrawTextMidRightA(rectst rect, const char *drawText, uint32 ulColor)
{
    char *uniText = NULL;

    uniText = strc2u(drawText);
    if (NULL != uniText)
    {
        DrawTextMidRightW(rect, uniText, ulColor);
        free(uniText);
    }
}

/*---------------------------------------------------------------------------*/

// 绘制按钮
// 参数：区域，文字，焦点，状态
void DrawButtonW(rectst rect, const char *title, uint8 IsFocus, uint8 IsPress)
{
    uint32 ulLight, ulDark, ulFocus;

    ulLight = AppColor.back_light;
    ulDark = AppColor.back_deep;
    ulFocus = AppColor.back_deep;

    DrawRoundBorderEx(rect.x, rect.y, rect.w, rect.h, (0 == IsFocus) ? ulDark : ulFocus);
    DrawShadeRectEx(rect.x + 1, rect.y + 1, rect.w - 2, rect.h - 2, 
        (0 == IsPress) ? ulLight : ulDark, (0 == IsPress) ? ulDark : ulLight);
    DrawTextMidW(rect, title, (0 == IsFocus) ? AppColor.text_normal : AppColor.text_focus);
}

// 绘制普通工具栏
// 参数：区域，左按钮文本，右按钮文本，状态(0 - 普通，1 - 左软键，2 - 右软键)
void DrawNormalToolBarW(rectst rect, const char *lStr, const char *rStr, uint8 state)
{
    rectst tRect;

    // 背景
    DrawShadeRect(rect);
    DrawRoundBorder(rect);

    // 左按钮文字
    tRect = rect;
    tRect.x += 2;
    if (1 == state)
    {
        tRect.x += 1;
        tRect.y += 1;
    }
    DrawTextMidLeftW(tRect, lStr, AppColor.text_light);

    // 右按钮文字
    tRect = rect;
    tRect.w -= 2;
    if (2 == state)
    {
        tRect.w += 1;
        tRect.y += 1;
    }
    DrawTextMidRightW(tRect, rStr, AppColor.text_light);
}

// 绘制普通标题栏
// 参数：区域，标题文本
void DrawNormalTitleBarW(rectst rect, const char *title)
{
    rectst tRect;

    tRect.x = rect.x + 2;
    tRect.y = rect.y + 2;
    tRect.w = rect.w - 4;
    tRect.h = rect.h - 4;

    DrawShadeRect(rect);
    DrawRoundBorder(rect);
    DrawTextMidLeftW(tRect, title, AppColor.text_light);
}

// 绘制普通标题栏
// 参数：区域，标题文本
void DrawNormalTitleBarA(rectst rect, const char *title)
{
    rectst tRect;

    tRect.x = rect.x + 2;
    tRect.y = rect.y + 2;
    tRect.w = rect.w - 4;
    tRect.h = rect.h - 4;

    DrawShadeRect(rect);
    DrawRoundBorder(rect);
    DrawTextMidLeftA(tRect, title, AppColor.text_light);
}
