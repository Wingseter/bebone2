#pragma once
#include "cell.h"
#include <afxwin.h>
#include <list>

class column {
public:
	column(TCHAR * name, INT w, CDC * dc);
	~column();
	void draw();
	void insertRow(INT nRow, TCHAR * data);
private:	
	CDC* c_dc;
	INT width;			// 
	INT cellCount;		// column ���� cell�� ����
	TCHAR* colName;		// column �̸�
	std::list<cell*> cells;		// cell ����
	std::list<cell*>::iterator itor; // cell itorator

};