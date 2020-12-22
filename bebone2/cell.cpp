#include "pch.h"
#include "cell.h"

cell::cell(TCHAR* newData, CDC* dc)
{
	strcpy_s(data, newData);
	c_dc = dc;
}

cell::~cell()
{
}

void cell::draw(INT x, INT y)
{
	c_dc->TextOutA(x, y, data);
}

void cell::setText(TCHAR* newData)
{
	strcpy_s(data, newData);
}

