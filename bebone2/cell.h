#pragma once
#include <afxwin.h>

class cell {
public:
	cell(CDC * dc);
	~cell();
	void draw(int xPos, int yPos);
private:
	char data[100];
	CDC* dc;
};