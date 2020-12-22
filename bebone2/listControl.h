#pragma once
#include <stdlib.h>
#include <vector>
#include "column.h"

class listControl {
public:
	listControl(INT x, INT y, INT w, INT h, CDC * dc);
	~listControl();

	// 리스트 컨트롤 그리기
	void draw();

	// 열 추가
	void insertColumn(INT nCol, TCHAR * colName, INT width);

	// 행 추가
	void insertItem(INT nRow, TCHAR * data);

	// 행에 아이템 추가
	void setItemText(INT nRow, INT nSubItem, TCHAR* data);

	// 클라이언트의 가로 세로 길이 가져오기
	void GetClientRect(CRect* rect);

	// 모든 아이템 삭제
	void deleteAllItems();

private:
	INT xPos, yPos;		// x, y 위치
	INT width, height;	// 가로 세로 길이
	CDC * c_dc;		// 그리기 위한 dc
	INT colCount;	// column 개수
	std::vector<column> columns; // column 모음
	std::vector<column>::iterator itor; // column iterator
};