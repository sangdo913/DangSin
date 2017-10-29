#include"Physics.h"
#include"Matrix.h"
#include<math.h>
#include<iostream>
#include"System.h"
using namespace std;
inline Vector3& getFriction(const Vector3 &a, float magnitude)
{
	Vector3 result;
	result = a*-1;
	result.normalize();

	result *= magnitude;
	return result;
}

Transform::Transform()
{
	forward = Vector3(0, 0, 1);
	upVector = Vector3(0, 1, 0);
	leftVector = Vector3(1, 0, 0);

	position = Vector3(0, 0, 0);
	force = Vector3(0, 0, 0);
	velocity = Vector3(0, 0, 0);

	quaternion = Quaternion();

	friction = 0.0f;
	weight = 1.0f;
}

Transform::Transform(Vector3 pos) : position(pos)
{
	forward = Vector3(0, 0, 1);	
	upVector = Vector3(0, 1, 0);
	leftVector = Vector3(1, 0, 0);
	
	force = Vector3(0, 0, 0);
	velocity = Vector3(0, 0, 0);

	quaternion = Quaternion();

	friction = 0.0f;
	weight = 1.0f;
}

const Vector3* const Transform::Getforward(void)
{
	return &forward;
}

Transform::~Transform()
{
}

const Vector3* const Transform::GetUp(void)
{
	return &upVector;
}
const Vector3* const Transform::GetLeft(void)
{
	return &leftVector;
}

void Transform::rotate(const float xAngle, const float yAngle, const float zAngle)
{
	Matrix xRotate(leftVector);

	xRotate = xRotate.Rotate(xAngle);
	upVector = xRotate*upVector;
	forward = xRotate*forward;


	Matrix yRotate(upVector);
	yRotate = yRotate.Rotate(yAngle);
	forward = yRotate*forward;
	leftVector = yRotate*leftVector;


	Matrix zRotate(forward);
	zRotate = zRotate.Rotate(zAngle);
	upVector = zRotate*upVector;
	leftVector = zRotate*leftVector;
}

Vector3 Transform::move()
{
	velocity = velocity + (force / weight)/System.frame;

	//if (Vector3::length(velocity) < friction / System.frame)
	//{
	//	velocity = Vector3(0, 0, 0);
	////}
	//else
	//{
		Vector3 fric = getFriction(velocity, friction);
		if (Vector3::length(velocity) < friction/System.frame)
		{		
			velocity = Vector3(0, 0, 0);
		}
		else
		{
			velocity = velocity + fric / System.frame;
			position = position + (velocity);
		}
	//}

	force = Vector3(0, 0, 0);

	return position;
}

void Transform::SetForce(const Vector3 force)
{
	this->force = force;
}

void Transform::setVelocity(const Vector3 velocity)
{
	this->velocity = velocity;
}

void Transform::potentiate(const Vector3 force)
{
	this->force += force;
}

void Transform::setFriction(const float friction)
{
	this->friction = friction;
}
void Transform::setWeight(const float weight)
{
	this->weight = weight;
}

void Transform::resetRotate()
{
	this->upVector = Vector3(0, 1, 0);
	forward = Vector3(0, 0, 1);
	leftVector = Vector3(1, 0, 0);
}


const Vector3* Transform::getForce(void) const
{
	return &force;
}

const Vector3 & Transform::getVelocity(void) const
{
	return velocity;
}
