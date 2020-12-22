#pragma once
#include <stdlib.h>
#include <vector>
#include "column.h"

class listControl {
public:
	listControl(INT x, INT y, INT w, INT h, CDC * dc);
	~listControl();

	// ����Ʈ ��Ʈ�� �׸���
	void draw();

	// �� �߰�
	void insertColumn(INT nCol, TCHAR * colName, INT width);

	// �� �߰�
	void insertItem(INT nRow, TCHAR * data);

	// �࿡ ������ �߰�
	void setItemText(INT nRow, INT nSubItem, TCHAR* data);

	// Ŭ���̾�Ʈ�� ���� ���� ���� ��������
	void GetClientRect(CRect* rect);

	// ��� ������ ����
	void deleteAllItems();

private:
	INT xPos, yPos;		// x, y ��ġ
	INT width, height;	// ���� ���� ����
	CDC * c_dc;		// �׸��� ���� dc
	INT colCount;	// column ����
	std::vector<column> columns; // column ����
	std::vector<column>::iterator itor; // column iterator
};