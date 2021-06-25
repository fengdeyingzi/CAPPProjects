/*
 * 程序本地控件调用
 * 版权所有 (C) 2011-2012 eleqian
 * [7/8/2012]
 */

#include "mrc_base.h"
#include "src/base.h"
#include "AppMain.h"
#include "LocalUI.h"
#include "XString.h"
#include "src/android.h"

static int32 UIHandle = 0;
static char InputBuffer[MAX_INPUT_BUF_SIZE];
static INPUT_CB CallBackFunc;

/*---------------------------------------------------------------------------*/
// 显示编辑框
// 参数：标题，原始内容，类型，回调函数
int32 ShowInput(char *stitle, char *stext, int32 type, int32 max_size, INPUT_CB cbFunc)
{
    char *unistr = NULL;

    SetAppState(APPSTATE_LOCALUI, 1);

    CallBackFunc = cbFunc;
    memset(InputBuffer, 0, MAX_INPUT_BUF_SIZE);
    wstrcpy(InputBuffer, stext);

    if (max_size > MAX_INPUT_TEXT_LEN)
        max_size = MAX_INPUT_TEXT_LEN;
    unistr = strc2u(stitle);
    UIHandle = editcreate(unistr, InputBuffer, type, max_size);
    free(unistr);

    return UIHandle;
}

//从本地编辑窗口取得输入数据（文本），参数：缓冲区
static int32 GetEditText(char *sBuffer, int32 bufSize)
{
    LOGI("start");
    const char *tStr = editget(UIHandle);
    int32 tSize = 0;
    LOGI("start");
    if(NULL != tStr)
    {
        tSize = wstrlen((char*)tStr);
        if (tSize > bufSize - 2)
            tSize = bufSize - 2;
        memcpy(sBuffer, tStr, tSize);
        sBuffer[tSize] = sBuffer[tSize + 1] = '\0';
    }
    LOGI("start");
    return tSize;
}

// 删除本地编辑窗口，参数：句柄
static int32 DestoryEdit(void)
{
    int32 ret;

    ret = editdel(UIHandle);
    UIHandle = 0;

    return ret;
}

/*---------------------------------------------------------------------------*/
// 处理对话框事件
int32 LocalDialogEvent(int32 KeyCode)
{
    switch (KeyCode)
    {
    case MR_DIALOG_KEY_OK://确定，返回数据
    LOGI("获取编辑框文本");
        GetEditText(InputBuffer, MAX_INPUT_BUF_SIZE);
            LOGI("释放编辑框");
        DestoryEdit();
            LOGI("释放编辑框");
        SetAppState(APPSTATE_RETURN, 1);
        LOGI("调用回调函数");
        if (wstrlen(InputBuffer) > 0)
            (*CallBackFunc)(InputBuffer);
        break;
    case MR_DIALOG_KEY_CANCEL://取消
        DestoryEdit();
        SetAppState(APPSTATE_RETURN, 1);
        break;
    }

    return 0;
}


