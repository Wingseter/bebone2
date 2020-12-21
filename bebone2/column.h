#pragma once
#include "cell.h"
#include <afxwin.h>

class column {
public:
	column(CDC * c_dc);
	~column();
private:	
	CDC* c_dc;
};