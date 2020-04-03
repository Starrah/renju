#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
int main()
{
	cout << "*************�������˻�����AI*************" << endl;
	cout << "����: newblack  ��������" << endl;
	cout << "����: newwhite  ���Ժ���" << endl;
	//��������
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
            cout << "��������ֲ�������ȷ��������\"newblack\"��\"newwhite\"��" << endl;
            continue;
        }
    }

    system("cls");
    cout << "����: move x y  ��ʾ���ӵ�" << endl;
    print();

    //��Ϸ��ѭ��
    int gameOverValue = 0;
    do {
        int nowPlayer = currentPlayer;
        Point playPoint = currentPlayer == black? getMoveFromAI(): getMoveFromConsole();
        bool moveResult = makeMove(playPoint, currentPlayer);
        while (true) {
            if (moveResult) break;
            else {
                cout << "���Ӳ��Ϸ���������x��y������Ч��Χ��x��y��Ҫ����1��"
                        + std::to_string(GRID_NUM - 1) + "֮�䡣" << endl;
                continue;
            }
        }
        system("cls");
        cout << "����: move x y  ��ʾ���ӵ�" << endl;
        print();
        cout << (nowPlayer == black? "����": "���") << "�ո�����λ��("
            << playPoint.x << ", " << playPoint.y << ")" << endl;
        gameOverValue = gameover();
    } while (gameOverValue == 0);

    cout << "��Ϸ��������ϲ" << (gameOverValue == black? "����": "���") << "��ʤ��" << endl;
}
