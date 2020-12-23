#pragma once
#include <afxwin.h>

class cell {
public:
	cell(TCHAR* newData, CDC* dc);
	~cell();
	void draw(INT x, INT y);	// cell �׸���
	void draw(INT x, INT y, CDC* otherDC);	// ����Ʈ�� �׸���
	void setText(TCHAR* data);	// cell�� ������ ����
private:
	TCHAR data[100];	// cell ������ ������
	CDC* c_dc;			// dc ������
};