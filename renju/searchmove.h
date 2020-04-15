#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_
//ËÑË÷ºËÐÄ
#include "createmoves.h"
#include"evaluate.h"
#include <tuple>

#define RECORD_ALL_SEARCH_STEP

struct SearchStepResult {
    double evaScore = 0;
    LegalMove move;
#if defined(_DEBUG) && defined(RECORD_ALL_SEARCH_STEP)
    vector<tuple<double, LegalMove, int>> hh;
#endif
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
