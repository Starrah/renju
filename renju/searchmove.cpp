#include "define.h"
#include "evaluate.h"
#include "searchmove.h"
#include <cfloat>
//两个内联函数体
#include "stopSearchSiblingsTest.h"
#include "cutoffTest.h"
#include "hashsearch.h"

//#define PRINT_STEP_LOG


bool GameFullStatus::putChess(const LegalMove &move) {
    if (board[move.p.x][move.p.y] != blank) return false;
    board[move.p.x][move.p.y] = player;
    playHistory.emplace_back(player, move.p);
    updateZobristOnMove(zobrist, move.p, player);
    player = oppositePlayer(player);
    return true;
}

bool GameFullStatus::unputChess(const LegalMove &move) {
    if (board[move.p.x][move.p.y] != oppositePlayer(player)) return false;
    player = oppositePlayer(player);
    assert(playHistory[playHistory.size() - 1].first == player &&
           playHistory[playHistory.size() - 1].second.x == move.p.x &&
           playHistory[playHistory.size() - 1].second.y == move.p.y);
    updateZobristOnUnMove(zobrist, move.p, player);
    playHistory.pop_back();
    board[move.p.x][move.p.y] = blank;
    return true;
}

int searchStepTotalCounter = 0;

inline void printLogWhenDebug(const GameFullStatus &status, const int &depth, const int &alpha, const int &beta,
                              const SearchStepResult &result) {
#if defined(_DEBUG) && defined(PRINT_STEP_LOG)
    cout << depth << "\t" << (status.player == black ? "black" : "white") << "\t";
    if (result.move.p.x == 0) {
        cout << "Evaluat" << "\t";
    } else {
        cout << "(" << result.move.p.x << "," << result.move.p.y << ")" << "\t";
    }
    cout << result.evaScore << "\t" << alpha << "," << beta << "\t" << endl;
#endif
}

inline void make_centers(vector<Point> &result, const GameFullStatus &status, const int &count) {
    int size = status.playHistory.size();
    for (int index = size - 1; size - 1 - index < count && index >= 0; index--) {
        result.push_back(status.playHistory[index].second);
    }
}

#define CENTER_USED_COUNT 2

inline Point erasePoint(vector<LegalMove> &vec, const Point &p) {
    for (auto it = vec.begin(); it < vec.end(); it++) {
        if (it->p == p) {
            Point res = it->p;
            vec.erase(it);
            return res;
        }
    }
    return {};
}

SearchStepResult searchStep(GameFullStatus &status, int depth, int alpha, int beta) {
    searchStepTotalCounter++;
    if (cutoffTest(status, depth, alpha, beta)) {
        int evaScore = evaluate(status.board, oppositePlayer(status.player),status.playHistory);
#if defined(_DEBUG) && defined(RECORD_ALL_SEARCH_STEP)
        vector<tuple<int, LegalMove, int>> qwq;
        qwq.emplace_back(evaScore, LegalMove{Point(0, 0), 0}, status.player);
        SearchStepResult evaResult = SearchStepResult{evaScore, Point(0, 0), 0, qwq};
#else
        SearchStepResult evaResult = SearchStepResult{evaScore, Point(0, 0), 0};
#endif
        recordMoveInHashset(status, evaResult, depth, EXACT_VAL);
        printLogWhenDebug(status, depth, alpha, beta, evaResult);
        return evaResult;
    }

    auto resultPrior = findInHashset(status, depth, alpha, beta);
    if (resultPrior.resultType == RECORD_VALID)
        return SearchStepResult{resultPrior.item.score, resultPrior.item.bestMove};//如果发现哈希表中有有效记录，则直接返回结果

    // 产生可行下棋位及其顺序的vector。
    // 规则：如果哈希表中有无效结果，无效结果的move（也就是之前搜索层数不足的时候得到的最好路径）排名第一，
    // 其余的按照LegalMove的权值排列。
    vector<Point> centers;
    make_centers(centers, status, CENTER_USED_COUNT);
    vector<LegalMove> legalMoves = createMoves(status.board, centers);
    if (resultPrior.resultType == RECORD_INVALID) {
        Point eraseResult = erasePoint(legalMoves, resultPrior.item.bestMove);
        if (eraseResult.x) legalMoves.insert(legalMoves.begin(), LegalMove{eraseResult});
    }

    SearchStepResult bestResult = SearchStepResult{status.player == black ? INT_MIN : INT_MAX,
                                                   LegalMove{Point(0, 0), 0}};
    int recordInHashType = EXACT_VAL;
    if (status.player == black) {
        for (const LegalMove &move: legalMoves) {
            if (!status.putChess(move)) continue;
            auto res = searchStep(status, depth - 1, alpha, beta);
#if defined(_DEBUG) && defined(RECORD_ALL_SEARCH_STEP)
            vector<tuple<int, LegalMove, int>> qwq = res.hh;
            qwq.emplace_back(res.evaScore, move, oppositePlayer(status.player));
            SearchStepResult curResult = {res.evaScore, move, qwq};
#else
            SearchStepResult curResult = {res.evaScore, move};
#endif
            if (curResult.evaScore > bestResult.evaScore) {
                bestResult = curResult;
                alpha = max(alpha, bestResult.evaScore);
            }
            bool r = status.unputChess(move);
            assert(r);
            if (stopSearchSiblingsTest(curResult, bestResult, status, depth, alpha, beta)) {
                recordInHashType = BETA_VAL;
                break;
            }
        }
    } else if (status.player == white) {
        for (const LegalMove &move: legalMoves) {
            if (!status.putChess(move)) continue;
            auto res = searchStep(status, depth - 1, alpha, beta);
#if defined(_DEBUG) && defined(RECORD_ALL_SEARCH_STEP)
            vector<tuple<int, LegalMove, int>> qwq = res.hh;
            qwq.emplace_back(res.evaScore, move, oppositePlayer(status.player));
            SearchStepResult curResult = {res.evaScore, move, qwq};
#else
            SearchStepResult curResult = {res.evaScore, move};
#endif
            if (curResult.evaScore < bestResult.evaScore) {
                bestResult = curResult;
                beta = min(beta, bestResult.evaScore);
            }
            bool r = status.unputChess(move);
            assert(r);
            if (stopSearchSiblingsTest(curResult, bestResult, status, depth, alpha, beta)) {
                recordInHashType = ALPHA_VAL;
                break;
            }
        }
    }
    recordMoveInHashset(status, bestResult, depth, recordInHashType);
    printLogWhenDebug(status, depth, alpha, beta, bestResult);
    return bestResult;
}

Point searchMove() //搜索函数主体
{
    int board[GRID_NUM][GRID_NUM];
    memcpy(board, chessBoard, sizeof(int) * GRID_NUM * GRID_NUM);
    vector<pair<int, Point>> fakeHistory = history; //搜索过程中的推演过程的下棋记录，非真实棋盘的记录。
    unsigned long long zobrist = calculateZobristFull(board, currentPlayer);
    GameFullStatus fullStatus{currentPlayer, board, fakeHistory, zobrist};

    searchStepTotalCounter = 0;
    int searchDepth = MAX_DEPTH_FIXED;
    if (evaluate(board, oppositePlayer(currentPlayer),fullStatus.playHistory) >= MUST_WIN_VALUE) searchDepth = 1;
    auto finalRes = searchStep(fullStatus, searchDepth, INT_MIN, INT_MAX);
    return finalRes.move.p;
}

