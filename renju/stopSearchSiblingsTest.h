#ifndef RENJU_STOPSEARCHSIBLINGSTEST_H
#define RENJU_STOPSEARCHSIBLINGSTEST_H

#include "searchmove.h"

inline bool stopSearchSiblingsTest(const SearchStepResult &curResult, const SearchStepResult &bestResult,
                                   const GameFullStatus &status, const int &depth, const int &alpha,
                                   const int &beta) {
    return status.player == black ? (bestResult.evaScore >= beta) : (bestResult.evaScore <= alpha);
}

#endif //RENJU_STOPSEARCHSIBLINGSTEST_H
