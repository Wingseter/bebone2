#pragma once
#include <afxwin.h>

class cell {
public:
	cell(TCHAR * newData, CDC * dc);
	~cell();
	void draw(INT x, INT y);
private:
	INT xPos, yPos;
	TCHAR data[100];
	CDC* c_dc;
};