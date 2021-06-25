/*
 * 长按键控制
 * 版权所有 (C) 2011-2012 eleqian
 * [4/8/2012]
 */

#include "mrc_base.h"
#include "src/base.h"
#include "KeyTimer.h"

static int32 KeyTimerHandle = 0;  // 按键定时器
static timerCB KeyTimerCB;    // 按键回调

// 按住按键
static void KeyTimerReDo(int32 data)
{
    timerstop(KeyTimerHandle);
    timerstart(KeyTimerHandle, 75, data, KeyTimerCB, 1);
}

// 开始按键延时(按下按键)
void KeyTimerStart(int32 data, timerCB timercb)
{
    KeyTimerStop();

    KeyTimerCB = timercb;
    KeyTimerHandle = timercreate();
    timerstart(KeyTimerHandle, 300, data, KeyTimerReDo, 0);
    KeyTimerCB(data);
}

// 结束按键延时(抬起按键)
void KeyTimerStop(void)
{
    if (KeyTimerHandle != 0)
    {
        timerstop(KeyTimerHandle);
        timerdel(KeyTimerHandle);
        KeyTimerHandle = 0;
    }
}
