#include "hashsearch.h"
#include "searchmove.h"

default_random_engine _engine;
uniform_int_distribution<unsigned long long> _randomDis(0, ULLONG_MAX);

unsigned long long _zobristRandArray[GRID_NUM][GRID_NUM][3] = {0};
unsigned long long _zobristPlayerRandValue; //如果player是2，则再额外异或一下这个值。

#define HASHSET_INITIAL_SIZE 3000000

void initializeHashSearchModule() {
    for (int i = 1; i < GRID_NUM; i++) {
        for (int j = 1; j < GRID_NUM; j++) {
            for (int k = 1; k <= 2; k++) {
                _zobristRandArray[i][j][k] = _randomDis(_engine);
            }
        }
    }
    _zobristPlayerRandValue = _randomDis(_engine);
    hashset.rehash(HASHSET_INITIAL_SIZE);
}

unsigned long long calculateZobristFull(int board[GRID_NUM][GRID_NUM], int player) {
    unsigned long long result = 0;
    for (int i = 1; i < GRID_NUM; i++) {
        for (int j = 1; j < GRID_NUM; j++) {
            result ^= _zobristRandArray[i][j][board[i][j]];
        }
    }
    if (player == white) result ^= _zobristPlayerRandValue;
    return result;
}

unordered_set<HashTableItem, HashFunc> hashset;