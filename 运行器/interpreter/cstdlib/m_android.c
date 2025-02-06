


#include "../interpreter.h"
#include "../../mrc_base.h"
#include "../../android.h"
#include "../../dsm.h"
// #include "loadDex.h"
//#include "../../mpc_malloc.h"


static void Lib_d(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->Pointer = mrc_memcpy(Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer);
}


static void Lib_Cmd(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->Integer = an_Cmd(Param[0]->Val->Pointer);
}

static void Lib_RootCmd(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->Integer = an_RootCmd(Param[0]->Val->Pointer);
}


static void Lib_Toast(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // an_Toast(Param[0]->Val->Pointer,  Param[1]->Val->Integer);
}


static void Lib_getPackagePath(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->Pointer = an_getPackagePath();
}

static void Lib_getTextFromAssets(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //  ReturnValue->Val->Pointer =an_readFromAssets(Param[0]->Val->Pointer,Param[1]->Val->Pointer);
}


static void Lib_getFilesDir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Pointer =an_getFilesDir();
}


static void Lib_getDataPath(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Pointer =an_getDataPath(Param[0]->Val->Pointer);
}


static void Lib_SwitchPath(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // SwitchPath(Param[0]->Val->Pointer);
}


static void Lib_ReadFromAssets(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->Pointer = an_readFromAssets(Param[0]->Val->Pointer, Param[1]->Val->Pointer);
}
/*
static void Lib_NewButton(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
     an_newButton(Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Integer,Param[3]->Val->Integer, Param[4]->Val->Integer,Param[5]->Val->Integer);
}



static void Lib_NewEditText(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    an_newEditText(Param[0]->Val->Integer, Param[1]->Val->Pointer,Param[2]->Val->Integer, Param[3]->Val->Integer, Param[4]->Val->Integer, Param[5]->Val->Integer);
}

static void Lib_NewCheckBox(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    an_newCheckBox(Param[0]->Val->Integer, Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,Param[4]->Val->Integer,Param[5]->Val->Integer);
}
*/
static void Lib_ClearView(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    //  an_clearView();
}

static void Lib_ex_call(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->Pointer = an_ex_call(Param[0]->Val->Pointer, Param[1]->Val->Pointer);
}



static void Lib_setOrientation(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // an_setOrientation(Param[0]->Val->Integer);
}



static void Lib_setNoLimits(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // an_setNoLimits(Param[0]->Val->Integer);
}


static void Lib_createView(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Integer = an_createView(Param[0]->Val->Pointer);
}

static void Lib_setView(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // an_setView(Param[0]->Val->Integer, Param[1]->Val->Pointer);
}


static void Lib_view_getId(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //  ReturnValue->Val->Integer=  an_view_getId(Param[0]->Val->Integer);
}

static void Lib_findViewById(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //  ReturnValue->Val->Integer= an_findViewById(Param[0]->Val->Integer);
}

static void Lib_removeView(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // an_removeView(Param[0]->Val->Integer);
}

static void Lib_addView(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // an_addView(Param[0]->Val->Integer, Param[1]->Val->Integer);
}

static void Lib_setVisibility(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // an_setVisibility(Param[0]->Val->Integer, Param[1]->Val->Integer);
}

static void Lib_setContextView(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // an_setContextView(Param[0]->Val->Pointer);
}

static void Lib_view_setBackground(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    
// an_view_setBackground(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

static void Lib_edit_getText(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Pointer =   an_view_getText(Param[0]->Val->Integer);
}


static void Lib_edit_setText(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // an_view_setText(Param[0]->Val->Integer, Param[1]->Val->Pointer);
}


static void Lib_openInput(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // openInput(Param[0]->Val->Integer);
}


static void Lib_closeInput(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // closeInput();
}

static void Lib_inputMode(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //  ReturnValue->Val->Integer= an_softInputMode();
}

static void Lib_inputIsActive(struct ParseState *Parser, struct Value *ReturnValue,struct Value **Param, int NumArgs)
{
// ReturnValue->Val->Integer = an_inputIsActive();
}

static void Lib_softInput(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // an_softInput(Param[0]->Val->Pointer);
}


static void Lib_edit_goto(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // edit_goto(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

static void Lib_selection(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // edit_selection(Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer);
}


static void Lib_insert(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // edit_insert(Param[0]->Val->Integer, Param[1]->Val->Integer,Param[2]->Val->Pointer);
}

static void Lib_clipSetText(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // clipSetText(Param[0]->Val->Pointer);
}

static void Lib_clipGetText(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Pointer=  clipGetText();
}

static void Lib_setVideoPath(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // setVideoPath(Param[0]->Val->Integer,Param[1]->Val->Pointer);
}


static void Lib_videoStart(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //  view_start(Param[0]->Val->Integer);
}


static void Lib_videoPause(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //  view_pause(Param[0]->Val->Integer);
}


static void Lib_videoResume(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // view_resume(Param[0]->Val->Integer);
}


static void Lib_videoSeekTo(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //  view_seekTo(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

static void Lib_videoIsPlaying(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Integer=  view_isPlaying(Param[0]->Val->Integer);
}


static void Lib_loadUrl(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //  view_loadUrl(Param[0]->Val->Integer,Param[1]->Val->Pointer);
}

static void Lib_seekBar_getProgress(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Integer=  seekBar_getProgress(Param[0]->Val->Integer);
}


static void Lib_seekBar_setProgress(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //  seekBar_setProgress(Param[0]->Val->Integer,Param[1]->Val->Integer);
}


static void Lib_seekBar_setMax(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //  seekBar_setMax(Param[0]->Val->Integer,Param[1]->Val->Integer);
}


static void Lib_an_setChecked(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // an_setChecked(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

static void Lib_an_isChecked(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
// ReturnValue->Val->Integer=an_isChecked(Param[0]->Val->Integer);
}

static void Lib_listView_add(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //  listView_add(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Pointer,Param[4]->Val->Pointer);
}

static void Lib_listView_remove(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //  listView_remove(Param[0]->Val->Integer,Param[1]->Val->Integer);
}
static void Lib_listView_getSize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Integer=   listView_getSize(Param[0]->Val->Integer);
}

static void Lib_listView_getItemTitle(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Pointer=   listView_getItemTitle(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

static void Lib_listView_getItemInfo(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Pointer=   listView_getItemInfo(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

static void Lib_listView_getItemClock(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Integer=   listView_getItemClock(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

static void Lib_listView_notifyDataSetChanged(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  //  listView_notifyDataSetChanged(Param[0]->Val->Integer);
}


static void Lib_createIntent(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
// ReturnValue->Val->Integer=  an_createIntent();
}
 
static void Lib_setAction(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
//  an_setAction(Param[0]->Val->Integer,Param[1]->Val->Pointer);
}

static void Lib_setData(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // an_setData(Param[0]->Val->Integer, Param[1]->Val->Pointer);
}

static void Lib_setType(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
//  an_setType(Param[0]->Val->Integer, Param[1]->Val->Pointer);
}
static void Lib_setDataAndType(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
//  an_setDataAndType(Param[0]->Val->Integer, Param[1]->Val->Pointer,Param[2]->Val->Pointer);
}

static void Lib_putEx(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
// an_putEx(Param[0]->Val->Integer,Param[1]->Val->Pointer,Param[2]->Val->Pointer);
}

static void Lib_startActivity(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Integer=   an_startActivity(Param[0]->Val->Integer);
}

static void Lib_setTitle(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
//  an_setTitle(Param[0]->Val->Pointer);
}

static void Lib_loadDex(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Integer=   loadDex(Param[0]->Val->Pointer);
}

static void Lib_loadClass(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Integer=   loadClass(Param[0]->Val->Integer,Param[1]->Val->Pointer);
}

static void Lib_runClass(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Integer=   runClass(Param[0]->Val->Integer);
}

static void Lib_putString(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
  // ReturnValue->Val->Pointer=   dex_putString(Param[0]->Val->Integer,Param[1]->Val->Pointer);
}




const char android_Defs[] = "\
  enum{LENGTH_SHORT,LENGTH_LONG};\
	enum{VIEW_DOWN=20,VIEW_UP=21};\
	enum{VISIBLE=0,INVISIBLE=4,GONE=8};\
	enum{INPUT_MASK_STATE = 15,\
  INPUT_STATE_UNSPECIFIED = 0,\
  INPUT_STATE_UNCHANGED = 1,\
  INPUT_STATE_HIDDEN = 2,\
  INPUT_STATE_ALWAYS_HIDDEN = 3,\
  INPUT_STATE_VISIBLE = 4,\
  INPUT_STATE_ALWAYS_VISIBLE = 5,\
  INPUT_MASK_ADJUST = 240,\
  INPUT_ADJUST_UNSPECIFIED = 0,\
  INPUT_ADJUST_RESIZE = 16,\
  INPUT_ADJUST_PAN = 32,\
  INPUT_ADJUST_NOTHING = 48,\
  INPUT_IS_FORWARD_NAVIGATION = 256};\
";




struct LibraryFunction androidFunctions[] =
{
    { Lib_Cmd,                "int cmd(char*);" },
    { Lib_RootCmd,            "int rootcmd(char*);" },
	  { Lib_Toast,              "void toast(char*,int);" },
		{ Lib_getTextFromAssets,  "char* getTextFromAssets(char*);"        },
		{ Lib_getPackagePath,     "char* getPackagePath();" },
	  { Lib_getFilesDir,        "char* getFileDir();" },	
		{ Lib_getDataPath,        "char* getDataPath(char*);" },	
		{ Lib_SwitchPath,         "void switchPath(char*);" },	
		{Lib_ReadFromAssets,      "void* readFileFromAssets(char*,int*);"},
	//	{ Lib_NewButton,          "void newbutton(int,char*,int,int,int,int);" },	
	//	 { Lib_NewEditText,       "void newedit(int,char*,int,int,int,int);" },	
	//	 { Lib_NewCheckBox,       "void newcheck(int,int,int,int,int,int);" },	
		 { Lib_ClearView,         "void clearView();" },

		{Lib_setOrientation ,      "void setOrientation(int);" },	
	  {Lib_setNoLimits ,         "void setNoLimits(int);" },	

		  { Lib_createView,         "int createView(char*);" },	
		  { Lib_setView,         "void setView(int,char*);" },	
			{Lib_view_getId,       "int view_getId(int);"},
			  { Lib_findViewById,         "int findViewById(int);" },	
			  { Lib_removeView,         "void removeView(int);" },	
			  { Lib_addView,            "void addView(int,int);" },	
			  { Lib_setVisibility,         "void setVisibility(int,int);" },	
				{Lib_view_setBackground,     "void view_setBackground(int,int);"},
		  { Lib_setContextView,         "void setContextView(char*);" },	
			  { Lib_edit_getText,         "char* view_getText(int);" },	
			  { Lib_edit_setText,         "void view_setText(int,char*);" },	
			  { Lib_openInput,         "void openInput(int);" },	
			  { Lib_closeInput,         "void closeInput();" },	
			  { Lib_edit_goto,         "void edit_goto(int,int);" },	
			  { Lib_selection,         "void edit_selection(int,int,int);" },	
			  { Lib_insert,            "void edit_insert(int,int,char*);" },	

			  { Lib_inputMode,         "int inputMode();" },	
			  { Lib_inputIsActive,       "int inputIsActive();" },	
				{ Lib_softInput,           "void softInput(int);"},
			  { Lib_clipSetText,         "void clipSetText(char*);" },	
				{ Lib_clipGetText,             "char *clipGetText();"},
				{Lib_setVideoPath,         "void setVideoPath(int,char*);"},
				{Lib_videoStart,           "void videoStart(int);"},
				{Lib_videoPause,           "void videoPause(int);"},
				{Lib_videoResume,         "void videoResume(int);"},
				{Lib_videoSeekTo,         "void videoSeekTo(int,int);"},
				{Lib_videoIsPlaying,       "int videoIsPlaying(int);"},
				{Lib_loadUrl,              "void loadUrl(int,char*);"},
				{Lib_seekBar_getProgress, "int seekBar_getProgress(int);"},
				{Lib_seekBar_setProgress, "void seekBar_setProgress(int,int);"},
				{Lib_seekBar_setMax,      "void seekBar_setMax(int,int);"},
				
				{Lib_an_setChecked,       "void setChecked(int,int);"},
				{Lib_an_isChecked,        "int isChecked(int);"},
				
				
				{Lib_listView_add,        "void list_add(int,int,int,char*,char*);"},
				{Lib_listView_remove,     "void list_remove(int,int);"},
				{Lib_listView_getSize,    "int list_getSize(int);"},
				{Lib_listView_getItemTitle, "char* list_getItemTitle(int,int);"},
				{Lib_listView_getItemInfo, "char* list_getItemInfo(int,int);"},
				{Lib_listView_getItemClock, "int list_getItemClock(int,int);"},
				{ Lib_listView_notifyDataSetChanged, "void list_notifyData(int);"   },
				{Lib_createIntent,          "int in_createIntent();"},
				{Lib_setAction,              "void in_setAction(int,char*);"},
				{Lib_setData,               "void in_setData(int,char*);"},
				{Lib_setType,               "void in_setType(int,char*);"},
				{Lib_setDataAndType,        "void in_setDataAndType(int,char*,char*);"},
				{Lib_putEx,                 "void in_putEx(int,char*,char*);"},
				{Lib_startActivity,         "int startActivity(int);"},
				{Lib_setTitle,              "void setTitle(char*);"},	
        {Lib_loadDex,      "int loadDex(char*);"},
        {Lib_loadClass,    "int loadClass(int, char*);"},
        {Lib_runClass,     "int runClass(int);"},
        {Lib_putString,    "char* dex_putString(int,char*);"},
        {Lib_ex_call,    "char* ex_call(char*,char*);"},



				
				
    { NULL,             NULL }
};

/* creates various system-dependent definitions */
void androidSetupFunc(Picoc *pc)
{
 /*
    VariableDefinePlatformVar(NULL, "M_E", &FPType, (union AnyValue *)&M_EValue, FALSE);
    VariableDefinePlatformVar(NULL, "M_LOG2E", &FPType, (union AnyValue *)&M_LOG2EValue, FALSE);
	*/
}
