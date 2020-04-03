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
using namespace std;

#define blank 0		//空白点
#define black 1		//黑方
#define white 2		//白方
#define inf 1000000		
#define inboard(a,b) (a>0 && a<=15 && b>0 && b<=15)		//用于检验招法是否在棋盘上

#define GRID_NUM 16	//棋盘规模	
extern int chessBoard[GRID_NUM][GRID_NUM]; //棋盘
int gameover(); //判断是否游戏结束

struct Point{
    int x;
    int y;
    Point(int t_x, int t_y);
};

extern int currentPlayer;//1表示黑棋（电脑），2表示白棋（玩家）
#endif