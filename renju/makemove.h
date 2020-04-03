#ifndef _MAKEMOVE_
#define _MAKEMOVE_
//走法执行器

#include "define.h"

bool makeMove(Point p, int player);//执行走法

void unMakeMove();//撤销走法

Point getMoveFromConsole();

Point getMoveFromAI();

#endif