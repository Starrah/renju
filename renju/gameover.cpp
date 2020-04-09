#include "define.h"
int gameover()//判断是否游戏结束，未结束返回0，已结束返回1或2表示胜利的一方
{
    //如果没有空位置了，就是和棋
    if (emptyPlaces.empty()) return draw;
    // 由于_continuousPiecesCount[0]恒等于4，因此max_element返回非0的位置，
    // 当且仅当_continuousPiecesCount[1]或[2]>=5，也就是游戏应当结束。
    int* maxPointer = std::max_element(_continuousPiecesCount, _continuousPiecesCount + 3);
    return (int)(maxPointer - _continuousPiecesCount);
}

int _continuousPiecesCount[3] = {4, 0, 0};//第i个元素表示玩家i当前在棋盘上最长连珠的长度。

int _spreadDirections[8][2] = { {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}};

void updateContinuousPieceCount() {
    pair<int, Point> lastPlayPair = history[history.size() - 1];
    int lastPlayer = lastPlayPair.first;
    Point lastPoint = lastPlayPair.second;
    int lineResults[4] = {1, 1, 1, 1};
    for (int d=0; d<8; d++) {
        int deltaX = _spreadDirections[d][0];
        int deltaY = _spreadDirections[d][1];
        int i;
        for (i = 0; i <= 4; i++) {
            int newX = lastPoint.x + ((i + 1) * deltaX);
            int newY = lastPoint.y + ((i + 1) * deltaY);
            if (!(inboard(newX, newY) && chessBoard[newX][newY] == lastPlayer)) break;
        }
        lineResults[d % 4] += i;
    }
    int maxValue = *(std::max_element(lineResults, lineResults + 4));
    _continuousPiecesCount[lastPlayer] = std::max(_continuousPiecesCount[lastPlayer], maxValue);
}
