#pragma once
class Object;
class Vector3;

enum class ColliderType
{
	BALL = 0,
	WALL,
	FLOOR
};

class Collider
{
protected:
	float e;//탄성계수
public:
	bool isTriger;

	Collider();
	Collider(ColliderType type, float length);

	float length;

	ColliderType type;
	Object* obj;
	
	virtual bool CheckCollision(Collider *collider);
	virtual bool CheckCollision(Vector3 Vector3, float);
	virtual bool CheckCollision(float point[4],Vector3 Normal);
	virtual bool CheckCollision(char index, float value);
	
	void setE(float e);
	float getE() const;
};

class CircleCollider : public Collider
{
public:
	CircleCollider(Object* obj, float length);
	virtual bool CheckCollision(Collider *collider) override;
	virtual bool CheckCollision(Vector3 Vector3, float) override;
	virtual bool CheckCollision(float point[4], Vector3 normal) override;
	virtual bool CheckCollision(char index, float value) override;
};

class BoxCollider : public Collider
{
public:

	BoxCollider(Object* obj, float length);
	virtual bool CheckCollision(Collider *collider) override;
	virtual bool CheckCollision(Vector3 Vector3, float) override;
	virtual bool CheckCollision(float point[4],Vector3 normal) override;
};

class WallCollider :public Collider
{
private:
	// 앞의숫자 0 : x 1 : y 2 : z , 뒤의숫자 0 : 작음, 1: 큼
	char index;
public:
	WallCollider(Object* obj, float length, char index);
	char getIndex();

	virtual bool CheckCollision(Collider *collider) override;
	virtual bool CheckCollision(Vector3 point, float length) override;
};