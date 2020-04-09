#ifndef _CREATEMOVES_
#define _CREATEMOVES_

#include <set>
struct LegalMove{
    Point p;
    int priority = 0;//���ȼ���Խ����ԽӦ������������
    inline bool operator<(const LegalMove& other) const
    {
        return priority < other.priority;
    }
};

//�߷�������

vector<LegalMove> createMoves(int curBoard[GRID_NUM][GRID_NUM], vector<Point>& centers);

#endif
