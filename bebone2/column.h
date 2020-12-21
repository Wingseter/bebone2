#pragma once
#include "cell.h"
#include <afxwin.h>

class column {
public:
	column(TCHAR * name, INT w, CDC * dc);
	~column();
	void draw();
	void insertRow();
private:	
	CDC* c_dc;
	INT width;
	TCHAR* colName;
};