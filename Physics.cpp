#include "Physics.h"

Vector3 & Rect::operator=(const Rect & in)
{
	return Vector3(in.x, in.y, 0);
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
}

RectTransform::RectTransform()
{
	position.x = 0;
	position.y = 0;
	position.depth = 0;
}
