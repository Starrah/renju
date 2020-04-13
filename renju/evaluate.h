#ifndef _EVALUATE_
#define _EVALUATE_

#include "define.h"
//��ֵ������
//��ȫ�ֽ�������ͳ�ƣ����������״̬�½��У��������������
//���ַ����������ؼ����ͣ���ɱ�������ж�ʤ��������һ��ֵ�������ۼӵõ��ܹ�ֵ
//�õ��Ĺ�ֵΪ�����ͶԷ�����֮��

int evaluate(int board[GRID_NUM][GRID_NUM], int player );//��ֵ�㷨�����ع�ֵ��������Խ���ʾ�ڷ�Խ�á�
//�ж�ĳһ����Χ������
void evaluatePoint(int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y);
//ÿ�ε���evaluate�㷨��ˢ��
void reset();
//�ж��Ըõ�Ϊ���ĵ�ĳ�����ϵ�9������ɵ�����
void analysisLine(int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y, int dir_idx);
//�õ��Ըõ�Ϊ���ĵ�ĳ�������ϵ�9��������
void getline(int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y, int dir_idx, int line[]);
//����Ѿ���¼���͵����ӣ���ֹ�ظ�����
void set_record(int board[GRID_NUM][GRID_NUM], int p_x, int p_y, int left, int right, int dir_idx);
//�õ������Ĺ�ֵ
int getScore(int mine_count[], int oppo_count[]);

#endif
