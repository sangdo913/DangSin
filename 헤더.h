#pragma once
#include "Headers.h"

class Test
{
public:

	Test();
	Line line[20];
	Line way[5];
	int lineCount;

	point3 color;

	void clearLine();
	void setColor(const point3& colorIn);
	void clearWay();
};