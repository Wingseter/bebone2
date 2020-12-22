#pragma once
#include "cell.h"
#include <afxwin.h>
#include <list>

class column {
public:
	column(INT x, INT y, INT w, INT h, TCHAR * name, CDC * dc);
	~column();
	void draw();							// column �׸���
	void insertRow(INT nRow, TCHAR * data);	// ���ο� ��� �߰�
	void setXpos(INT x);					// x��ǥ�� �����Ѵ�.
	INT getWidth();							// width ���� ��ȯ�Ѵ�.
private:	
	CDC* c_dc;
	INT xPos, yPos;						// x��ġ, y��ġ
	INT width, height;					// ����, ���� ���� 
	INT cellCount;						// column ���� cell�� ����
	TCHAR* colName;						// column �̸�
	std::list<cell*> cells;				// cell ����
	std::list<cell*>::iterator itor;	// cell itorator

	
};