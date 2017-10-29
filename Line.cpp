#include "Line.h"

Line::Line()
{
	DrawFactory(FaceType::Line);
	line = (DrawLine*)this->Draw;
}

void Line::setStart(Vector3 & start)
{
	line->setStart(start);
}

void Line::setEnd(Vector3 & end)
{
	line->setEnd(end);
}

void Line::setColor(const point3 & color)
{
	line->setColor(color);
}


