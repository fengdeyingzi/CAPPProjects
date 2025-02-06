#include "interpreter.h"
#include <math.h>
#include "ex_math.h"
//#ifndef BUILTIN_MINI_STDLIB
//#ifndef NO_FP

	
	static	void Lib_isPointCollisionRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = ex_isPointCollisionRect(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,Param[4]->Val->Integer,Param[5]->Val->Integer);
}

static	void Lib_IsCircleCollisionRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = ex_IsCircleCollisionRect(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,Param[4]->Val->Integer,Param[5]->Val->Integer, Param[6]->Val->Integer);
}

static	void Lib_isCollisionRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)ex_isCollisionRect(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer,Param[4]->Val->Integer,Param[5]->Val->Integer, Param[6]->Val->Integer,Param[7]->Val->Integer);
}
static	void Lib_toSpan(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
   ex_toSpin(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer, Param[4]->Val->Integer,  Param[5]->Val->Pointer, Param[6]->Val->Pointer);
}


static	void Lib_getLineSize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)ex_getLineSize(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer);
}
static	void Lib_getRadiam(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = (int)ex_getRadiam(Param[0]->Val->Integer,Param[1]->Val->Integer,Param[2]->Val->Integer,Param[3]->Val->Integer);
}

	struct LibraryFunction Ex_MathFunctions[] =
{
	{Lib_isPointCollisionRect,    "int isPointCollRect(int,int,int,int,int,int);"},
	{Lib_IsCircleCollisionRect,   "int isCirCollRect(int,int,int,int,int,int,int);"},
    { Lib_isCollisionRect,           "int isCollRect(int,int,int,int,int,int,int,int);" },
    { Lib_toSpan,            "int toSpin(int,int,int,int,int,int*,int*);" },
		{ Lib_getLineSize,            "int getLineSize(int,int,int,int);" },
		{ Lib_getRadiam,         "int getRadiam(int,int,int,int);" },
    {NULL,NULL}
 };

 
 void Ex_MathSetupFunc(Picoc *pc)
 {
	 
 }
