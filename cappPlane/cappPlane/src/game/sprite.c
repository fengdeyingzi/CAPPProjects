#include "./sprite.h"

#include "../api/ex_math.h"
#include "../tools/res.h"

//运行精灵
void runSpr(Spr *spr) {
	if (spr == NULL)
		return;
	Act *act = &(spr->act[spr->ind]);
	act->ind++;
	act->ind =
		act->ind % act->pic_num;
}

//旋转绘制
void drawSprAngle(Spr *spr, int x2, int y2, int roat) {
	/*
 if(spr==NULL)
 {
  printf("Spr绘制失败\n");
  return ;
 }
 int x=x2-spr->x;
 int y=y2-spr->y;
 
 int32 bit = 
 getRes(spr->file,tImg)->id;
 Act*act = &(spr->act[spr->ind]);
 Pic*pic = &(act->pic[act->ind]);
 
 int rImg=
 createBitmap(pic->pw,pic->ph);
 drawBitmapOld(rImg,bit, 0, 0,
 pic->pw, pic->ph, 
 pic->px, pic->py);

 drawBitmapRotate(rImg,x2,y2, 
 spr->x,spr->y,
 roat-90,0xffffffff);


 bitmapFree(rImg);*/
}

//绘制精灵
void drawSpr(Spr *spr, int x2, int y2) {

	if (spr == NULL) {
		printf("Spr绘制失败\n");
		return;
	}
	
	int x = x2 - spr->x;

	int y = y2 - spr->y;

	int32 bit = getRes(spr->file, tImg)->id;

	Act *act = &(spr->act[spr->ind]);

	Pic *pic = &(act->pic[act->ind]);

#ifdef DEBUG

	drawRect(x, y, spr->w, spr->h, 0x50ff0000);

#endif

	drawBitmapEx(bit, x, y, spr->w, spr->h,
				 pic->px, pic->py, pic->pw, pic->ph);

}

void setSprActId(Spr *spr, int id) {
	if (spr == NULL)
		return;
	spr->ind = id;
}

void setSprImgId(Spr *spr, int id) {
	if (spr == NULL)
		return;
	Act *act = &(spr->act[spr->ind]);
	act->ind = id;
	act->ind = act->ind % act->pic_num;
}

//spr,w,h
void drawSprV9(Spr *spr, int x2, int y2, int iw, int ih, int vw, int vh) {
	printf("drawSpr...");
	if (spr == NULL)
		return;
	int x = x2 - spr->x;
	int y = y2 - spr->y;

	int32 bit = getRes(spr->file, tImg)->id;
	Act *act = &(spr->act[spr->ind]);
	Pic *pic = &(act->pic[act->ind]);
	//上一行
	drawBitmapEx(bit, x, y, vw, vh,
				 pic->px, pic->py, vw, vh);
	drawBitmapEx(bit, x + vw, y, spr->w - vw * 2, vh,
				 pic->px + vw, pic->py, iw - vw * 2, vh);
	drawBitmapEx(bit, x + spr->w - vw, y, vw, vh,
				 pic->px + iw - vw, pic->py, vw, vh);
	//绘制中间
	drawBitmapEx(bit, x, y + vh, vw, spr->h - vh * 2,
				 pic->px, pic->py + vh, vw, ih - vh * 2);
	drawBitmapEx(bit, x + vw, y + vh, spr->w - vw * 2, spr->h - vh * 2,
				 pic->px + vw, pic->py + vh, iw - vw * 2, ih - vh * 2);
	drawBitmapEx(bit, x + spr->w - vw, y + vh, vw, spr->h - vh * 2,
				 pic->px + iw - vw, pic->py + vh, vw, ih - vh * 2);
	//下一行
	drawBitmapEx(bit, x, y + spr->h - vh, vw, vh,
				 pic->px, pic->py + ih - vh, vw, vh);
	drawBitmapEx(bit, x + vw, y + spr->h - vh, spr->w - vw * 2, vh,
				 pic->px + vw, pic->py + ih - vh, iw - vw * 2, vh);
	drawBitmapEx(bit, x + spr->w - vw, y + spr->h - vh, vw, vh,
				 pic->px + iw - vw, pic->py + ih - vh, vw, vh);
}

//设置切片
void setPicJson(Pic *pic,
				cJSON *json, int len) {
	Pic *pi = pic;
	cJSON *temp[10];
	for (int i = 0; i < len; i++) {
		//获取切片
		temp[0] =
			cJSON_GetArrayItem(json, i);
		//保存切片
		temp[1] = cJSON_GetObjectItem(
			temp[0], "px");
		pi->px = temp[1]->valueint;
		temp[1] = cJSON_GetObjectItem(
			temp[0], "py");
		pi->py = temp[1]->valueint;
		temp[1] = cJSON_GetObjectItem(
			temp[0], "pw");
		pi->pw = temp[1]->valueint;
		temp[1] = cJSON_GetObjectItem(
			temp[0], "ph");
		pi->ph = temp[1]->valueint;
		pi++;
	}
}

//设置动作
void setActJson(Act *act,
				cJSON *json, int len) {
	int num;
printf("LogTag: - 0 num");
	char *name;
printf("LogTag: - 1 name");
	Act *ac = act;
printf("LogTag: - 2 act");
	cJSON *temp[10];
printf("LogTag: - 3 temp");
	for (int i = 0; i < len; i++) {
		//获取动作
		temp[0] =
			cJSON_GetArrayItem(json, i);
printf("LogTag: - 6 i");
		//获取切片
		temp[1] =
			cJSON_GetObjectItem(temp[0],
								"picture");
printf("LogTag: - 7 temp");
		num =
			cJSON_GetArraySize(temp[1]);
printf("LogTag: - 8 temp");
		//载入切片
		setPicJson(&(ac->pic[0]),
				   temp[1], num);
printf("LogTag: - 9 num");
		//保存动作
		ac->pic_num = num;
printf("LogTag: - 10 num");
		ac->ind = 0;
printf("LogTag: - 11 ind");
		temp[2] =
			cJSON_GetObjectItem(temp[0],
								"name");
printf("LogTag: - 12 temp");
		name = temp[2]->valuestring;
printf("LogTag: - 13 valuestring");
		ac->name = (char *)
					   getRes(name, tStr)
						   ->id;
printf("LogTag: - 14 id");
		ac++;
printf("LogTag: - 15 ac");
	}
}

Spr *loadSprFile(char *path) {
	printf("loadSprFile %s", path);
printf("LogTag: - 0 path");
	int len = 0, num = 0;
printf("LogTag: - 1 num");
	char *file;
printf("LogTag: - 2 file");
	cJSON *temp[10];
printf("LogTag: - 3 temp");
	Spr *spr = malloc(sizeof(Spr));
printf("LogTag: - 4 Spr");
	//读取精灵文件
	cJSON *sprJson = (cJSON *)getRes(path, tJsn)->id;
printf("LogTag: - 5 id");
	printf("loadSprite 2..");
printf("LogTag: - 6 printf");
	//解析精灵文件
	if (sprJson) {
		printf("读取宽高 %p", sprJson);
		//读取宽高
		temp[0] =
			cJSON_GetObjectItem(sprJson,
								"w");
	    printf("111");
		spr->w = temp[0]->valueint;
printf("LogTag: - 8 valueint");
		temp[0] =
			cJSON_GetObjectItem(sprJson,
								"h");
printf("LogTag: - 9 sprJson");
		spr->h = temp[0]->valueint;
printf("LogTag: - 10 valueint");
		temp[0] =
			cJSON_GetObjectItem(sprJson,
								"x");
printf("LogTag: - 11 sprJson");
		spr->x = temp[0]->valueint;
printf("LogTag: - 12 valueint");
		temp[0] =
			cJSON_GetObjectItem(sprJson,
								"y");
printf("LogTag: - 13 sprJson");
		spr->y = temp[0]->valueint;
printf("LogTag: - 14 valueint");
		temp[0] =
			cJSON_GetObjectItem(sprJson,
								"file");
printf("LogTag: - 15 sprJson");
		file = temp[0]->valuestring;
printf("LogTag: - 16 valuestring");
		printf("loadSprite 33..");
printf("LogTag: - 17 printf");
		spr->file = (char *)
						getRes(file, tStr)
							->path;
printf("LogTag: - 18 path");
		printf("3333333");
printf("LogTag: - 19 printf");
		//读取动作
		temp[0] =
			cJSON_GetObjectItem(sprJson,
								"action");
printf("LogTag: - 20 sprJson");
		printf("loadSprite 44..");
printf("LogTag: - 21 printf");
		num =
			cJSON_GetArraySize(temp[0]);
printf("LogTag: - 22 temp");
		printf("335");
printf("LogTag: - 23 printf");
		len = cJSON_GetArraySize(temp[0]);
printf("LogTag: - 24 temp");
		setActJson(&(spr->act[0]),
				   temp[0], len);
printf("LogTag: - 25 len");
	}
	spr->ind = 0;
printf("LogTag: - 26 ind");
	spr->act_num = num;
printf("LogTag: - 27 num");
	printf("re....");
printf("LogTag: - 28 printf");
	return spr;
printf("LogTag: - 29 spr");
}

//打印spr
char *printSpr(Spr *spr) {
	//总json
	cJSON *jSpr = cJSON_CreateObject();
	//基础属性
	cJSON_AddStringToObject(jSpr,
							"file", spr->file);
	cJSON_AddNumberToObject(jSpr,
							"w", spr->w);
	cJSON_AddNumberToObject(jSpr,
							"h", spr->h);
	cJSON_AddNumberToObject(jSpr,
							"x", spr->x);
	cJSON_AddNumberToObject(jSpr,
							"y", spr->y);

	Act *act;
	//act数组
	cJSON *aArr = cJSON_CreateArray();
	for (int i = 0; i < spr->act_num; i++) {
		act = &(spr->act[i]);
		cJSON *aObj =
			cJSON_CreateObject();

		//pic数组
		cJSON *pArr =
			cJSON_CreateArray();
		for (int j = 0;
			 j < act->pic_num; j++) {
			cJSON *pObj =
				cJSON_CreateObject();
			//循环添加pic
			Pic *pic = &(act->pic[j]);
			cJSON_AddNumberToObject(pObj,
									"pw", pic->pw);
			cJSON_AddNumberToObject(pObj,
									"ph", pic->ph);
			cJSON_AddNumberToObject(pObj,
									"px", pic->px);
			cJSON_AddNumberToObject(pObj,
									"py", pic->py);
			cJSON_AddItemToArray(pArr,
								 pObj);
		}
		Act *act = &(spr->act[0]);
		cJSON_AddStringToObject(aObj,
								"name", act->name);
		cJSON_AddItemToObject(aObj,
							  "picture", pArr);
		cJSON_AddItemToArray(aArr,
							 aObj);
	}
	cJSON_AddItemToObject(jSpr,
						  "action", aArr);
	return cJSON_Print(jSpr);
}
