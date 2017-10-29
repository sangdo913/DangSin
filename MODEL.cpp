#include "MODEL.h"

point3 * MODEL::getVertices()
{
	return vertices;
}

point3 * MODEL::getVectors()
{
	return vectors;
}

pos * MODEL::getLink()
{
	return link;
}

int MODEL::getSize()
{
	return size;
}

void MODEL::setVertices(int size, point3 * getVertices)
{
	this->size = size;
	if (vertices) delete[] vertices;
	this->vertices = new point3[size];
	memcpy(this->vertices, vectors, sizeof(point3)*size);
}

void MODEL::setVectors(int size, point3 * vectors)
{
	this->size = size;
	if (this->vectors) delete[] this->vectors;
	this->vectors = new point3[size];
	memcpy(this->vectors, vectors, sizeof(point3)*size);
}

void MODEL::setLink(int size, pos * link)
{
	this->size = size;
	if (this->link)delete[]link;
	this->link = new pos[size];
	memcpy(this->link, link, sizeof(pos)*size);
}

MODEL::MODEL()
{
	size = 0;
	vectors = nullptr;
	vertices = nullptr;
}

MODEL::MODEL(int sizeOfVertices, point3 * vertices, point3 * NormalVec)
{
	size = sizeOfVertices;

	if (this->vertices) delete[] this->vertices;
	this->vertices = new point3[size];
	memcpy(this->vertices, vertices, sizeof(point3)*size);

	if (this->vectors) delete[] this->vectors;
	this->vectors = new point3[size];
	memcpy(this->vectors, NormalVec, sizeof(point3)*size);
}

MODEL::~MODEL()
{
	if (vectors) delete[]vectors;
	if (vertices)delete[]vertices;
	if (link) delete[]link;
}
