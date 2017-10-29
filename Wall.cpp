#include"Object.h"
#include"Collider.h"
#include "Physics.h"
#include"Wall.h"
#include"DangSinState.h"
#include<math.h>
WALL::WALL(Vector3 position, char index, float length)
{
	transform->position = position;
	SetCollider(ColliderType::WALL, length, index);
}

void WALL::collide(Collider * collider)
{
	Object* colObj= collider->obj;
	Vector3 position = transform->position;
	Vector3 colPos = collider->obj->transform->position;

	
	Transform* colT = colObj->transform;
	float length = collider->length;
	float value = this->collider->length;
	float d;
	int index = ((WallCollider*)this->collider)->getIndex();
	// 0 : x 1 : y 2 :z
	// 0: 작음, 1 : 큼
	switch (index)
	{
		//x 가 기준값보다 작음
	case 0x00:
		d = colT->position.x - position.x;
		//colT->position.x = position.x + length;
		colT->position = colT->position + colT->getVelocity()*(-1)*fabs((length - d)/ colT->getVelocity().x);
		break;

		//y가 기준값보다 작음
	case 0x10:
		colT->position.y = position.y + length;
		
		break;

	case 0x20:
		//z가 기준값 보다 작음
		d = colT->position.z - position.z;
			//colT->position.z = position.z + length;
			colT->position = colT->position + colT->getVelocity()*(-1)*fabs((length - d) /  colT->getVelocity().z);
		break;

	case 0x01:
		d = position.x - colT->position.x;
		colT->position = colT->position + colT->getVelocity()*(-1)*fabs((length - d) / colT->getVelocity().x);
		break;

	case 0x11:
		colT->position.y = position.y - length;
		break;

	case 0x21:
		d = position.z-colT->position.z;
		//colT->position.z = position.z + length;
		colT->position = colT->position + colT->getVelocity()*(-1)*fabs((length - d) / colT->getVelocity().z);
		break;
	}
}

FLOOR::FLOOR(point3 p1, point3 p2, point3 p3, point3 p4,unsigned char* texture)
{
	point3 *points = new point3[4];
	memcpy(points[0], p1, sizeof(point3));
	memcpy(points[1], p2, sizeof(point3));
	memcpy(points[2], p3, sizeof(point3));
	memcpy(points[3], p4, sizeof(point3));
	point3 normal[4];

	memcpy(normal[0], (point3&)Vector3(0, 1, 0), sizeof(point3));
	memcpy(normal[1], (point3&)Vector3(0, 1, 0), sizeof(point3));
	memcpy(normal[2], (point3&)Vector3(0, 1, 0), sizeof(point3));
	memcpy(normal[3], (point3&)Vector3(0, 1, 0), sizeof(point3));
	model = new MODEL(4, points, normal);

	this->texture = new Texture(texture, 2, 2, 3);
	this->model = new MODEL(4, points, normal);

	pos link[4];
	link[0][0] = 0.1f;
	link[0][1] = 0.1f;

	link[1][0] = 0.1f;
	link[1][1] = 0.1f;

	link[2][0] = 0.1f;
	link[2][1] = 0.1f;

	link[3][0] = 0.1f;
	link[3][1] = 0.1f;
	model->setLink(4, link);

	DrawFactory(FaceType::Rectangular);
	delete[] points;
}

Object* a = new StateManager();