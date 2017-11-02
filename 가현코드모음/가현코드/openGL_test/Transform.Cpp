#include"Physics.h"
#include"Matrix.h"
class Matrix;

Transform::Transform()
{
	forward = Vector3(0, 0, 1);
	upVector = Vector3(0, 1, 0);
	leftVector = Vector3(1, 0, 0);
	position = Vector3(0, 0, 0);
	velocity = Vector3(0, 0, 0);
	p = Vector3(0, 0, 0);
}

Transform::Transform(Vector3 pos) : position(pos)
{
	forward = Vector3(0, 0, 1);	
	upVector = Vector3(0, 1, 0);
	leftVector = Vector3(1, 0, 0);
	velocity = Vector3(0, 0, 0);
	p = Vector3(0, 0, 0);
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