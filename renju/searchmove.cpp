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

inline void printLogWhenDebug(const GameFullStatus &status, const int &depth, const double &alpha, const double &beta,
                              const SearchStepResult &result) {
#if !defined(NDEBUG) && defined(PRINT_STEP_LOG)
    cout << depth << "\t" << (status.player == black ? "black" : "white") << "\t";
    if (result.move.p.x == 0) {
        cout << "Evaluat" << "\t";
    } else {
        cout << "(" << result.move.p.x << "," << result.move.p.y << ")" << "\t";
    }
    cout << result.evaScore << "\t" << alpha << "," << beta << "\t" << endl;
#endif
}

//double fakeEvaluate(int board[GRID_NUM][GRID_NUM])//估值算法，返回估值：浮点数，越大表示黑方越好。
//{
//    //TODO 删除它，替换为真正evaluate
//    return rand();
//}

inline void make_centers(vector<Point> &result, const GameFullStatus &status, const int &count) {
    int size = status.playHistory.size();
    for (int index = size - 1; size - 1 - index < count && index >= 0; index--) {
        result.push_back(status.playHistory[index].second);
    }
}

#define CENTER_USED_COUNT 2

SearchStepResult searchStep(GameFullStatus &status, int depth, double alpha, double beta) {
    if (cutoffTest(status, depth, alpha, beta)) {
        double evaScore = evaluate(status.board,status.player);
        SearchStepResult evaResult = SearchStepResult{evaScore, Point(0, 0)};
        printLogWhenDebug(status, depth, alpha, beta, evaResult);
        return evaResult;
    }
    SearchStepResult bestResult = SearchStepResult{status.player == black ? DBL_MIN : DBL_MAX,
                                                   LegalMove{Point(0, 0), 0}};
    vector<Point> centers;
    make_centers(centers, status, CENTER_USED_COUNT);
    vector<LegalMove> legalMoves = createMoves(status.board, centers);
    if (status.player == black) {
        for (const LegalMove &move: legalMoves) {
            if(!status.putChess(move)) continue;
            auto res = searchStep(status, depth + 1, alpha, beta);
            SearchStepResult curResult = {res.evaScore, move};
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
            SearchStepResult curResult = {res.evaScore, move};
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

    auto finalRes = searchStep(fullStatus, 0, DBL_MIN, DBL_MAX);
    return finalRes.move.p;
}

