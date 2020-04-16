#include "define.h"
#include "createmoves.h"
#include <cmath>

/**
 * ������㷽ʽ���涨ÿ�����Ժ������б�ߣ���ô��p��center��Ҫ�߼�����
 * @param p
 * @param center
 * @return
 */
inline int ToCenterDistance(const Point& p, const Point& center){
    return max(abs(p.x - center.x), abs(p.y - center.y));
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
    if (curBoard[GRID_NUM / 2][GRID_NUM / 2] == blank) return vector<LegalMove>{LegalMove{BOARD_CENTER}};
    if (centers.empty()) centers.push_back(BOARD_CENTER);
    vector<LegalMove> result;
    for (const Point& emptyPlace: emptyPlaces) {
        if (curBoard[emptyPlace.x][emptyPlace.y] == blank) {
            int minVal = INT_MAX;
            for (const Point& center: centers) {
                minVal = min(minVal, ToCenterDistance(emptyPlace, center));
            }
            result.push_back(LegalMove{emptyPlace, minVal});
        }
    }
    sort(result.begin(), result.end());
    return result;
}
//�������кϷ����ӵ㡣������������˵�������ϵĿհ׵��Ϊ�����߷���