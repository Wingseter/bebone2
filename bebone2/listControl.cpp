#include "pch.h"
#include "listControl.h"


listControl::listControl(INT x, INT y, INT w, INT h, CDC* dc)
{
	xPos = x;
	yPos = y;
	width = w;
	height = h;
	c_dc = dc;

	colCount = 0;
}

listControl::~listControl()
{
}

void listControl::draw()
{
	c_dc->Rectangle(xPos, yPos, width, height);
	INT i = 0;
	for (itor = columns.begin(); itor != columns.end(); itor++, i++) {
		columns[i]->draw();
	}
}

void listControl::insertColumn(INT nCol, TCHAR* colName, INT width)
{
	column* newColumn = new column(colName, width, c_dc);

	if (colCount == 0 || nCol == -1 || colCount < nCol ) {
		columns.push_back(newColumn);
	}
	else {
		INT i = 0;
		for (itor = columns.begin(); itor != columns.end(); itor++, i++) {
			if (nCol == i) {
				columns.insert(itor + 1, newColumn);
			}
		}
	}

	colCount++;
}

void listControl::insertItem(INT nRow, TCHAR* data)
{
	itor = columns.begin();
	columns[nRow]->draw();
}
