#pragma once
#include<iostream>
using namespace std;
typedef float point3[3];

class Vector3 {
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float x, float y, float z);
	Vector3(float fnum[3]);
	~Vector3();

	Vector3& normalize();

	//define operator 
	Vector3& operator =(const Vector3 &Vector3In);
	Vector3& operator *=(const float Input);

	Vector3& operator +=(const float Input);
	Vector3& operator +=(const double Input);
	Vector3& operator +=(const int Input);
	Vector3& operator +=(const Vector3 &In);

	Vector3& operator -=(const float Input);
	Vector3& operator -=(const int Input);
	Vector3& operator -=(const double Input);

	Vector3& operator /=(const float Input);

	Vector3 operator +(const Vector3 &Vector3In) const;
	Vector3 operator -(const Vector3 &Vector3In) const;
	Vector3 operator *(const int nInput) const;
	Vector3 operator *(const float nInput) const;
	Vector3 operator *(const double nInput) const;
	Vector3 operator *(const Vector3 & VEctor3In) const;
	friend ostream& operator <<(ostream& os, const Vector3 &In);
	

	operator const point3&() const;

	Vector3 operator /(const int nInput) const;
	Vector3 operator /(const float nInput) const;
	Vector3 operator /(const double nInput) const;

	float distance(Vector3 input);

	void set(const Vector3 In);

	static float inner(const Vector3 &In1, const Vector3 &In2);
	static float length(const Vector3 &in);
	static Vector3& normalize(const Vector3 &In);
};

class Quaternion
{
public:
	float x, y, z;

	Quaternion();
	~Quaternion();

};

class Transform
{
private:
	Vector3 forward;
	Vector3 upVector;
	Vector3 leftVector;

	Vector3 force;
	Vector3 velocity;
	float friction;

public:
	Vector3 position;
	Quaternion quaternion;

	float weight;
	Transform();
	Transform(Vector3 position);
	~Transform();

	//Get Functions
	const Vector3* const Getforward(void);
	const Vector3* const GetUp(void);
	const Vector3* const GetLeft(void);

	//physics functions
	Vector3 move(void);
	void SetForce(const Vector3 force);
	void setVelocity(const Vector3 velocity);
	void potentiate(const Vector3 force);
	void setFriction(const float friction);
	void setWeight(const float weight);

	void resetRotate();

	const Vector3* getForce(void) const;
	const Vector3& getVelocity(void) const;
	void rotate(const float xAngle, const float yAngle, const float zAngle);
};
class Rect;

class Rect
{
public:
	int x;
	int y;

	int width;
	int height;
	int depth;

	Vector3& operator =(const Rect& in);
};

class RectTransform
{
public:
	Rect position;
	RectTransform();
};
