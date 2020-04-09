#include "define.h"
int gameover()//�ж��Ƿ���Ϸ������δ��������0���ѽ�������1��2��ʾʤ����һ��
{
    //���û�п�λ���ˣ����Ǻ���
    if (emptyPlaces.empty()) return draw;
    // ����_continuousPiecesCount[0]�����4�����max_element���ط�0��λ�ã�
    // ���ҽ���_continuousPiecesCount[1]��[2]>=5��Ҳ������ϷӦ��������
    int* maxPointer = std::max_element(_continuousPiecesCount, _continuousPiecesCount + 3);
    return (int)(maxPointer - _continuousPiecesCount);
}

int _continuousPiecesCount[3] = {4, 0, 0};//��i��Ԫ�ر�ʾ���i��ǰ�������������ĳ��ȡ�

int _spreadDirections[8][2] = { {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}};

void updateContinuousPieceCount() {
    pair<int, Point> lastPlayPair = history[history.size() - 1];
    int lastPlayer = lastPlayPair.first;
    Point lastPoint = lastPlayPair.second;
    int lineResults[4] = {1, 1, 1, 1};
    for (int d=0; d<8; d++) {
        int deltaX = _spreadDirections[d][0];
        int deltaY = _spreadDirections[d][1];
        int i;
        for (i = 0; i <= 4; i++) {
            int newX = lastPoint.x + ((i + 1) * deltaX);
            int newY = lastPoint.y + ((i + 1) * deltaY);
            if (!(inboard(newX, newY) && chessBoard[newX][newY] == lastPlayer)) break;
        }
        lineResults[d % 4] += i;
    }
    int maxValue = *(std::max_element(lineResults, lineResults + 4));
    _continuousPiecesCount[lastPlayer] = std::max(_continuousPiecesCount[lastPlayer], maxValue);
}
