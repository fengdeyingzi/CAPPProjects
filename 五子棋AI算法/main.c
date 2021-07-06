#include <base.h>
#include <graphics.h>
#include "gobang.h"
int *board;
//玩家棋子类型
int my_type;
//绘制棋盘
void drawUI(){ 
    int ix,iy;
    int type;
    int ir = SCRW/XN;
    int px = 0+ir/2;
    int py = (SCRH-SCRW)/2+ir/2;
    int xmax = XN*ir-ir;
    int ymax = YN*ir-ir;
    cls(200, 200, 200);
    for(ix = 0;ix<XN;ix++){
dline(px+ix*ir, py+0, px+ix*ir, py+ymax, 20,20,20);
    }
    for(iy = 0;iy<XN;iy++){
dline(px+0, py+iy*ir, px+xmax, py+iy*ir, 20,20,20);
    }
    for(ix = 0;ix<XN;ix++){
        for(iy = 0;iy<YN;iy++){
            type = board_getxy(board, ix, iy);
            if(type == CT_BLACK){
                drawCir(px+ix*ir,py+iy*ir,ir/2, 0xff202020);
            }
            if(type == CT_WHITE){
                drawCir(px+ix*ir,py+iy*ir,ir/2, 0xfff0f0f0);
            }
        }
    }
    ref(0,0, SCRW, SCRH);
}

int init() {
    board = malloc(sizeof(int)*XN*YN);
    memset(board, 0, sizeof(int)*XN*YN);
    my_type = CT_BLACK;
    board_down(board, 10,8, CT_BLACK);
    board_down_ai(board, CT_WHITE);
    board_down(board, 11,10, CT_BLACK);
    board_down_ai(board, CT_WHITE);
    drawUI();
    return 0;
}

int event(int type, int p0, int p1) {
    int dx = 0,dy = 0;
    int ir = SCRW/XN;
    int px = 0+ir/2;
    int py = (SCRH-SCRW)/2+ir/2;
    int xmax = XN*ir-ir;
    int ymax = YN*ir-ir;
  if (type == KY_UP) {
    if (p0 == _BACK) {
      exitApp();
      exit();
    }
  }
  if(type == MS_DOWN){
      dx = (p0-px + ir/2) / ir ;
      dy = (p1-py + ir/2) / ir ;
      board_down(board,dx,dy,my_type);
      drawUI();
      board_down_ai(board, CT_WHITE);
      drawUI();
  }

  return 0;
}

int pause() { return 0; }

int resume() { return 0; }

int exitApp() { return 0; }
