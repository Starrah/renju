#include "define.h"
#include "createmoves.h"
#include <cmath>
#include "searchmove.h"

/**
 * 距离计算方式：规定每步可以横或竖或斜走，那么从p到center需要走几步。
 * @param p
 * @param center
 * @return
 */
inline int ToCenterDistance(const Point &p, const Point &center) {
    return max(abs(p.x - center.x), abs(p.y - center.y));
}

inline int calculatePriorityFromToCenterDistance(int toCenterDistance, int toPieceDist) {
    return ((toPieceDist >= SKIP_MOVE_SEARCHING_BY_DISTENCE_TO_OTHER_PIECE__MINVALUE) * (GRID_NUM * GRID_NUM)) +
           (toCenterDistance * GRID_NUM) + toPieceDist;
}

/**
 * 产生合法的走法集，走法已经排好了顺序。
 * 排序是按照priority进行的，priorty的算法为到所有中心点的L1距离的最小值。
 * 中心点暂时取为在本次计算之前两步的下棋位置。
 * @param curBoard
 * @param centers
 * @return
 */
vector<LegalMove> createMoves(int curBoard[GRID_NUM][GRID_NUM], vector<Point> &centers,
                              const int originDistanceMatrix[GRID_NUM][GRID_NUM]) //生成全部合法走法集
{
    if (curBoard[GRID_NUM / 2][GRID_NUM / 2] == blank) return vector<LegalMove>{LegalMove{BOARD_CENTER}};
    if (centers.empty()) centers.push_back(BOARD_CENTER);
    int newDistanceMatrix[GRID_NUM][GRID_NUM] = {0};

    // 如果给了起始距离矩阵，就根据新下的棋子刷新起始距离矩阵供后面计入priority使用。
    if (originDistanceMatrix != nullptr) {
        memcpy(newDistanceMatrix, originDistanceMatrix, sizeof(int) * GRID_NUM * GRID_NUM);
        for (const Point &emptyPlace: emptyPlaces) {
            if (curBoard[emptyPlace.x][emptyPlace.y] != blank) {
                updateDistanceMatrixWithNewChess(newDistanceMatrix, emptyPlace);
            }
        }
    }

    vector<LegalMove> result;
    for (const Point &emptyPlace: emptyPlaces) {
        if (curBoard[emptyPlace.x][emptyPlace.y] == blank) {
            int minVal = INT_MAX; // 到所有中心的距离第最小值
            for (const Point &center: centers) {
                minVal = min(minVal, ToCenterDistance(emptyPlace, center));
            }
            result.push_back(LegalMove{emptyPlace, calculatePriorityFromToCenterDistance(
                    minVal, newDistanceMatrix[emptyPlace.x][emptyPlace.y])});
        }
    }
    sort(result.begin(), result.end());
    return result;
}
//查找所有合法落子点。对于五子棋来说，棋盘上的空白点均为可行走法。