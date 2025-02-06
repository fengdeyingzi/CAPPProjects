#include "./res.h"

#include "../api/base.h"
#include "../api/graphics.h"
#include "../game/object.h"
#include "../game/sprite.h"
#include "../tools/fnt.h"

char* resTypeStr[] = {
	"图片", "字体", "声音",
	"定时器", "字符串",
	"精灵", "JSON", "Object"};

//载入资源
Res* loadRes(char* path, ResType type) {
	printf("loadRes 1.. %d：%s:%s %d\n", ResList.num - 1,
		   resTypeStr[type], path, (int)type);
printf("LogTag: - 0 type");
	printf("00");
printf("LogTag: - 1 printf");
	char *text=NULL, *sprStr=NULL;
printf("LogTag: - 2 NULL");
	printf("0000");
printf("LogTag: - 3 printf");
	Res* res = &(ResList.res[ResList.num - 1]);
printf("LogTag: - 4 num");
	printf("........11");
printf("LogTag: - 5 printf");
	switch (type) {
	//图片
	case tImg:
		res->id = readBitmapFromAssets(path);
printf("LogTag: - 6 path");
		res->type = type;
printf("LogTag: - 7 type");
		res->path = getRes(path, tStr)->path;
printf("LogTag: - 8 path");
		break;
printf("LogTag: - 9 break");

	//字体
	case tFnt:
		text = malloc(sizeof(char) * strlen(path));
printf("LogTag: - 10 path");
		int len = strlen(path);
printf("LogTag: - 11 path");
		strcpy(text, path);
printf("LogTag: - 12 path");
		text[len - 1] = 'g';
printf("LogTag: - 13 len");
		text[len - 2] = 'n';
printf("LogTag: - 14 len");
		text[len - 3] = 'p';
printf("LogTag: - 15 len");
		res->id = (int32)fnt_create(text, path);
printf("LogTag: - 16 path");
		res->type = type;
printf("LogTag: - 17 type");
		res->path = getRes(path, tStr)->path;
printf("LogTag: - 18 path");
		free(text);
printf("LogTag: - 19 text");
		break;
printf("LogTag: - 20 break");

	//定时器
	case tTim:
		res->id = timercreate();
printf("LogTag: - 21 timercreate");
		res->type = type;
printf("LogTag: - 22 type");
		res->path = getRes(path, tStr)->path;
printf("LogTag: - 23 path");
		break;
printf("LogTag: - 24 break");

	//字符串
	case tStr:
	printf("111");
printf("LogTag: - 25 printf");
		text = malloc(sizeof(char) * strlen(path));
printf("LogTag: - 26 path");
		printf("222");
printf("LogTag: - 27 printf");
		strcpy(text, path);
printf("LogTag: - 28 path");
		res->type = type;
printf("LogTag: - 29 type");
		strcpy(text, path);
printf("LogTag: - 30 path");
		res->path = text;
printf("LogTag: - 31 text");
		res->id = (int32)text;
printf("LogTag: - 32 text");
		printf("333");
printf("LogTag: - 33 printf");
		break;
printf("LogTag: - 34 break");

	//精灵
	case tSpr:
		res->id = (int32)loadSprFile(path);
printf("LogTag: - 35 path");
		res->type = type;
printf("LogTag: - 36 type");
		res->path = getRes(path, tStr)->path;
printf("LogTag: - 37 path");
		break;
printf("LogTag: - 38 break");

	//Json
	case tJsn:
		sprStr = readFileFromAssets(path, &len);
printf("LogTag: - 39 len");
		//解析精灵文件
		if (len > 0) {
			res->id = (int32)cJSON_Parse(sprStr);
			res->type = type;
printf("LogTag: - 41 type id = %p", (cJSON*)res->id);

			res->path = getRes(path, tStr)->path;
printf("LogTag: - 42 path");
		}
		free(sprStr);
printf("LogTag: - 43 sprStr");
		break;
printf("LogTag: - 44 break");

	case tObj:

		break;
printf("LogTag: - 45 break");

	default:
		break;
printf("LogTag: - 46 break");
	}
	printf("加载完成");
printf("LogTag: - 47 printf");
	return res;
printf("LogTag: - 48 res");
}

void freeOneRes(Res* res,
				ResType type) {
	Res* res2 = NULL;
	//遍历资源
	if (ResList.num > 0)
		for (int i = 0; i < ResList.num; i++) {
			res2 = &(ResList.res[i]);
			//资源已载入
			if (res->type == type)
				if (strcmp(res->path,
						   res2->path) == 0) {
					printf("释放资源%d:%s\n", i, res2->path);
					switch (res2->type) {
					//图片
					case tImg:
						bitmapFree(res2->id);
						break;

					//字体
					case tFnt:
						fnt_free((_FNT*)(res2->id));
						break;

					//定时器
					case tTim:
						timerstop(res2->id);
						timerdel(res2->id);
						break;

					//精灵
					case tSpr:
						free((Spr*)(res2->id));
						break;

					//Json
					case tJsn:
						cJSON_Delete(
							(cJSON*)res2->id);
						break;

					case tStr:
						return;
						break;

					case tObj:

						break;

					default:
						break;
					}

					for (int j = i; j < ResList.num - 1; j++) {
						ResList.res[j] =
							ResList.res[j + 1];
					}
					ResList.num--;
					return;
					break;
				}
		}
	//资源未载入
	printf("释放资源失败：%s\n",
		   res2->path);
	//返回资源
	return;
}

//释放资源资源
void freeRes() {
	//遍历Res
	Res* res;
	for (int i = 0; i < ResList.num; i++) {
		res = &(ResList.res[i]);
		printf("释放资源%d：%s:%s\n", i, resTypeStr[res->type], res->path);

		switch (res->type) {
		//图片
		case tImg:
			bitmapFree(res->id);
			break;

		//字体
		case tFnt:
			fnt_free((_FNT*)(res->id));
			break;

		//定时器
		case tTim:
			timerstop(res->id);
			timerdel(res->id);
			break;

		//精灵
		case tSpr:
			free((Spr*)(res->id));
			break;

		//Json
		case tJsn:
			cJSON_Delete(
				(cJSON*)res->id);
			break;

		case tStr:
			free(res->path);
			break;

		case tObj:

			break;

		default:
			break;
		}
	}
}

//获取资源
Res* getRes(char* path, ResType type) {
	
	Res* res = NULL;
	//遍历资源
	if (ResList.num > 0)
		for (int i = 0; i < ResList.num; i++) {
			res = &(ResList.res[i]);
			//资源已载入
			if (res->type == type)
				if (strcmp(path, res->path) == 0) {
					return res;
					break;
				}
		}
	//资源未载入
	ResList.num++;
	res = loadRes(path, type);
	
	//返回资源
	return res;
}
