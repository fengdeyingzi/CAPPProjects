#ifndef __MRC_BASE_H__
#define __MRC_BASE_H__


enum {
    MR_KEY_0,               //按键 0
    MR_KEY_1,               //按键 1
    MR_KEY_2,               //按键 2
    MR_KEY_3,               //按键 3
    MR_KEY_4,               //按键 4
    MR_KEY_5,               //按键 5
    MR_KEY_6,               //按键 6
    MR_KEY_7,               //按键 7
    MR_KEY_8,               //按键 8
    MR_KEY_9,               //按键 9
    MR_KEY_STAR,            //按键 *
    MR_KEY_POUND,           //按键 #
    MR_KEY_UP,              //按键 上
    MR_KEY_DOWN,            //按键 下
    MR_KEY_LEFT,            //按键 左
    MR_KEY_RIGHT,           //按键 右
    MR_KEY_POWER,           //按键 挂机键
    MR_KEY_SOFTLEFT,        //按键 左软键
    MR_KEY_SOFTRIGHT,       //按键 右软键
    MR_KEY_SEND,            //按键 接听键
    MR_KEY_SELECT,          //按键 确认/选择（若方向键中间有确认键，建议设为该键）
    MR_KEY_VOLUME_UP,       //按键 侧键上
    MR_KEY_VOLUME_DOWN,     //按键 侧键下
    MR_KEY_NONE             //按键 保留
};

enum {
    MR_NET_ID_MOBILE,                  //移动
    MR_NET_ID_CN,          // 联通gsm
    MR_NET_ID_CDMA,       //联通CDMA
    MR_NET_ID_NONE       //未插卡
};

enum {
    MR_EDIT_ANY,            //任何字符
    MR_EDIT_NUMERIC,        // 数字
    MR_EDIT_PASSWORD       //密码，用"*"显示
};

enum {
    MR_SIM_NEW,     //新手机第一次插入SIM卡
    MR_SIM_CHANGE, //用户更换SIM卡
    MR_SIM_SAME    //未进行换卡操作
};

enum {
    MR_DIALOG_OK,           //对话框有"确定"键。
    MR_DIALOG_OK_CANCEL,    //对话框有"确定" "取消"键。
    MR_DIALOG_CANCEL        //对话框有"返回"键。
};

enum {
    MR_DIALOG_KEY_OK,     //对话框/文本框等的"确定"键被点击(选择)
    MR_DIALOG_KEY_CANCEL  //对话框/文本框等的"取消"("返回")键被点击(选择)
};

enum {
    MR_LOCALUI_KEY_OK,    //本地控件的"确定"键被点击(选择)
    MR_LOCALUI_KEY_CANCEL//本地控件的"取消"("返回")键被点击(选择)
};


enum {
    MR_KEY_PRESS, 	//按键按下 0
    MR_KEY_RELEASE, //按键释放 1
    MR_MOUSE_DOWN, 	//鼠标按下 2
    MR_MOUSE_UP, 	//鼠标释放 3
    MR_MENU_SELECT, //菜单选择 4
    MR_MENU_RETURN, //菜单返回 5
    MR_DIALOG_EVENT, //对话框 文本框 6
    MR_EVENT01, //
    MR_EXIT_EVENT, //
    MR_EVENT02, //
    MR_LOCALUI_EVENT, //文件浏览事件
    MR_OSD_EVENT, //
    MR_MOUSE_MOVE, //鼠标移动 12
    MR_ERROR_EVENT, //13执行异常通过这个事件来通知
    MR_PHB_EVENT,//
    MR_SMS_OP_EVENT,//
    MR_SMS_GET_SC,//
    MR_DATA_ACCOUNT_EVENT,//
    MR_MOTION_EVENT,// 传感器 18

    MR_TIMER_EVENT = 1001,
    MR_NET_EVENT
};

typedef enum
{
    MR_SOUND_MIDI,
    MR_SOUND_WAV,
    MR_SOUND_MP3,
    MR_SOUND_PCM, //8K 16bit
    MR_SOUND_M4A,
    MR_SOUND_AMR,
    MR_SOUND_AMR_WB
}MR_SOUND_TYPE;

typedef enum
{
    MR_FONT_SMALL,
    MR_FONT_MEDIUM,
    MR_FONT_BIG
}MR_FONT_TYPE;

enum
{
    MR_SEEK_SET,             //从文件起始开始
    MR_SEEK_CUR,             //从当前位置开始
    MR_SEEK_END             //从文件末尾开始
};

enum
{
    MR_SOCK_STREAM,
    MR_SOCK_DGRAM
};

enum
{
    MR_IPPROTO_TCP,
    MR_IPPROTO_UDP
};

enum
{
    MR_ENCODE_ASCII, //ansi gb编码
    MR_ENCODE_UNICODE //unicode编码
};

enum {
    MR_SOCKET_BLOCK,          //阻塞方式（同步方式）
    MR_SOCKET_NONBLOCK       //非阻塞方式（异步方式）
};

enum {
    BM_OR,         //SRC .OR. DST*   半透明效果
    BM_XOR,        //SRC .XOR. DST*
    BM_COPY,       //DST = SRC*      覆盖
    BM_NOT,        //DST = (!SRC)*
    BM_MERGENOT,   //DST .OR. (!SRC)
    BM_ANDNOT,     //DST .AND. (!SRC)
    BM_TRANSPARENT, //透明色不显示，图片的第一个象素（左上角的象素）是透明色
    BM_AND,
    BM_GRAY,
    BM_REVERSE
};

#define MR_IS_FILE     1      //文件
#define MR_IS_DIR      2      //目录
#define MR_IS_INVALID  8  //无效(非文件、非目录)

#define MR_FILE_RDONLY         1//以只读的方式打开文件。
#define MR_FILE_WRONLY        2//以只写的方式打开文件。
#define MR_FILE_RDWR             4//以读写的方式打开文件。
#define MR_FILE_CREATE          8//如果文件不存在，创建该文件。

/*
 *  zefang_wang 2010.12.21 :
 *    这个值之前定义有错误， 16 在底层的实现为 SHARE_OPEN，
 *    但是之前被定义成了   RECREATE.
 */

#define MR_FILE_SHARE_OPEN      16// 一边写， 一边读。

#define DRAW_TEXT_EX_IS_UNICODE          1 //是否使用UNICODE码, 网络字节序
#define DRAW_TEXT_EX_IS_AUTO_NEWLINE    2 //是否自动换行

#define MR_PLAT_VALUE_BASE 1000    //用于某些返回值的基础值

#define MR_FILE_RDONLY         1//以只读的方式打开文件。
#define MR_FILE_WRONLY        2//以只写的方式打开文件。
#define MR_FILE_RDWR             4//以读写的方式打开文件。
#define MR_FILE_CREATE          8//如果文件不存在，创建该文件。


#endif

