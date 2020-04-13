#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-deprecated-headers"

#ifndef _DEFINE_
#define _DEFINE_
//全局变量定义

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

#define blank 0		//空白点
#define black 1		//黑方
#define white 2		//白方
#define draw 3      //和棋
#define inf 1000000		
#define inboard(a,b) (a>0 && a<=15 && b>0 && b<=15)		//用于检验招法是否在棋盘上
#define Empty 0

#define Two 1
#define LThree 2
#define SThree 3
#define LFour 4
#define SFour 5
#define Five 6

#define TFiveS 10000
#define NTFiveS -10000
#define TFourS 9030
#define NTLFourS -9050
#define NTSFourS -9040
#define TSFourALThree 9020
#define NTLThree -9010
#define TSFourS 1000
#define NTLThreeS 1000
#define TLThreeS 200
#define NTSThreeS 200
#define TSThreeS 100
#define NTTwoS 100
#define TTwoS 50



struct dir
{
	int x;
	int y;
	dir(int t_x, int t_y);
};

static dir dir_set[4] = { {0,1},{1,0},{-1,-1},{1,1} };
static int black_count[8];
static int white_count[8];
#define oppositePlayer(a) (a == black? white: black)

#define GRID_NUM 16	//棋盘规模	
extern int chessBoard[GRID_NUM][GRID_NUM]; //棋盘
static int record[GRID_NUM][GRID_NUM][4] = { 0 };
int gameover(); //判断是否游戏结束
extern int _continuousPiecesCount[3];//第i个元素表示玩家i当前在棋盘上最长连珠的长度。
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

extern int currentPlayer;//1表示黑棋（电脑），2表示白棋（玩家）

extern vector<pair<int, Point>> history;//列表表示下棋历史记录，每个元素是pair，first表示下棋的玩家，second表示下棋的位置
extern set<Point> emptyPlaces;

void initializeGame();
#endif