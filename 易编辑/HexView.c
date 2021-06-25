/*
 * Hex查看
 * 版权所有 (C) 2011-2012 eleqian
 * [6/21/2012]
 */

#include "src/base.h"
#include "src/android.h"
#include "src/graphics.h"
#include "src/mrc_exb.h"
#include "src/exb.h"
#include "mrc_base.h"
#include "AppMain.h"
#include "HexView.h"
#include "HexEdit.h"
#include "Menu.h"
#include "MainMenu.h"
#include "KeyTimer.h"
#include "Functions.h"
#include "DrawLib.h"


// 最大显示HEX字符行列数
#define MAX_HEX_VIEW_COL    48  // 这里每个HEX算一列
#define MAX_HEX_VIEW_LINE   32

// 字符数据
typedef struct
{
    uint8 *data;
    uint8 len;
    uint8 w;
    uint8 h;
} CHAR_BITS_ST;

// Hex显示页面信息结构体
typedef struct
{
    //uint16 Font;    // 字体大小
    uint16 CharW;     // 字符宽
    uint16 CharH;     // 字符高
    uint16 ColCount;  // 列数(每个字节算一列)
    uint16 LineCount; // 行数
    uint32 PageSize; // 每页字节数
    CHAR_BITS_ST CharBits[16];  // 0-9,A-F字符数据
} PAGEINFO_ST;

static PAGEINFO_ST PageInfo;       // Hex字符信息
static POINT_ST PosTable[MAX_HEX_VIEW_LINE][MAX_HEX_VIEW_COL];  // 各个Hex字符位置

static rectst rectMain, rectInfo;   // 主显示区域，信息栏
static rectst rectTitle, rectTool;  // 标题栏，工具栏
static rectst rectTCmd1, rectTCmd2; // 工具栏按钮
static rectst rectBtn1, rectBtn2;   // 翻页按钮

static uint8 IsMsgShowing = 0;   // 是否在显示信息
static uint8 InfoInitState = 0;  // 初始化状态

// Hex与数值转换表
const uint8 ArrInt2Hex[17] = "0123456789ABCDEF";
const uint8 ArrChar2Int[256] = 
{
    0, 0, 0, 0, 0, 0, 0, 0, /*  0- 7 */
    0, 0, 0, 0, 0, 0, 0, 0, /*  8-15 */
    0, 0, 0, 0, 0, 0, 0, 0, /* 16-23 */
    0, 0, 0, 0, 0, 0, 0, 0, /* 24-31 */
    0, 0, 0, 0, 0, 0, 0, 0, /* 32-39 */
    0, 0, 0, 0, 0, 0, 0, 0, /* 40-47 */
    0, 1, 2, 3, 4, 5, 6, 7, /* 48-55 */
    8, 9, 0, 0, 0, 0, 0, 0, /* 56-63 */
    0, 10,11,12,13,14,15,0, /* 64-71 */
    0, 0, 0, 0, 0, 0, 0, 0, /* 72-79 */
    0, 0, 0, 0, 0, 0, 0, 0, /* 80-87 */
    0, 0, 0, 0, 0, 0, 0, 0, /* 88-95 */
    0, 10,11,12,13,14,15,0, /* 96-.. */
    /* 省略部分为0 */
};

//格式化数据为Hex字符串
int32 Data2Hex(uint8 *data, int32 dataSize, uint8 *hexBuf, int32 bufSize)
{
    int32 i, convSize;

    memset(hexBuf, 0, bufSize);
    convSize = MIN(dataSize, bufSize / 2);

    for (i = 0; i < convSize; i++)
    {
        hexBuf[i * 2] = ArrInt2Hex[data[i] >> 4];
        hexBuf[i * 2 + 1] = ArrInt2Hex[data[i] & 0x0f];
    }

    return convSize;
}

//Hex字符串转换为数据
int32 Hex2Data(uint8 *hex, int32 hexSize, uint8 *dataBuf, int32 bufSize)
{
    int32 i, convSize;

    memset(dataBuf, 0, bufSize);
    convSize = MIN(hexSize / 2, bufSize);

    for (i = 0; i < convSize; i++)
    {
        dataBuf[i] = (ArrChar2Int[hex[i * 2]] << 4) + ArrChar2Int[hex[i * 2 + 1]];
    }

    return convSize;
}

/*---------------------------------------------------------------------------*/

static mr_datetime NowTime;    // 当前时间
static int32 TimeTimerHandle;  // 时间显示定时器
static int16 TimeStrMaxWidth;  // 时间字符串显示宽度

// 刷新时间
static void RefreshTime(int32 data)
{
    mr_datetime t_dt;

    getdatetime(&t_dt);
    if (t_dt.minute != NowTime.minute || t_dt.hour != NowTime.hour)
    {
        getdatetime(&NowTime);
        if (GetAppState() == APPSTATE_HEXVIEW || GetAppState() == APPSTATE_HEXEDIT)
        {
            Main_Draw(1);
        }
    }
}

// 开始显示时间
int32 StartShowTime(void)
{
    getdatetime(&NowTime);
    TimeTimerHandle = timercreate();
    timerstart(TimeTimerHandle, 500, 0, RefreshTime, 1);

    return 0;
}

// 结束时间显示
int32 StopShowTime(void)
{
    if (TimeTimerHandle != 0)
    {
        timerstop(TimeTimerHandle);
        timerdel(TimeTimerHandle);
    }

    return 0;
}

/*--------------------------------------------------------------------------------------------*/

// 转换压缩的字符点阵为点阵数组
static void MapHexChar(int32 index, uint8 *font)
{
    CHAR_BITS_ST *cdata;
    uint32 totalPoint;
    uint32 totalIndex;
    uint32 fontLen;
    uint8 *fontMap;
    uint8 temp;
    uint32 i, j;

    cdata = &PageInfo.CharBits[index];
    fontMap = cdata->data;
    fontLen = cdata->len;
    totalPoint = cdata->w * cdata->h;
    totalIndex = 0;

    for (i = 0; i < fontLen; i++)
    {
        temp = *(font + i);
        for (j = 0; j < 8; j++)
        {
            *(fontMap + totalIndex) = (temp & 0x80);  // ? 1 : 0;
            totalIndex++;

            if (totalIndex >= totalPoint)
                break;

            temp <<= 1;
        }
    }
}

// 释放字符点阵数据
static void HV_ReleaseCharTable(void)
{
    int32 i;

    for (i = 0; i < 16; i++)
    {
        TRYFREE(PageInfo.CharBits[i].data);
    }
}

//初始化各个Hex字符数据和位置
static int32 HV_InitCharTable(void)
{
    char *fname = NULL;
    uint8 *fdata = NULL;
    int32 flen, foffset;
    int16 mfw, charw2;
    int16 x, y;
    uint16 i, j;

    HV_ReleaseCharTable();

    switch (AppDatas.AppFont)
    {
    case MR_FONT_BIG:
        fname = "f2.bin";
        break;
    case MR_FONT_MEDIUM:
        fname = "f1.bin";
        break;
    case MR_FONT_SMALL:
        fname = "f0.bin";
        break;
    default:
        fname = "f1.bin";
    }

    // 读取字符数据
//    fdata = mrc_readFileFromMrp(fname, &flen, 0); //xldebug
    fdata = readFileFromAssets(fname, &flen); //xldebug
    if (NULL == fdata)
    {
        return -1;
    }

    foffset = 1;
    mfw = 0;

    // 分离各字符数据
    for (i = 0; i < 16; i++) 
    {
        PageInfo.CharBits[i].w =  *(fdata + foffset);
        PageInfo.CharBits[i].h = *fdata;
        PageInfo.CharBits[i].len = *(fdata + foffset + 1);
        PageInfo.CharBits[i].data = (uint8*)malloc(PageInfo.CharBits[i].w * PageInfo.CharBits[i].h);
        MapHexChar(i, (fdata + foffset + 2));
        foffset += PageInfo.CharBits[i].len + 2;

        if (PageInfo.CharBits[i].w > mfw) 
            mfw = PageInfo.CharBits[i].w;
    }

//    mrc_freeFileData(fdata, flen); //xldebug
free(fdata);
    // 计算页面信息
    charw2 = mfw * 2 + mfw / 2 + 1;  // 两个(一组)字符的宽度
    PageInfo.CharW = (uint16)mfw;
    PageInfo.CharH = (uint16)PageInfo.CharBits[0].h;

    PageInfo.ColCount = (rectMain.w - 6) / charw2;
    if (PageInfo.ColCount > MAX_HEX_VIEW_COL / 2)
        PageInfo.ColCount = MAX_HEX_VIEW_COL / 2;

    PageInfo.LineCount = (rectMain.h - 6) / (PageInfo.CharH + 1);
    if (PageInfo.LineCount > MAX_HEX_VIEW_LINE)
        PageInfo.LineCount = MAX_HEX_VIEW_LINE;

    PageInfo.PageSize = PageInfo.ColCount * PageInfo.LineCount;

    // 生成每个字符的位置信息

    // x坐标
    for (j = 0; j <= (PageInfo.ColCount * 2); j++)
    {
        x = (rectMain.x + 2 + charw2 * (j >> 1) + mfw / 4);
        if (j & 1)
            x += (mfw + 1);

        // 不用PageInfo.LineCount是因为会随信息行数改变，下同
        for (i = 0; i < MAX_HEX_VIEW_LINE; i++) 
        {
            PosTable[i][j].X = x;
        }
    }

    // y坐标
    for (i = 0; i < MAX_HEX_VIEW_LINE; i++)  
    {
        y = (rectMain.y + 3 + i * (PageInfo.CharH + 1));

        for (j = 0; j <= (PageInfo.ColCount * 2); j++)
        {
            PosTable[i][j].Y = y;
        }
    }

    return 0;
}

// Hex编辑初始化
int32 HV_Init(void)
{
    int32 ret;
    int32 fw, fh;
    uint16 scnWidth, scnHeight;
    uint16 cmdWidth, cmdHeight;
    uint16 pagebtnw; 

    if (AppDatas.PageButton)
        pagebtnw = 18;
    else
        pagebtnw = 0;

    GetTextSizeW("\x65\x87\x67\x2c\x0\x0", &fw, &fh); //"文本"

    // 设定宽高
    scnWidth = (uint16)AppDatas.ScnWidth;
    scnHeight = (uint16)AppDatas.ScnHeight;
    cmdWidth = (uint16)(fw + 8);
    cmdHeight = (uint16)(fh + 4);

    // 设定区域信息

    rectTitle.x = 0; rectTitle.y = 0; 
    rectTitle.w = scnWidth; rectTitle.h = cmdHeight;
    rectInfo.x = 0; rectInfo.w = scnWidth;
    rectInfo.h = (uint16)(fh + 1) * AppDatas.InfoCount + 3; 
    rectInfo.y = scnHeight - cmdHeight - rectInfo.h - 1;
    rectMain.x = 0; rectMain.y = rectTitle.h + 1; 
    rectMain.w = scnWidth - pagebtnw; rectMain.h = rectInfo.y - rectMain.y - 1;
    rectTool.x = 0; rectTool.w = scnWidth; 
    rectTool.h = cmdHeight; rectTool.y = scnHeight - rectTool.h;

    rectTCmd1.x = 0; rectTCmd1.y = rectTool.y; 
    rectTCmd1.w = cmdWidth; rectTCmd1.h = rectTool.h;
    rectTCmd2.x = scnWidth - cmdWidth; rectTCmd2.y = rectTool.y;
    rectTCmd2.w = cmdWidth; rectTCmd2.h = rectTool.h;

    rectBtn1.x = rectMain.x + rectMain.w + 1; rectBtn1.y = rectMain.y;
    rectBtn1.w = pagebtnw - 1; rectBtn1.h = rectMain.h / 2;
    rectBtn2.x = rectMain.x + rectMain.w + 1; rectBtn2.y = rectMain.y + rectMain.h / 2;
    rectBtn2.w = pagebtnw - 1; rectBtn2.h = rectMain.h / 2;

    if (!AppDatas.PageButton)
    {
        rectBtn1.w = 0;
        rectBtn2.w = 0;
    }

    ret = HV_InitCharTable();

    InfoInitState = 0;
    GetTextSizeW16("\x0\x30\x0\x30\x0\x3a\x0\x30\x0\x30\x0\x0", &TimeStrMaxWidth, NULL);  // 00:00

    return ret;
}

// Hex编辑结束
int32 HV_End(void)
{
    HV_ReleaseCharTable();

    return 0;
}

/*---------------------------------------------------------------------------*/

// Hex字符绘制
static void HV_DrawHexChar(char ch, uint32 x0, uint32 y0, uint16 color)
{
    uint32 x, y, x1, y1, x_add;
    uint16 *dest, *dest_x0;
    uint8 *pbitmap;
    CHAR_BITS_ST *cdata;

    x_add = AppDatas.ScnWidth;
    dest_x0 = AppDatas.ScnBuf + y0 * AppDatas.ScnWidth + x0;
    cdata = PageInfo.CharBits + ArrChar2Int[(uint8)ch];
    pbitmap = cdata->data;
    x1 = x0 + cdata->w;
    y1 = y0 + cdata->h;

    for (y = y0; y < y1; y++)
    {
        dest = dest_x0;
        for (x = x0; x < x1; x++)
        {
            if (0 != *pbitmap)
                *dest = color;
            pbitmap++;
            dest++;
        }
        dest_x0 += x_add;
    }
	//char text[30];
	//sprintf(text,"%x",ch);
	//mrc_drawText(text,x0,y0,200,40,50,0,1);
	//vm_drawChar(ch,x0,y0,0xff202020,1);
			//vm_(((uint16)ch)<<8, x0, y0, color, 1);
			//log_i("绘制hex字符",x0);

}

// 绘制字符焦点
// 参数：屏幕位置，字符，是否焦点
static void HV_DrawFocusChar(POINT_ST dPos, uint8 dChar, uint8 IsFocus)
{
    rectst tRect;
    uint16 color;

    // 转换颜色
    color = RGB888TO565((IsFocus > 0) ? AppColor.text_focus : AppColor.text_normal);

    //清除以前的字符
    tRect.x = dPos.X; tRect.y = dPos.Y; tRect.w = PageInfo.CharW; tRect.h = PageInfo.CharH;
    ClearRect(tRect);

    //绘制字符
    HV_DrawHexChar((char)dChar, dPos.X, dPos.Y, color);
}

// 绘制Hex焦点
// 参数：位置，焦点模式，是否刷新
void HV_DrawFocus(POINT_ST dPos, uint8 focusType, uint8 refresh)
{
    rectst tRect;
    int16 x, y;
    uint8 *hexbuf;
    uint32 cokor;

    if (AppDatas.HDataCur->FileSize <= 0)
        return;

    x = dPos.X;
    y = dPos.Y;
    hexbuf = &AppDatas.HDataCur->HexBuffer[(AppDatas.HDataCur->DataShowBegin + y * PageInfo.ColCount) * 2 + x];

    if (focusType & 0x4)
    {
        // 绘制两个字符焦点
        HV_DrawFocusChar(PosTable[y][x - (x & 1)], *(hexbuf - (x & 1)), 1);
        HV_DrawFocusChar(PosTable[y][x - (x & 1) + 1], *(hexbuf - (x & 1) + 1), 1);
    }
    else if (0 == focusType)
    {
        // 绘制两个字符无焦点
        HV_DrawFocusChar(PosTable[y][x - (x & 1)], *(hexbuf - (x & 1)), 0);
        HV_DrawFocusChar(PosTable[y][x - (x & 1) + 1], *(hexbuf - (x & 1) + 1), 0);
    }
    else
    {
       // 字符1
        HV_DrawFocusChar(PosTable[y][x], *hexbuf, focusType & 0x1);

        // 字符2
        if (0 == (x & 1))
            HV_DrawFocusChar(PosTable[y][x + 1], *(hexbuf + 1), focusType & 0x2);
    }
 
    // 方框
    tRect.x = PosTable[y][x - (x & 1)].X - 2;
    tRect.y = PosTable[y][x - (x & 1)].Y - 1;
    if (PageInfo.CharW >= 8)
        tRect.w = PageInfo.CharW * 2 + 5;
    else
        tRect.w = PageInfo.CharW * 2 + PageInfo.CharW / 2 + 1;
    tRect.h = PageInfo.CharH + 2;
    cokor = (0 == focusType) ? AppColor.back_normal : AppColor.text_focus;
    DrawRoundBorderEx(tRect.x, tRect.y, tRect.w, tRect.h, cokor);

    if (refresh)
        RefreshRect(tRect);

    // 进度条
    tRect.x = rectMain.x + rectMain.w - 3;
    tRect.y = rectMain.y + 1;
    tRect.w = 2;
    tRect.h = rectMain.h - 2;
    DrawFillRect(tRect, AppColor.back_normal);

    DrawFillRectEx(tRect.x, tRect.y, tRect.w, (int16)((rectMain.h - 2) * 
        (AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataBufOffset + 1) /
        AppDatas.HDataCur->FileSize), AppColor.back_deep);

    if (refresh)
        RefreshRect(tRect);
}

// 显示Hex内容
void HV_DrawHexAll(uint8 showFocus, uint8 refresh)
{
    int32 i, j;
    int32 offset, maxcol;
    uint16 color;
    uint8 *hexbuf;
    POINT_ST *pos;

    color = RGB888TO565(AppColor.text_normal);

    ClearRect(rectMain);

    // 循环绘制所有字符
    for (i = 0; i <= PageInfo.LineCount; i++)
    {
        offset = AppDatas.HDataCur->DataShowBegin + i * PageInfo.ColCount;
        maxcol = AppDatas.HDataCur->DataBufUsed - offset;
        if (maxcol > PageInfo.ColCount)
            maxcol = PageInfo.ColCount;

        // 因为每2个HEX字符为1字节
        offset <<= 1;
        maxcol <<= 1;

        hexbuf = AppDatas.HDataCur->HexBuffer + offset;
        pos = PosTable[i];

        for (j = 0; j < maxcol; j++)
        {
            HV_DrawHexChar(*hexbuf, pos[j].X, pos[j].Y, color);
            hexbuf++;
        }
    }

    if (showFocus)
    {
        if (0 == AppDatas.HDataCur->CurPos.X % 2 && APPSTATE_HEXEDIT != GetAppState())
            HV_DrawFocus(AppDatas.HDataCur->CurPos, 3, 0);
        else
            HV_DrawFocus(AppDatas.HDataCur->CurPos, 1, 0);
    }

    DrawRoundBorder(rectMain);

    // 恢复被覆盖的间隙
    DrawHLine(rectMain.x + 1, rectMain.x + rectMain.w - 2, rectMain.y + rectMain.h - 2, AppColor.back_normal);
    DrawHLine(rectMain.x, rectMain.x + rectMain.w - 2, rectMain.y + rectMain.h, AppColor.back_normal);

    if (refresh)
        RefreshRect(rectMain);
}

// 绘制主界面标题栏
void HV_DrawTitle(uint8 Refresh)
{
    rectst tRect;
    char tmpStr[8];
    char tmpStrw[16];
    int16 strw;

    DrawShadeRect(rectTitle);
    DrawRoundBorder(rectTitle);

    // 显示窗口序号
    sprintf(tmpStr, "[%d]-", AppDatas.HIndex + 1);
    Asc2Uni(tmpStr, tmpStrw, MAX_FILENAME_LEN_W);
    GetTextSizeW16(tmpStrw, &strw, NULL);
    tRect.x = rectTitle.x; tRect.y = rectTitle.y;
    tRect.h = rectTitle.h; tRect.w = strw;
    DrawTextMidLeftW(tRect, tmpStrw, AppColor.text_light);

    // 显示窗口标题
    tRect.x = rectTitle.x + strw; tRect.y = rectTitle.y;
    tRect.h = rectTitle.h; tRect.w = rectTitle.w - TimeStrMaxWidth - strw - 4;
    if (AppDatas.HDataCur->FileSize > 0)
    {
        DrawTextMidLeftW(tRect, AppDatas.HDataCur->FileNameW, AppColor.text_light);
    }
    else
    {
        // 易编辑
        DrawTextMidLeftW(tRect, "\x66\x13\x7f\x16\x8f\x91\x0\x0", AppColor.text_light);
    }

    // 显示时间
    tRect.x = rectTitle.x; tRect.y = rectTitle.y;
    tRect.h = rectTitle.h; tRect.w = rectTitle.w - 2;
    sprintf(tmpStr, "%2d:%02d", NowTime.hour, NowTime.minute);
    Asc2Uni(tmpStr, tmpStrw, MAX_FILENAME_LEN_W);
    DrawTextMidRightW(tRect, tmpStrw, AppColor.text_light);
}

// 绘制底部工具栏
// 参数：状态：0 - 普通，1 - 左软键，2 - 右软键
void HV_DrawToolBar(uint8 state, uint8 refresh)
{
    // 菜单 / 切换
    DrawNormalToolBarW(rectTool, "\x83\xdc\x53\x55\x0\x0", "\x52\x07\x63\x62\x0\x0", state);

    if (AppDatas.HDataCur->FileSize > 0)
    {
        char tOffset[16];
        char wstr[32];

        sprintf(tOffset, "[%d]", AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataBufOffset);
        Asc2Uni(tOffset, wstr, 32);
        DrawTextMidW(rectTool, wstr, AppColor.text_focus);
    }

    if (refresh)
        RefreshRect(rectTool);
}

// 绘制底部工具栏
// 参数：状态：0 - 普通，1 - 左软键，2 - 右软键
void HE_DrawToolBar(uint8 state, uint8 refresh)
{
    // 确定 / 取消
    DrawNormalToolBarW(rectTool, "\x78\x6e\x5b\x9a\x0\x0", "\x53\xd6\x6d\x88\x0\x0", state);

    if (AppDatas.HDataCur->FileSize > 0)
    {
        char tOffset[16];
        char wstr[32];

        sprintf(tOffset, "[%d]", AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataBufOffset);
        Asc2Uni(tOffset, wstr, 32);
        DrawTextMidW(rectTool, wstr, AppColor.text_focus);
    }

    if (refresh)
        RefreshRect(rectTool);
}

// 绘制翻页按钮
void HV_DrawPageButton(uint8 index, uint8 state, uint8 refresh)
{
    if (1 & index)
    {
        DrawButtonW(rectBtn1, "\x21\x91\x0\x0", 0, state);
        if (refresh)
            RefreshRect(rectBtn1);
    }

    if (2 & index)
    {
        DrawButtonW(rectBtn2, "\x21\x93\x0\x0", 0, 1 - state);
        if (refresh)
            RefreshRect(rectBtn2);
    }
}

// 显示当前位置数据信息
void HV_DrawInfo(uint8 refresh)
{
#define MAX_INFO_COUNT 10  // 最大信息种类数

    static const char infoTitles[MAX_INFO_COUNT + 1][16] =  // 信息标题
    {
        "\x0",
        "\x0\x2b\x0\x38\x4f\x4d\x0\x3a\x0",
        "\x0\xb1\x0\x38\x4f\x4d\x0\x3a\x0",
        "\x0\x2b\x0\x31\x0\x36\x4f\x4d\x0\x3a\x0",
        "\x0\xb1\x0\x31\x0\x36\x4f\x4d\x0\x3a\x0",
        "\x0\x2b\x0\x33\x0\x32\x4f\x4d\x0\x3a\x0",
        "\x0\xb1\x0\x33\x0\x32\x4f\x4d\x0\x3a\x0",
        "\x0\x55\x0\x43\x0\x53\x0\x32\x0\x42\x0\x45\x0\x3a\x0",
        "\x0\x55\x0\x43\x0\x53\x0\x32\x0\x4c\x0\x45\x0\x3a\x0",
        "\x0\x47\x0\x42\x0\x32\x0\x33\x0\x31\x0\x32\x0\x3a\x0",
        "\x0\x55\x0\x54\x0\x46\x0\x2d\x0\x38\x0\x3a\x0"
    };

    static char infoBuffers[MAX_INFO_COUNT][48];  // 信息内容缓冲区
    static char uniInfoStr[48];
    static int16 InfoTitleW = 0;
    static int16 InfoTitleH = 0; 

    uint8 textCodes[MAX_INFO_COUNT] = {0};
    uint8 titleIndexs[MAX_INFO_COUNT] = {0};
    uint32 infoType;
    int16 infoCount;
    int32 infoIndex;
    uint8 *readpos;
    uint32 dataValue;
    int32 i;

    // 预先初始化一些信息，为了加快显示速度
    if (InfoInitState == 0)
    {
        int32 w, h;

        InfoTitleW = 0;
        InfoTitleH = 0; 

        for (i = 0; i < MAX_INFO_COUNT; i++)
        {
            GetTextSizeW(infoTitles[i], &w, &h);
            if (w > InfoTitleW)
                InfoTitleW = (int16)w;
            if (h > InfoTitleH)
                InfoTitleH = (int16)h;
        }

        InfoInitState = 1;
    }

    // 不能显示信息
    if (AppDatas.HDataCur->FileSize <= 0)
    {
        rectst tRect;
        //uint32 mem_remain;

        tRect.x = rectInfo.x + 2;
        tRect.y = rectInfo.y + 2;
        tRect.w = rectInfo.w - 4;
        tRect.h = rectInfo.h - 4;

        //mem_remain = mrc_getMemoryRemain();
        /*sprintf(infoBuffers[0], "请从菜单中打开文件。\n内存剩余: %uByte", mem_remain);*/
      //  sprintf(infoBuffers[0], "请从菜单中打开文件。");
        sprintf(infoBuffers[0], "\xc7\xeb\xb4\xd3\xb2\xcb\xb5\xa5\xd6\xd0\xb4\xf2\xbf\xaa\xce\xc4\xbc\xfe\xa1\xa3");
        ClearRect(rectInfo);
        DrawTextLinesA(tRect, infoBuffers[0], AppColor.text_normal);
        DrawRoundBorder(rectInfo);

        if (refresh)
            RefreshRect(rectInfo);

        return;
    }
    else if (AppDatas.InfoType == 0 || AppDatas.InfoCount > MAX_INFO_COUNT)
    {
        ClearRect(rectInfo);
        DrawRoundBorder(rectInfo);  // 边框

        if (refresh)
            RefreshRect(rectInfo);

        return;
    }

    readpos = AppDatas.HDataCur->DataBuffer + AppDatas.HDataCur->DataBufOffset;
    infoType = AppDatas.InfoType;
    infoCount = AppDatas.InfoCount;
    infoIndex = 0;

    memset(infoBuffers, 0, sizeof(infoBuffers));
// XL 显示文本
    if ((infoType & VIEWTYPE_MASK_UINT8) && infoIndex < infoCount) //uint8
    {
        dataValue = *readpos;
        sprintf(infoBuffers[infoIndex], "%d", dataValue); 
        textCodes[infoIndex] = 0;
        titleIndexs[infoIndex] = 1;
        infoIndex++;
    }

    if ((infoType & VIEWTYPE_MASK_INT8) && infoIndex < infoCount) //int8
    {
        dataValue = *readpos;
        sprintf(infoBuffers[infoIndex], "%d", (int8)dataValue); 
        textCodes[infoIndex] = 0;
        titleIndexs[infoIndex] = 2;
        infoIndex++;
    }

    if ((infoType & VIEWTYPE_MASK_UINT16) && infoIndex < infoCount) //uint16
    {
        if (0 == AppDatas.BigEndian)
            dataValue = readLittleEndianUint16(readpos);
        else
            dataValue = readBigEndianUint16(readpos);
        sprintf(infoBuffers[infoIndex], "%d", dataValue); 
        textCodes[infoIndex] = 0;
        titleIndexs[infoIndex] = 3;
        infoIndex++;
    }

    if ((infoType & VIEWTYPE_MASK_INT16) && infoIndex < infoCount) //int16
    {
        if (0 == AppDatas.BigEndian)
            dataValue = readLittleEndianUint16(readpos);
        else
            dataValue = readBigEndianUint16(readpos);
        sprintf(infoBuffers[infoIndex], "%d", (int16)dataValue); 
        textCodes[infoIndex] = 0;
        titleIndexs[infoIndex] = 4;
        infoIndex++;
    }

    if ((infoType & VIEWTYPE_MASK_UINT32) && infoIndex < infoCount) //uint32
    {
        if (0 == AppDatas.BigEndian)
            dataValue = readLittleEndianUint32(readpos);
        else
            dataValue = readBigEndianUint32(readpos);
        sprintf(infoBuffers[infoIndex], "%u", dataValue); 
        textCodes[infoIndex] = 0;
        titleIndexs[infoIndex] = 5;
        infoIndex++;
    }

    if ((infoType & VIEWTYPE_MASK_INT32) && infoIndex < infoCount) //int32
    {
        if (0 == AppDatas.BigEndian)
            dataValue = readLittleEndianUint32(readpos);
        else
            dataValue = readBigEndianUint32(readpos);
        sprintf(infoBuffers[infoIndex], "%d", (int32)dataValue); 
        textCodes[infoIndex] = 0;
        titleIndexs[infoIndex] = 6;
        infoIndex++;
    }

    if ((infoType & VIEWTYPE_MASK_UCS2BE) && infoIndex < infoCount) //Unicode-B
    {
        memcpy(infoBuffers[infoIndex], readpos, 32);
        textCodes[infoIndex] = 1;
        titleIndexs[infoIndex] = 7;
        infoIndex++;
    }

    if ((infoType & VIEWTYPE_MASK_UCS2LE) && infoIndex < infoCount) //Unicode-L
    {
        memcpy(infoBuffers[infoIndex], readpos, 32);
        SwapBytes((uint8*)infoBuffers[infoIndex], 32);
        textCodes[infoIndex] = 1;
        titleIndexs[infoIndex] = 8;
        infoIndex++;
    }

    if ((infoType & VIEWTYPE_MASK_GB2312) && infoIndex < infoCount) //GB2312
    {
		int strsize=24;
        char tempStr[24];
        
        memcpy(tempStr, readpos, strsize-2);
        tempStr[strsize-1] = tempStr[strsize-2] = '\0';
        GBToUni(tempStr, infoBuffers[infoIndex], 48);

        textCodes[infoIndex] = 1;
        titleIndexs[infoIndex] = 9;
        infoIndex++;
    }

    if ((infoType & VIEWTYPE_MASK_UTF8) && infoIndex < infoCount) //UTF-8
    {
		int utfsize=24;
        char tempStr[24];

        memcpy(tempStr, readpos, utfsize-2);
        tempStr[utfsize-2] = '\0';
        UTF8ToUni(tempStr, infoBuffers[infoIndex], 48);
        textCodes[infoIndex] = 1;
        titleIndexs[infoIndex] = 10;
        infoIndex++;
    }

    {
	    rectst trect, irect;
	
	    trect.x = rectInfo.x + 1;
	    trect.w = InfoTitleW + 2;
	    trect.h = (rectInfo.h - 2) / infoCount;
	    trect.y = rectInfo.y + 1;
	    irect.x = rectInfo.x + InfoTitleW + 10;
	    irect.w = rectInfo.w - InfoTitleW - 10;
	    irect.y = trect.y;
	    irect.h = trect.h;

	    ClearRect(rectInfo);

	    // 显示每条信息
	    for (i = 0; i < infoCount; i++)
	    {
	        DrawTextMidRightW(trect, infoTitles[titleIndexs[i]], AppColor.text_normal);
	        if (textCodes[i] == 0)
	        {
	            //DrawTextMidLeftA(irect, infoBuffers[i], AppColor.text_normal);
	            Asc2Uni(infoBuffers[i], uniInfoStr, sizeof(uniInfoStr));
	            DrawTextMidLeftW(irect, uniInfoStr, AppColor.text_normal);
	        }
	        else
	        {
	            DrawTextMidLeftW(irect, infoBuffers[i], AppColor.text_normal);
	        }

	        trect.y += trect.h;
	        irect.y = trect.y;
	    }

	    DrawRoundBorder(rectInfo);
    }

    if (refresh)
        RefreshRect(rectInfo);
}

// 重绘界面
int32 HV_Draw(uint8 refresh)
{
    HV_DrawTitle(0);
    HV_DrawHexAll(1, 0);
    HV_DrawInfo(0);
    HV_DrawToolBar(0, 0);
    HV_DrawPageButton(3, 0, 0);

    if (refresh)
        RefreshScreen();

    return 0;
}

// 信息显示定时器回调
static void HV_MsgTimerCb(int32 data)
{
    HV_ShowMsgA(NULL, 1);
}

// 显示提示信息
int32 HV_ShowMsgA(char *sText, uint8 fefresh)
{
    static int32 MsgShowTimer = 0;
    rectst tRect;

    if (AppInitState != 0 || GetAppState() != APPSTATE_HEXVIEW)
        return - 1;

    // 为NULL时取消显示内容
    if (NULL == sText)
    {
        IsMsgShowing = 0;
        HV_DrawInfo(fefresh);

        // 停止信息显示定时器
        if (0 != MsgShowTimer)
        {
            timerdel(MsgShowTimer);
            MsgShowTimer = 0;
        }

        return 0;
    }

    IsMsgShowing = 1;

    if (0 == MsgShowTimer)
    {
        // 启动信息显示定时器，过时自动不显示
        MsgShowTimer = timercreate();
        timerstart(MsgShowTimer, 3000, 0, HV_MsgTimerCb, 0);
    }
    else
    {
        // 重设定时器
        timersettime(MsgShowTimer, 3000);
    }

    tRect.x = rectInfo.x + 2;
    tRect.y = rectInfo.y + 2;
    tRect.w = rectInfo.w - 4;
    tRect.h = rectInfo.h - 4;

    ClearRect(rectInfo);
    DrawTextLinesA(tRect, sText, AppColor.text_focus);
    DrawRoundBorder(rectInfo); //边框

    if (fefresh)
        RefreshRect(rectInfo);

    return 0;
}

/*---------------------------------------------------------------------------*/

// 菜单刷新背景回调
static void HV_MenuCallback(int32 type)
{
    if (MENU_CALLBACK_CANCLE == type)
    {
        // 什么也不需要做
    }
    else
    {
        uint8 refresh = (uint8)type;

        HV_DrawTitle(refresh);
        HV_DrawHexAll(1, refresh);
        HV_DrawInfo(refresh);
        //DrawToolBar(0, 0, refresh);
        HV_DrawPageButton(3, 0, refresh);
    }
}

// 显示主菜单
void HV_ShowMenu(void)
{
    if (HV_IsFileOpen())
    {
        MainMenu_SetEnabled(1, 0, 0, 1);
        MainMenu_SetEnabled(2, 1, 0, 0);
        MainMenu_SetEnabled(2, 2, 0, 0);
        MainMenu_SetEnabled(2, 3, 0, 0);
        MainMenu_SetEnabled(2, 4, 0, 1);
        MainMenu_SetEnabled(2, 5, 0, 1);
    }
    else
    {
        MainMenu_SetEnabled(1, 0, 0, 0);
        MainMenu_SetEnabled(2, 1, 0, 1);
        MainMenu_SetEnabled(2, 2, 0, 1);
        MainMenu_SetEnabled(2, 3, 0, 1);
        MainMenu_SetEnabled(2, 4, 0, 0);
        MainMenu_SetEnabled(2, 5, 0, 0);
    }

    Menu_Show(AppDatas.MainMenu, HV_MenuCallback, rectMain.x, rectMain.y + rectMain.h + rectInfo.h,
        (AppDatas.MenuIndex ? MENU_SHOW_FLAG_INDEX : 0));
}

// 显示查找菜单
void HV_ShowMenuFind(void)
{
    if (HV_IsFileOpen())
    {
        if (0 != AppDatas.PopMenu)
        {
            PMENU_LINK pm;

            pm = Menu_GetByIndex(AppDatas.MainMenu, 1);;
            pm = Menu_GetByIndex(pm, 1);
            Menu_Show(pm, HV_MenuCallback, rectMain.x, rectMain.y + rectMain.h, 
                (AppDatas.MenuIndex ? MENU_SHOW_FLAG_INDEX : 0));
        }
        else
        {
            M_FindNext(0);
        }
    }
}

// 打开替换菜单
void HV_ShowMenuReplace(void)
{
    if (HV_IsFileOpen())
    {
        if (0 != AppDatas.PopMenu)
        {
            PMENU_LINK pm;

            pm = Menu_GetByIndex(AppDatas.MainMenu, 1);;
            pm = Menu_GetByIndex(pm, 2);
            Menu_Show(pm, HV_MenuCallback, rectMain.x, rectMain.y + rectMain.h, 
                (AppDatas.MenuIndex ? MENU_SHOW_FLAG_INDEX : 0));
        }
        else
        {
            M_WriteNext(0);
        }
    }
}

// 打开比较菜单
void HV_ShowMenuCompare(void)
{
    if (HV_IsFileOpen())
    {
        if (0 != AppDatas.PopMenu)
        {
            PMENU_LINK pm;

            pm = Menu_GetByIndex(AppDatas.MainMenu, 1);;
            pm = Menu_GetByIndex(pm, 4);
            Menu_Show(pm, HV_MenuCallback, rectMain.x, rectMain.y + rectMain.h, 
                (AppDatas.MenuIndex ? MENU_SHOW_FLAG_INDEX : 0));
        }
        else
        {
            M_CompareNext(0);
        }
    }
}

/*---------------------------------------------------------------------------*/

// 取得文件大小
int32 HV_GetFileSize(void)
{
    return AppDatas.HDataCur->FileSize;
}

// 取得开始显示位置
int32 HV_GetFileShowOffset(void)
{
    return AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataShowBegin;
}

// 取得当前文件偏移
int32 HV_GetFileOffset(void)
{
    return AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataBufOffset;
}

// 取得当前数据缓冲区偏移
int32 HV_GetDataOffset(void)
{
    return AppDatas.HDataCur->DataBufOffset;
}

// 取得当前光标位置
POINT_ST HV_GetFocusPos(void)
{
    return AppDatas.HDataCur->CurPos;
}

// 文件是否打开
int32 HV_IsFileOpen(void)
{
    return ('\0' != AppDatas.HDataCur->FileNameA[0]);
}

/*---------------------------------------------------------------------------*/

// 切换显示窗口
int32 HV_SwitchWindow(int32 index)
{
    if (index == -1)
    {
        if (0 == AppDatas.HIndex)
            AppDatas.HIndex = 1;
        else
            AppDatas.HIndex = 0;
    }
    else
    {
        if (index >= 0 && index <= 1)
        {
            AppDatas.HIndex = index;
        }
    }

    AppDatas.HDataCur = &AppDatas.HDatas[AppDatas.HIndex];

    return 0;
}

// 关闭文件
int32 HV_CloseFile(void)
{
    TRYFREE(AppDatas.HDataCur->DataBuffer);
    TRYFREE(AppDatas.HDataCur->HexBuffer);

    AppDatas.HDataCur->FilePath[0] = '\0';
    AppDatas.HDataCur->FileNameA[0] = '\0';
    AppDatas.HDataCur->FileNameW[0] = '\0';
    AppDatas.HDataCur->FileSize = 0;
    AppDatas.HDataCur->FileReadBegin = 0;
    AppDatas.HDataCur->DataBufUsed = 0;
    AppDatas.HDataCur->DataBufOffset = 0;
    AppDatas.HDataCur->DataShowBegin = 0;
    AppDatas.HDataCur->CurPos.X = 0;
    AppDatas.HDataCur->CurPos.Y = 0;

    Main_Draw(1);

    return 0;
}

// 打开文件
int32 HV_OpenFile(const char *dir, const char *name)
{
    if (NULL == dir || NULL == name)
        return -1;
LOGI("打开文件");
    // 获取文件大小
  //  AppDatas.HDataCur->FileSize = FileLenInPath(dir, name);
      AppDatas.HDataCur->FileSize = app_getlen(name);
	LOGI("获取文件大小",AppDatas.HDataCur->FileSize);
    if (AppDatas.HDataCur->FileSize <= 0)
    {
        HV_CloseFile();
        HV_ShowMsgA("打开文件失败！", 1);
        return -1;
    }
LOGI("申请数据缓存");
    // 申请数据缓冲区内存
    if (NULL == AppDatas.HDataCur->DataBuffer)
    {
        AppDatas.HDataCur->DataBuffer = (uint8*)malloc(DATA_BUFFER_SIZE + 32); //加大点避免内存越界
        if (NULL == AppDatas.HDataCur->DataBuffer)
        {
            HV_ShowMsgA("打开文件失败，内存不足！", 1);
            return -1;
        }
    }
LOGI("申请hex缓存");
    // 申请HEX字符缓冲区内存
    if (NULL == AppDatas.HDataCur->HexBuffer)
    {
        AppDatas.HDataCur->HexBuffer = (uint8*)malloc(HEX_BUFFER_SIZE + 64);
        if (NULL == AppDatas.HDataCur->HexBuffer)
        {
            HV_ShowMsgA("打开文件失败，内存不足！", 1);
            return -1;
        }
    }

    memset(AppDatas.HDataCur->DataBuffer, 0, DATA_BUFFER_SIZE + 32);
    memset(AppDatas.HDataCur->HexBuffer, 0, HEX_BUFFER_SIZE + 64);
LOGI("记录路径");
    // 记录路径
    // 可能在调用时直接传入，所以指针不同才复制
    if (AppDatas.HDataCur->FilePath != dir)
        strcpy(AppDatas.HDataCur->FilePath, dir);
    if (AppDatas.HDataCur->FileNameA != name)
        strcpy(AppDatas.HDataCur->FileNameA, name);
    GBToUni(name, AppDatas.HDataCur->FileNameW, MAX_FILENAME_LEN_W);
LOGI("记录历史");
    // 记录历史
 //   sprintf(AppDatas.Recent, "%s%s", dir, name);
    sprintf(AppDatas.Recent, "%s",  name);
    // 初始化相关数据
    AppDatas.HDataCur->CurPos.X = 0;
    AppDatas.HDataCur->CurPos.Y = 0;
    AppDatas.HDataCur->FileReadBegin = 0;
    AppDatas.HDataCur->DataBufOffset = 0;
    AppDatas.HDataCur->DataShowBegin = 0;
	//读取数据
	LOGI("读取数据");
    AppDatas.HDataCur->DataBufUsed = ReadFile(AppDatas.HDataCur->FilePath, AppDatas.HDataCur->FileNameA, 
        AppDatas.HDataCur->FileReadBegin, AppDatas.HDataCur->DataBuffer, DATA_BUFFER_SIZE);
		LOGI("格式化hex");
    Data2Hex(AppDatas.HDataCur->DataBuffer, AppDatas.HDataCur->DataBufUsed, 
        AppDatas.HDataCur->HexBuffer, HEX_BUFFER_SIZE);
LOGI("显示");
    Main_Draw(1);

    return 0;
}

// 移动光标到下个Hex字符
void HV_GotoNextHex(void)
{
    if (1 == AppDatas.HDataCur->CurPos.X % 2)
    {
        HV_GotoFileOffset(AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataBufOffset + 1);
    }
    else
    {
        HV_DrawFocus(AppDatas.HDataCur->CurPos, 2, 1);
        AppDatas.HDataCur->CurPos.X++;
    }
}

// 刷新光标显示位置并在必要时重绘所有hex字符
int32 HV_RefreshFocus(void)
{
    static int32 OldFileShowBegin;
    APPSTATE_ENUM appState;
    POINT_ST NewPos;

    // 计算新光标位置
    NewPos.X = (int16)(AppDatas.HDataCur->DataBufOffset - AppDatas.HDataCur->DataShowBegin) % PageInfo.ColCount;
    NewPos.Y = (int16)(AppDatas.HDataCur->DataBufOffset - AppDatas.HDataCur->DataShowBegin) / PageInfo.ColCount;

    NewPos.X *= 2;

    appState = GetAppState();

    // 刷新显示
    if (APPSTATE_HEXEDIT == appState || APPSTATE_HEXVIEW == appState)
    {
        // 不需重绘字符
        if (OldFileShowBegin == AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataShowBegin)  
        {
            // 取消原焦点
            HV_DrawFocus(AppDatas.HDataCur->CurPos, 0, 0);

            AppDatas.HDataCur->CurPos.X = NewPos.X;
            AppDatas.HDataCur->CurPos.Y = NewPos.Y;

            // 绘制新焦点
            if (APPSTATE_HEXVIEW == appState)
                HV_DrawFocus(AppDatas.HDataCur->CurPos, 3, 0);
            else if (APPSTATE_HEXEDIT == appState)
                HV_DrawFocus(AppDatas.HDataCur->CurPos, 1, 0);
        }
        else
        {
            AppDatas.HDataCur->CurPos.X = NewPos.X;
            AppDatas.HDataCur->CurPos.Y = NewPos.Y;

            // 重绘全部
            HV_DrawHexAll(1, 0);

            OldFileShowBegin = AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataShowBegin;
        }

        if (APPSTATE_HEXVIEW == appState)
        {
            HV_DrawToolBar(0, 0);
            HV_DrawInfo(0);
        }

        RefreshScreen();
    }
    else
    {
        AppDatas.HDataCur->CurPos.X = NewPos.X;
        AppDatas.HDataCur->CurPos.Y = NewPos.Y;
    }

    return 0;
}

// 转到文件地址
int32 HV_GotoFileOffset(int32 fOffset)
{
    int32 OldFileShowBegin;
    int32 OldShowLine;

    if (fOffset < 0)
        fOffset = 0;

    if (fOffset > AppDatas.HDataCur->FileSize - 1)
        fOffset = AppDatas.HDataCur->FileSize - 1;

    OldFileShowBegin = AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataShowBegin;
    OldShowLine = (AppDatas.HDataCur->DataBufOffset - AppDatas.HDataCur->DataShowBegin) / PageInfo.ColCount;

    // 在当前缓冲区外
    if (fOffset < AppDatas.HDataCur->FileReadBegin + DATA_BUF_SIDE_SIZE || 
        fOffset >  AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataBufUsed - DATA_BUF_SIDE_SIZE) 
    {
        // 刷新缓冲区
        // 减DATA_BUF_SIDE_SIZE*2是因为文件开头不需要切换
        AppDatas.HDataCur->DataBufOffset = (fOffset - DATA_BUF_SIDE_SIZE * 2) % 
            (DATA_BUFFER_SIZE - DATA_BUF_SIDE_SIZE * 3) + DATA_BUF_SIDE_SIZE * 2;
        if (AppDatas.HDataCur->FileReadBegin != fOffset - AppDatas.HDataCur->DataBufOffset)
        {
            AppDatas.HDataCur->FileReadBegin = fOffset - AppDatas.HDataCur->DataBufOffset;
            AppDatas.HDataCur->DataBufUsed = ReadFile(AppDatas.HDataCur->FilePath, AppDatas.HDataCur->FileNameA, 
                AppDatas.HDataCur->FileReadBegin, AppDatas.HDataCur->DataBuffer, DATA_BUFFER_SIZE);
            Data2Hex(AppDatas.HDataCur->DataBuffer, AppDatas.HDataCur->DataBufUsed, AppDatas.HDataCur->HexBuffer, HEX_BUFFER_SIZE);
        }
    }
    else // 在当前缓冲区内
    {
        AppDatas.HDataCur->DataBufOffset = fOffset - AppDatas.HDataCur->FileReadBegin;
    }

    // 不在当前显示页
    if ((fOffset < OldFileShowBegin) || ((uint32)(fOffset - OldFileShowBegin) >= PageInfo.PageSize))
    {
        // 计算第一行显示的数据偏移
        AppDatas.HDataCur->DataShowBegin = (fOffset / PageInfo.ColCount - OldShowLine) * PageInfo.ColCount - AppDatas.HDataCur->FileReadBegin;
        if (AppDatas.HDataCur->DataShowBegin < 0)
            AppDatas.HDataCur->DataShowBegin = 0;
        if (AppDatas.HDataCur->DataShowBegin > AppDatas.HDataCur->DataBufOffset)
            AppDatas.HDataCur->DataShowBegin = AppDatas.HDataCur->DataBufOffset - fOffset % PageInfo.ColCount;
    }

    // 刷新显示
    HV_RefreshFocus();

    return 0;
}

// 改变当前数据偏移
void HV_ChangeDataOffset(int32 type)
{
    int32 OldFilePos;

    if (AppDatas.HDataCur->DataBufUsed <= 0 || AppDatas.HDataCur->FileSize <=0)
        return;

    OldFilePos = AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataBufOffset;

    switch (type)
    {
    case OFFSET_SEEK_LINE_UP: //↑
        HV_GotoFileOffset(OldFilePos - PageInfo.ColCount);
        break;
    case OFFSET_SEEK_LINE_DOWN: //↓
        HV_GotoFileOffset(OldFilePos + PageInfo.ColCount);
        break;
    case OFFSET_SEEK_BYTE_LAST: //←
        HV_GotoFileOffset(OldFilePos - 1);
        break;
    case OFFSET_SEEK_BYTE_NEXT: //→
        HV_GotoFileOffset(OldFilePos + 1);
        break;
    case OFFSET_SEEK_PAGE_UP: //上一页
        HV_GotoFileOffset(OldFilePos - PageInfo.PageSize);
        break;
    case OFFSET_SEEK_PAGE_DOWN: //下一页
        HV_GotoFileOffset(OldFilePos + PageInfo.PageSize);
        break;
    case OFFSET_SEEK_BEGIN: //开头
        HV_GotoFileOffset(0);
        break;
    case OFFSET_SEEK_END: //末尾
        HV_GotoFileOffset(AppDatas.HDataCur->FileSize - 1);
        break;
    }
}

/*------------------------------------------------------------------------------*/

// 根据触屏位置确定数据偏移
// 参数：位置作标
static void HV_Pos2Offset(int32 X, int32 Y)
{
    int16 i;
    POINT_ST NewPos;

    NewPos.X = -1;
    NewPos.Y = -1;

    // 查找X坐标
    for (i = 0; i < PageInfo.ColCount * 2; i++)
    {
        if (X >= PosTable[0][i].X && X < PosTable[0][i + 1].X)
        {
            NewPos.X = i;
            break;
        }
    }

    // 查找Y坐标
    for (i = 0; i < PageInfo.LineCount; i++)
    {
        if (Y >= PosTable[i][0].Y && Y < PosTable[i + 1][0].Y)
        {
            NewPos.Y = i;
            break;
        }
    }

    // 不在字符显示区域
    if (-1 == NewPos.X || -1 == NewPos.Y)
        return;

    if (AppDatas.HDataCur->CurPos.X == NewPos.X && AppDatas.HDataCur->CurPos.Y == NewPos.Y) 
    {
        // 再次选择，切换到编辑状态
        SetAppState(APPSTATE_HEXEDIT, 1);
    }
    else if (NewPos.X / 2 + NewPos.Y * PageInfo.ColCount < 
        AppDatas.HDataCur->FileSize - AppDatas.HDataCur->FileReadBegin - AppDatas.HDataCur->DataShowBegin)  
    {
        // 第一次点击并在数据范围内，设为焦点
        AppDatas.HDataCur->DataBufOffset = AppDatas.HDataCur->DataShowBegin + NewPos.X / 2 + NewPos.Y * PageInfo.ColCount;

        // 重绘焦点
        HV_DrawFocus(AppDatas.HDataCur->CurPos, 0, 1);
        AppDatas.HDataCur->CurPos.X = NewPos.X;
        AppDatas.HDataCur->CurPos.Y = NewPos.Y;
        HV_DrawFocus(AppDatas.HDataCur->CurPos, 4, 1);

        if (APPSTATE_HEXVIEW == GetAppState())
        {
            HV_DrawInfo(1);
            HV_DrawToolBar(0, 1);
        }
    }
}

// 模拟连续按键
static void KeyTimerDo(int32 data)
{
    HV_ChangeDataOffset(data);
}

// 按键UP
static int32 HV_DoKeyUp(int32 KeyCode)
{
    int32 fOpen = HV_IsFileOpen();

    switch (KeyCode)
    {
    case MR_KEY_SOFTRIGHT:
        HV_SwitchWindow(-1);
        Main_Draw(1);
        break;
    case MR_KEY_SOFTLEFT:
        HV_ShowMenu();
        break;
    case MR_KEY_5:
    case MR_KEY_SELECT:
        if (fOpen)
            SetAppState(APPSTATE_HEXEDIT, 1);
        break;
    case MR_KEY_UP:
    case MR_KEY_VOLUME_UP:
    case MR_KEY_DOWN:
    case MR_KEY_VOLUME_DOWN:
    case MR_KEY_LEFT:
    case MR_KEY_RIGHT:
    case MR_KEY_1:
    case MR_KEY_4:
        KeyTimerStop();
        break;
    case MR_KEY_3:
        if (fOpen)
            HV_ChangeDataOffset(OFFSET_SEEK_BEGIN);
        break;
    case MR_KEY_6:
        if (fOpen)
            HV_ChangeDataOffset(OFFSET_SEEK_END);
        break;
    case MR_KEY_2:
        if (fOpen)
            M_GotoOffset(0);
        break;
    case MR_KEY_7:
        HV_ShowMenuFind();
        break;
    case MR_KEY_8:
        HV_ShowMenuReplace();
        break;
    case MR_KEY_9:
        HV_ShowMenuCompare();
        break;
    case MR_KEY_0:
        HE_RedoAction();
        break;
    case MR_KEY_POUND:
        M_PluginMgr(0);
        break;
    default:
        return MR_IGNORE;
    }

    return MR_SUCCESS;
}

// 按键DOWN
static int32 HV_DoKeyDown(int32 KeyCode)
{
    int32 fOpen = HV_IsFileOpen();

    KeyTimerStop();

    switch (KeyCode)
    {
    case MR_KEY_SOFTRIGHT:
        HV_DrawToolBar(2, 1);
        break;
    case MR_KEY_SOFTLEFT:
        HV_DrawToolBar(1, 1);
        break;
    case MR_KEY_SELECT:
        break;
    case MR_KEY_UP:
        if (fOpen)
            KeyTimerStart(OFFSET_SEEK_LINE_UP, KeyTimerDo);
        break;
    case MR_KEY_DOWN:
        if (fOpen)
            KeyTimerStart(OFFSET_SEEK_LINE_DOWN, KeyTimerDo);
        break;
    case MR_KEY_LEFT:
        if (fOpen)
            KeyTimerStart(OFFSET_SEEK_BYTE_LAST, KeyTimerDo);
        break;
    case MR_KEY_RIGHT:
        if (fOpen)
            KeyTimerStart(OFFSET_SEEK_BYTE_NEXT, KeyTimerDo);
        break;
    case MR_KEY_VOLUME_UP:
    case MR_KEY_1:
        if (fOpen)
            KeyTimerStart(OFFSET_SEEK_PAGE_UP, KeyTimerDo);
        break;
    case MR_KEY_VOLUME_DOWN:
    case MR_KEY_4:
        if (fOpen)
            KeyTimerStart(OFFSET_SEEK_PAGE_DOWN, KeyTimerDo);
        break;
    default:
        return MR_IGNORE;
        break;
    }

    return MR_SUCCESS;
}

// 触屏事件
static int32 HV_DoMouseEvent(int32 type, int32 X, int32 Y)
{
    static POINT_ST MousePos; // 触屏按下位置

    if (MR_MOUSE_DOWN == type)
    {
        MousePos.X = (int16)X;
        MousePos.Y = (int16)Y;
        
        if (Y >= rectTool.y && Y < rectTool.y + rectTool.h)
        {
            if (X >= rectTCmd1.x && X < rectTCmd1.x + rectTCmd1.w)
            {
                HV_Event(MR_KEY_PRESS, MR_KEY_SOFTLEFT, 0);
            }
            else if (X >= rectTCmd2.x && X < rectTCmd2.x + rectTCmd2.w)
            {
                HV_Event(MR_KEY_PRESS, MR_KEY_SOFTRIGHT, 0);
            }
        }
        else if (Y >= rectInfo.y && Y < rectInfo.y + rectInfo.h)
        {
            if (X < rectInfo.x + rectInfo.w / 4)
                KeyTimerStart(OFFSET_SEEK_BYTE_LAST, KeyTimerDo);
            else if (X > rectInfo.x + (rectInfo.w / 4) * 3)
                KeyTimerStart(OFFSET_SEEK_BYTE_NEXT, KeyTimerDo);
            else if (Y < rectInfo.y + rectInfo.h / 2)
                KeyTimerStart(OFFSET_SEEK_LINE_UP, KeyTimerDo);
            else
                KeyTimerStart(OFFSET_SEEK_LINE_DOWN, KeyTimerDo);
        }
        else if (X > rectBtn1.x)  // 翻页按钮
        {
            if (Y >= rectBtn1.y && Y < rectBtn1.y + rectBtn1.h)
            {
                HV_DrawPageButton(1, 1, 1);
                HV_DoKeyDown(MR_KEY_1);
            }
            else if (Y >= rectBtn2.y && Y < rectBtn2.y + rectBtn2.h)
            {
                HV_DrawPageButton(2, 1, 1);
                HV_DoKeyDown(MR_KEY_4);
            }
        }
        /*else
        {
            HV_Pos2Offset(X, Y);
        }*/
    }
    else if (MR_MOUSE_UP == type)
    { 
        KeyTimerStop();

        if (Y >= rectTool.y && Y < rectTool.y + rectTool.h)
        {
            if (X >= rectTCmd1.x && X < rectTCmd1.x + rectTCmd1.w)
            {
                HV_Event(MR_KEY_RELEASE, MR_KEY_SOFTLEFT, 0);
            }
            else if (X >= rectTCmd2.x && X < rectTCmd2.x + rectTCmd2.w)
            {
                HV_Event(MR_KEY_RELEASE, MR_KEY_SOFTRIGHT, 0);
            }
            else if ((X >= rectTool.w / 3) && (X < rectTool.w * 2 / 3))
            {
                HV_Event(MR_KEY_RELEASE, MR_KEY_2, 0);
            }
        }
        else if (Y >= rectMain.y && Y < rectMain.y + rectMain.h)
        {
            if (X - MousePos.X > (int32)rectMain.w / 4) //向右滑动
            {
                HV_ChangeDataOffset(OFFSET_SEEK_PAGE_UP);
            }
            else if (MousePos.X - X > (int32)rectMain.w / 4) //向左滑动
            {
                HV_ChangeDataOffset(OFFSET_SEEK_PAGE_DOWN);
            }
            else if (X > rectBtn1.x)  // 翻页按钮
            {
                if (Y >= rectBtn1.y && Y < rectBtn1.y + rectBtn1.h)
                {
                    HV_DrawPageButton(1, 0, 1);
                    HV_DoKeyUp(MR_KEY_1);
                }
                else if (Y >= rectBtn2.y && Y < rectBtn2.y + rectBtn2.h)
                {
                    HV_DrawPageButton(2, 0, 1);
                    HV_DoKeyUp(MR_KEY_4);
                }
            }
            else
            {
                HV_Pos2Offset(X, Y);
            }
        }
    }
    else if (MR_MOUSE_MOVE == type)
    {
        int16 lines;

        lines = (int16)((Y - MousePos.Y) / (PageInfo.CharH + 1));

        if (0 != lines) // 滑动
        {
            AppDatas.HDataCur->DataShowBegin -= lines * PageInfo.ColCount;
            if(AppDatas.HDataCur->DataShowBegin < 0)AppDatas.HDataCur->DataShowBegin = 0; //xladd
            HV_GotoFileOffset(AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataBufOffset - lines * PageInfo.ColCount);
            MousePos.Y += lines * (PageInfo.CharH + 1);
        }
    }

    return MR_SUCCESS;
}

// Hex编辑界面事件
int32 HV_Event(int32 type, int32 p1, int32 p2)
{
    int32 ret;

    // 从信息显示状态返回
    if (IsMsgShowing)
    {
        if (MR_KEY_RELEASE == type || MR_MOUSE_UP == type)
        {
            HV_Draw(1);
            IsMsgShowing = 0;
        }
        return MR_SUCCESS;
    }

    switch (type)
    {
    case MR_KEY_PRESS:
        ret = HV_DoKeyDown(p1);
        break;
    case MR_KEY_RELEASE:
        ret = HV_DoKeyUp(p1);
        break;
    case MR_MOUSE_DOWN:
    case MR_MOUSE_UP:
    case MR_MOUSE_MOVE:
        ret = HV_DoMouseEvent(type, p1, p2);
        break;
    default:
        ret = MR_IGNORE;
        break;
    }

    return ret;
}
