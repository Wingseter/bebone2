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
	CPen newPen, * oldPen;			// 선을 위한 pen 설정 
	CBrush newBrush, * oldBrush;	// 채우기 위한 brush 설정
	INT oldMode;					// 텍스트 배경을 위한 모드

	// 큰 사각형 그리기
	c_dc->Rectangle(xPos, yPos, xPos + width, yPos + height);

	// 팬 브러시 설정
	newPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	newBrush.CreateSolidBrush(RGB(235, 230, 230));
	oldPen = c_dc->SelectObject(&newPen);
	oldBrush = c_dc->SelectObject(&newBrush);

	// 제목 사각형 그리기
	c_dc->Rectangle(xPos, yPos, xPos + width, yPos + 20);

	// 펜 원래대로 변경
	c_dc->SelectObject(oldPen);
	c_dc->SelectObject(oldBrush);
	newPen.DeleteObject();
	newBrush.DeleteObject();

	// 글꼴 하얀 배경 없애기
	oldMode = c_dc->SetBkMode(TRANSPARENT);
	c_dc->TextOutA(xPos + 7, yPos + 1, colName);
	c_dc->SetBkMode(oldMode);

	// 내부의 Cell 그리기
	INT cellX = xPos + 1;
	INT cellY = yPos;
	for (itor = cells.begin(); itor != cells.end(); itor++) {
		cellY += 20;
		itor->draw(cellX, cellY);
	}
}

void column::draw(INT otherX, INT otherY, CDC* otherDC)
{
	CPen newPen, * oldPen;			// 선을 위한 pen 설정 
	CBrush newBrush, * oldBrush;	// 채우기 위한 brush 설정
	INT oldMode;					// 텍스트 배경을 위한 모드

	// 큰 사각형 그리기
	otherDC->Rectangle(otherX, otherY, otherX + width, otherY + height);

	// 팬 브러시 설정
	newPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	newBrush.CreateSolidBrush(RGB(235, 230, 230));
	oldPen = otherDC->SelectObject(&newPen);
	oldBrush = otherDC->SelectObject(&newBrush);

	// 제목 사각형 그리기
	otherDC->Rectangle(otherX, otherY, otherX + width, otherY + 20);

	// 펜 원래대로 변경
	otherDC->SelectObject(oldPen);
	otherDC->SelectObject(oldBrush);
	newPen.DeleteObject();
	newBrush.DeleteObject();

	// 글꼴 하얀 배경 없애기
	oldMode = otherDC->SetBkMode(TRANSPARENT);
	otherDC->TextOutA(otherX + 7, otherY + 1, colName);
	otherDC->SetBkMode(oldMode);

	// 내부의 Cell 그리기
	INT cellX = otherX + 1;
	INT cellY = otherY + 1;
	for (itor = cells.begin(); itor != cells.end(); itor++) {
		cellY += 20;
		itor->draw(cellX, cellY, otherDC);
	}
}

void column::insertRow(INT nRow, TCHAR* data)
{
	// 새로운 cell 생성
	cell newCell = cell(data, c_dc);

	// cell 삽입
	if (cellCount == 0 || nRow == -1 || cellCount <= nRow) {
		cells.push_back(newCell);
	}
	else {
		INT i = 0;
		itor = cells.begin();

		// cell의 위치를 찾아서 insert 
		for (itor = cells.begin(); itor != cells.end(); itor++, i++) {
			if (nRow == i) {
				cells.insert(itor, newCell);
			}
		}
	}

	// cell의 개수 증가
	cellCount++;
}

void column::setXpos(INT x)
{
	xPos = x;
}

void column::setCellText(INT nRow, TCHAR* data)
{
	// 위치 탐색
	itor = cells.begin();
	for (int i = 0; i < nRow; i++) {
		itor++;
	}

	// 텍스트 설정
	itor->setText(data);
}

void column::deleteAllCells()
{
	// 모든 셀 삭제
	for (itor = cells.begin(); itor != cells.end();) {
		itor = cells.erase(itor);
	}

	// 전체 셀 개수 0으로 설정 
	cellCount = 0;
}


INT column::getWidth()
{
	// 넓이 반환
	return width;
}
