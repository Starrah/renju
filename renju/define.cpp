#include "define.h"
#include "hashsearch.h"

int chessBoard[GRID_NUM][GRID_NUM];//��������
int currentPlayer = 1;//1��ʾ���壨���ԣ���2��ʾ���壨��ң�
Point::Point(int t_x, int t_y): x(t_x), y(t_y) {}
Point::Point(): Point(0, 0) {}

dir::dir(int t_x, int t_y) : x(t_x), y(t_y) {}
vector<pair<int, Point>> history;//�б��ʾ������ʷ��¼��ÿ��Ԫ����pair��first��ʾ�������ң�second��ʾ�����λ��
set<Point> emptyPlaces;

void initializeGame() {
    for (int i=0; i<GRID_NUM; i++) {
        for (int j=0;j<GRID_NUM;j++) {
            auto res = emptyPlaces.insert(Point(i, j));
            assert(res.second);
        }
    }
    initializeHashSearchModule();
}
