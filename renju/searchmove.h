#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_
//ËÑË÷ºËÐÄ
#include "createmoves.h"

struct SearchStepResult {
    double evaScore = 0;
    LegalMove move;
};

class GameFullStatus {
public:
    int player;
    int (*board)[GRID_NUM];
    vector<pair<int, Point>> playHistory;

    inline bool putChess(const LegalMove &move);

    inline bool unputChess(const LegalMove &move);
};

Point searchMove();//ËÑË÷ºËÐÄ

#endif
