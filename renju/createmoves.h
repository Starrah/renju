#ifndef _CREATEMOVES_
#define _CREATEMOVES_

#include <set>
struct LegalMove{
    Point p;
    int priority = 0;//优先级，越低则越应当被首先搜索
    inline bool operator<(const LegalMove& other) const
    {
        return priority < other.priority;
    }
};

//走法生成器

vector<LegalMove> createMoves(int curBoard[GRID_NUM][GRID_NUM], vector<Point>& centers);

#endif
