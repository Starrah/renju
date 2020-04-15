#include "define.h"
#include "evaluate.h"
#include "searchmove.h"
#include <cfloat>
//两个内联函数体
#include "stopSearchSiblingsTest.h"
#include "cutoffTest.h"

//#define PRINT_STEP_LOG


bool GameFullStatus::putChess(const LegalMove &move) {
    if (board[move.p.x][move.p.y] != blank) return false;
    board[move.p.x][move.p.y] = player;
    playHistory.emplace_back(player, move.p);
    player = oppositePlayer(player);
    return true;
}

bool GameFullStatus::unputChess(const LegalMove &move) {
    if (board[move.p.x][move.p.y] != oppositePlayer(player)) return false;
    player = oppositePlayer(player);
    assert(playHistory[playHistory.size() - 1].first == player &&
           playHistory[playHistory.size() - 1].second.x == move.p.x &&
           playHistory[playHistory.size() - 1].second.y == move.p.y);
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

SearchStepResult searchStep(GameFullStatus &status, int depth, int alpha, int beta) {
    searchStepTotalCounter++;
    if (cutoffTest(status, depth, alpha, beta)) {
        int evaScore = evaluate(status.board, oppositePlayer(status.player));
#if defined(_DEBUG) && defined(RECORD_ALL_SEARCH_STEP)
        vector<tuple<int, LegalMove, int>> qwq;
        qwq.emplace_back(evaScore, LegalMove{Point(0, 0), 0}, status.player);
        SearchStepResult evaResult = SearchStepResult{evaScore, Point(0, 0), 0, qwq};
#else
        SearchStepResult evaResult = SearchStepResult{evaScore, Point(0, 0), 0};
#endif
        printLogWhenDebug(status, depth, alpha, beta, evaResult);
        return evaResult;
    }
    vector<Point> centers;
    make_centers(centers, status, CENTER_USED_COUNT);
    vector<LegalMove> legalMoves = createMoves(status.board, centers);
    SearchStepResult bestResult = SearchStepResult{status.player == black ? INT_MIN : INT_MAX,
                                                   LegalMove{Point(0, 0), 0}};
    if (status.player == black) {
        for (const LegalMove &move: legalMoves) {
            if(!status.putChess(move)) continue;
            auto res = searchStep(status, depth + 1, alpha, beta);
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
                break;
            }
        }
    } else if (status.player == white) {
        for (const LegalMove &move: legalMoves) {
            if(!status.putChess(move)) continue;
            auto res = searchStep(status, depth + 1, alpha, beta);
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
                break;
            }
        }
    }
    printLogWhenDebug(status, depth, alpha, beta, bestResult);
    return bestResult;
}

Point searchMove() //搜索函数主体
{
    int board[GRID_NUM][GRID_NUM];
    memcpy(board, chessBoard, sizeof(int) * GRID_NUM * GRID_NUM);
    vector<pair<int, Point>> fakeHistory = history; //搜索过程中的推演过程的下棋记录，非真实棋盘的记录。
    GameFullStatus fullStatus{currentPlayer, board, fakeHistory};

    searchStepTotalCounter = 0;
    auto finalRes = searchStep(fullStatus, 0, INT_MIN, INT_MAX);
    return finalRes.move.p;
}

