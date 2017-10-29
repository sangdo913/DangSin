#pragma once
#include"Object.h"

typedef float point4[4];
typedef float pos[2];

class MODEL
{
protected:
	int size;
	point3 * vectors;
	point3* vertices;

	pos* link;
public:
	point3* getVertices();
	point3* getVectors();
	pos* getLink();

	int getSize();

	void setVertices(int size, point3* getVertices);
	void setVectors(int size, point3* vectors);
	void setLink(int size, pos* link);

	MODEL();
	MODEL(int sizeOfVertices, point3* vertices, point3* NormalVec);

	~MODEL();
};