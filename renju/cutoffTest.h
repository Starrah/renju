#ifndef RENJU_CUTOFFTEST_H
#define RENJU_CUTOFFTEST_H

#include "searchmove.h"

<<<<<<< HEAD
#define MAX_DEPTH_FIXED 4

=======
>>>>>>> ccc12fc001d04e68d2f905d14320f660915b04d2
inline bool cutoffTest(const GameFullStatus &status, const int &depth, const int &alpha, const int &beta) {
    return depth <= 0;
}
#endif //RENJU_CUTOFFTEST_H
