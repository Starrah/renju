#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-deprecated-headers"

#ifndef _DEFINE_
#define _DEFINE_
//ȫ�ֱ�������

#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <set>

#include <cassert>

using namespace std;

#define blank 0		//�հ׵�
#define black 1		//�ڷ�
#define white 2		//�׷�
#define inf 1000000		
#define inboard(a,b) (a>0 && a<=15 && b>0 && b<=15)		//���ڼ����з��Ƿ���������

#define oppositePlayer(a) (a == black? white: black)

#define GRID_NUM 16	//���̹�ģ	
extern int chessBoard[GRID_NUM][GRID_NUM]; //����
int gameover(); //�ж��Ƿ���Ϸ����
extern int _continuousPiecesCount[3];//��i��Ԫ�ر�ʾ���i��ǰ�������������ĳ��ȡ�
void updateContinuousPieceCount();

struct Point{
    int x;
    int y;
    Point(int t_x, int t_y);
    Point();
    inline bool operator<(const Point& other) const {
        return x != other.x? x < other.x: y < other.y;
    }
};

extern int currentPlayer;//1��ʾ���壨���ԣ���2��ʾ���壨��ң�

extern vector<pair<int, Point>> history;//�б��ʾ������ʷ��¼��ÿ��Ԫ����pair��first��ʾ�������ң�second��ʾ�����λ��
extern set<Point> emptyPlaces;
#endif