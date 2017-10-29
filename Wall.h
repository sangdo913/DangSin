#pragma once
#include"Object.h"
class Transform;
class Collider;
class Object;
class Vector3;


class WALL : public Object
{
private:
	Vector3 position;
	char index;
public:
	WALL(Vector3 position, char index, float length);
	virtual void collide(Collider* collider)override;

};

class FLOOR : public Object
{
private:
	Vector3 position;
public:
	FLOOR(point3 p1, point3 p2, point3 p3, point3 p4, unsigned char* texture);
};