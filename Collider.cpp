#include "Collider.h"
#include "Physics.h"
#include "Object.h"
#include<math.h>
Collider::Collider()
{
	isTriger = false;
}

Collider::Collider(ColliderType type, float length) : type(type), length(length)
{
	isTriger = false;
}

bool Collider::CheckCollision(Collider *collider)
{
	return false;
}

bool Collider::CheckCollision(Vector3 Vector3, float length)
{
	return false;
}

bool Collider::CheckCollision(float point[4], Vector3 Normal)
{
	return false;
}

bool Collider::CheckCollision(char index, float value)
{
	return false;
}

void Collider::setE(float e)
{
	this->e = e;
}

float Collider::getE() const
{
	return e;
}


CircleCollider::CircleCollider(Object* obj, float length)
{
	this->obj = obj;
	this->length = length;
}

bool CircleCollider::CheckCollision(Collider *collider)
{
	bool check = collider->CheckCollision(obj->transform->position, length);
	return check;
}

bool CircleCollider::CheckCollision(Vector3 point, float length)
{
	Vector3 myPosition = obj->transform->position;
	float distance = Vector3::length(myPosition - point);

	return distance < this->length + length;
}

bool CircleCollider::CheckCollision(float point[4],Vector3 normal)
{
	return false;
}

bool CircleCollider::CheckCollision(char index, float value)
{
	Vector3 position = obj->transform->position;
	// 0 : x 1 : y 2 :z
	// 0: 작음, 1 : 큼
	switch (index)
	{
		//x 가 length보다 작음
	case 0x00:
		return position.x - length < value;
	case 0x10:
		return position.y - length < value;
	case 0x20:
		return position.z - length < value;
	case 0x01:
		return position.x + length > value;
	case 0x11:
		return position.y + length > value;
	case 0x21:
		return position.z + length > value;
	}
	return false;
}

BoxCollider::BoxCollider(Object* obj, float length)
{
	this->obj = obj;
	this->length = length;
}

bool BoxCollider::CheckCollision(Collider *collider)
{
	Transform* myTransform = obj->transform;
	Transform* transform = collider->obj->transform;

	Vector3 myPosition = myTransform->position;
	Vector3 colPosition = transform->position;

	bool check1 = fabsf(myPosition.x - colPosition.x) < length;
	bool check2 = fabsf(myPosition.y - colPosition.y) < length;
	bool check3 = fabsf(myPosition.z - colPosition.z) < length;
	return false;
}

bool BoxCollider::CheckCollision(Vector3 Vector3, float)
{
	return false;
}

bool BoxCollider::CheckCollision(float point[4], Vector3 normal)
{
	return false;
}

WallCollider::WallCollider(Object* obj, float length, char index) :index(index)
{
	this->obj = obj;
	this->length = length;
}

char WallCollider::getIndex()
{
	return index;
}

bool WallCollider::CheckCollision(Collider *collider)
{
	
	return collider->CheckCollision(index,length);
}

bool WallCollider::CheckCollision(Vector3 position, float length)
{
	switch (index)
	{
		//x 가 length보다 작음
	case 0x00:
		return position.x - length < this->length;
	case 0x10:
		return position.y - length < this->length;
	case 0x20:
		return position.z - length < this->length;
	case 0x01:
		return position.x + length > this->length;
	case 0x11:
		return position.y + length > this->length;
	case 0x21:
		return position.z + length > this->length;
	}
	return false;
}
