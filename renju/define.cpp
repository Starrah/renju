#include "define.h"

int chessBoard[GRID_NUM][GRID_NUM];//��������
int currentPlayer = 1;//1��ʾ���壨���ԣ���2��ʾ���壨��ң�
Point::Point(int t_x, int t_y): x(t_x), y(t_y) {}
Point::Point(): Point(0, 0) {}
vector<pair<int, Point>> history;//�б��ʾ������ʷ��¼��ÿ��Ԫ����pair��first��ʾ�������ң�second��ʾ�����λ��
set<Point> emptyPlaces;
