#include"physics.h"
#include<math.h>
#include"Headers.h"
#include<iostream>
//∫§≈Õ¿‘¥œ¥Ÿ.
using namespace std;
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

Vector3::Vector3(float fnum[3])
{
	x = fnum[0];
	y = fnum[1];
	z = fnum[2];
}

Vector3::~Vector3()
{
	
}

Vector3& Vector3::normalize()
{
	float l = sqrt(x*x + y*y + z*z);
	
	if (l != 0)
	{
		x /= l;
		y /= l;
		z /= l;
	}
	return (*this);
}

Vector3& Vector3::operator= (const Vector3 &Vector3In)
{
	x = Vector3In.x;
	y = Vector3In.y;
	z = Vector3In.z;

	return *this;
}

ostream& operator<<(ostream& os, const Vector3& In)
{
	os  <<"x: "<< (float)In.x << " y: " <<(float)In.y << " z: " << (float)In.z << endl;

	return os;
}

Vector3& Vector3::operator*= (const float Input)
{
	x *= Input;
	y *= Input;
	z *= Input;

	return *this;
}

Vector3& Vector3::operator+= (const float Input)
{
	x += Input;
	y += Input;
	z += Input;

	return *this;
}

Vector3& Vector3::operator+= (const int Input)
{
	return this->operator +=((float)Input);
}

Vector3& Vector3::operator+= (const double Input)
{
	return this->operator +=((float)Input);
}

Vector3& Vector3::operator+= (const Vector3 &Input)
{
	x += Input.x;
	y += Input.y;
	z += Input.z;

	return *this;
}

Vector3& Vector3::operator-= (const float Input)
{
	x -= Input;
	y -= Input;
	z -= Input;

	return *this;
}

Vector3& Vector3::operator-= (const int Input)
{
	return this->operator +=((float)Input);
}

Vector3& Vector3::operator-= (const double Input)
{
	return this->operator +=((float)Input);
}

Vector3& Vector3::operator/= (const float Input)
{
	if (Input == 0)
	{
		printf("0 division???? it is ignored \n");
		return *this;
	}

	x /= Input;
	y /= Input;
	z /= Input;

	return *this;
}

Vector3 Vector3::operator+ (const Vector3 &Vector3In) const
{
	Vector3 result(0,0,0);
	result.x = x + Vector3In.x;
	result.y = y + Vector3In.y;
	result.z = z + Vector3In.z;

	return result;
}

Vector3 Vector3::operator- (const Vector3 &Vector3In) const
{
	Vector3 result(0, 0, 0);
	result.x = x - Vector3In.x;
	result.y = y - Vector3In.y;
	result.z = z - Vector3In.z;

	return result;
}

Vector3    Vector3::operator*(const int nInput) const
{
	Vector3 result;
	result = *this;

	result.x = result.x*nInput;
	result.y = result.y*nInput;
	result.z = result.z*nInput;
	return result;
}
Vector3    Vector3::operator *(const float Input) const
{
	Vector3 result;
	result = *this;

	result.x = result.x*Input;
	result.y = result.y*Input;
	result.z = result.z*Input;
	return result;
}
Vector3    Vector3::operator *(const double Input) const
{
	Vector3 result;
	result = *this;

	result.x = result.x*Input;
	result.y = result.y*Input;
	result.z = result.z*Input;
	return result;
}

Vector3    Vector3::operator*(const Vector3 &Input) const
{
	Vector3 result;
	result = *this;

	result.x = result.x*Input.x;
	result.y = result.y*Input.y;
	result.z = result.z*Input.z;
	return result;
}

Vector3::operator const point3&() const
{
	point3 result;
	result[0] = x;
	result[1] = y;
	result[2] = z;

	return (point3&) result;
}

Vector3    Vector3::operator/(const int nInput) const
{
	Vector3 result;
	result = *this;

	result.x /= nInput;
	result.y /= nInput;
	result.z /= nInput;
	return result;
}
Vector3    Vector3::operator /(const float nInput) const
{
	Vector3 result;
	result = *this;

	result.x /= nInput;
	result.y /= nInput;
	result.z /= nInput;
	return result;
}
Vector3    Vector3::operator /(const double nInput) const
{
	Vector3 result;
	result = *this;

	result.x /= nInput;
	result.y /= nInput;
	result.z /= nInput;
	return result;
}

float Vector3::distance(Vector3 input)
{
	float dis;
	dis = sqrt((x - input.x)*(x - input.x) + (y - input.y)*(y - input.y) + (z - input.z)*(z - input.z));
	return dis;
}

void Vector3::set(const Vector3 In)
{
	x = In.x;
	y = In.y;
	z = In.z;
}

float		Vector3::inner(const Vector3 &in1, const Vector3 &in2)
{
	return in1.x*in2.x, in1.y*in2.y, in1.z*in2.z;
}

float	Vector3::length(const Vector3 &in)
{
	return sqrt(in.x*in.x + in.y*in.y + in.z*in.z);
}

Vector3& Vector3::normalize(const Vector3 &In)
{
	Vector3 result = In;

	float l = Vector3::length(In);

	if (l == 0)
	{
		result = Vector3(0, 0, 0);
		return result;
	}
	result /= l;

	return result;

}
