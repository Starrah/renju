#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
int main()
{
	cout << "*************五子棋人机对弈AI*************" << endl;
	cout << "输入: newblack  电脑先手" << endl;
	cout << "输入: newwhite  电脑后手" << endl;
	//设置先手
    while (true) {
        string setting;
        getline(cin, setting);
        if (setting.find("newblack") != string::npos){
            currentPlayer = black;
            break;
        }
        else if (setting.find("newwhite") != string::npos){
            currentPlayer = white;
            break;
        }
        else {
            cout << "输入的先手参数不正确。请输入\"newblack\"或\"newwhite\"。" << endl;
            continue;
        }
    }

    system("cls");
    cout << "输入: move x y  表示落子点" << endl;
    print();

    //游戏主循环
    int gameOverValue = 0;
    do {
        int nowPlayer = currentPlayer;
        Point playPoint = currentPlayer == black? getMoveFromAI(): getMoveFromConsole();
        bool moveResult = makeMove(playPoint, currentPlayer);
        while (true) {
            if (moveResult) break;
            else {
                cout << "落子不合法！可能是x、y超出有效范围，x、y需要介于1至"
                        + std::to_string(GRID_NUM - 1) + "之间。" << endl;
                continue;
            }
        }
        system("cls");
        cout << "输入: move x y  表示落子点" << endl;
        print();
        cout << (nowPlayer == black? "电脑": "玩家") << "刚刚下了位置("
            << playPoint.x << ", " << playPoint.y << ")" << endl;
        gameOverValue = gameover();
    } while (gameOverValue == 0);

    cout << "游戏结束！恭喜" << (gameOverValue == black? "电脑": "玩家") << "获胜！" << endl;
}
