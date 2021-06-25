/*
 * 程序菜单代码
 * 版权所有 (C) 2011-2012 eleqian
 * [7/24/2012]
 */

#include "mrc_base.h"
#include "src/base.h"
#include "AppMain.h"
#include "Menu.h"
#include "DrawLib.h"
#include "KeyTimer.h"
#include "XString.h"

typedef struct {
    int32 ShowFlag;     // 菜单显示标志
    MENU_CBF CallBack;  // 菜单背景重绘回调
    PMENU_LINK RootMenu;    // 根菜单
    PMENU_LINK ActiveMenu;  // 当前活动菜单
    rectst Rects[MENU_MAX_LAYER + 1];  // 各级菜单区域
    int8 MenuLayer;         // 菜单级数
} MENU_DATA_ST;

static rectst rectTool;   // 工具栏区域
static rectst rectSpace;  // 总菜单可显示区域

static uint16 ItemHeight;  // 菜单项显示高度
static uint16 ButtonWidth; // 按钮宽度(工具栏)

static MENU_DATA_ST MenuData;  // 菜单数据

/*---------------------------------------------------------------------------*/

// 菜单初始化
int32 Menu_Init(void)
{
    int32 fw, fh;
    int16 scnWidth, scnHeight;

    GetScreenSize16(&scnWidth, &scnHeight);
    GetTextSizeW("\x65\x87\x67\x2c\x0\x0", &fw, &fh); //"文本"
    ItemHeight = (uint16)(fh + 4);
    ButtonWidth = (uint16)fw + 8;

    rectTool.x = 0; rectTool.y = scnHeight - ItemHeight;
    rectTool.w = scnWidth; rectTool.h = ItemHeight;

    return 0;
}

// 菜单结束
int32 Menu_End(void)
{
    return 0;
}

// 添加菜单
// 参数：文本，回调函数，父菜单，有效，复选
// 返回：添加的菜单项
PMENU_LINK Menu_Add(PMENU_LINK mParent, char *sTitle, MENU_CBF CBFunc, int32 data, int32 flag)
{
    PMENU_LINK mla = mParent;
    PMENU_LINK ml = (MENU_LINK*)malloc(sizeof(MENU_LINK));

    ml->Flag = flag;
    ml->Data = data;
    ml->CBFunc = CBFunc;
    ml->Next = NULL;
    ml->Child = NULL;
    ml->Children = 0;

    // 确定菜单文本
    if (flag & MENU_FLAG_UNICODE)
    {
        // 是unicode则直接复制
        wstrncpy(ml->Title, sTitle, sizeof(ml->Title));
    }
    else
    {
        // 转换文本为unicode
        GBToUni(sTitle, ml->Title, sizeof(ml->Title));
    }

    if (NULL != mla) //有父菜单
    {
        mla->Children++; //子菜单数+1
        ml->Index = mla->Children; //序号=总数
        ml->Parent = mla;

        if (NULL != mla->Child) //已有子菜单，添加到最后
        {
            mla = mla->Child;

            //最后菜单项
            while(NULL != mla->Next)
                mla = mla->Next;

            ml->Before = mla;
            mla->Next = ml;
        }
        else //无子菜单，直接添加
        {
            ml->Before = NULL;
            mla->Child = ml;
        }
    }
    else //无父菜单
    {
        ml->Index = 1;
        ml->Before = NULL;
        ml->Parent = NULL;
    }

    return ml;
}

// 绘制某级菜单
// 参数：父菜单，可绘制范围，位置信息（x-左,y-上,h-高,w-宽）
static void Menu_DrawLayer(PMENU_LINK mParent, rectst rectDraw, rectst *rectMenu)
{
    PMENU_LINK pMenu = NULL;
    rectst rectItem;
    rectst rectIndex;
    rectst rectText;
    rectst rectCheck;
    rectst rectArr;
    uint8 HaveCheck = 0;
    uint8 HaveChild = 0;
    int16 max_strw = 0;
    int16 strw;

    if (NULL == mParent)
        return;

    // 遍历菜单调整绘制范围
    for (pMenu = mParent->Child; NULL != pMenu; pMenu = pMenu->Next)
    {
        GetTextSizeW16(pMenu->Title, &strw, NULL);
        if (MENU_GET_FLAG(pMenu, MENU_FLAG_CHECK))
            HaveCheck = 1;
        if (pMenu->Child)
            HaveChild = 1;
        if (strw > max_strw)
            max_strw = strw;
    }

    rectText.w = (max_strw + 2);
    rectMenu->h = mParent->Children * ItemHeight + 4;
    rectMenu->w = rectText.w + 5;

    // 计算序号显示位置
    if (MenuData.ShowFlag & MENU_SHOW_FLAG_INDEX) {
        char sIndex[8];
        char wsIndex[16];

        max_strw = 0;

        for (pMenu = mParent->Child; NULL != pMenu; pMenu = pMenu->Next)
        {
            sprintf(sIndex, "%d.", pMenu->Index);
            Asc2Uni(sIndex, wsIndex, sizeof(wsIndex));
            GetTextSizeW16(wsIndex, &strw, NULL);
            if (strw > max_strw)
                max_strw = strw;
        }

        rectIndex.w = max_strw;
        rectMenu->w += rectIndex.w;
    } else {
        rectIndex.w = 0;
    }

    // 有复选
    if (HaveCheck) {
        rectCheck.w = 8;
        rectMenu->w += rectCheck.w;
    } else {
        rectCheck.w = 0;
    }

    // 有子菜单
    if (HaveChild) {
        rectArr.w = 8;
        rectMenu->w += rectArr.w;
    } else {
        rectArr.w = 0;
    }

    // 调整绘制位置
    if (rectMenu->y + rectMenu->h >= rectDraw.y + rectDraw.h)
        rectMenu->y = rectDraw.y + rectDraw.h - rectMenu->h - 1;

    if (rectMenu->x + rectMenu->w >= rectDraw.x + rectDraw.w)
        rectMenu->x = rectDraw.x + rectDraw.w - rectMenu->w + 1;

    rectItem.x = rectMenu->x + 3;
    rectItem.y = rectMenu->y + 2;
    rectItem.h = ItemHeight;
    rectItem.w = rectMenu->w - 5;

    rectCheck.x = rectItem.x;
    rectCheck.h = rectItem.h;
    rectIndex.x = rectCheck.x + rectCheck.w;
    rectIndex.h = rectItem.h;;
    rectText.x = rectIndex.x + rectIndex.w;
    rectText.h = rectItem.h;
    rectArr.x = rectText.x + rectText.w;
    rectArr.h = rectItem.h;

    // 菜单边框
    ClearRect(*rectMenu);
    DrawRoundBorder(*rectMenu);
    DrawVLine(rectMenu->x + 1, rectMenu->y, rectMenu->y + rectMenu->h - 1, AppColor.back_deep);

    pMenu = mParent->Child;

    while (NULL != pMenu)
    {
        uint32 dColor;
        int16 ymid;

        // 绘制菜单项背景
        if (MENU_GET_FLAG(pMenu, MENU_FLAG_ACTIVE) && MENU_GET_FLAG(pMenu, MENU_FLAG_ENABLE)) // 活动
            DrawShadeRect(rectItem);

        // 文字颜色
        dColor = MENU_GET_FLAG(pMenu, MENU_FLAG_ENABLE) ? AppColor.text_normal : AppColor.text_disabled;

        // 绘制菜单序号
        if (MenuData.ShowFlag & MENU_SHOW_FLAG_INDEX)
        {
            char sIndex[8];
            char wsIndex[16];

            rectIndex.y = rectItem.y;
            sprintf(sIndex, "%d.", pMenu->Index);
            Asc2Uni(sIndex, wsIndex, sizeof(wsIndex));
            DrawTextMidLeftW(rectIndex, wsIndex, dColor);
        }

        // 绘制菜单文字
        rectText.y = rectItem.y;
        DrawTextMidLeftW(rectText, pMenu->Title, dColor);

        if (MENU_GET_FLAG(pMenu, MENU_FLAG_CHECK)) // 绘制复选勾
        {
            rectCheck.y = rectItem.y;
            ymid = rectCheck.y + rectCheck.h / 2;

            DrawVLine(rectCheck.x + 1, ymid - 2, ymid + 1, dColor);
            DrawVLine(rectCheck.x + 2, ymid - 1, ymid + 2, dColor);
            DrawVLine(rectCheck.x + 3, ymid - 0, ymid + 3, dColor);
            DrawVLine(rectCheck.x + 4, ymid - 1, ymid + 2, dColor);
            DrawVLine(rectCheck.x + 5, ymid - 2, ymid + 1, dColor);
            DrawVLine(rectCheck.x + 6, ymid - 3, ymid - 0, dColor);
            DrawVLine(rectCheck.x + 7, ymid - 4, ymid - 1, dColor);
        }

        if (pMenu->Child) // 绘制下级菜单箭头
        {
            rectArr.y = rectItem.y;
            ymid = rectArr.y + rectArr.h / 2;

            DrawVLine(rectArr.x + 1, ymid - 5, ymid + 4, dColor);
            DrawVLine(rectArr.x + 2, ymid - 4, ymid + 3, dColor);
            DrawVLine(rectArr.x + 3, ymid - 3, ymid + 2, dColor);
            DrawVLine(rectArr.x + 4, ymid - 2, ymid + 1, dColor);
            DrawVLine(rectArr.x + 5, ymid - 1, ymid + 0, dColor);
        }

        pMenu = pMenu->Next;
        rectItem.y += rectItem.h;
    }
}

// 绘制底部工具栏
// 参数：状态：0 - 普通，1 - 左软键，2 - 右软键
static void Menu_DrawToolBar(uint8 state, uint8 refresh)
{
    if (MENU_SHOW_FLAG_NO_TOOLBAR & MenuData.ShowFlag)
        return;

    // 确定 / 取消
    DrawNormalToolBarW(rectTool, "\x78\x6e\x5b\x9a\x0\x0", "\x53\xd6\x6d\x88\x0\x0", state);

    if (refresh)
        RefreshRect(rectTool);
}

// 重绘所有菜单-支持控制是否绘制背景
int32 Menu_DrawEx(uint8 drawBack, uint8 refresh)
{
    PMENU_LINK mp = MenuData.ActiveMenu;
    PMENU_LINK dm[MENU_MAX_LAYER + 1] = {NULL};
    int16 i;

    if (NULL == mp)
        return -1;

    // 重绘背景
    if (drawBack && NULL != MenuData.CallBack)
    {
        ClearRect(rectSpace);
        MenuData.CallBack(0);
    }

    // 追溯父菜单
    for (i = MenuData.MenuLayer; i > 0; i--)
    {
        if (NULL != mp)
            mp = mp->Parent;
        dm[i] = mp;
    }

    // 绘制每级菜单
    for (i = 1; i <= MenuData.MenuLayer; i++)
    {
        Menu_DrawLayer(dm[i], rectSpace, MenuData.Rects + i);
    }

    if (refresh)
        RefreshRect(rectSpace);

    return 0;
}

// 重绘菜单
int32 Menu_Draw(uint8 refresh)
{
    Menu_DrawToolBar(0, refresh);

    return Menu_DrawEx(1, refresh);
}

// 展开菜单
int32 Menu_Expand(PMENU_LINK mParent)
{
    if(NULL == mParent || NULL == mParent->Child)
        return -1;

    MenuData.Rects[MenuData.MenuLayer + 1].x = MenuData.Rects[MenuData.MenuLayer].x + MenuData.Rects[MenuData.MenuLayer].w;
    MenuData.Rects[MenuData.MenuLayer + 1].y = MenuData.Rects[MenuData.MenuLayer].y + (mParent->Index - 1) * ItemHeight;
    MenuData.Rects[MenuData.MenuLayer + 1].w = 0;
    MenuData.Rects[MenuData.MenuLayer + 1].h = 0;
    MenuData.MenuLayer++;

    MenuData.ActiveMenu = mParent->Child;

    while (NULL != MenuData.ActiveMenu->Next)
    {
        if (MENU_GET_FLAG(MenuData.ActiveMenu, MENU_FLAG_ENABLE))
            break;
        MenuData.ActiveMenu = MenuData.ActiveMenu->Next;
    }

    if (NULL != MenuData.ActiveMenu)
        MENU_SET_FLAG(MenuData.ActiveMenu, MENU_FLAG_ACTIVE);

    return 0;
}

// 重新展开各级菜单
int32 Menu_Refresh(uint8 refresh)
{
    PMENU_LINK mp = MenuData.ActiveMenu;
    PMENU_LINK dm[MENU_MAX_LAYER + 1] = {NULL};
    int8 i, old_layer;

    if (NULL == mp)
        return -1;

    old_layer = MenuData.MenuLayer;

    // 追溯父菜单
    for (i = MenuData.MenuLayer; i >= 0; i--)
    {
        dm[i] = mp;
        if (NULL != mp)
            mp = mp->Parent;
    }

    Menu_Hide();
    
    // 重绘背景
    if (NULL != MenuData.CallBack)
    {
        ClearRect(rectSpace);
        MenuData.CallBack(0);
    }

    // 重新展开每级菜单
    for (i = 0; i < old_layer; i++)
    {
        Menu_Expand(dm[i]);
        MENU_CLEAR_FLAG(MenuData.ActiveMenu, MENU_FLAG_ACTIVE);
        MenuData.ActiveMenu = dm[i + 1];
        MENU_SET_FLAG(MenuData.ActiveMenu, MENU_FLAG_ACTIVE);
        Menu_DrawLayer(dm[i], rectSpace, MenuData.Rects + i + 1);
        //Menu_JuedgPos(dm[i], rectSpace, &rectMenus[i + 1]);
    }

    if (refresh)
    {
        RefreshRect(rectSpace);
        //Menu_Draw(1);
    }

    return 0;
}

// 折叠菜单
int32 Menu_Fold(PMENU_LINK mParent)
{
    if (NULL == mParent)
        return -1;

    MenuData.MenuLayer--;
    MENU_CLEAR_FLAG(mParent, MENU_FLAG_ACTIVE);
    MenuData.ActiveMenu = mParent->Parent;

    if (MenuData.ActiveMenu == MenuData.RootMenu)
    {
        Menu_Hide();
        return -1;
    }

    return 0;
}

// 递归折叠所有子菜单
static int32 MenuFoldEx(PMENU_LINK fMenu)
{
    PMENU_LINK ml = fMenu;

    while (NULL != ml)
    {
        if (NULL != ml->Child)
        {
            MenuFoldEx(ml->Child);
        }
        MENU_CLEAR_FLAG(ml, MENU_FLAG_ACTIVE);
        ml = ml->Next;
    }

    return 0;
}

// 折叠所有菜单
int32 Menu_Hide(void)
{
    MenuFoldEx(MenuData.RootMenu);
    MenuData.MenuLayer = 0;
    SetAppState(APPSTATE_RETURN, 1);
    MenuData.CallBack(MENU_CALLBACK_CANCLE);

    return 0;
}

// 显示菜单
int32 Menu_Show(PMENU_LINK menu, MENU_CBF cb, int16 x, int16 y, int32 flag)
{
    int16 scrw, scrh;

    if (NULL == menu)
        return -1;

    GetScreenSize16(&scrw, &scrh);

    MenuData.RootMenu = menu;
    MenuData.ActiveMenu = MenuData.RootMenu->Child;
    MenuData.CallBack = cb;
    MenuData.ShowFlag = flag;

    if (MENU_SHOW_FLAG_NO_TOOLBAR & flag)  // 不带工具栏
    {
        rectSpace.x = 0;
        rectSpace.y = 0;
        rectSpace.w = scrw;
        rectSpace.h = scrh;
    }
    else
    {
        rectSpace.x = 0;
        rectSpace.y = 0;
        rectSpace.w = scrw;
        rectSpace.h = scrh - rectTool.h;
    }

    MenuData.MenuLayer = 0;
    MenuData.Rects[0].x = x;
    MenuData.Rects[0].y = y;
    MenuData.Rects[0].w = 0;
    MenuData.Rects[0].h = 0;

    Menu_Expand(MenuData.RootMenu);
    //Menu_DrawExl(1, 0);

    SetAppState(APPSTATE_MENU, 1);

    return 0;
}

// 递归清除菜单项及其子菜单
static void MenuDelEx(PMENU_LINK fMenu)
{
    PMENU_LINK ml = fMenu, p1;

    while (NULL != ml)
    {
        if (NULL != ml->Child)
            MenuDelEx(ml->Child);
        p1 = ml->Next;
        free(ml);
        ml = p1;
    }
}

// 清除所有菜单
int32 Menu_Destroy(PMENU_LINK menu)
{
    if (NULL == menu)
        return -1;

    MenuDelEx(menu);

    return 0;
}

// 下一菜单
int32 Menu_Next(PMENU_LINK Menu, uint8 refresh)
{
    PMENU_LINK mp = Menu;

    if (NULL == mp)
        return - 1;

    MENU_CLEAR_FLAG(mp, MENU_FLAG_ACTIVE);

    do {
        mp = mp->Next;
        if(NULL == mp)
            mp = Menu->Parent->Child;
    } while (!MENU_GET_FLAG(mp, MENU_FLAG_ENABLE));

    MENU_SET_FLAG(mp, MENU_FLAG_ACTIVE);
    MenuData.ActiveMenu = mp;

    Menu_DrawEx(0, refresh);

    return 0;
}

// 上一菜单
int32 Menu_Before(PMENU_LINK Menu, uint8 refresh)
{
    PMENU_LINK mp = Menu;

    if (NULL == mp)
        return - 1;

    MENU_CLEAR_FLAG(mp, MENU_FLAG_ACTIVE);

    do {
        mp = mp->Before;
        if(NULL == mp)
        {
            mp = Menu->Parent->Child;
            while (NULL != mp->Next)
            {
                mp = mp->Next;
            }
        }
    } while (!MENU_GET_FLAG(mp, MENU_FLAG_ENABLE));

    MENU_SET_FLAG(mp, MENU_FLAG_ACTIVE);

    MenuData.ActiveMenu = mp;

    Menu_DrawEx(0, refresh);

    return 0;
}

// 根据序号取得菜单项
// 参数：父菜单，序号
PMENU_LINK Menu_GetByIndex(PMENU_LINK mParent, uint8 index)
{
    PMENU_LINK mp;

    if (NULL == mParent)
        return NULL;

    mp = mParent->Child;
    while (NULL != mp)
    {
        if(mp->Index == index)
        {
            return mp;
        }
        mp = mp->Next;
    }

    return NULL;
}

// 获取当前焦点菜单
// 返回：菜单
PMENU_LINK Menu_GetActive(void)
{
    return MenuData.ActiveMenu;
}

// 获取菜单可用状态
// 参数：菜单
uint8 Menu_IsEnable(PMENU_LINK menu)
{
    if (NULL == menu)
        return 0;

    return MENU_GET_FLAG(menu, MENU_FLAG_ENABLE) ? 1 : 0;
}

// 获取菜单选中状态
// 参数：菜单
uint8 Menu_IsCheck(PMENU_LINK menu)
{
    if (NULL == menu)
        return 0;

    return MENU_GET_FLAG(menu, MENU_FLAG_CHECK) ? 1 : 0;
}

// 激活某菜单
// 参数：菜单
int32 Menu_SetActive(PMENU_LINK menu)
{
    PMENU_LINK mp = menu;

    if (NULL != mp && MENU_GET_FLAG(mp, MENU_FLAG_ENABLE))
    {
        MENU_CLEAR_FLAG(MenuData.ActiveMenu, MENU_FLAG_ACTIVE);
        MenuData.ActiveMenu = mp;
        MENU_SET_FLAG(MenuData.ActiveMenu, MENU_FLAG_ACTIVE);
    }
    else
    {
        return -1;
    }

    MenuData.MenuLayer = 0;
    while (NULL != mp && MenuData.RootMenu != mp)
    {
        MenuData.MenuLayer++;
        mp = mp->Parent;
    }

    return 0;
}

// 设置菜单是否可用
// 参数：菜单，是否可用
int32 Menu_SetEnable(PMENU_LINK menu, uint8 enable)
{
    if (NULL == menu)
        return -1;

    MENU_SET_FLAG_EX(menu, MENU_FLAG_ENABLE, enable);

    return 0;
}

// 设置菜单是否选中
// 参数：菜单，是否选中
int32 Menu_SetCheck(PMENU_LINK menu, uint8 check)
{
    if (NULL == menu)
        return -1;

    MENU_SET_FLAG_EX(menu, MENU_FLAG_CHECK, check);

    return 0;
}

// 设置菜单显示标志
int32 Menu_SetShowFlag(int32 flag)
{
    MenuData.ShowFlag = flag;

    return 0;
}

/*---------------------------------------------------------------------------*/

// 模拟连续按键
static void MKeyTimerDo(int32 data)
{
    switch (data)
    {
    case MR_KEY_UP: //上
    case MR_KEY_VOLUME_UP:
        Menu_Before(MenuData.ActiveMenu, 1);
        break;
    case MR_KEY_DOWN: //下
    case MR_KEY_VOLUME_DOWN:
        Menu_Next(MenuData.ActiveMenu, 1);
        break;
    }
}

/*---------------------------------------------------------------------------*/
// 菜单事件处理
int32 Menu_Event(int32 type, int32 p1, int32 p2)
{
    int8 i, j;
    PMENU_LINK mp;

    if (MenuData.ActiveMenu == NULL)
        return MR_IGNORE;

    switch (type)
    {
    case MR_KEY_PRESS://选择活动菜单
        switch (p1)
        {
        case MR_KEY_UP: //上
        case MR_KEY_VOLUME_UP:
            KeyTimerStart(MR_KEY_UP, MKeyTimerDo);
            return MR_SUCCESS;
            break;
        case MR_KEY_DOWN: //下
        case MR_KEY_VOLUME_DOWN:
            KeyTimerStart(MR_KEY_DOWN, MKeyTimerDo);
            return MR_SUCCESS;
            break;
        case MR_KEY_LEFT: //左
            if (0 == Menu_Fold(MenuData.ActiveMenu))
                Menu_DrawEx(1, 1);
            return MR_SUCCESS;
            break;
        case MR_KEY_RIGHT: //右
            if (0 == Menu_Expand(MenuData.ActiveMenu))
                Menu_DrawEx(0, 1);
            return MR_SUCCESS;
            break;
        case MR_KEY_SOFTLEFT:
            Menu_DrawToolBar(1, 1);
            return MR_SUCCESS;
            break;
        case MR_KEY_SOFTRIGHT:
            Menu_DrawToolBar(2, 1);
            return MR_SUCCESS;
            break;
        default:
            if (p1 >= MR_KEY_1 && p1 <= MenuData.ActiveMenu->Parent->Children)  // 键盘输入序号
            {
                mp = Menu_GetByIndex(MenuData.ActiveMenu->Parent, (uint8)p1);
                Menu_SetActive(mp);
                Menu_DrawEx(1, 1);
                return MR_SUCCESS;
            }
            break;
        }
        break;
    case MR_KEY_RELEASE:
        switch (p1)
        {
        case MR_KEY_UP: //上
        case MR_KEY_VOLUME_UP:
            KeyTimerStop();
            return MR_SUCCESS;
            break;
        case MR_KEY_DOWN: //下
        case MR_KEY_VOLUME_DOWN:
            KeyTimerStop();
            return MR_SUCCESS;
            break;
        case MR_KEY_SOFTLEFT:
            Menu_DrawToolBar(0, 1);
        case MR_KEY_SELECT: //OK
            if (NULL != MenuData.ActiveMenu->Child)
            {
                Menu_Expand(MenuData.ActiveMenu);
                Menu_DrawEx(0, 1);
            }
            else
            {
                if (MENU_GET_FLAG(MenuData.ActiveMenu, MENU_FLAG_AUTOFOLD))
                {
                    Menu_Hide();
                }

                if (NULL != MenuData.ActiveMenu->CBFunc)
                {
                    MenuData.ActiveMenu->CBFunc(MenuData.ActiveMenu->Data); //执行回调
                }
            }
            return MR_SUCCESS;
            break;
        case MR_KEY_SOFTRIGHT: //取消
            Menu_DrawToolBar(0, 1);
            Menu_Hide();
            return MR_SUCCESS;
            break;
        default:
            if (p1 >= MR_KEY_1 && p1 <= MenuData.ActiveMenu->Parent->Children) //键盘输入序号
            {
                return Menu_Event(MR_KEY_RELEASE, MR_KEY_SELECT, 0);
            }
            break;
        }
        break;
    case MR_MOUSE_UP: //触屏抬起
        // 是当前级菜单
        if (p1 >= MenuData.Rects[MenuData.MenuLayer].x &&
            p1 < MenuData.Rects[MenuData.MenuLayer].x + MenuData.Rects[MenuData.MenuLayer].w && 
            p2 >= MenuData.Rects[MenuData.MenuLayer].y &&
            p2 < MenuData.Rects[MenuData.MenuLayer].y + MenuData.Rects[MenuData.MenuLayer].h)
        {
            // 是激活项并且无子菜单
            if (NULL == MenuData.ActiveMenu->Child && 
                MenuData.ActiveMenu->Index == (uint8)((p2 - MenuData.Rects[MenuData.MenuLayer].y) / ItemHeight + 1)) 
            {
                return Menu_Event(MR_KEY_RELEASE, MR_KEY_SELECT, 0);
            }
        }
        else // 不是当前级菜单
        {
            // 遍历所有菜单区域
            for (i = MenuData.MenuLayer - 1; i > 0; i--)
            {
                if (p1 >= MenuData.Rects[i].x && p1 < MenuData.Rects[i].x + MenuData.Rects[i].w 
                    && p2 >= MenuData.Rects[i].y && p2 < MenuData.Rects[i].y + MenuData.Rects[i].h)
                {
                    break;
                }
            }

            // 不在菜单区域
            if (i <= 0)
            {
                if (!(MENU_SHOW_FLAG_NO_TOOLBAR & MenuData.ShowFlag) &&
                    p2 >= rectTool.y && p2 < rectTool.y + rectTool.h)  // 工具栏
                {
                    if (p1 < ButtonWidth)
                    {
                        return Menu_Event(MR_KEY_RELEASE, MR_KEY_SOFTLEFT, 0);
                    }
                    else if (p1 >= rectTool.w - ButtonWidth)
                    {
                        return Menu_Event(MR_KEY_RELEASE, MR_KEY_SOFTRIGHT, 0);
                    }
                }
                else  // 退出菜单
                {
                    Menu_Hide();
                }
            }

            return MR_SUCCESS;
        }
        break;
    case MR_MOUSE_DOWN: // 触屏按下
        mp = MenuData.ActiveMenu;

        // 遍历所有菜单区域
        for (i = MenuData.MenuLayer; i > 0; i--)
        {
            if (p1 >= MenuData.Rects[i].x && p1 < MenuData.Rects[i].x + MenuData.Rects[i].w 
                && p2 >= MenuData.Rects[i].y && p2 < MenuData.Rects[i].y + MenuData.Rects[i].h)
                break;
            mp = mp->Parent;
        }

        // 在菜单区域
        if (i > 0) 
        {
            mp = Menu_GetByIndex(mp->Parent, (uint8)((p2 - MenuData.Rects[i].y) / ItemHeight + 1));

            // 无效菜单项
            if (0 == Menu_IsEnable(mp)) 
                return 0;

            // 取消以前的焦点
            for (j = MenuData.MenuLayer; j > i; j--) 
            {
                MENU_CLEAR_FLAG(MenuData.ActiveMenu, MENU_FLAG_ACTIVE);
                MenuData.ActiveMenu = MenuData.ActiveMenu->Parent;
            }

            // 激活菜单项
            Menu_SetActive(mp);

            // 展开子菜单
            if (NULL != mp->Child)
                Menu_Expand(mp);

            // 如果不是同级菜单就刷新背景
            Menu_DrawEx((i == MenuData.MenuLayer) ? 0 : 1, 1); 
            return MR_SUCCESS;
        }
        else if (!(MENU_SHOW_FLAG_NO_TOOLBAR & MenuData.ShowFlag) &&
            p2 >= rectTool.y && p2 < rectTool.y + rectTool.h)  // 工具栏
        {
            if (p1 < ButtonWidth)
            {
                return Menu_Event(MR_KEY_PRESS, MR_KEY_SOFTLEFT, 0);
            }
            else if (p1 >= rectTool.w - ButtonWidth)
            {
                return Menu_Event(MR_KEY_PRESS, MR_KEY_SOFTRIGHT, 0);
            }
        }
        break;
    }

    return MR_IGNORE;
}
