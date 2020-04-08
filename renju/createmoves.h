#ifndef _CREATEMOVES_
#define _CREATEMOVES_

#include <set>
struct LegalMove{
    Point p;
    int priority;//优先级，越低则越应当被首先搜索
    static inline int getPriority(const Point& p, const Point& center){
        return abs(p.x - center.x) + abs(p.y - center.y);
    }
    inline bool operator<(const LegalMove& other) const
    {
        return (((priority - other.priority) * 256) + ((p.x - other.p.x) * 16) + (p.y - other.p.y)) < 0 ;
    }
};

//走法生成器

set<LegalMove> createMoves();

#endif
