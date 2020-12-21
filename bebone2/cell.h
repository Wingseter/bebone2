#pragma once
#include <afxwin.h>

class cell {
public:
	cell(INT x, INT y, TCHAR * newData, CDC * dc);
	~cell();
	void draw();
private:
	INT xPos, yPos;
	TCHAR data[100];
	CDC* c_dc;
};