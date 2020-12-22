#include "pch.h"
#include "column.h"

column::column(INT x, INT y, INT w, INT h, TCHAR* name, CDC* dc)
{
	xPos = x;
	yPos = y;
	width = w;
	height = h;

	colName = name;
	c_dc = dc;
	cellCount = 0;
}

column::~column()
{
}

void column::draw()
{
	CPen newPen, * oldPen;			// ���� ���� pen ���� 
	CBrush newBrush, * oldBrush;	// ä��� ���� brush ����
	INT oldMode;					// �ؽ�Ʈ ����� ���� ���

	// ū �簢�� �׸���
	c_dc->Rectangle(xPos, yPos, xPos + width, yPos + height);
	
	// ������ Cell �׸���
	for (itor = cells.begin(); itor != cells.end(); itor++) {
		cell* itorcell = *itor;
		itorcell->draw();
	}

	// �� �귯�� ����
	newPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	newBrush.CreateSolidBrush(RGB(235, 230, 230));
	oldPen = c_dc->SelectObject(&newPen);
	oldBrush = c_dc->SelectObject(&newBrush);

	c_dc->Rectangle(xPos, yPos, xPos + width, yPos + 20);

	
	c_dc->SelectObject(oldPen);
	c_dc->SelectObject(oldBrush);
	newPen.DeleteObject();
	newBrush.DeleteObject();

	oldMode = c_dc->SetBkMode(TRANSPARENT);
	c_dc->TextOutA(xPos + 7, yPos + 1, colName);
	c_dc->SetBkMode(oldMode);
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

void column::setXpos(INT x)
{
	xPos = x;
}

INT column::getWidth()
{
	return width;
}
