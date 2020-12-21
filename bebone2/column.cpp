#include "pch.h"
#include "column.h"

column::column(TCHAR* name, INT w, CDC* dc)
{
	colName = name;
	width = w;
	c_dc = dc;
}

column::~column()
{
}

void column::draw()
{
	c_dc->Rectangle(0, 0, 10, 10);
}
