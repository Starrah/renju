#include "define.h"

int chessBoard[GRID_NUM][GRID_NUM];//��������
int currentPlayer = 1;//1��ʾ���壨���ԣ���2��ʾ���壨��ң�
Point::Point(int t_x, int t_y) {
    x = t_x;
    y = t_y;
}
