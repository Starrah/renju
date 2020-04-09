#include "define.h"
#include "searchmove.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

bool makeMove(Point p, int player) {
    if(player == currentPlayer && inboard(p.x, p.y) && chessBoard[p.x][p.y] == blank){
        chessBoard[p.x][p.y] = currentPlayer;
        history.emplace_back(currentPlayer, p);
        auto erasedCount = emptyPlaces.erase(p);
        assert(erasedCount);
        updateContinuousPieceCount();
        currentPlayer = oppositePlayer(currentPlayer);
        return true;
    }
    else return false;
}

bool unMakeMove() {
    //撤销落子操作（chessboard[i][j]=0）
    return true;
}

Point getMoveFromConsole() {
    while (true) {
        string input;
        getline(cin, input);
        stringstream ss = stringstream(input);
        string strMove;
        int x, y;
        ss >> strMove >> x >> y;
        if (!(ss.good() || ss.eof()) || strMove != "move") {
            cout << "输入不正确。请输入move x y表示落子点。" << endl;
            continue;
        }
        return {x, y};
    }
}

Point getMoveFromAI() {
    return searchMove();
}

