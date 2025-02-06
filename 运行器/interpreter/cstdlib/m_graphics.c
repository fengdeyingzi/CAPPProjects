


#include "../interpreter.h"
#include "mrc_base.h"
#include "graphics.h"

/*

union AnyValue
{
    unsigned char Character;
    short ShortInteger;
    int Integer;
    long LongInteger;
    unsigned short UnsignedShortInteger;
    unsigned int UnsignedInteger;
    unsigned long UnsignedLongInteger;
    char *Identifier;
    char ArrayMem[2];               // 数据开始的占位符，它不指向
    struct ValueType *Typ;
    struct FuncDef FuncDef;
    struct MacroDef MacroDef;
#ifndef NO_FP
    double FP;
#endif
    void *Pointer;                  // unsafe native pointers
};

*/



void Lib_createBitmap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->LongInteger =
	 createBitmap(Param[0]->Val->Integer, Param[1]->Val->Integer);
}

void Lib_readBitmap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->LongInteger =readBitmap( Param[0]->Val->Pointer);
}
void Lib_readBitmapFromAssets(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->LongInteger =readBitmapFromAssets( Param[0]->Val->Pointer);
}


void Lib_clipBitmap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->LongInteger =clipBitmap(Param[0]->Val->LongInteger,  Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,Param[4]->Val->Integer);
}

void Lib_drawBitmap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   drawBitmap(Param[0]->Val->LongInteger, Param[1]->Val->Integer,Param[2]->Val->Integer);
}

void Lib_drawBitmapEx(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   drawBitmapEx(Param[0]->Val->LongInteger,
	 Param[1]->Val->Integer,Param[2]->Val->Integer, Param[3]->Val->Integer,Param[4]->Val->Integer,
	 Param[5]->Val->Integer,Param[6]->Val->Integer, Param[7]->Val->Integer,Param[8]->Val->Integer);
}

void Lib_drawBitmapExb(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
   // drawBitmapExb(Param[0]->Val->Integer,
	//  Param[1]->Val->Integer,Param[2]->Val->Integer, Param[3]->Val->Integer,Param[4]->Val->Integer,
	//  Param[5]->Val->Integer,Param[6]->Val->Integer, Param[7]->Val->Integer,Param[8]->Val->Integer);
}

void Lib_drawBitmapExc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
   // drawBitmapExc(Param[0]->Val->Integer,
	//  Param[1]->Val->Integer,Param[2]->Val->Integer, Param[3]->Val->Integer,Param[4]->Val->Integer,
	//  Param[5]->Val->Integer,Param[6]->Val->Integer, Param[7]->Val->Integer,Param[8]->Val->Integer,
	//  Param[9]->Val->Integer,Param[10]->Val->Integer, Param[11]->Val->Integer, Param[12]->Val->Integer);
}



void Lib_whiteBitmap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs){
   //  whiteBitmap(Param[0]->Val->Integer, Param[1]->Val->Integer);
}

void Lib_bitmapFree(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->Integer =bitmapFree(Param[0]->Val->LongInteger);
}

void Lib_saveBitmap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->Integer =saveBitmap(Param[0]->Val->LongInteger, Param[1]->Val->Pointer,Param[2]->Val->Integer,Param[3]->Val->Integer);
}

void Lib_drawBitmapOld(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
   ReturnValue->Val->Integer = drawBitmapOld(Param[0]->Val->LongInteger, Param[1]->Val->Integer,  Param[2]->Val->Integer, Param[3]->Val->Integer, Param[4]->Val->Integer, Param[5]->Val->Integer, Param[6]->Val->Integer, Param[7]->Val->Integer);
}

void Lib_drawBitmapFlip(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
   ReturnValue->Val->Integer = drawBitmapFlip(Param[0]->Val->LongInteger, Param[1]->Val->Integer,  Param[2]->Val->Integer, Param[3]->Val->Integer, Param[4]->Val->Integer, Param[5]->Val->Integer, Param[6]->Val->Integer);
}


void Lib_drawBitmapAlpha(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
//  ReturnValue->Val->Integer = drawBitmapAlpha(Param[0]->Val->Integer, Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer);
}

void Lib_drawBitmapRotate(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param,int NumArgs)
{
 ReturnValue->Val->Integer = drawBitmapRotate(Param[0]->Val->LongInteger, Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,Param[4]->Val->Integer,Param[5]->Val->Integer,Param[6]->Val->Integer);
}

void Lib_bitmapGetInfo(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   ReturnValue->Val->Integer =bitmapGetInfo( Param[0]->Val->LongInteger,Param[1]->Val->Pointer);
}

void Lib_bitmapGetPixel(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   // ReturnValue->Val->Integer =bitmapGetPixel( Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer);
}

void Lib_bitmapSetPixel(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   // bitmapSetPixel( Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer, Param[3]->Val->Integer);
}

static void Lib_drawRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   drawRect( Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer, Param[3]->Val->Integer,Param[4]->Val->Integer);
}

static void Lib_drawCir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
   drawCir( Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer, Param[3]->Val->Integer);
}

static void Lib_clipRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
//  ReturnValue->Val->Integer=  clipRect( Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer, Param[3]->Val->Integer);
}
const char bitmap_Defs[] = "\
enum\
{\
 _JPG=0,\
 _PNG=1,\
 _BMP16=2\
};\
typedef struct \
{\
unsigned int width; \
unsigned int height; \
unsigned int stride;\
int format; \
unsigned int flags;\
void *ptr; \
} BITMAPINFO;\
";





struct LibraryFunction bitmapFunctions[] =
{
   // { MathAcos,         "float acos(float);" },
    {Lib_createBitmap ,               "long createBitmap(int,int);" },
		{Lib_readBitmap ,               "long readBitmap(char*);" },
	  {Lib_clipBitmap ,               "long clipBitmap(long,int,int,int,int);" },
		{Lib_drawBitmap ,               "void drawBitmap(long,int,int);" },
		{Lib_drawBitmapEx ,               "void drawBitmapEx(long,int,int,int,int,int,int,int,int);" },
		{Lib_drawBitmapExb ,               "void drawBitmapExb(long,int,int,int,int,int,int,int,int);" },
		{Lib_drawBitmapExc ,               "void drawBitmapExc(long,int,int,int,int,int,int,int,int,int,int,int,int);" },
	{Lib_whiteBitmap,                      "void whiteBitmap(long,int);"},
	  {Lib_bitmapFree ,               "int bitmapFree(long);" },
	  {Lib_saveBitmap ,               "int saveBitmap(long,char*,int,int);" },
		{Lib_drawBitmapOld,             "int drawBitmapOld(long,int,int,int,int,int,int,int);"},
		{Lib_drawBitmapFlip,           "int drawBitmapFlip(long,int,int,int,int,int,int);"},
		{Lib_drawBitmapAlpha,          "int drawBitmapAlpha(long,int,int,int);"},
		{Lib_drawBitmapRotate,         "int drawBitmapRotate(long,int,int,int,int,int,int);"},
		
		 
		{Lib_readBitmapFromAssets,      "long readBitmapFromAssets(char*);"},
		{Lib_bitmapGetInfo,             "int bitmapGetInfo(long,BITMAPINFO*);"},
		{Lib_bitmapGetPixel,           "int bitmapGetPixel(long,int,int);"},
		{Lib_bitmapSetPixel,           "void bitmapSetPixel(long,int,int,int);"},

		{Lib_drawRect,                "void drawRect(int,int,int,int,int);"},
		{Lib_drawCir,                 "void drawCir(int,int,int,int);"},
		{Lib_clipRect,                "int clipRect(int,int,int,int);"},
    { NULL,             NULL }
};

/* creates various system-dependent definitions */
void bitmapSetupFunc(Picoc *pc)
{
 /*
    VariableDefinePlatformVar(NULL, "M_E", &FPType, (union AnyValue *)&M_EValue, FALSE);
    VariableDefinePlatformVar(NULL, "M_LOG2E", &FPType, (union AnyValue *)&M_LOG2EValue, FALSE);
	*/
}

