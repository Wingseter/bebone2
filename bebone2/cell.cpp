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
	// 데이터 출력
	c_dc->TextOutA(x, y, data);
}

void cell::draw(INT x, INT y, CDC* otherDC)
{
	// 데이터 출력
	otherDC->TextOutA(x, y, data);
}

void cell::setText(TCHAR* newData)
{
	// 데이터 설정
	strcpy_s(data, newData);
}


