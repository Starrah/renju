#ifndef _EVALUATE_
#define _EVALUATE_

#include "define.h"
//估值生成器
//对全局进行棋型统计，在已下棋的状态下进行，需遍历所有棋子
//两种方法：遇到关键棋型：必杀（可以判定胜负）返回一定值，否则累加得到总估值
//得到的估值为己方和对方分数之差

int evaluate(const int board[GRID_NUM][GRID_NUM], int player,const vector<pair<int, Point>>& playHistory);//估值算法，返回估值：整数，越大表示黑方越好。
//判定某一点周围的棋型
void evaluatePoint(const int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y);
//每次调用evaluate算法，刷新
void reset();
//判定以该点为中心的某方向上的9个点组成的棋型
void analysisLine(const int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y, int dir_idx);
//得到以该点为中心的某个方向上的9个点的组成
void getline(const int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y, int dir_idx, int line[]);
//标记已经记录棋型的棋子，防止重复计入
void set_record(const int board[GRID_NUM][GRID_NUM], int p_x, int p_y, int left, int right, int dir_idx);
//得到己方的估值
int getScore(const int board[GRID_NUM][GRID_NUM],int mine_count[], int oppo_count[], const vector<pair<int, Point>>& playHistory);

#endif
