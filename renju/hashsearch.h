#ifndef RENJU_HASHSEARCH_H
#define RENJU_HASHSEARCH_H

#include "define.h"
#include <random>
#include <unordered_set>
#include "searchmove.h"

void initializeHashSearchModule();

extern unsigned long long _zobristRandArray[GRID_NUM][GRID_NUM][3];
extern unsigned long long _zobristPlayerRandValue; //���player��2�����ٶ������һ�����ֵ��

/**
 *
 * @param zobrist
 * @param p
 * @param player �ⲽ����������
 */
inline void updateZobristOnMove(unsigned long long &zobrist, const Point &p, const int &player) {
    zobrist ^= _zobristRandArray[p.x][p.y][player];
    zobrist ^= _zobristPlayerRandValue;
}

/**
 *
 * @param zobrist
 * @param p
 * @param player �ⲽ�����������ʵ���������
 */
inline void updateZobristOnUnMove(unsigned long long &zobrist, const Point &p, const int &player) {
    zobrist ^= _zobristRandArray[p.x][p.y][player];
    zobrist ^= _zobristPlayerRandValue;
}

unsigned long long calculateZobristFull(int board[GRID_NUM][GRID_NUM], int player);


#define EXACT_VAL 0
#define ALPHA_VAL 1
#define BETA_VAL 2

struct HashTableItem {
    unsigned long long zobrist;
    int depth;
    int score;
    int scoreType;
    Point bestMove;

    inline bool operator==(const HashTableItem &item) const {
        return zobrist == item.zobrist;
    }
};

struct HashFunc {
    inline size_t operator()(const HashTableItem &item) const {
        return item.zobrist;
    }
};


extern unordered_set<HashTableItem, HashFunc> hashset;

/**
 * ����ĳһ״̬�µ����������¼����ϣ��
 * @param status
 * @param stepResult
 * @param depth ��һ���������Ӧ���������
 * @param scoreType ������������ͣ�evaluateֱ�Ӳ�����/ALPHA��֦��/BETA��֦��
 * @return �������ϣ���Ƿ�ɹ������ҽ�����ϣ�����Ѿ�����ͬһ��ϣֵ��Ԫ��������Ԫ�ض�Ӧ��depth�ȵ�ǰҪ�����ֵ��depth����
 */
inline bool recordMoveInHashset(const GameFullStatus &status, const SearchStepResult &stepResult, const int &depth,
                                int scoreType) {
    HashTableItem item{status.zobrist, depth, stepResult.evaScore, scoreType, stepResult.move.p};
    auto existedIter = hashset.find(item);
    if (existedIter == hashset.end()) {
        auto insRes = hashset.insert(item);
        assert(insRes.second);
        return true;
    } else {
        if (existedIter->depth <= depth) {
            hashset.erase(existedIter);
            auto insRes = hashset.insert(item);
            assert(insRes.second);
            return true;
        } else {
            return false;
        }
    }
}

#define NO_RECORD 0
#define RECORD_VALID 1
#define RECORD_INVALID 2

struct HashSetFindResult {
    int resultType;
    const HashTableItem &item;
};

inline HashSetFindResult
findInHashset(const GameFullStatus &status, const int &depth, const int &alpha, const int &beta) {
    HashTableItem item{status.zobrist};
    auto existedIter = hashset.find(item);
    if (existedIter == hashset.end()) {
        return HashSetFindResult{NO_RECORD, item};
    } else {
        return {(existedIter->depth >= depth &&
                 ((existedIter->scoreType == EXACT_VAL ||
                   (existedIter->scoreType == ALPHA_VAL &&
                    existedIter->score <= alpha) ||
                   (existedIter->scoreType == BETA_VAL && existedIter->score >= beta))))
                ? RECORD_VALID : (existedIter->bestMove.x ? RECORD_INVALID : NO_RECORD),
                *existedIter};
    }
}


#endif //RENJU_HASHSEARCH_H
