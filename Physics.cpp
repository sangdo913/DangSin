#include "Physics.h"

Vector3 & Rect::operator=(const Rect & in)
{
	return Vector3(in.x, in.y, 0);
	// TODO: 여기에 반환 구문을 삽입합니다.
}

RectTransform::RectTransform()
{
	position.x = 0;
	position.y = 0;
	position.depth = 0;
}
