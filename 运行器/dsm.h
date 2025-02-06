
#ifndef DSM_H
#define DSM_H


/*
#if __ANDROID_API__ >=9 
#include <android/asset_manager.h> 
 #include <android/asset_manager_jni.h> 
#endif
*/
#include "base.h"

extern int32 SCREEN_WIDTH,SCREEN_HEIGHT;


//--- DSM 配置参数 ----------------------------

#define DSM_MAX_FILE_LEN	600
#define DSM_MAX_NAME_LEN	128
#define MAX_IMEI_LEN		15
#define MAX_IMSI_LEN		15
#define MAX_SMS_CENTER_LEN	15


#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

#define FREE_SET_NULL(ptr) \
	if(ptr){ \
		free(ptr); ptr = NULL; \
	}



#define MAKERGB(r, g, b) \
	 ( ((uint16)(r>>3) << 11) | ((uint16)(g>>2) << 5) | ((uint16)(b>>3)) )
#define MAKEARGB(a,r,g,b) ((int)a<<24 | ((int)r<<16 | (int)g<<8 | b))
	 
	
#define DSM_ENWORD_H	16
#define DSM_ENWORD_W	8
#define DSM_CHWORD_H	16
#define DSM_CHWORD_W	16

#define DSM_SUPPROT_SOC_NUM                        (5)

/**
 * 协议：SDCARD 作为跟目录 以 /结尾
 *		dsmWorkPath 以 / 结尾，切换到跟路径后为空
 */
 /*
#define DSM_ROOT_PATH		"mythroad/"
#define SDCARD_PATH			"/mnt/sdcard/"

#define DSM_HIDE_DRIVE		".disk/"
#define DSM_DRIVE_A			"a/"
#define DSM_DRIVE_B			"b/"
#define DSM_ROOT_PATH_SYS	"mythroad/"

#define TMP_PATH			".tmp"
*/
//------------------------------------------------
#define DSM_FACTORY			"mrpej"
#define DSM_TYPE			"android"


/*请不要做修改*/
#define DSM_FACTORY_ID                                  "skymp"				/*厂商标识，最多七个小写字符*/

#define MT6235

/*请不要修改这些值*/

#if (defined(MT6223P)||defined(MT6223)||defined(MT6223P_S00))
#define DSM_PLAT_VERSION                                       (2) /*手机平台区分(1~99)*/
#elif (defined(MT6226)||defined(MT6226M)||defined(MT6226D))
#define DSM_PLAT_VERSION                                       (4)  /*手机平台区分(1~99)*/
#elif (defined(MT6228))
#define DSM_PLAT_VERSION                                       (5)  /*手机平台区分(1~99)*/
#elif (defined(MT6225))
#define DSM_PLAT_VERSION                                        (3)  /*手机平台区分(1~99)*/
#elif (defined(MT6230))
#define DSM_PLAT_VERSION                                        (6)  /*手机平台区分(1~99)*/
#elif (defined(MT6227)||defined(MT6227D))
#define DSM_PLAT_VERSION                                        (7)
#elif (defined(MT6219))
#define DSM_PLAT_VERSION                                        (1)
#elif(defined(MT6235)||defined(MT6235B))
#define DSM_PLAT_VERSION                                        (8)
#elif(defined(MT6229))
#define DSM_PLAT_VERSION                                        (9)
#elif(defined(MT6253)||defined(MT6253T))
#define DSM_PLAT_VERSION                                        (10)
#elif(defined(MT6238))
#define DSM_PLAT_VERSION                                         (11)
#elif(defined(MT6239))
#define DSM_PLAT_VERSION                                          (12)
#else
#error PLATFORM NOT IN LIST PLEASE CALL SKY TO ADD THE PLATFORM
#endif

#ifdef DSM_IDLE_APP
#define DSM_FAE_VERSION                                       (180)    /*由平台组统一分配版本号，有需求请联系平台组*/
#else
#define DSM_FAE_VERSION                                       (182)    /*由平台组统一分配版本号，有需求请联系平台组*/
#endif


#define DSM_HANDSET_ID                                  "android"				 /*手机标识，最多七个小写字符*/


//---------------------------------
typedef enum {
	NETTYPE_WIFI=0,
	NETTYPE_CMWAP=1,
	NETTYPE_CMNET=2,
	NETTYPE_UNKNOW=3
}AND_NETTYPE;

typedef enum
{
	DSM_SOC_CLOSE,
	DSM_SOC_OPEN,
	DSM_SOC_CONNECTING,
	DSM_SOC_CONNECTED,
	DSM_SOC_ERR
}T_DSM_SOC_STAT_ENUM;

typedef enum
{
	DSM_SOC_NOREAD,
	DSM_SOC_READABLE
}T_DSM_SOC_READ_STAT;

typedef enum
{
	DSM_SOC_NOWRITE,
	DSM_SOC_WRITEABLE
}T_DSM_SOC_WRITE_STAT;


typedef struct
{
	uint8 mod_id;
	uint8 identifier;   
	int event_id;
	int result;
} mr_socket_event_struct;

typedef struct
{
	int socketId; //socket 句柄
	int realSocketId; //真实 socket 句柄（代理有效）
	int isProxy; //代理标志
	int realConnected; //真实连接上标志

	int socStat;
	int readStat;
	int writeStat;
}T_DSM_SOC_STAT;

typedef struct
{     
	void *callBack;
} mr_socket_struct;

typedef struct
{
   int32 pos;  //单位,秒s.
}T_SET_PLAY_POS;

typedef struct
{
	int32 pos;
} T_MEDIA_TIME;

/*回调有两种可能的返回值：
ACI_PLAY_COMPLETE   0  //播放结束
ACI_PLAY_ERROR       1  //播放时遇到错误
Loop ：1，循环播放；0，不循环播放；2，PCM循环播放模式
Block：1，阻塞播放；0，不阻塞播放*/
typedef void (*ACI_PLAY_CB)(int32 result);

typedef struct
{
	ACI_PLAY_CB cb; //回调函数
	int32 loop;
	int32 block;
}T_DSM_MEDIA_PLAY;


//获取图片信息所需要的结构体
/*
typedef struct 
{
 char *src; 
 int32 len; 
 int32 src_type;// MRAPP_SRC_TYPE 
 } MRAPP_IMAGE_ORIGIN_T; 
 */
 /*
 enum
 { 
 SRC_NAME = 0, //传到移植接口是文件名 
 SRC_STREAM //传到移植接口的是图片数据流 
 }MRAPP_SRC_TYPE;
 */



typedef struct
{
   int32 width;    //图片的宽度
   int32 height;   //图片的高度
}MRAPP_IMAGE_SIZE_T;
/*
typedef struct
{
	char *src;
	int32 src_len;
	int32 src_type;
	int32 ox;
	int32 oy;
	int32 w;
	int32 h;
} T_DRAW_DIRECT_REQ;
*/
typedef struct {
	uint8 level;
	uint8 current_band;
	uint8 rat;
	uint8 flag;
} T_RX;

//XL：定义菜单结构体
typedef struct// MR_UI_MENU
{
 char *title;
 char **text_item;
 int16 num;
 int16 gb;
} MR_MENU;

//XL：传感器
typedef struct 
{ 
 int32 x; //重力加速速度在x方向的分量 
 int32 y; //重力加速速度在y方向的分量 
 int32 z; //重力加速速度在z方向的分量 
} T_MOTION_ACC;


//XL：文件浏览 数据结构
typedef struct
{
 int32 def_list; //文件类型
 char list_path[260]; //gb绝对路径
} MR_T_FMGR_REQ;


/*
def_list
0:MR_DSPL_NONE
1:MR_DSPL_IMAGE
2:MR_DSPL_AUDIO
3:MR_DSPL_VIDEO
4:MR_DSPL_NES

*/
typedef struct
{
 char filepath[300];
 int len;
 
} XL_FILELIST;


//---------------------------------
void dsm_init(void);
void dsm_reset(void);
int setRootDir(char *RootPath);

int32 mr_exit(void);
int mr_getSocketState(int s);
void mr_cacheFlush(int id);

/** 设置 SD卡路径，参数底层不做错误检查 */
void SetDsmSDPath(const char * path);
void SetDsmWorkPath(const char *path);
 char *dsm_getPlatDir();
	 
	 




extern int32 picoc_init(void);
extern int32 picoc_event(int32 p1,int32 p2,int32 p3);
extern int32 picoc_pause(void);
extern int32 picoc_resume(void);
extern int32 picoc_exitApp(void);

extern int32 tcc_init(void);
extern int32 tcc_event(int32 p1,int32 p2,int32 p3);
extern int32 tcc_pause(void);
extern int32 tcc_resume(void);
extern int32 tcc_exitApp(void);

extern int32 so_init(void);
extern void capp_test(void);
extern int32 so_event(int32 p1,int32 p2,int32 p3);
extern int32 so_pause(void);
extern int32 so_resume(void);
extern int32 so_exitApp(void);

//全局assets
/*
#if __ANDROID_API__ >=9
extern jobject AssetsManger ;
extern AAssetManager *assets;
#endif
*/
extern uint16 *cacheScreenBuffer;//屏幕缓存指针
extern uint16 *realScreenBuffer;//真正的屏幕








extern int32 mr_screen_w; //缓存区宽度
extern int32 mr_screen_h; //缓存区高度
extern int32 mr_screen_bit; //屏幕缓存位数
extern int dsmNetType;

//extern int32 SCNW,SCNH,SCNBIT;//屏幕宽高，像素深度
//extern uint16 *screenBuf; //屏幕缓存



/*
//音乐播放sound
extern jmethodID
id_playSoundExInit,
id_playSoundExLoadFile,
id_playSoundEx,
id_pauseSoundEx,
id_resumeSoundEx,
id_stopSoundEx,
id_closeSoundEx,
id_setVolume,
id_getSoundTotalTime,
id_getSoundCurTime,
id_getSoundCurTimeMs,
id_setPlayPos,
id_setPlayTime,
id_getDeviceState;
//振动
jmethodID
id_startShake,
id_stopShake;

//图形绘制及bitmap
extern jmethodID
id_setScreenSize,//设置屏幕宽高
id_drawBitmap, //显示
id_drawBitmapFlip,
id_bitmapGetPixel,
id_bitmapSetPixel,
id_drawBitmapRotate, //旋转绘制
id_drawBitmapAlpha, //透明绘制
id_createBitmap, //创建
id_readBitmap, //读取图片
id_readBitmapFromAssets,
id_clipBitmap, //裁剪
id_bitmapFree, //释放
id_drawBitmapEx,
id_saveBitmap,
id_drawRect,
id_drawCir,
id_bitmapGetInfo; //图片信息

*/
//安卓android


//获取工程路径
char *getProjectPath(void);
 
 
int32 vm_event(int32 type, int32 p1, int32 p2);

/*启动定时器*/
extern int32 mr_timerStart(uint16 t);
/*停止定时器。*/
extern int32 mr_timerStop(void);

extern int32 vm_timerStart(int time);
void vm_timerCD(int f);


void SwitchPath(char *c);


int getFileLen(char *filename);
char *FormatPathString(char *path, char sep);
char *dsm_getProjectPath(void);
char *dsm_getRunName(void);
char *dsm_getPlatDir(void);
char *dsm_getDocDir(void);
char *dsm_getCacheDir(void);
extern int IS_RUN;
void dsm_parseArgs(int argc, char *argv[]);




#endif
