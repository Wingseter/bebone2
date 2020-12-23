// listControl.cpp : DLL의 초기화 루틴을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "listControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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

// 리스트 컨트롤 그리기
void listControl::draw()
{
	// 사각형으로 전체 리스트 배경을 그린다
	c_dc->Rectangle(xPos, yPos, xPos + width, yPos + height);
	for (itor = columns.begin(); itor != columns.end(); itor++) {
		itor->draw();
	}
}

void listControl::draw(INT otherX, INT otherY, CDC* otherDC)
{
	// 사각형으로 전체 리스트 배경을 그린다
	otherDC->Rectangle(otherX, otherY, otherX + width, otherY + height);

	//  안의 column 그리기
	INT columnX = otherX;
	for (itor = columns.begin(); itor != columns.end(); itor++) {
		itor->draw(columnX, otherY, otherDC);
		columnX += itor->getWidth();
	}
}

void listControl::insertColumn(INT nCol, TCHAR* colName, INT width)
{
	INT columnX = xPos;	// column의 x 좌표는 list control의 x좌표로 초기화
	INT columnY = yPos;	// column의 y 좌표는 list Control 상단에 위치한다.

	// 새로운 Column 생성
	column newColumn = column(columnX, columnY, width, height, colName, c_dc);

	// Column 목록에 Insert
	if (colCount == 0 || nCol == -1 || colCount <= nCol) {
		columns.push_back(newColumn);
	}
	else {
		itor = columns.begin();
		columns.insert(itor + nCol, newColumn);
	}

	// 새로운 Column에 맞추어 width 조절
	for (itor = columns.begin(); itor != columns.end(); itor++) {
		itor->setXpos(columnX);
		columnX += itor->getWidth();
	}

	// 전체 column 개수증가
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

