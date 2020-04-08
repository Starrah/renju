#include "define.h"
#include "createmoves.h"
#include <cmath>
#define BOARD_CENTER Point(8, 8)

set<LegalMove> createMoves() //����ȫ���Ϸ��߷���
{
    set<LegalMove> result;
    //����λ������һ�������λ�û���Ԫ
    Point center = BOARD_CENTER;
    if (!history.empty()) center = (history.end() - 1)->second;
    for (int i=1; i<GRID_NUM; i++) {
        for (int j=1; j<GRID_NUM; j++){
            if (chessBoard[i][j] == blank) {
                Point p = Point(i, j);
                auto insRes = result.insert(LegalMove{p, LegalMove::getPriority(p, center)});
                assert_debug(insRes.second);
            }
        }
    }
    return result;
}
//�������кϷ����ӵ㡣������������˵�������ϵĿհ׵��Ϊ�����߷���