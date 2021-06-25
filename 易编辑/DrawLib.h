/*
 * 绘图函数库头文件
 * 版权所有 (C) 2011-2012 eleqian
 * [6/4/2012]
 */

#ifndef __DRAWLIB_H__
#define __DRAWLIB_H__

#include "src/base.h"

// 返回颜色的RGB值
#define PIXEL888RED(pixel)    (uint8)(((pixel) >> 16) & 0xff)
#define PIXEL888GREEN(pixel)  (uint8)(((pixel) >> 8) & 0xff)
#define PIXEL888BLUE(pixel)   (uint8)((pixel) & 0xff)

// 由RGB值生成颜色
#define MAKERGB888(r, g, b) \
    (uint32)(((uint32)(r) << 16) | ((uint32)(g) << 8) | ((uint32)(b)))
#define MAKERGB565(r, g, b) \
    (uint16)((((uint32)(r) >> 3) << 11) | (((uint32)(g) >> 2) << 5) | (((uint32)(b) >> 3)))

// 转换颜色存储形式
#define RGB888TO565(c) \
    (uint16)((((uint32)(c) & 0x00f80000) >> 8) | (((uint32)(c) & 0x0000fc00) >> 5) | (((uint32)(c) & 0x000000f8) >> 3))
#define RGB565TO888(c) \
    (uint32)((((uint32)(c) & 0x0000f800) << 8) | (((uint32)(c) & 0x000007e0) << 5) | (((uint32)(c) & 0x0000001f) << 3))

// 定义12号字体的类型
#define MR_FONT_SIZE12 (MR_FONT_BIG + 1)

typedef struct
{
    uint8 type;      //颜色模式
    uint32 back_normal;   //背景色
    uint32 back_light;    //亮色
    uint32 back_deep;     //深色
    uint32 text_normal;   //文本色-深
    uint32 text_light;    //文本色-亮
    uint32 text_focus;    //焦点色
    uint32 text_disabled; //不可用色
} COLORSET;

extern COLORSET AppColor;   // 配色模式
extern int16 ScreenWidth;   // 屏幕宽度
extern int16 ScreenHeight;  // 屏幕高度
extern uint16 *ScreenBuf;   // 屏幕缓冲区

int32 DrawLib_Init(void);
int32 DrawLib_End(void);

int32 DrawLib_SetFont(uint16 font);
int32 DrawLib_SetColor(uint8 cType);
int32 DrawLib_LoadSkin(uint8 type);
int32 DrawLib_SkinName(uint8 type, char *name);

int32 RefreshTrigger(void);
int32 RefreshUnTrigger(void);
void RefreshRect(rectst fRect);
void RefreshScreen(void);
void ClearRect(rectst rect);
void ClearScreen(void);

int32 GetTextSizeW(const char *unistr, int32 *w, int32 *h);
int32 GetTextSizeW16(const char *unistr, int16 *w, int16 *h);
int32 GetScreenSize(int32 *w, int32 *h);
int32 GetScreenSize16(int16 *w, int16 *h);

void DrawHLine565(int16 x1, int16 x2, int16 y, uint16 color16);
void DrawHLine(int16 x1, int16 x2, int16 y, uint32 color);
void DrawHLineEx(int16 x1, int16 x2, int16 y, uint8 r, uint8 g, uint8 b);
void DrawVLine(int16 x, int16 y1, int16 y2, uint32 color);
void DrawVLineEx(int16 x1, int16 y1, int16 y2, uint8 r, uint8 g, uint8 b);
void DrawLine(int16 x1, int16 y1, int16 x2, int16 y2, uint32 color);
void DrawLineEx(int16 x1, int16 y1, int16 x2, int16 y2, uint8 r, uint8 g, uint8 b);

void DrawFillRectEx(int16 x, int16 y, int16 w, int16 h, uint32 dColor);
void DrawFillRect(rectst drawRect, uint32 dColor);
void DrawRoundBorderEx(int16 x, int16 y, int16 w, int16 h, uint32 ulFrame);
void DrawRoundBorder(rectst drawRect);
void DrawShadeRectEx(int16 x, int16 y, int16 w, int16 h, uint32 ulLight, uint32 ulDark);
void DrawShadeRect(rectst drawRect);

int32 DrawTextScreenW(const char *drawText, int16 x, int16 y);
void DrawTextLinesW(rectst rect, const char *drawText, uint32 ulColor);
void DrawTextMidW(rectst drawRect, const char *drawText, uint32 ulColor);
void DrawTextMidLeftW(rectst drawRect, const char *drawText, uint32 ulColor);
void DrawTextMidRightW(rectst rect, const char *drawText, uint32 ulColor);
int32 DrawTextExW(const char *drawText, int16 x, int16 y, rectst rect, uint32 ulColor, int32 flag);

int32 DrawTextScreenA(const char *drawText, int16 x, int16 y);
void DrawTextLinesA(rectst rect, const char *drawText, uint32 ulColor);
void DrawTextMidA(rectst rect, const char *drawText, uint32 ulColor);
void DrawTextMidLeftA(rectst rect, const char *drawText, uint32 ulColor);
void DrawTextMidRightA(rectst rect, const char *drawText, uint32 ulColor);
int32 DrawTextExA(const char *drawText, int16 x, int16 y, rectst rect, uint32 ulColor, int32 flag);

void DrawButtonW(rectst rect, const char *Tile, uint8 IsFocus, uint8 IsPress);
void DrawNormalToolBarW(rectst rect, const char *lStr, const char *rStr, uint8 state);
void DrawNormalTitleBarW(rectst rect, const char *title);
void DrawNormalTitleBarA(rectst rect, const char *title);

#endif  // __DRAWLIB_H__
