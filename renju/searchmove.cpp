#include "define.h"
#include "evaluate.h"
#include "searchmove.h"
#include <cfloat>
//两个内联函数体
#include "stopSearchSiblingsTest.h"
#include "cutoffTest.h"
#include "hashsearch.h"
#include <sstream>

//#define PRINT_STEP_LOG

int distanceMatrixWhenAISearchBegin[GRID_NUM][GRID_NUM];

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
    return {0, 0};
}

inline int distanceToNearestChessPiece(const LegalMove &move) {
    return move.priority % GRID_NUM;
}

inline bool hasKDisNeighbour(const int board[GRID_NUM][GRID_NUM], const LegalMove &move, int k) {
    for (int i = max(move.p.x - k, 1); i <= min(move.p.x + k, GRID_NUM - 1); i++) {
        for (int j = max(move.p.y - k, 1); j <= min(move.p.y + k, GRID_NUM - 1); j++) {
            if (board[i][j] != blank) return true;
        }
    }
    return move.p.x == GRID_NUM / 2 && move.p.y == GRID_NUM / 2;
}

SearchStepResult searchStep(GameFullStatus &status, int depth, int alpha, int beta) {
    searchStepTotalCounter++;
    if (cutoffTest(status, depth, alpha, beta)) {
        int evaScore = evaluate(status.board, oppositePlayer(status.player), status.playHistory);
#if defined(_DEBUG) && defined(DEBUG_RECORD_ALL_SEARCH_STEP)
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
    vector<LegalMove> legalMoves = createMoves(status.board, centers,
                                               ENABLE_RECORD_DISTANCE_TO_PIECE_MATRIX
                                               ? distanceMatrixWhenAISearchBegin : nullptr);
    if (resultPrior.resultType == RECORD_INVALID) {
        Point eraseResult = erasePoint(legalMoves, resultPrior.item.bestMove);
        if (eraseResult.x) legalMoves.insert(legalMoves.begin(), LegalMove{eraseResult});
    }

    SearchStepResult bestResult = SearchStepResult{status.player == black ? INT_MIN : INT_MAX,
                                                   LegalMove{Point(0, 0), 0}};
    int recordInHashType = EXACT_VAL;
    if (status.player == black) {
        for (const LegalMove &move: legalMoves) {
            if (ENABLE_DIRECTLY_CALCULATE_DISTANCE_TO_PIECE_MATRIX &&
                !hasKDisNeighbour(status.board, move, SKIP_MOVE_SEARCHING_BY_DISTENCE_TO_OTHER_PIECE__MINVALUE - 1))
                continue;
            if (!status.putChess(move)) continue;
            auto res = searchStep(status, depth - 1, alpha, beta);
#if defined(_DEBUG) && defined(DEBUG_RECORD_ALL_SEARCH_STEP)
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
            if (ENABLE_DIRECTLY_CALCULATE_DISTANCE_TO_PIECE_MATRIX &&
                !hasKDisNeighbour(status.board, move, SKIP_MOVE_SEARCHING_BY_DISTENCE_TO_OTHER_PIECE__MINVALUE - 1))
                continue;
            if (!status.putChess(move)) continue;
            auto res = searchStep(status, depth - 1, alpha, beta);
#if defined(_DEBUG) && defined(DEBUG_RECORD_ALL_SEARCH_STEP)
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

int root_depth;
clock_t startClock;

#define FORCE_PRINT_AI_DEBUG_OUTPUT

Point searchMove() //搜索函数主体
{
    int board[GRID_NUM][GRID_NUM];
    memcpy(board, chessBoard, sizeof(int) * GRID_NUM * GRID_NUM);
    vector<pair<int, Point>> fakeHistory = history; //搜索过程中的推演过程的下棋记录，非真实棋盘的记录。
    unsigned long long zobrist = calculateZobristFull(board, currentPlayer);
    GameFullStatus fullStatus{currentPlayer, board, fakeHistory, zobrist};

    setupDistanceMatrix(distanceMatrixWhenAISearchBegin);

    searchStepTotalCounter = 0;
    SearchStepResult finalRes = SearchStepResult{fullStatus.player == black ? INT_MIN : INT_MAX,
                                                 LegalMove{Point(0, 0), 0}};
    int currentEva = evaluate(board, oppositePlayer(currentPlayer), fullStatus.playHistory);
    if (currentEva >= MUST_WIN_VALUE) {
        root_depth = 1;
        // 对于黑方可以必杀结束游戏的情况，就只进行一层搜索以便可以直接结束游戏、不会拖延。
        finalRes = searchStep(fullStatus, 1, INT_MIN, INT_MAX);
    } else {
        setStartClock();//开始计时
        for (root_depth = ROOT_DEPTH_START; root_depth <= MAX_ROOT_DEPTH; root_depth++) {
            auto result = searchStep(fullStatus, root_depth, INT_MIN, INT_MAX);
            assert(fullStatus.player == currentPlayer &&
                   memcmp(fullStatus.board, board, sizeof(int) * GRID_NUM * GRID_NUM) == 0 &&
                   fullStatus.playHistory == fakeHistory && fullStatus.zobrist == zobrist);
            if (root_depth >= STOP_MIN_ROOT_DEPTH - 1 && nowToStartMsec() > TIME_GIVEN_MSEC) {
                // 如果运行到这里，说明迭代深度搜索由于超时而被停止，那么这一搜索就有很大的概率是一个不完整的结果。
                // 在这种情况下，直接选用这个不完整的结果是不合理的，更合理的做法应当是利用这个被中断的部分搜索结果
                // 与之前产生的结果取其中较好的一个。
                if (root_depth < STOP_MIN_ROOT_DEPTH ||
                    ((fullStatus.player == black && result.evaScore > finalRes.evaScore) ||
                     (fullStatus.player == white && result.evaScore < finalRes.evaScore))) {
                    finalRes = result;
                }
                break;
            } else finalRes = result;//除超时外，则结果必定是被完整搜索的，就直接抛弃旧的结果采信新的结果
        }
    }
#if defined(_DEBUG) || defined (FORCE_PRINT_AI_DEBUG_OUTPUT)
    stringstream optss;
    optss << "当前估值" << currentEva << ", " << "搜索最大层数" << root_depth << ", "
          << "总时间" << nowToStartMsec() << "ms, " << "总步数" << searchStepTotalCounter << ", "
          << "评估分数" << finalRes.evaScore << ", " << endl;
    DebugAIOutputString = optss.str();
#endif
    return finalRes.move.p;
}

