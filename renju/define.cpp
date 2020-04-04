#include "define.h"

int chessBoard[GRID_NUM][GRID_NUM];//定义棋盘
int currentPlayer = 1;//1表示黑棋（电脑），2表示白棋（玩家）
Point::Point(int t_x, int t_y): x(t_x), y(t_y) {}
Point::Point(): Point(0, 0) {}
vector<pair<int, Point>> history;//列表表示下棋历史记录，每个元素是pair，first表示下棋的玩家，second表示下棋的位置
