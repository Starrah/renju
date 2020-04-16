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
#include<fstream>

#include <cassert>

using namespace std;

#if defined(_DEBUG) || !defined(NDEBUG)
#ifndef _DEBUG
#define _DEBUG
#endif
#undef NDEBUG
#else
#undef _DEBUG
#ifndef NDEBUG
#define NDEBUG
#endif
#endif

#define blank 0		//�հ׵�
#define black 1		//�ڷ�
#define white 2		//�׷�
#define draw 3      //����
#define inf 1000000		
#define inboard(a,b) (a>0 && a<=15 && b>0 && b<=15)		//���ڼ����з��Ƿ���������
#define Empty 0

//���ͼ�¼ �����XMMX��������(PMMMX)������(XMMMX)������(PMMMMX)������(XMMMMX)������(MMMMM)
#define Two 1
#define LThree 2
#define SThree 3
#define LFour 4
#define SFour 5
#define Five 6

//�������һ��Ϊ����
//��ɱ��
//�������� 10000
//�������� - 10000
//�����������൱��һ����
//�׻��� - 9050
//�׳��� - 9040
//�ڻ��� 9030
//�ڳ��Ļ��� 9020
//���޳��İ��л��� -9010
//�������������޻��������� 9000
//��� ���� �ۼ�
//TurnFiveScore
#define TFiveS 1000000
//NotTurnFiveScore
#define NTFiveS -1000000
#define TFourS 9030
#define NTLFourS -9050
#define NTSFourS -9040
#define TSFourALThree 9020
#define NTLThree -9010
#define TSFourS 400
#define NTLThreeS 400
#define TLThreeS 100
#define NTSThreeS 100
#define TSThreeS 80
#define NTTwoS 80
#define TTwoS 40

#define MUST_WIN_VALUE 8500 //search��ʱ�������жϣ����Ƿ���ֵ���ڵ��ڸ�ֵ���������Ϊ���б�ʤ����������ֻ����һ����

//����
struct dir
{
	int x;
	int y;
	dir(int t_x, int t_y);
};

static dir dir_set[4] = { {0,1},{1,0},{-1,1},{1,1} };
//���ͼ���
static int black_count[8];
static int white_count[8];
#define oppositePlayer(a) (a == black? white: black)

#define GRID_NUM 16	//���̹�ģ	
extern int chessBoard[GRID_NUM][GRID_NUM]; //����
static int record[GRID_NUM][GRID_NUM][4] = { 0 };//����ʽ�����б�Ǹ������Ƿ��Ѿ�����¼
int gameover(); //�ж��Ƿ���Ϸ����
extern int _continuousPiecesCount[3];//��i��Ԫ�ر�ʾ���i��ǰ�������������ĳ��ȡ�
void updateContinuousPieceCount();
#define BOARD_CENTER Point(8, 8)

struct Point{
    int x;
    int y;
    Point(int t_x, int t_y);
    Point();
    inline bool operator<(const Point& other) const {
        return x != other.x? x < other.x: y < other.y;
    }
    inline bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

extern int currentPlayer;//1��ʾ���壨���ԣ���2��ʾ���壨��ң�

extern vector<pair<int, Point>> history;//�б��ʾ������ʷ��¼��ÿ��Ԫ����pair��first��ʾ�������ң�second��ʾ�����λ��
extern set<Point> emptyPlaces;

void initializeGame();

extern string DebugAIOutputString;
#endif