#ifndef _EVALUATE_
#define _EVALUATE_

#include "define.h"
//估值生成器
//对全局进行棋型统计，在已下棋的状态下进行，需遍历所有棋子
//两种方法：遇到关键棋型（可以判定胜负）直接返回


int evaluate(int board[GRID_NUM][GRID_NUM], int player );//估值算法，返回估值：整数，越大表示黑方越好。
void evaluatePoint(int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y);
void reset();
void analysisLine(int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y, int dir_idx);
void getline(int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y, int dir_idx, int line[]);
void set_record(int board[GRID_NUM][GRID_NUM], int p_x, int p_y, int left, int right, int dir_idx);
int getScore(int mine_count[], int oppo_count[]);

#endif
