#include "define.h"
#include "createmoves.h"
#include "evaluate.h"
#include <cfloat>

//#define PRINT_STEP_LOG

struct SearchStepResult {
    double evaScore;
    LegalMove move;
};

class GameFullStatus {
public:
    int player;
    int (*board)[GRID_NUM];
    set<LegalMove> &legalMoves;
    vector<LegalMove> &playHistory;

    inline void putChess(const LegalMove &move) {
        assert(board[move.p.x][move.p.y] == blank);
        board[move.p.x][move.p.y] = player;
        playHistory.push_back(move);
        auto count_removed = legalMoves.erase(move);
        assert(count_removed);
        player = oppositePlayer(player);
    }

    inline void unputChess() {
        player = oppositePlayer(player);
        LegalMove& move = playHistory[playHistory.size() - 1];
        auto add_res = legalMoves.insert(move);
        assert(add_res.second);
        playHistory.pop_back();
        assert(board[move.p.x][move.p.y] == player);
        board[move.p.x][move.p.y] = blank;
    }
};

#define MAX_DEPTH_FIXED 4

inline bool cutoffTest(const GameFullStatus &status, const int &depth, const double &alpha, const double &beta) {
    return depth >= MAX_DEPTH_FIXED;
}

inline bool stopSearchSiblingsTest(const SearchStepResult &curResult, const SearchStepResult &bestResult,
                                   const GameFullStatus &status, const int &depth, const double &alpha,
                                   const double &beta) {
    return status.player == black ? (bestResult.evaScore >= beta) : (bestResult.evaScore <= alpha);
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

double fakeEvaluate(int board[GRID_NUM][GRID_NUM])//估值算法，返回估值：浮点数，越大表示黑方越好。
{
    //TODO 删除它，替换为真正evaluate
    return rand();
}

SearchStepResult searchStep(GameFullStatus &status, int depth, double alpha, double beta) {
    if (cutoffTest(status, depth, alpha, beta)) {
        double evaScore = fakeEvaluate(status.board);
        SearchStepResult evaResult = SearchStepResult{evaScore, Point(0, 0)};
        printLogWhenDebug(status, depth, alpha, beta, evaResult);
        return evaResult;
    }
    SearchStepResult bestResult = SearchStepResult{status.player == black ? DBL_MIN : DBL_MAX,
                                                   LegalMove{Point(0, 0), 0}};
    if (status.player == black) {
        set<LegalMove> legalMoves = status.legalMoves;
        for (const LegalMove &move: legalMoves) {
            status.putChess(move);
            auto res = searchStep(status, depth + 1, alpha, beta);
            SearchStepResult curResult = {res.evaScore, move};
            if (curResult.evaScore > bestResult.evaScore) {
                bestResult = curResult;
                alpha = max(alpha, bestResult.evaScore);
            }
            status.unputChess();
            if (stopSearchSiblingsTest(curResult, bestResult, status, depth, alpha, beta)) {
                break;
            }
        }
    } else if (status.player == white) {
        set<LegalMove> legalMoves = status.legalMoves;
        for (const LegalMove &move: legalMoves) {
            status.putChess(move);
            auto res = searchStep(status, depth + 1, alpha, beta);
            SearchStepResult curResult = {res.evaScore, move};
            if (curResult.evaScore < bestResult.evaScore) {
                bestResult = curResult;
                beta = min(beta, bestResult.evaScore);
            }
            status.unputChess();
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
    auto legalMoves = createMoves();
    vector<LegalMove> fakeHistory; //搜索过程中的推演过程的下棋记录，非真实棋盘的记录。
    GameFullStatus fullStatus{currentPlayer, board, legalMoves, fakeHistory};

    auto finalRes = searchStep(fullStatus, 0, DBL_MIN, DBL_MAX);
    return finalRes.move.p;
}
