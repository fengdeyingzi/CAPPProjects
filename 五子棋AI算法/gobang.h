#include <base.h>
// #include <string.h>
#define XN 16  //横向棋格数
#define YN 16  //纵向棋格数
typedef int boolean;
//棋子类型
enum CHESS_TYPE{CT_NONE,
 CT_BLACK, CT_WHITE };

 //各种棋型
//依次为：成5，活4，死4，活3，死3，活2，死2，单子
enum PIECES_TYPE {
  PT_FIVE,
  PT_FOUR_1,
  PT_FOUR_2,
  PT_THREE_1,
  PT_THREE_2,
  PT_TWO_1,
  PT_TWO_2,
  PT_ONE
};


//获取棋盘上xy坐标的棋子类型
int board_getxy(int *board,int x,int y){
    return board[y*XN + x];
}

//下一颗棋
boolean board_down(int *board, int x,int y,int type){
    if(board_getxy(board,x,y) != CT_NONE){
        return FALSE;
    }
    board[y*XN + x] = type;
    return TRUE;
};

//获取棋盘消息
void GetChessMsg(int *board, int x, int y, int type, char *c){
 if(type != board[y*XN + x])
  return ;
 int i;
 memset(c, 0, 8);

//1.向上检查
 for(i = 0; i < 4; i ++){
  if(y - i - 1 < 0) break;
  if(board_getxy(board,x, y - i) == board_getxy(board, x, y - i - 1)) c[0] ++;
  else break;
 }
 
//2.向下检查
 for(i = 0; i < 4; i ++){
  if(y + i + 1 == YN) break;
  if(board_getxy(board,x, y + i) == board_getxy(board,x, y + i + 1)) c[1]++;
  else break;
 }

//3.向左检查 
 for(i = 0; i < 4; i ++){
  if(x - i - 1 < 0) break;
  if(board_getxy(board,x - i,y) == board_getxy(board,x - i - 1,y)) c[2] ++;
  else break;
 }

//4.向右检查
 for(i = 0; i < 4; i++){
  if(x + i + 1 == XN) break;
  if(board_getxy(board,x + i,y) == board_getxy(board, x + i + 1, y)) c[3] ++;
  else break;
 }

//5.左上检查
 for(i = 0; i < 4; i++){
  if((x - i - 1 < 0) || (y - i - 1 < 0)) break;
  if(board_getxy(board,x - i, y - i) == board_getxy(board,x - i - 1, y - i - 1))  c[4] ++;
  else break;
 }

//6.右下检查
 for(i = 0; i < 4; i++){
  if((x + i + 1 == XN) || (y + i + 1 == YN)) break;
  if(board_getxy(board,x + i, y + i) == board_getxy(board,x + i + 1, y + i + 1)) c[5] ++;
  else break;
 }

 //7.右上检查
 for(i = 0; i < 4; i++){
  if((x + i + 1 == XN)||(y - i - 1 < 0)) break;
  if(board_getxy(board,x + i, y - i) == board_getxy(board,x + i + 1, y - i - 1)) c[6] ++;
  else break;
 }

//8.左下检查
 for(i = 0; i < 4; i++){
  if((x - i - 1 < 0) || (y + i + 1 == YN)) break;
  if(board_getxy(board,x - i,y + i) == board_getxy(board,x - i - 1, y + i + 1)) c[7] ++;
  else break;
 }

}

//获取某地棋型分数
// AI取正值,玩家取负值
 int GtChssScr(int *board, int ix, int iy, int type) {
  int s = 0, i, r1, r2, cnt;
  int j = 0;  //防止陷入死循环
  char c[8];  //8方向棋子连接数
  char n[8];  //每种棋型的数量
  //8个方向的xy参数(相当于单位向量)
    char ADD_XN[8] = { 0, 0, -1, 1, -1, 1, 1, -1 };
    char ADD_YN[8] = { 1, -1, 0, 0, -1, 1, -1, 1 };
  GetChessMsg(board,ix, iy, type, c);
  

  //跳过四周都有阻碍物的点
  if (0 == c[0] + c[1] + c[2] + c[3] + c[4] + c[5] + c[6] + c[7]) return 0;

  memset(n, 0, 8);

  for (i = 0; i < 8; i += 2) {
    //一条线上的端点是否有阻碍物，无取TRUE
    r1 = CT_NONE == board_getxy(board, ix + ADD_XN[i] * c[i], iy + ADD_YN[i] * c[i]);
    r2 = CT_NONE ==
         board_getxy(board,ix + ADD_XN[i + 1] * c[i + 1],iy + ADD_YN[i + 1] * c[i + 1]);
    cnt = c[i] + c[i + 1] + 1;  //一条线上总棋数

    if (1 == cnt)
      n[PT_ONE]++;

    else if (2 == cnt) {
      if (r1 || r2)
        n[PT_TWO_2]++;
      else
        n[PT_TWO_1]++;
    }

    else if (3 == cnt) {
      if (r1 || r2)
        n[PT_THREE_2]++;
      else
        n[PT_THREE_1]++;
    }

    else if (4 == cnt) {
      if (r1 || r2)
        n[PT_FOUR_2]++;
      else
        n[PT_FOUR_1]++;
      ;
    }

    else
      n[PT_FIVE]++;
  }

  i = 0;

  //成5,1000000分
  if (0 < n[PT_FIVE]) {
    s += 1000000 * n[PT_FIVE];
    i += n[PT_FIVE];
    n[PT_FIVE] = 0;
  }

  //单子，0分
  if (0 < n[PT_ONE]) {
    i += n[PT_ONE];
    n[PT_ONE] = 0;
  }

  //活4，10000分
  if (0 < n[PT_FOUR_1]) {
    s += 10000 * n[PT_FOUR_1];
    i += n[PT_FOUR_1];
    n[PT_FOUR_1] = 0;
  }

  //双死4，10000分
  if (1 < n[PT_FOUR_2]) {
    s += 10000 * (n[PT_FOUR_2] / 2);
    i += (n[PT_FOUR_2] / 2);
    n[PT_FOUR_2] %= 2;
  }

  //双活2，100分
  if (1 < n[PT_TWO_1]) {
    s += 100 * (n[PT_TWO_1] / 2);
    i += (n[PT_TWO_1] / 2);
    n[PT_TWO_1] %= 2;
  }

  //死2，5分
  if (0 < n[PT_TWO_2]) {
    s += 5 * n[PT_TWO_2];
    i += n[PT_TWO_2];
    n[PT_TWO_2] = 0;
  }

  
  while (i < 4 && j < 3) {
    j++;

    //死4活3，10000分
    if (0 < n[PT_FOUR_2] && 0 < n[PT_THREE_1]) {
      s += 10000;
      n[PT_FOUR_2]--;
      n[PT_THREE_1]--;
      i += 2;
    }

    if (i > 3) break;
    //双活3，5000分
    if (1 < n[PT_THREE_1]) {
      s += 5000 * (n[PT_THREE_1] / 2);
      i += (n[PT_THREE_1] / 2);
      n[PT_THREE_1] %= 2;
    }

    if (i > 3) break;
    //死3活3，1000分
    if (0 < n[PT_THREE_1] && 0 < n[PT_THREE_2]) {
      s += 1000;
      n[PT_THREE_1]--;
      n[PT_THREE_2]--;
      i += 2;
    }

    if (i > 3) break;
    //死4，500分
    if (0 < n[PT_FOUR_2]) {
      s += 500;
      n[PT_FOUR_2]--;
      i++;
    }

    if (i > 3) break;
    //活3，200分
    if (0 < n[PT_THREE_1]) {
      s += 200 * n[PT_THREE_1];
      i += n[PT_THREE_1];
      n[PT_THREE_1] = 0;
    }

    if (i > 3) break;
    //活2，10分
    if (0 < n[PT_TWO_1]) {
      s += 10 * n[PT_TWO_1];
      i += n[PT_TWO_1];
      n[PT_TWO_1] = 0;
    }

    if (i > 3) break;
    //死3，50分
    if (0 < n[PT_THREE_2]) {
      s += 50 * n[PT_THREE_2];
      i += n[PT_THREE_2];
      n[PT_THREE_2] = 0;
    }
  }

  if (i > 4) printf("%d", i);

  return type == CT_WHITE ? s : -s;
}

/* AI下棋
主要步骤:
 第一步：设置好搜索深度 depth
 第二步：
  1.若depth = 0,返回
  2.若depth为奇数，扫描当前棋盘，找到对玩家最大的分数点(Max)
  3.若depth为偶数，扫描当前棋盘，找到对玩家最小的分数点(Min)
  4.depth - 1
 第三步：重复第二步，直到depth=0
*/
void AI_Player(int *board,int down_type) {
    int i;
    uint16
 downNum,  //已经落子数，用来停止落子
 allNum = XN*YN;  //总共能落棋子数
 char ix1 = 0, iy1 = 0, ix2 = XN - 1, iy2 = YN - 1, r_ix, r_iy, ix, iy;
  int max_score = -1, score_w, score_b;
 //计算已经落子数
 for( i=0;i<XN*YN;i++){
     if(board[i] != CT_NONE){
         downNum++;
     }
 }
  if (downNum == allNum) return;

  

  /*
  //扫描范围，目前是扫描(top_x-1, top_y-1)~(down_x-1, down_y-1)区域
   ix1 = r_ix = top_x - 3 >= 0 ? top_x - 1 : top_x;
   iy1 = r_iy = top_y - 3 >= 0 ? top_y - 3 : top_y;
   ix2 = down_x +1 < XN ? down_x + 3 : down_x;
   iy2 = down_y +1 < YN ? down_y + 3 : down_y; */

  for (iy = iy1; iy <= iy2; iy++)
    if (iy != YN)
      for (ix = ix1; ix <= ix2; ix++)
        if (ix != XN) {
          if (CT_NONE != board_getxy(board,ix,iy)) continue;

          board[iy*XN + ix] = CT_WHITE;
          score_w = GtChssScr(board,ix, iy, CT_WHITE);

          board[iy*XN + ix] = CT_BLACK;
          score_b = -GtChssScr(board,ix, iy, CT_BLACK);

          if (score_w >= max_score) {
            max_score = score_w;
            r_ix = ix;
            r_iy = iy;
          }

          if (score_b >= max_score) {
            max_score = score_b;
            r_ix = ix;
            r_iy = iy;
          }
          board[iy*XN + ix] = CT_NONE; //xldebug
        }

  
//   fx = r_ix; //焦点位置
//   fy = r_iy;
  board_down(board, r_ix, r_iy, down_type);
}

//用ai下一颗棋
boolean board_down_ai(int *board, int type){
AI_Player(board,type);

return TRUE;
};




