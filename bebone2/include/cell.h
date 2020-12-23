#pragma once
#include <afxwin.h>

class cell {
public:
	cell(TCHAR* newData, CDC* dc);
	~cell();
	void draw(INT x, INT y);	// cell 그리기
	void draw(INT x, INT y, CDC* otherDC);	// 프린트용 그리기
	void setText(TCHAR* data);	// cell의 데이터 설정
private:
	TCHAR data[100];	// cell 내부의 데이터
	CDC* c_dc;			// dc 포인터
};