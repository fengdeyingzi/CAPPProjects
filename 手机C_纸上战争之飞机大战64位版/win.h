#ifndef _WIN_H_
#define _WIN_H_
#include "menu.h"
#include "game.h"


enum
{
 WIN_MAIN,
 WIN_LOAD,
 WIN_GAME,
 WIN_HELP,
 WIN_ABOUT
 
};

int win;
#ifdef TCC
extern MENU *menu;
extern _GAME *game;
#endif

int win_set(int i)
{
printf("%s\n","win_set");
 win=i;
 switch(win)
 {
  case WIN_MAIN:
  printf("%s\n","WIN_MAIN");
  if(game!=NULL)
  {
   game_free(game);
   game=NULL;
  }
  menu=menu_create();
  printf("%s\n","WIN_MAIN ok");
  break;
  case WIN_GAME:
  if(menu!=NULL)
  {
  menu_free(menu);
  menu=NULL;
  }
  game=game_create();
  break;
  case WIN_HELP:
  break;
  case WIN_ABOUT:
  break;
 }
 
 return 0;
}

//win回调事件
int win_event(int type)
{
 
 return 0;
}



#endif