#include"Headers.h"
#define PI 3.141592

float ReturnTheta(float x, float y)
{
	return atanf(y / x);
}

float Get2DLength(float a, float b)
{
	return sqrt(a*a + b*b);
}

void ZRotate(point3 &point, float theta)
{
	float r = Get2DLength(point[0], point[1]);
	point[0] = cos(theta / 180.0f * PI)*r;
	point[1] = sin(theta / 180.0f * PI)*r;
	point[2] = 0;
}

void YRotate(point3 &point, float theta)
{
	float r = Get2DLength(point[0], point[2]);
	point[0] = cos(theta / 180 * PI) * r;
	point[2] = sin(theta / 180 * PI) * r;
}

void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void Normalize(point3 &p)
{
	double d = p[0] * p[0] + p[1] * p[1] + p[2] * p[2];
	if (d > 0)
	{
		float len = (float)(1.0 / sqrt(d));
		p[0] *= len;
		p[1] *= len;
		p[2] *= len;
	}
}
