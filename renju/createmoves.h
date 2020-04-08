#ifndef _CREATEMOVES_
#define _CREATEMOVES_

#include <set>
struct LegalMove{
    Point p;
    int priority;//���ȼ���Խ����ԽӦ������������
    static inline int getPriority(const Point& p, const Point& center){
        return abs(p.x - center.x) + abs(p.y - center.y);
    }
    inline bool operator<(const LegalMove& other) const
    {
        return (((priority - other.priority) * 256) + ((p.x - other.p.x) * 16) + (p.y - other.p.y)) < 0 ;
    }
};

//�߷�������

set<LegalMove> createMoves();

#endif
