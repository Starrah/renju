#include "define.h"
#include "printchessboard.h"
#include "makemove.h"
#include "debugChessEvaluate.h"

//存盘
void saveChess() {
    ofstream OutFile("ChessSave.txt");
    for (std::vector<pair<int, Point>>::iterator it = history.begin(); it != history.end(); ++it) {
        OutFile << (*it).first << " " << (*it).second.x << " " << (*it).second.y << endl;
    }
    OutFile.close();
}

//复盘
void reviewChess() {
    ifstream InFile;
    InFile.open("ChessSave.txt");
    if (InFile.fail()) {
        cout << "打开文件失败！" << endl;
    } else {
        int review_x, review_y, review_player;
        while (!InFile.eof()) {
            while (1) {
                InFile >> review_player >> review_x >> review_y;
                chessBoard[review_x][review_y] = review_player;
                print();
                cout << "输入next查看下一步" << endl;
                cout << "输入exit退出复盘" << endl;
                string next;
                cin >> next;
                if (next == "next") {
                    break;
                } else if (next == "exit") {
                    return;
                }
            }
        }
    }
}

int main() {
    DebugEvaluate();

    cout << "*************五子棋人机对弈AI*************" << endl;
    cout << "输入: replay  播放复盘" << endl;
    cout << "输入: newblack  电脑先手" << endl;
    cout << "输入: newwhite  电脑后手" << endl;
    //设置先手
    while (true) {
        string setting;
        getline(cin, setting);
        if (setting.find("replay") != string::npos) {
            reviewChess();
            return 0;
        } else if (setting.find("newblack") != string::npos) {
            currentPlayer = black;
            break;
        } else if (setting.find("newwhite") != string::npos) {
            currentPlayer = white;
            break;
        } else {
            cout << "输入的参数不正确。请输入\"replay\"或\"newblack\"或\"newwhite\"。" << endl;
            continue;
        }
    }

    system("cls");
    initializeGame();
    cout << "输入: move x y  表示落子点" << endl;
    cout << "输入 regret 表示悔棋" << endl;
    print();

    //游戏主循环
    int gameOverValue = 0;
    do {
        int nowPlayer = currentPlayer;
        Point playPoint;
        while (true) {
            playPoint = currentPlayer == black ? getMoveFromAI() : getMoveFromConsole();
            //悔棋，在自己回合悔棋，每次撤销两个子
            if (playPoint.x == -1 && playPoint.y == -1 && history.size() > 1) {
                unMakeMove();
                unMakeMove();
                print();
                cout << "输入: move x y  表示落子点" << endl;
                cout << "输入 regret 表示悔棋" << endl;
            } else {
                bool moveResult = makeMove(playPoint, currentPlayer);
                if (moveResult) break;
                else {
                    cout << "落子不合法！可能是x、y超出有效范围，x、y需要介于1至"
                            + std::to_string(GRID_NUM - 1) + "之间。" << endl;
                    cout << "输入: move x y  表示落子点" << endl;
                    cout << "输入 regret 表示悔棋" << endl;
                    continue;
                }
            }
        }
        system("cls");
        cout << "输入: move x y  表示落子点" << endl;
        cout << "输入 regret 表示悔棋" << endl;
        print();
        cout << (nowPlayer == black ? "电脑" : "玩家") << "刚刚下了位置("
             << playPoint.x << ", " << playPoint.y << ")" << endl;
        gameOverValue = gameover();
    } while (gameOverValue == 0);

    cout << "游戏结束！" << (gameOverValue == draw ? "和棋！" : (gameOverValue == black ? "恭喜电脑获胜！" : "恭喜玩家获胜！")) << endl;

    //存盘
    cout << "是否要存盘？输入Y 或 N" << endl;
    while (true) {
        string input;
        getline(cin, input);
        if (input == "Y") {
            saveChess();
            break;
        } else if (input == "N") {
            break;
        } else {
            cout << "输入的参数不正确。请输入\"Y\"或\"N\"" << endl;
            continue;
        }
    }

    return 0;
}
