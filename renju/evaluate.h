#ifndef _EVALUATE_
#define _EVALUATE_

#include "define.h"
//��ֵ������
//��ȫ�ֽ�������ͳ�ƣ����������״̬�½��У��������������
//���ַ����������ؼ����ͣ������ж�ʤ����ֱ�ӷ���


int evaluate(int board[GRID_NUM][GRID_NUM], int player );//��ֵ�㷨�����ع�ֵ��������Խ���ʾ�ڷ�Խ�á�
void evaluatePoint(int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y);
void reset();
void analysisLine(int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y, int dir_idx);
void getline(int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y, int dir_idx, int line[]);
void set_record(int board[GRID_NUM][GRID_NUM], int p_x, int p_y, int left, int right, int dir_idx);
int getScore(int mine_count[], int oppo_count[]);

#endif
