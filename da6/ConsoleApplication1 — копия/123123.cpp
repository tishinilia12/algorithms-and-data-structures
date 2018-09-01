// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "c:\tc\bin\my\biblioteka.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int main(void)
{
	int gdriver = DETECT, gmode, errorcode;
	int i, maxx, maxy;
	int poly[8];
	initgraph(&gdriver, &gmode, "");

	maxx = getmaxx(); //Получаем максимальные координаты по х и по у.
	maxy = getmaxy();

	poly[0] = 20; //1-я вершина
	poly[1] = maxy / 2;

	poly[2] = maxx - 20; //2-я вершина
	poly[3] = 20;

	poly[4] = maxx - 50; //3-я вершина
	poly[5] = maxy - 20;

	poly[6] = maxx / 2; //4-я - то же, что и первая
	poly[7] = maxy / 2;

	//Рисуем, меняя способы заполнения
	for (i = EMPTY_FILL; i<USER_FILL; i++)
	{
		setfillstyle(i, getmaxcolor());
		fillpoly(4, poly);
		getch();
	}
	closegraph();
	return 0;
}
