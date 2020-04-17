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
#define MAX_ROOT_DEPTH 20
#define DETECT_TIMEOUT_MIN_DEPTH 3
#define ENABLE_RECORD_DISTANCE_TO_PIECE_MATRIX false
#define ENABLE_DIRECTLY_CALCULATE_DISTANCE_TO_PIECE_MATRIX true
#define SKIP_MOVE_SEARCHING_BY_DISTENCE_TO_OTHER_PIECE__MINVALUE 3

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

SearchStepResult searchStep(GameFullStatus &status, int depth, int alpha, int beta);

Point searchMove();//ËÑË÷ºËÐÄ

extern clock_t startClock;

inline void setStartClock() {
    startClock = clock();
}

inline int nowToStartMsec() {
    return (clock() - startClock) * 1000 / CLOCKS_PER_SEC;
}

#endif
