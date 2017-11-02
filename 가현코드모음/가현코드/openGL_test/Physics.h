#pragma once

class Vector3 {
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();

	Vector3 normalize();
};



class Transform
{
private:
	Vector3 forward;
	Vector3 upVector;
	Vector3 leftVector;
	

public:
	Vector3 velocity;
	Vector3 position;
	Vector3 p;//momentum

	Transform();
	Transform(Vector3 position);
	~Transform();

	//Functions
	const Vector3* const Getforward(void);
	const Vector3* const GetUp(void);
	const Vector3* const GetLeft(void);
	void rotate(const float xAngle, const float yAngle, const float zAngle);
};
