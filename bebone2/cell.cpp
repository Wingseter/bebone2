#include "pch.h"
#include "cell.h"

cell::cell(INT x, INT y, TCHAR* newData, CDC* dc)
{
	strcpy_s(data, newData);
	c_dc = dc;
	xPos = x;
	yPos = y;
}

cell::~cell()
{
}

void cell::draw()
{
	c_dc->TextOutA(xPos, yPos, data);
}
