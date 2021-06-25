
static int _time=0;



int getTime()
{
 int time=getuptime();
 
 int re = time - _time;
 _time= time;
 return re;
}
 
