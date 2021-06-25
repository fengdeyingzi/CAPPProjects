#include <base.h>

#include "horizontal_ref.h"
#include "up_ref.h"


int refi=0;

int hor;

int init()
{
hor=up_create();
cls(240,240,240);
for(int i=0;i<60;i++)
{
 if(up_ref(hor))
  break;
 sleep(30);
}
up_free(hor);
ref(0,0,SCRW,SCRH);




return 0;
}




int resume()
{return 0;}

int pause()
{return 0;}

int event(int32 type,int32 p,int32 p2)
{
if(type==KY_UP)
  {
  if(p==_SRIGHT)
  exit();
  }

return 0;
}

