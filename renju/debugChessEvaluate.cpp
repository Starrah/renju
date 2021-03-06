#include "debugChessEvaluate.h"
#include "evaluate.h"
#include "searchmove.h"
#include "hashsearch.h"
#include <sstream>

#define DEBUG_EVALUATE_ENABLE

/**
 * 在这里输入要估值的棋盘：input是一个vector，每个元素表示一个棋盘
 * 每个棋盘由16行字符串相加构成，前15行每一行字符串有15个数，分别代表每个棋子；
 * 最后一行只有一个数取值为1或2，表示**刚刚下过棋**的玩家。
 * 每个数取值0表示该位置无棋子，1表示黑棋，2表示白棋
 * 填写好这个input vector后直接运行程序即可在控制台看到每个棋盘的估值
 */
vector<string> input{
        string() +
        "000000000000000" +
        "000000000000000" +
        "000000000000000" +
        "000000000000000" +
        "000000020000000" +
        "000002221000000" +
        "000000000100000" +
        "000000011000000" +
        "000000010000000" +
        "000000000000000" +
        "000000000000000" +
        "000000000000000" +
        "000000000000000" +
        "000000000000000" +
        "000000000000000" +
        "1",

//            string() +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "1",
//
//            string() +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "1",
//
//            string() +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "000000000000000" +
//            "1",
//
};

void _convertInput(int result[GRID_NUM][GRID_NUM], const string &str) {
    for (int i = 0; i < 15 * 15; i++) {
        int lineNo = (i / 15) + 1;
        int columnNo = (i % 15) + 1;
        result[lineNo][columnNo] = str[i] - '0';
    }
}

void DebugEvaluate() {
#if defined(_DEBUG) && defined (DEBUG_EVALUATE_ENABLE)
    for (const string &one: input) {
        initializeGame();
        int Board[GRID_NUM][GRID_NUM];
        _convertInput(Board, one);
        int player = one[15 * 15] - '0';
        int score = evaluate(Board, player, vector<pair<int, Point>>());
        cout << "DebugEvaluate: " << score << endl;
    }
#endif
}

void DebugSearchMove() {
#if defined(_DEBUG) && defined (DEBUG_EVALUATE_ENABLE)
    for (const string &one: input) {
        initializeGame();
        _convertInput(chessBoard, one);
        currentPlayer = oppositePlayer(one[15 * 15] - '0');
        history.clear();
        auto pres = searchMove();
        cout << "(" << pres.x << "," << pres.y << ")" << "  ";
        cout << DebugAIOutputString<<endl;
    }
#endif
}