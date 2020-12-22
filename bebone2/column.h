#pragma once
#include "cell.h"
#include <afxwin.h>
#include <list>

class column {
public:
	column(INT x, INT y, INT w, INT h, TCHAR * name, CDC * dc);
	~column();
	void draw();							// column 그리기
	void insertRow(INT nRow, TCHAR * data);	// 새로운 요소 추가
	void setXpos(INT x);					// x좌표를 변경한다.
	INT getWidth();							// width 값을 반환한다.
private:	
	CDC* c_dc;
	INT xPos, yPos;						// x위치, y위치
	INT width, height;					// 가로, 세로 길이 
	INT cellCount;						// column 안의 cell의 개수
	TCHAR* colName;						// column 이름
	std::list<cell*> cells;				// cell 모음
	std::list<cell*>::iterator itor;	// cell itorator

	
};