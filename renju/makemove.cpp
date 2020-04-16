#include "define.h"
#include "searchmove.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

bool makeMove(Point p, int player) {
    if (emptyPlaces.size() == (GRID_NUM - 1) * (GRID_NUM - 1) && !(p == BOARD_CENTER)) return false;
    if (player == currentPlayer && inboard(p.x, p.y) && chessBoard[p.x][p.y] == blank){
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

//撤销落子操作：history弹出一项，将棋盘对应点置为0，emptyplaces插入对应点
void unMakeMove() {
	if (!history.empty())
	{
		Point point = history.back().second;
		history.pop_back();
		chessBoard[point.x][point.y] = 0;
		emptyPlaces.insert(point);
	 }
}

Point getMoveFromConsole() {
    while (true) {
        string input;
        getline(cin, input);
        stringstream ss = stringstream(input);
        string strMove;
        int x, y;
        ss >> strMove >> x >> y;
		if (strMove == "regret")
		{
			return { -1,-1 };
		}
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

