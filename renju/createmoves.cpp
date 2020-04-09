#include "define.h"
#include "createmoves.h"
#include <cmath>
#define BOARD_CENTER Point(8, 8)

inline int L1Distance(const Point& p, const Point& center){
    return abs(p.x - center.x) + abs(p.y - center.y);
}

/**
 * 产生合法的走法集，走法已经排好了顺序。
 * 排序是按照priority进行的，priorty的算法为到所有中心点的L1距离的最小值。
 * 中心点暂时取为在本次计算之前两步的下棋位置。
 * @param curBoard
 * @param centers
 * @return
 */
vector<LegalMove> createMoves(int curBoard[GRID_NUM][GRID_NUM], vector<Point>& centers) //生成全部合法走法集
{
    vector<LegalMove> result;
    for (const Point& emptyPlace: emptyPlaces) {
        if (curBoard[emptyPlace.x][emptyPlace.y] == blank) {
            int minVal = INT_MAX;
            for (const Point& center: centers) {
                minVal = min(minVal, L1Distance(emptyPlace, center));
            }
            result.push_back(LegalMove{emptyPlace, minVal});
        }
    }
    sort(result.begin(), result.end());
    return result;
}
//查找所有合法落子点。对于五子棋来说，棋盘上的空白点均为可行走法。