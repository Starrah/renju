#include "define.h"
#include "createmoves.h"
#include <cmath>
#define BOARD_CENTER Point(8, 8)

inline int L1Distance(const Point& p, const Point& center){
    return abs(p.x - center.x) + abs(p.y - center.y);
}

/**
 * �����Ϸ����߷������߷��Ѿ��ź���˳��
 * �����ǰ���priority���еģ�priorty���㷨Ϊ���������ĵ��L1�������Сֵ��
 * ���ĵ���ʱȡΪ�ڱ��μ���֮ǰ����������λ�á�
 * @param curBoard
 * @param centers
 * @return
 */
vector<LegalMove> createMoves(int curBoard[GRID_NUM][GRID_NUM], vector<Point>& centers) //����ȫ���Ϸ��߷���
{
    vector<LegalMove> result;
    for (const Point& emptyPlace: emptyPlaces) {
        if (curBoard[emptyPlace.x][emptyPlace.y] == blank) {
            int minVal = INT_MAX;
            for (const Point& center: centers) {
                minVal = min(minVal, L1Distance(emptyPlace, center));
            }
            result.push_back(LegalMove{emptyPlace, minVal});
        }
    }
    sort(result.begin(), result.end());
    return result;
}
//�������кϷ����ӵ㡣������������˵�������ϵĿհ׵��Ϊ�����߷���