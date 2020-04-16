#ifndef _EVALUATE_
#define _EVALUATE_

#include "define.h"
//��ֵ������
//��ȫ�ֽ�������ͳ�ƣ����������״̬�½��У��������������
//���ַ����������ؼ����ͣ���ɱ�������ж�ʤ��������һ��ֵ�������ۼӵõ��ܹ�ֵ
//�õ��Ĺ�ֵΪ�����ͶԷ�����֮��

int evaluate(const int board[GRID_NUM][GRID_NUM], int player,const vector<pair<int, Point>>& playHistory);//��ֵ�㷨�����ع�ֵ��������Խ���ʾ�ڷ�Խ�á�
//�ж�ĳһ����Χ������
void evaluatePoint(const int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y);
//ÿ�ε���evaluate�㷨��ˢ��
void reset();
//�ж��Ըõ�Ϊ���ĵ�ĳ�����ϵ�9������ɵ�����
void analysisLine(const int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y, int dir_idx);
//�õ��Ըõ�Ϊ���ĵ�ĳ�������ϵ�9��������
void getline(const int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y, int dir_idx, int line[]);
//����Ѿ���¼���͵����ӣ���ֹ�ظ�����
void set_record(const int board[GRID_NUM][GRID_NUM], int p_x, int p_y, int left, int right, int dir_idx);
//�õ������Ĺ�ֵ
int getScore(const int board[GRID_NUM][GRID_NUM],int mine_count[], int oppo_count[], const vector<pair<int, Point>>& playHistory);

#endif
