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
	INT xPos, yPos;		// x위치, y위치
	INT width, height;  // 가로, 세로 길이 
	INT cellCount;		// column 안의 cell의 개수
	TCHAR* colName;		// column 이름
	std::list<cell*> cells;		// cell 모음
	std::list<cell*>::iterator itor; // cell itorator
};