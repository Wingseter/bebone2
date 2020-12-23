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

// ����Ʈ ��Ʈ�� �׸���
void listControl::draw()
{
	// �簢������ ��ü ����Ʈ ����� �׸���
	c_dc->Rectangle(xPos, yPos, xPos + width, yPos + height);
	for (itor = columns.begin(); itor != columns.end(); itor++) {
		itor->draw();
	}
}

void listControl::draw(INT otherX, INT otherY, CDC* otherDC)
{
	// �簢������ ��ü ����Ʈ ����� �׸���
	otherDC->Rectangle(otherX, otherY, otherX + width, otherY + height);

	//  ���� column �׸���
	INT columnX = otherX;
	for (itor = columns.begin(); itor != columns.end(); itor++) {
		itor->draw(columnX, otherY, otherDC);
		columnX += itor->getWidth();
	}
}

void listControl::insertColumn(INT nCol, TCHAR* colName, INT width)
{
	INT columnX = xPos;	// column�� x ��ǥ�� list control�� x��ǥ�� �ʱ�ȭ
	INT columnY = yPos;	// column�� y ��ǥ�� list Control ��ܿ� ��ġ�Ѵ�.

	// ���ο� Column ����
	column newColumn = column(columnX, columnY, width, height, colName, c_dc);

	// Column ��Ͽ� Insert
	if (colCount == 0 || nCol == -1 || colCount <= nCol ) {
		columns.push_back(newColumn);
	}
	else {
		itor = columns.begin();
		columns.insert(itor + nCol, newColumn);
	}

	// ���ο� Column�� ���߾� width ����
	for (itor = columns.begin(); itor != columns.end(); itor++) {
		itor->setXpos(columnX);
		columnX += itor->getWidth();
	}

	// ��ü column ��������
	colCount++;
}

void listControl::insertItem(INT nRow, TCHAR* data)
{
	itor = columns.begin();

	BOOL first = TRUE;
	for (itor = columns.begin(); itor != columns.end(); itor++) {
		if (first == TRUE) {
			itor->insertRow(nRow, data);
			first = FALSE;
		}
		else {
			itor->insertRow(nRow, "");
		}
	}
}

void listControl::setItemText(INT nRow, INT nSubItem, TCHAR* data)
{
	columns[nSubItem].setCellText(nRow, data);
}

void listControl::GetClientRect(CRect* rect)
{
	rect->SetRect(xPos, yPos, xPos + width, yPos + height);
}

void listControl::deleteAllItems()
{
	for (itor = columns.begin(); itor != columns.end(); itor++) {
		itor->deleteAllCells();
	}
}

