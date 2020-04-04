#include "define.h"
#include "printchessboard.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

bool makeMove(Point p, int player) {
    if(player == currentPlayer && inboard(p.x, p.y) && chessBoard[p.x][p.y] == blank){
        chessBoard[p.x][p.y] = currentPlayer;
        history.emplace_back(currentPlayer, p);
        updateContinuousPieceCount();
        currentPlayer = currentPlayer == black? white: black;
        return true;
    }
    else return false;
}

bool unMakeMove() {
    //�������Ӳ�����chessboard[i][j]=0��
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
            cout << "���벻��ȷ��������move x y��ʾ���ӵ㡣" << endl;
            continue;
        }
        return {x, y};
    }
}

Point getMoveFromAI() {
    //TODO
    return getMoveFromConsole();
}

