#include "pch.h"
#include "column.h"

column::column(TCHAR* name, INT w, CDC* dc)
{
	colName = name;
	width = w;
	c_dc = dc;
	cellCount = 0;
}

column::~column()
{
}

void column::draw()
{
	c_dc->Rectangle(0, 0, 10, 10);
	for (itor = cells.begin(); itor != cells.end(); itor++) {
		cell* itorcell = *itor;
		itorcell->draw();
	}
}

void column::insertRow(INT nRow, TCHAR* data)
{
	cell* newCell = new cell(0, 0, data, c_dc);

	if (cellCount == 0 || nRow == -1 || cellCount < nRow) {
		cells.push_back(newCell);
	}
	else {
		INT i = 0;
		for (itor = cells.begin(); itor != cells.end(); itor++, i++) {
			if (nRow == i) {
				cells.insert(itor, newCell);
			}
		}
	}

	cellCount++;
}
