/*
 * 信息页显示
 * 版权所有 (C) 2011-2012 eleqian
 * [6/2/2012]
 */

#include "mrc_base.h"
#include "src/base.h"
#include "AppMain.h"
#include "InfoPage.h"
#include "KeyTimer.h"
#include "DrawLib.h"
#include "Functions.h"
#include "XString.h"

// 行信息
typedef struct LineInfo_st
{
    int32 index;  // 行序号
    char *start;  // 字符开始位置
    int32 len;    // 字符长度
    struct LineInfo_st *next;  // 下一行
} LINEINFO_ST; 

// 信息页数据
typedef struct TextInfoData_st
{
    char *title;      // 窗口标题
    char *content;    // 文件字符串
    char tbStrL[16];  // 工具栏左按钮文字
    char tbStrR[16];  // 工具栏右按钮文字
    int32 flag;       // 标志位
    uint16 height;    // 行高
    uint16 pagesize;  // 每页行数
    uint16 pagestart; // 页开始行数
    uint16 linenum;   // 总行数
    LINEINFO_ST *lineinfo;  // 排版的行信息
    INFOPAGE_CBF callback;  // 回调函数
} TEXTINFODATA, *PTEXTINFODATA;

static PTEXTINFODATA InfoData; // 本窗口数据

static rectst rectTitle, rectTool; // 标题栏，工具栏
static rectst rectText, rectScroll; // 文本框，滚动条
static uint16 ItemWidth; // 两个字宽度

// 添加新行信息
static LINEINFO_ST *NewLineInfo(LINEINFO_ST *lastline, char *start)
{
    LINEINFO_ST *newline;

    newline = (LINEINFO_ST *)malloc(sizeof(LINEINFO_ST));
    newline->index = lastline->index + 1;
    newline->start = start;
    lastline->next = newline;
    InfoData->linenum++;

    return newline;
}

// 排版
static void InfoPage_Composing(void)
{
    int32 w, h;
    char tmp[4] = {0};
    int32 i, word, wl;
    int32 lastspace, linewidth, maxwidth;
    char *pContent = InfoData->content;
    LINEINFO_ST *line;

    wl = 0;
    word = 0;
    linewidth = 0;
    lastspace = -1;
    maxwidth = rectText.w - 4;

    line = InfoData->lineinfo = (LINEINFO_ST*)malloc(sizeof(LINEINFO_ST));
    line->start = pContent;
    line->index = 0;

    for (i = 0; (pContent[i] || pContent[i + 1]); i += 2)
    {
        tmp[0] = pContent[i];
        tmp[1] = pContent[i + 1];

        if (0 == tmp[0])
        {
            if (' ' == tmp[1]) // 空格
            {
                lastspace = i;
                word = 1;
                wl = 0;
            }
            else if ('\n' == tmp[1]) // 换行
            {
                lastspace = -1;
                linewidth = 0;
                word = 1;
                line->len = pContent + i - line->start;
                line = NewLineInfo(line, pContent + i + 2);
                continue;
            }
        }
        else
        {
            word = 0;
        }

        GetTextSizeW(tmp, &w, &h);

        if (h > InfoData->height)
            InfoData->height = (uint16)h;

        if (word) 
            wl += w;

        linewidth += w;

        if (linewidth > maxwidth)
        {
            if (word && lastspace != -1 && lastspace != i)
            {
                line->len = pContent + lastspace + 2 - line->start;
                linewidth = wl;
            }
            else
            {
                line->len = pContent + i - line->start;
                linewidth = w;
            }

            line = NewLineInfo(line, line->start + line->len);
            lastspace = -1;
            word = 0;
        }
    }

    line->len = pContent + i - line->start;
    line->next = NULL;
    InfoData->linenum++;

    InfoData->height += 2; // 行间距
    InfoData->pagesize = (rectText.h - 4) / InfoData->height;
}

// 重置页面信息
static void InfoPage_Reset(void)
{
    LINEINFO_ST *line, *line1;

    if (InfoData->flag & INFOPAGE_FLAG_FREE_CONTENT)
        TRYFREE(InfoData->content);
    if (InfoData->flag & INFOPAGE_FLAG_FREE_TITLE)
        TRYFREE(InfoData->title);

    for (line = InfoData->lineinfo; NULL != line; )
    {
        line1 = line;
        line = line->next;
        free(line1);
    }

    InfoData->lineinfo = NULL;
    InfoData->linenum = 0;
    InfoData->height = 0;
    InfoData->pagestart = 0;
    InfoData->pagesize = 0;
    InfoData->flag = 0;
}

// 初始化
int32 InfoPage_Init(void)
{
    int16 scrw, scrh;
    uint16 itemH;
    int32 fw, fh;

    if (NULL != InfoData)
        InfoPage_End();

    GetScreenSize16(&scrw, &scrh); //获取屏幕尺寸信息
    GetTextSizeW("\x65\x87\x67\x2c", &fw, &fh); //"文本"
    itemH = (uint16)(fh + 4);
    ItemWidth = (uint16)(fw + 4);

    rectTitle.x = 0; rectTitle.y = 0; rectTitle.w = scrw; rectTitle.h = itemH;
    rectTool.x = 0; rectTool.y = scrh - itemH; rectTool.w = scrw; rectTool.h = itemH;
    rectText.x = 0; rectText.y = itemH + 1; rectText.w = scrw - 5; rectText.h = scrh - itemH * 2 - 2;
    rectScroll.x = scrw - 5; rectScroll.y = rectText.y; rectScroll.w = 5; rectScroll.h = rectText.h;

    InfoData = (TEXTINFODATA *)malloc(sizeof(TEXTINFODATA));
    memset(InfoData, 0, sizeof(TEXTINFODATA));

    return 0;
}

// 结束显示
int32 InfoPage_End(void)
{
    InfoPage_Reset();
    TRYFREE(InfoData);

    return 0;
}

// 绘制底部工具栏
// 参数：状态：0 - 普通，1 - 左软键，2 - 右软键，3 - 中键
static void InfoPage_DrawTool(int32 state, int32 refresh)
{
    if (InfoData->flag & INFOPAGE_FLAG_BUTTON_OK)
    {
        // 绘制左右按钮文字
        DrawNormalToolBarW(rectTool, InfoData->tbStrL, InfoData->tbStrR, (uint8)state);
    }
    else
    {
        // 只绘制右按钮文字
        DrawNormalToolBarW(rectTool, "\x0", InfoData->tbStrR, (uint8)state);
    }

    if (refresh)
        RefreshRect(rectTool);
}

// 绘制详细信息
int32 InfoPage_Draw(uint8 refresh)
{
    int32 i, x, y, to;
    uint8 linestr[128];
    int16 sclY, sclH;
    LINEINFO_ST *line;

    ClearScreen();

    DrawNormalTitleBarA(rectTitle, InfoData->title);
    InfoPage_DrawTool(0, 0);

    // 显示文本
    DrawRoundBorder(rectText);

    x = rectText.x + 2;
    y = rectText.y + 2;
    to = MIN(InfoData->pagestart + InfoData->pagesize, InfoData->linenum);

    // 查找显示首行信息
    for (line = InfoData->lineinfo; NULL != line; line = line->next)
    {
        if (line->index == InfoData->pagestart)
        {
            break;
        }
    }

    // 绘制各行文本
    for (i = InfoData->pagestart; i < to; i++)
    {
        if (line->len <= 0)
            continue;

        memcpy(linestr, line->start, line->len);
        linestr[line->len] = linestr[line->len + 1] = '\0';
        DrawTextExW((char*)linestr, (int16)x, (int16)y, rectText, AppColor.text_normal, 0);
        y += InfoData->height;
        line = line->next;
    }

    // 滚动条
    if (InfoData->linenum > InfoData->pagesize)
    {
        sclY = (int16)(rectScroll.y + 1 + (rectScroll.h - 2) * InfoData->pagestart / InfoData->linenum);
        sclH = (int16)((rectScroll.h - 2) * InfoData->pagesize / InfoData->linenum);
        DrawFillRectEx(rectScroll.x + 1, sclY, rectScroll.w - 1, sclH, AppColor.back_deep);
        DrawHLine(rectScroll.x + 2, rectScroll.x + rectScroll.w - 2, sclY - 1, AppColor.back_deep);
        DrawHLine(rectScroll.x + 2, rectScroll.x + rectScroll.w - 2, sclY + sclH, AppColor.back_deep);
    }

    if (refresh)
        RefreshScreen();

    return 0;
}

// 设置显示内容
int32 InfoPage_Show(char *title, char *content, int32 flag, INFOPAGE_CBF cb)
{
    InfoPage_Reset();

    InfoData->flag = flag;
    InfoData->title = title;
    InfoData->callback = cb;

    // 恢复默认按钮文本，确定 / 返回
    memcpy(InfoData->tbStrL, "\x78\x6e\x5b\x9a\x0\x0", 6);
    memcpy(InfoData->tbStrR, "\x8f\xd4\x56\xde\x0\x0", 6);

    if (flag & INFOPAGE_FLAG_CONTENT_GB)
    {
        /*int32 unisize = 0;
        uint16 *unistr = NULL;

        unistr = mrc_c2uVM(content, NULL, &unisize);
        InfoData->content = (char *)malloc(unisize);
        memcpy(InfoData->content, unistr, unisize);
        mrc_c2uVMfree(unistr, unisize);*/

        // 转换为UCS2BE
        InfoData->content = strc2u(content);

        // 释放原gb数据
        if (flag & INFOPAGE_FLAG_FREE_CONTENT)
        {
            TRYFREE(content);
        }

        // 保存unicode的内存需要在以后释放
        InfoData->flag |= INFOPAGE_FLAG_FREE_CONTENT;
    }
    else
    {
        InfoData->content = content;
    }

    InfoPage_Composing();

    SetAppState(APPSTATE_INFOPAGE, 1);

    return 0;
}

// 设置工具栏按钮文字
int32 InfoPage_SerToolBarText(const char *wStrL, const char *sStrR)
{
    wstrncpy(InfoData->tbStrL, wStrL, 14);
    wstrncpy(InfoData->tbStrR, sStrR, 14);

    InfoPage_Draw(1);

    return 0;
}

// 文本显示上下移动
static void InfoPage_LineUpDown(int32 kCode)
{
    int32 newstart;

    if (InfoData->pagesize >= InfoData->linenum)
        return;

    switch (kCode)
    {
    case MR_KEY_UP:
        if (InfoData->pagestart > 0)
            InfoData->pagestart--;
        break;
    case MR_KEY_DOWN:
        if (InfoData->pagestart + InfoData->pagesize < InfoData->linenum)
            InfoData->pagestart++;
        break;
    case MR_KEY_1:
    case MR_KEY_LEFT:
        newstart = InfoData->pagestart - InfoData->pagesize + 1;
        if (newstart < 0)
            InfoData->pagestart = 0;
        else
            InfoData->pagestart = (uint16)newstart;
        break;
    case MR_KEY_4:
    case MR_KEY_RIGHT:
        newstart = InfoData->pagestart + InfoData->pagesize - 1;
        if (newstart + InfoData->pagesize > InfoData->linenum)
            InfoData->pagestart = InfoData->linenum - InfoData->pagesize;
        else
            InfoData->pagestart = (uint16)newstart;
        break;
    case MR_KEY_3:
        InfoData->pagestart = 0;
        break;
    case MR_KEY_6:
        InfoData->pagestart = InfoData->linenum - InfoData->pagesize;
        break;
    }

    InfoPage_Draw(1);
}

// 事件处理
int32 InfoPage_Event(int32 type, int32 p1, int32 p2)
{
    static int32 lastY;

    switch (type)
    {
    case MR_KEY_PRESS:
        switch (p1)
        {
        case MR_KEY_SOFTLEFT:
            InfoPage_DrawTool(1, 1);
            break;
        case MR_KEY_SOFTRIGHT:
            InfoPage_DrawTool(2, 1);
            break;
        case MR_KEY_1:
        case MR_KEY_4:
        case MR_KEY_3:
        case MR_KEY_6:
        case MR_KEY_UP:
        case MR_KEY_DOWN:
        case MR_KEY_LEFT:
        case MR_KEY_RIGHT:
            KeyTimerStart(p1, InfoPage_LineUpDown);
            break; 
        case MR_KEY_SELECT:
            break;
        }
        break;
    case MR_KEY_RELEASE:
        switch(p1)
        {
        case MR_KEY_SOFTLEFT:
            InfoPage_DrawTool(0, 1);
            if (InfoData->flag & INFOPAGE_FLAG_BUTTON_OK)
            {
                if (NULL != InfoData->callback)
                {
                    SetAppState(APPSTATE_RETURN, 0);
                    InfoData->callback(1);
                }
                else
                {
                    SetAppState(APPSTATE_RETURN, 1);
                }
                InfoPage_Reset();
            }
            break;
        case MR_KEY_SOFTRIGHT:
            InfoPage_DrawTool(0, 1);
            if (NULL != InfoData->callback)
            {
                SetAppState(APPSTATE_RETURN, 0);
                InfoData->callback(1);
            }
            else
            {
                SetAppState(APPSTATE_RETURN, 1);
            }
            InfoPage_Reset();
            break;
        case MR_KEY_1:
        case MR_KEY_4:
        case MR_KEY_3:
        case MR_KEY_6:
        case MR_KEY_UP:
        case MR_KEY_DOWN:
        case MR_KEY_LEFT:
        case MR_KEY_RIGHT:
            KeyTimerStop();
            break;
        case MR_KEY_SELECT:
            break;
        }
        break;
    case MR_MOUSE_DOWN:
        lastY = p2;

        if (p2 > rectTool.y)
        {
            if (p1 < ItemWidth)
                InfoPage_Event(MR_KEY_PRESS, MR_KEY_SOFTLEFT, 0);
            else if (p1 > (int32)(rectTool.w - ItemWidth))
                InfoPage_Event(MR_KEY_PRESS, MR_KEY_SOFTRIGHT, 0);
        }
        else if (p2 > rectScroll.y && p2 < rectScroll.y + rectScroll.h /2)
        {
            if (p1 > rectScroll.x)
                InfoPage_Event(MR_KEY_PRESS, MR_KEY_UP, 0);
        }
        else if (p2 > rectScroll.y + rectScroll.h /2 && p2 < rectScroll.y + rectScroll.h)
        {
            if (p1 > rectScroll.x)
                InfoPage_Event(MR_KEY_PRESS, MR_KEY_DOWN, 0);
        }
        break;
    case MR_MOUSE_UP:
        KeyTimerStop();

        if (p2 > rectTool.y)
        {
            if (p1 < ItemWidth)
                InfoPage_Event(MR_KEY_RELEASE, MR_KEY_SOFTLEFT, 0);
            else if (p1 > (int32)(rectTool.w - ItemWidth))
                InfoPage_Event(MR_KEY_RELEASE, MR_KEY_SOFTRIGHT, 0);
        }
        break;
    case MR_MOUSE_MOVE:
        if (p2 - lastY > InfoData->height)
        {
            InfoPage_LineUpDown(MR_KEY_UP);
            lastY = p2 - InfoData->height;
        }
        else if (lastY - p2 > InfoData->height)
        {
            InfoPage_LineUpDown(MR_KEY_DOWN);
            lastY = p2 + InfoData->height;
        }
        break;
    default:
        break;
    }

    return 0;
}
