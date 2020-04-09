#ifndef RENJU_CUTOFFTEST_H
#define RENJU_CUTOFFTEST_H

#include "searchmove.h"

#define MAX_DEPTH_FIXED 4

inline bool cutoffTest(const GameFullStatus &status, const int &depth, const double &alpha, const double &beta) {
    return depth >= MAX_DEPTH_FIXED;
}
#endif //RENJU_CUTOFFTEST_H
