#include "define.h"

int chessBoard[GRID_NUM][GRID_NUM];//定义棋盘
int currentPlayer = 1;//1表示黑棋（电脑），2表示白棋（玩家）
Point::Point(int t_x, int t_y) {
    x = t_x;
    y = t_y;
}
