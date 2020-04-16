#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_
//ËÑË÷ºËÐÄ
#include "createmoves.h"
#include"evaluate.h"
#include <tuple>
#include <ctime>

#define DEBUG_RECORD_ALL_SEARCH_STEP

#define ROOT_DEPTH_START 3
#define TIME_GIVEN_MSEC 5000
#define STOP_MIN_ROOT_DEPTH 4
#define MAX_ROOT_DEPTH INT_MAX
#define DETECT_TIMEOUT_MIN_DEPTH 3

struct SearchStepResult {
    int evaScore = 0;
    LegalMove move;
#if defined(_DEBUG) && defined(DEBUG_RECORD_ALL_SEARCH_STEP)
    vector<tuple<int, LegalMove, int>> hh;
#endif
};

class GameFullStatus {
public:
    int player;
    int (*board)[GRID_NUM];
    vector<pair<int, Point>> playHistory;
    unsigned long long zobrist;

    inline bool putChess(const LegalMove &move);

    inline bool unputChess(const LegalMove &move);
};

extern int root_depth;

Point searchMove();//ËÑË÷ºËÐÄ

extern clock_t startClock;

inline void setStartClock() {
    startClock = clock();
}

inline int nowToStartMsec() {
    return (clock() - startClock) * 1000 / CLOCKS_PER_SEC;
}

#endif
