#include "define.h"
#include "printchessboard.h"
#include "makemove.h"
#include "debugChessEvaluate.h"

//����
void saveChess()
{
	ofstream OutFile("ChessSave.txt");
	for (std::vector<pair<int, Point>>::iterator it = history.begin(); it != history.end(); ++it)
	{
		OutFile << (*it).first <<" "<< (*it).second.x<<" " << (*it).second.y<<endl;
	}
	OutFile.close();
}

//����
void reviewChess()
{
	ifstream InFile;
	InFile.open("ChessSave.txt");
	if (InFile.fail())
	{
		cout << "���ļ�ʧ�ܣ�"<<endl;
	}
	else
	{
		int review_x, review_y, review_player;
		while (!InFile.eof())
		{
			InFile >> review_player >> review_x >> review_y;
			chessBoard[review_x][review_y] = review_player;
			print();
			while (1)
			{
				cout << "����next�鿴��һ��" << endl;
				cout << "����exit�˳�����" << endl;
				string next;
				cin >> next;
				if (next == "next")
				{
					break;
				}
				else if (next == "exit")
				{
					return;
				}
				else
				{
					cout << "��Ч���"<<endl;
				}
			}
	}
	}
}

int main() {
    DebugEvaluate();

	//����
	string save;
	cout << "�Ƿ�Ҫ���̣����� Y �� N" << endl;
	cin >> save;
	if (save == "Y")
	{
		reviewChess();
	}

	cin.ignore();
    cout << "*************�������˻�����AI*************" << endl;
    cout << "����: newblack  ��������" << endl;
    cout << "����: newwhite  ���Ժ���" << endl;
    //��������
    while (true) {
        string setting;
        getline(cin, setting);
        if (setting.find("newblack") != string::npos) {
            currentPlayer = black;
            break;
        } else if (setting.find("newwhite") != string::npos) {
            currentPlayer = white;
            break;
        } else {
            cout << "��������ֲ�������ȷ��������\"newblack\"��\"newwhite\"��" << endl;
            continue;
        }
    }

    system("cls");
    initializeGame();
    cout << "����: move x y  ��ʾ���ӵ�" << endl;
	cout << "���� regret ��ʾ����" << endl;
    print();

    //��Ϸ��ѭ��
    int gameOverValue = 0;
    do {
        int nowPlayer = currentPlayer;
        Point playPoint;
        while (true) {
            playPoint = currentPlayer == black ? getMoveFromAI() : getMoveFromConsole();
			//���壬���Լ��غϻ��壬ÿ�γ���������
			if (playPoint.x == -1 && playPoint.y == -1&&history.size()>1)
			{
				unMakeMove();
				unMakeMove();
				print();
				cout << "����: move x y  ��ʾ���ӵ�" << endl;
				cout << "���� regret ��ʾ����" << endl;
			}
			else
			{
				bool moveResult = makeMove(playPoint, currentPlayer);
				if (moveResult) break;
				else {
					cout << "���Ӳ��Ϸ���������x��y������Ч��Χ��x��y��Ҫ����1��"
						+ std::to_string(GRID_NUM - 1) + "֮�䡣" << endl;
					cout << "����: move x y  ��ʾ���ӵ�" << endl;
					cout << "���� regret ��ʾ����" << endl;
					continue;
				}
			}
        }
        system("cls");
        cout << "����: move x y  ��ʾ���ӵ�" << endl;
		cout << "���� regret ��ʾ����" << endl;
        print();
        cout << (nowPlayer == black ? "����" : "���") << "�ո�����λ��("
             << playPoint.x << ", " << playPoint.y << ")" << endl;
        gameOverValue = gameover();
    } while (gameOverValue == 0);

    cout << "��Ϸ������" << (gameOverValue == draw ? "���壡" : (gameOverValue == black ? "��ϲ���Ի�ʤ��" : "��ϲ��һ�ʤ��")) << endl;
	//����
	cout << "�Ƿ�Ҫ���̣�����Y �� N" << endl;
	cin >> save;
	if (save == "Y")
	{
		saveChess();
	}

	return 0;
}
