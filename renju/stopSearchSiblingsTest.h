#ifndef RENJU_STOPSEARCHSIBLINGSTEST_H
#define RENJU_STOPSEARCHSIBLINGSTEST_H

#include "searchmove.h"

inline int isDistanceToNearestChessPieceExceedLimit(const LegalMove &move) {
    return move.priority / (GRID_NUM * GRID_NUM);
}


inline bool stopSearchSiblingsTest(const SearchStepResult &curResult, const SearchStepResult &bestResult,
                                   const GameFullStatus &status, const int &depth, const int &alpha,
                                   const int &beta) {
    return (status.player == black ? (bestResult.evaScore >= beta) : (bestResult.evaScore <= alpha)) ||
#if ENABLE_RECORD_DISTANCE_TO_PIECE_MATRIX
           isDistanceToNearestChessPieceExceedLimit(curResult.move) ||
#endif
           (depth >= DETECT_TIMEOUT_MIN_DEPTH && root_depth >= STOP_MIN_ROOT_DEPTH &&
            nowToStartMsec() > TIME_GIVEN_MSEC);
}

#endif //RENJU_STOPSEARCHSIBLINGSTEST_H
