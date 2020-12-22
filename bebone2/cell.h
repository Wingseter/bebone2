#pragma once
#include <afxwin.h>

class cell {
public:
	cell(TCHAR * newData, CDC * dc);
	~cell();
	void draw(INT x, INT y);
	void setText(TCHAR* data);
private:
	TCHAR data[100];
	CDC* c_dc;
};