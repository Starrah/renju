#ifndef RENJU_CUTOFFTEST_H
#define RENJU_CUTOFFTEST_H

#include "searchmove.h"

inline bool cutoffTest(const GameFullStatus &status, const int &depth, const int &alpha, const int &beta) {
    return depth <= 0;
}
#endif //RENJU_CUTOFFTEST_H
