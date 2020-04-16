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

#define blank 0		//空白点
#define black 1		//黑方
#define white 2		//白方
#define draw 3      //和棋
#define inf 1000000		
#define inboard(a,b) (a>0 && a<=15 && b>0 && b<=15)		//用于检验招法是否在棋盘上
#define Empty 0

//棋型记录 活二（XMMX），眠三(PMMMX)，活三(XMMMX)，冲四(PMMMMX)，活四(XMMMMX)，连五(MMMMM)
#define Two 1
#define LThree 2
#define SThree 3
#define LFour 4
#define SFour 5
#define Five 6

//假设最后一步为黑棋
//必杀：
//黑棋连五 10000
//白棋连五 - 10000
//黑棋两冲四相当于一活四
//白活四 - 9050
//白冲四 - 9040
//黑活四 9030
//黑冲四活三 9020
//黑无冲四白有活三 -9010
//黑有两活三白无活三或眠三 9000
//活二 活三 累加
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

#define MUST_WIN_VALUE 8500 //search的时候用做判断，凡是返回值大于等于该值的情况均作为已有必胜策略来处理，只搜索一步。

//方向
struct dir
{
	int x;
	int y;
	dir(int t_x, int t_y);
};

static dir dir_set[4] = { {0,1},{1,0},{-1,1},{1,1} };
//棋型计数
static int black_count[8];
static int white_count[8];
#define oppositePlayer(a) (a == black? white: black)

#define GRID_NUM 16	//棋盘规模	
extern int chessBoard[GRID_NUM][GRID_NUM]; //棋盘
static int record[GRID_NUM][GRID_NUM][4] = { 0 };//启发式函数中标记该棋子是否已经被记录
int gameover(); //判断是否游戏结束
extern int _continuousPiecesCount[3];//第i个元素表示玩家i当前在棋盘上最长连珠的长度。
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

extern int currentPlayer;//1表示黑棋（电脑），2表示白棋（玩家）

extern vector<pair<int, Point>> history;//列表表示下棋历史记录，每个元素是pair，first表示下棋的玩家，second表示下棋的位置
extern set<Point> emptyPlaces;

void initializeGame();

extern string DebugAIOutputString;
#endif