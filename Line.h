#pragma once
#include"Physics.h"
#include "Object.h"
class Vector3;
class Obejct;

class Line : public Object
{
private:
	DrawLine* line;
public:
	Line();
	void setStart(Vector3& start);
	void setEnd(Vector3& end);
	void setColor(const point3& color);
};