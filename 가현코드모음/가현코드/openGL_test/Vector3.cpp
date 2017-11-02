#include"Physics.h"
#include<math.h>

//∫§≈Õ¿‘¥œ¥Ÿ.

Vector3::Vector3()
{
	x = 0.0f; y = 0.0f; z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	(*this).x = x;
	(*this).y = y;
	(*this).z = z;
}

Vector3::~Vector3()
{
	
}

Vector3 Vector3::normalize()
{
	float l = sqrt(x*x + y*y + z*z);
	
	x /= l;
	y /= l ;
	z /= l;
	return (*this);
}