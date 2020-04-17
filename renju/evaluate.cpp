#include "define.h"
#include "evaluate.h"

int evaluate(const int board[GRID_NUM][GRID_NUM], int player,const vector<pair<int, Point>>& playHistory)//��ֵ�㷨�����ع�ֵ��������Խ���ʾ�ڷ�Խ�á�
{
	reset();
	//����
	 for(int i=1;i<GRID_NUM;i++)
		 for (int j = 1; j < GRID_NUM; j++)
		 {
			 if (board[i][j] == black)
			 {
				 evaluatePoint(board, black, white,i,j);
			 }
			 if (board[i][j] == white)
			 {
				 evaluatePoint(board, white,black, i, j);
			 }
		 }
	 int score=0;
	 if (player == black)
	 {
		 score = getScore(board,black_count, white_count, playHistory);
	 }
	 else
	 {
		 score = (-getScore(board,white_count, black_count, playHistory));
	 }

	 return score;
} 

//���̷�ΧΪ 1-15
void evaluatePoint(const int board[GRID_NUM][GRID_NUM], int player,int opponent, int p_x,int p_y)
{
	//4�������ϲ�������
	for (int i = 0; i < 4; i++)
	{
		if (record[p_x][p_y][i] == 0)
		{
			analysisLine(board,player,opponent, p_x, p_y,i);
		}
	}
}

void reset()
{
	//���¼�¼ֵ
	for(int i=0;i<GRID_NUM;i++)
		for (int j = 0; j < GRID_NUM; j++)
			for (int k = 0; k < 4; k++)
			{
				record[i][j][k] = 0;
			}
	//����������
	for (int i = 0; i < 8; i++)
	{
		black_count[i] = 0;
		white_count[i] = 0;
	}
}

//��Ҫ�жϵĹؼ����ͣ����壬���ģ����ģ����������������
void analysisLine(const int board[GRID_NUM][GRID_NUM], int player,int opponent, int p_x, int p_y,int dir_idx)
{
	int line[9];
	int count[8] = {0};
	//�õ�ĳ�������ϵ��Բ��ҵ�Ϊ���ĵ�9������
	getline(board, player, opponent, p_x, p_y, dir_idx, line);
	int left_index, right_index;
	left_index = right_index = 4;
	//�õ����������ĵ�һ���������ӵ����λ��
	while (left_index > 0)
	{
		if (line[left_index - 1] != player)
		{
			break;
		}
		left_index = left_index - 1;
	}
	//�õ��ұ�������ĵ�һ���������ӵ����λ��
	while (right_index < 8)
	{
		if (line[right_index + 1] != player)
		{
			break;
		}
		right_index = right_index + 1;
	} 
	//��¼�Ѿ���ǹ������ӣ���ֹ��¼�ظ�����
	set_record(board, p_x, p_y, left_index, right_index, dir_idx);
	//��ȡ���ӵķ�Χ
	int range = right_index - left_index + 1; 
	//���壺MMMMM��ֱ�ӷ���
	if (range == 5)
	{
		count[Five] += 1;
	}
    
	//�����Ƿ�Ϊ��
	bool left_empty,right_empty;
	left_empty = right_empty = false;

	//���� XMMMMX
	//���� PMMMMX��XMMMMP
	if (range == 4)
	{
		if (line[left_index - 1] == Empty)
		{
			left_empty = true;
		 }
		if (line[right_index + 1] == Empty)
		{
			right_empty = true;
		}
		//XMMMMX
		if (right_empty&&left_empty)
		{
			count[LFour] += 1;
		}
		//PMMMMX
		else if (right_empty && !left_empty)
		{
			count[SFour] += 1;
		}
		//XMMMMP
		else if (!right_empty&&left_empty)
		{
			count[SFour] += 1;
		}
	}

	//���� MMMXM,MXMMM
	//���� XXMMMX,XMMMXX  
	//���� PMMMXX,XXMMMP,PXMMMXP
	if (range == 3)
	{
		
		if (line[right_index + 1] == Empty)
		{
			//MMMXM
			if (line[right_index + 2] == player)
			{
				count[SFour] += 1;
				record[p_x + (right_index + 2 - 4)*dir_set[dir_idx].x][p_y + (right_index + 2 - 4)*dir_set[dir_idx].y][dir_idx] = 1;
			}
			//PMMMXX
			if (line[right_index + 2] == Empty && line[left_index - 1] == opponent)
			{
				count[SThree] += 1;
			}
		}
		
		if (line[left_index - 1] == Empty)
		{
			//MXMMM
			if (line[left_index - 2] == player)
			{
				count[SFour] += 1;
				record[p_x + (left_index - 2 - 4)*dir_set[dir_idx].x][p_y + (right_index - 2 - 4)*dir_set[dir_idx].y][dir_idx] = 1;
			}
			//XXMMMP
			if (line[left_index - 2] == Empty && line[right_index + 1] == opponent)
			{
				count[SThree] += 1;
			}
		}
		
		if (line[left_index - 1] == Empty && line[right_index + 1] == Empty)
		{
			//XXMMMX,XMMMXX
			if (line[left_index - 2] == Empty || line[right_index + 2] == Empty)
			{
				count[LThree] += 1;
			}
			//PXMMMXP
			else if (line[left_index - 2] == opponent || line[right_index + 2] == opponent)
			{
				count[SThree] += 1;
			}
		}
	}

	//���� MMXMM ֻ�ü��һ������
	//���� XMXMMX,XMMXMX
	//���� PMXMMX,XMXMMP,PMMXMX,XMMXMP
    //��� XMMX	���������ظ����� 
	bool rightTwo = false;
	bool leftTwo = false;
	if (range == 2)
	{
		if (line[right_index + 1] == Empty)
		{
			
			if (line[right_index + 2] == player)
			{
				rightTwo = true;
				//MMXMM
				record[p_x + (right_index + 2 - 4)*dir_set[dir_idx].x][p_y + (right_index + 2 - 4)*dir_set[dir_idx].y][dir_idx] = 1;
				if (line[right_index + 3] == player)
				{
					record[p_x + (right_index + 3 - 4)*dir_set[dir_idx].x][p_y + (right_index + 3 - 4)*dir_set[dir_idx].y][dir_idx] = 1;
					count[SFour]++;
				}
				else if (line[right_index + 3] == Empty)
				{
					//XMMXMX
					if (line[left_index - 1] == Empty)
					{
						count[LThree]++;
					}
					//PMMXMX
					else if (line[left_index - 1] == opponent)
					{
						 count[SThree]++;
					}
				}
				else if (line[right_index + 3] = opponent)
				{
					//XMMXMP
					if (line[left_index - 1] == Empty)
					{
						count[SThree]++;
					}
				}
			}
			if (line[left_index - 1] == Empty)
			{
				if (line[left_index - 1] == player)
				{
					record[p_x + (left_index-1 - 4)*dir_set[dir_idx].x][p_y + (left_index - 1 - 4)*dir_set[dir_idx].y][dir_idx] = 1;
					leftTwo = true;
					//XMXMMX
					if (line[left_index - 2] == Empty)
					{
						count[LThree]++;
					}
					//PMXMMX
					else if (line[left_index - 2] == opponent)
					{
						count[SThree]++;
					}
				}
				//XMMX
				if (!rightTwo)
				{
					count[Two]++;
				}
			}
		}
		//	XMXMMP
		else if (line[left_index - 1] == Empty && line[left_index - 2] == player && line[left_index - 3] == Empty)
		{
			record[p_x + (left_index - 2 - 4)*dir_set[dir_idx].x][p_y + (left_index - 2 - 4)*dir_set[dir_idx].y][dir_idx] = 1;
			count[SThree]++;
		}

	}

	//��� XMXMX, XMXXMX ֻ���һ������
	if (range == 1)
	{
		if (line[left_index - 1] == Empty)
		{
			if (line[right_index + 1] == Empty)
			{
				if (line[right_index + 2] == player && line[right_index + 3] == Empty)
				{
					count[Two]++;
				}
				else if (line[right_index + 2] == Empty && line[right_index + 3] == player && line[right_index + 4] == Empty)
				{
					count[Two]++;
				}
			}
		}
	}
	if (player == black)
	{
		for (int i = 1; i < 7; i++)
		{
			black_count[i] += count[i];
		}
	}
	else
	{
		for (int i = 1; i < 7; i++)
		{
			white_count[i] += count[i];
		}
	}
}

void getline(const int board[GRID_NUM][GRID_NUM], int player, int opponent, int p_x, int p_y, int dir_idx,int line[])
{
	int temp_x = p_x + (-5)*dir_set[dir_idx].x;
	int temp_y = p_y + (-5)*dir_set[dir_idx].y;
	
	for (int i = 0; i < 9; i++)
	{
		temp_x = temp_x + dir_set[dir_idx].x;
		temp_y = temp_y + dir_set[dir_idx].y;
		//Խ��ֱ�����������Ӵ��������ͬ
		if (temp_x < 1 || temp_x>15 || temp_y < 1 || temp_y>15)
		{
			line[i] = opponent;
		}
		else
		{
			line[i] = board[temp_x][temp_y];
		}
	}
}

//����Ѿ�����¼�����ӣ���ֹ�ظ�
void set_record(const int board[GRID_NUM][GRID_NUM],int p_x, int p_y, int left,int right,int dir_idx)
{
	int temp_x= p_x + (-5+left)*dir_set[dir_idx].x;
	int temp_y = p_y + (-5 + left)*dir_set[dir_idx].y;
	for (int i = left; i < right + 1; i++)
	{
		temp_x += dir_set[dir_idx].x;
		temp_y += dir_set[dir_idx].y;
		record[temp_x][temp_y][dir_idx] = 1;
	}
}


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
int getScore(const int board[GRID_NUM][GRID_NUM],int mine_count[],int oppo_count[],const vector<pair<int, Point>>& playHistory)
{
	if (mine_count[Five] > 0 && oppo_count[Five] > 0)
	{
		int player = playHistory.back().first;
		Point point = playHistory.back().second;
		vector<pair<int, Point>> newHistory = playHistory;
		newHistory.pop_back();
		int newBoard[GRID_NUM][GRID_NUM];
		memcpy(newBoard, board, sizeof(int) * GRID_NUM * GRID_NUM);
		newBoard[point.x][point.y] = 0;
		return evaluate(newBoard, oppositePlayer(player), newHistory);
	}
	if (mine_count[Five] > 0&&oppo_count[Five]==0)
	{
		return TFiveS;
	 }
	if (oppo_count[Five] > 0&&mine_count[Five]==0)
	{
		return NTFiveS;
	}
	if (mine_count[SFour] > 1)
	{
		mine_count[LFour]++;
	}
	if (oppo_count[LFour] > 0)
	{
		return NTLFourS;
	}
	if (oppo_count[SFour] > 0)
	{
		return NTSFourS;
	}
	if (mine_count[LFour] > 0)
	{
		return TFourS;
	}
	if (mine_count[SFour] > 0 && mine_count[LThree] > 0)
	{
		return TSFourALThree;
	}
	if (mine_count[SFour] == 0 && oppo_count[LThree] > 0)
	{
		return -9010;
	}
	if (mine_count[LThree] > 1 && oppo_count[LThree] == 0 && oppo_count[SThree] == 0)
	{
		return 9000;
	}
	int mine_score, oppo_score;
	mine_score = oppo_score = 0;
	if (mine_count[SFour] > 0)
	{
		mine_score += TSFourS;
	}
	if (oppo_count[LThree] > 0)
	{
		oppo_score += oppo_count[LThree]*NTLThreeS;
	}
		mine_score += mine_count[LThree] * TLThreeS;
		mine_score += mine_count[SThree] * TSThreeS;
		mine_score += mine_count[Two] * TTwoS;
		oppo_score += oppo_count[SThree] * NTSThreeS;
		oppo_score += oppo_count[Two] * NTTwoS;
		return mine_score - oppo_score;
}