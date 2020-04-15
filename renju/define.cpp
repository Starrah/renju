#include "define.h"
#include "hashsearch.h"

int chessBoard[GRID_NUM][GRID_NUM];//定义棋盘
int currentPlayer = 1;//1表示黑棋（电脑），2表示白棋（玩家）
Point::Point(int t_x, int t_y): x(t_x), y(t_y) {}
Point::Point(): Point(0, 0) {}

dir::dir(int t_x, int t_y) : x(t_x), y(t_y) {}
vector<pair<int, Point>> history;//列表表示下棋历史记录，每个元素是pair，first表示下棋的玩家，second表示下棋的位置
set<Point> emptyPlaces;

void initializeGame() {
    for (int i=0; i<GRID_NUM; i++) {
        for (int j=0;j<GRID_NUM;j++) {
            auto res = emptyPlaces.insert(Point(i, j));
            assert(res.second);
        }
    }
    initializeHashSearchModule();
}
