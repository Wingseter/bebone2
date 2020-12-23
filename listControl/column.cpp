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

	// �� �귯�� ����
	newPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	newBrush.CreateSolidBrush(RGB(235, 230, 230));
	oldPen = c_dc->SelectObject(&newPen);
	oldBrush = c_dc->SelectObject(&newBrush);

	// ���� �簢�� �׸���
	c_dc->Rectangle(xPos, yPos, xPos + width, yPos + 20);

	// �� ������� ����
	c_dc->SelectObject(oldPen);
	c_dc->SelectObject(oldBrush);
	newPen.DeleteObject();
	newBrush.DeleteObject();

	// �۲� �Ͼ� ��� ���ֱ�
	oldMode = c_dc->SetBkMode(TRANSPARENT);
	c_dc->TextOutA(xPos + 7, yPos + 1, colName);
	c_dc->SetBkMode(oldMode);

	// ������ Cell �׸���
	INT cellX = xPos + 1;
	INT cellY = yPos;
	for (itor = cells.begin(); itor != cells.end(); itor++) {
		cellY += 20;
		itor->draw(cellX, cellY);
	}
}

void column::draw(INT otherX, INT otherY, CDC* otherDC)
{
	CPen newPen, * oldPen;			// ���� ���� pen ���� 
	CBrush newBrush, * oldBrush;	// ä��� ���� brush ����
	INT oldMode;					// �ؽ�Ʈ ����� ���� ���

	// ū �簢�� �׸���
	otherDC->Rectangle(otherX, otherY, otherX + width, otherY + height);

	// �� �귯�� ����
	newPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	newBrush.CreateSolidBrush(RGB(235, 230, 230));
	oldPen = otherDC->SelectObject(&newPen);
	oldBrush = otherDC->SelectObject(&newBrush);

	// ���� �簢�� �׸���
	otherDC->Rectangle(otherX, otherY, otherX + width, otherY + 20);

	// �� ������� ����
	otherDC->SelectObject(oldPen);
	otherDC->SelectObject(oldBrush);
	newPen.DeleteObject();
	newBrush.DeleteObject();

	// �۲� �Ͼ� ��� ���ֱ�
	oldMode = otherDC->SetBkMode(TRANSPARENT);
	otherDC->TextOutA(otherX + 7, otherY + 1, colName);
	otherDC->SetBkMode(oldMode);

	// ������ Cell �׸���
	INT cellX = otherX + 1;
	INT cellY = otherY + 1;
	for (itor = cells.begin(); itor != cells.end(); itor++) {
		cellY += 20;
		itor->draw(cellX, cellY, otherDC);
	}
}

void column::insertRow(INT nRow, TCHAR* data)
{
	// ���ο� cell ����
	cell newCell = cell(data, c_dc);

	// cell ����
	if (cellCount == 0 || nRow == -1 || cellCount <= nRow) {
		cells.push_back(newCell);
	}
	else {
		INT i = 0;
		itor = cells.begin();

		// cell�� ��ġ�� ã�Ƽ� insert 
		for (itor = cells.begin(); itor != cells.end(); itor++, i++) {
			if (nRow == i) {
				cells.insert(itor, newCell);
			}
		}
	}

	// cell�� ���� ����
	cellCount++;
}

void column::setXpos(INT x)
{
	xPos = x;
}

void column::setCellText(INT nRow, TCHAR* data)
{
	// ��ġ Ž��
	itor = cells.begin();
	for (int i = 0; i < nRow; i++) {
		itor++;
	}

	// �ؽ�Ʈ ����
	itor->setText(data);
}

void column::deleteAllCells()
{
	// ��� �� ����
	for (itor = cells.begin(); itor != cells.end();) {
		itor = cells.erase(itor);
	}

	// ��ü �� ���� 0���� ���� 
	cellCount = 0;
}


INT column::getWidth()
{
	// ���� ��ȯ
	return width;
}
