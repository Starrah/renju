#include "define.h"
#include "createmoves.h"
#include <cmath>
#define BOARD_CENTER Point(8, 8)

set<LegalMove> createMoves() //生成全部合法走法集
{
    set<LegalMove> result;
    //中心位置是上一玩家下棋位置或天元
    Point center = BOARD_CENTER;
    if (!history.empty()) center = (history.end() - 1)->second;
    for (int i=1; i<GRID_NUM; i++) {
        for (int j=1; j<GRID_NUM; j++){
            if (chessBoard[i][j] == blank) {
                Point p = Point(i, j);
                auto insRes = result.insert(LegalMove{p, LegalMove::getPriority(p, center)});
                assert_debug(insRes.second);
            }
        }
    }
    return result;
}
//查找所有合法落子点。对于五子棋来说，棋盘上的空白点均为可行走法。