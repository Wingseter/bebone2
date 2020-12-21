#include "pch.h"
#include "listControl.h"

listControl::listControl()
{

}

listControl::listControl(CDC * dc)
{
	c_dc = dc;
}

listControl::~listControl()
{
}

void listControl::draw()
{
	CRect rect;

	c_dc->Rectangle(0, 0, 100, 100);
}
