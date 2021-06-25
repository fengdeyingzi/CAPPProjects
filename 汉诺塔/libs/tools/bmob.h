#ifndef BMOB_H
#define BMOB_H
#include "./http.h"

char*BMOB_ID = "45c25eaaaf3d38511ab76625a1fa6c4a";
char*BMOB_KEY = "d0b1ba2c2cf7bc436e327d24c1e6c58e";

typedef struct
{
 _DEX*http;
 char*appid;
 char*reskey;
}_bmob;


void*initBmob(_DEX*http,char*id,char*key)
{
 _bmob*bmob = malloc(sizeof(_bmob));
 bmob->http = http;
 bmob->appid = id;
 bmob->reskey = key;
 return bmob;
}

int getBmobData(_bmob*bmob,char*url)
{
 httpSetRequest(bmob->http,url,"GET");
 httpAddHeader(bmob->http,"X-Bmob-Application-Id",bmob->appid);
 httpAddHeader(bmob->http,"X-Bmob-REST-API-Key",bmob->reskey);
 httpSend(bmob->http);
 return 0;
}

int addBmobData(_bmob*bmob,char*url,char*json)
{
 httpSetRequest(bmob->http,url,"GET");
 httpAddHeader(bmob->http,"X-Bmob-Application-Id",bmob->appid);
 httpAddHeader(bmob->http,"X-Bmob-REST-API-Key",bmob->reskey);
 httpAddHeader(bmob->http,"Content-Type","application/json");
 httpSetData(bmob->http,json);
 httpSend(bmob->http);
 return 0;
}

int freeBmob(_bmob*bmob)
{
 if(bmob!=NULL)
 {
  free(bmob);
  bmob = NULL;
 }
 return 0;
}


#endif