#include"Headers.h"
Draw::Draw(): obj(NULL) {}

Draw::Draw(Object *objIn) : obj(objIn)
{
	/*if (this->vertices) delete[] this->vertices;
	this->vertices = new point3[size];
	memcpy(this->vertices, vertices, sizeof(point3)*size);

	if (this->vectors) delete[] this->vectors;
	this->vectors = new point3[size];
	memcpy(this->vectors, vectors, sizeof(point3)*size);*/
}
void Draw::draw() {}

Draw& Draw::operator = (const Draw &In) const
{
	Draw result(obj/*, size, vertices,vectors*/);
	return result;
}

DrawRectangular::DrawRectangular(Object*  obj/*, int size, point3*vertices, point3*vectors*/)
{
	this->obj = obj;
//	this->size = size;
//
//	if (this->vertices != NULL) delete( this->vertices);
//	this->vertices = new point3[size];
//	memcpy(this->vertices, vertices, sizeof(point3)*size);
//
//	//if (this->vectors) delete[] this->vectors;
//	this->vectors = new point3[size];
//	memcpy(this->vectors, vectors, sizeof(point3)*size);
}

DrawTriangle::DrawTriangle(Object* obj/*, int size, point3*vertices, point3*vectors*/)
{
	this->obj = obj;
	//this->size = size;
	//
	//if (this->vertices) delete[] this->vertices;
	//this->vertices = new point3[size];
	//memcpy(this->vertices, vertices, sizeof(point3)*size);

	//if (this->vectors) delete[] this->vectors;
	//this->vectors = new point3[size];
	//memcpy(this->vectors, vectors, sizeof(point3)*size);
}

void DrawTriangle::draw()
{
	point3 vertex;
	MODEL* model = obj->model;

	int size = model->getSize();

	if (size != 0)
	{
		Texture* texture = obj->texture;
		point3* vertices = model->getVertices();
		point3* vectors = model->getVectors();
		pos* link = model->getLink();

		glBegin(GL_TRIANGLE_STRIP);

		for (int i = 0; i < size; i++)
		{
			for (int k = 0; k < 3; k++)
			{
				vertex[k] = vertices[i][k] + *(point3&)(obj->transform->position)[k];
			}
			glNormal3fv(vectors[i]);
			glTexCoord2f(link[i][0],link[i][1]);
			glVertex3fv(vertex);
		}
		glEnd();
	}
}

void DrawRectangular::draw()
{
	point3 vertex;
	MODEL* model = obj->model;

	int size = model->getSize();
	if (size != 0)
	{
		Texture* texture = obj->texture;
		point3* vertices = model->getVertices();
		point3* vectors = model->getVectors();
		pos* link = model->getLink();
		if (texture)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture->getTexID());
		}

		glBegin(GL_QUAD_STRIP);

		for (int i = 0; i < size; i++)
		{
			if (texture && link) glTexCoord2f(link[i][0], link[i][1]);
			for (int k = 0; k < 3; k++)
			{
				vertex[k] = vertices[i][k] + *(point3&)(obj->transform->position)[k];
			}
			glNormal3fv(vectors[i]);
			glVertex3fv(vertex);
		}
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}
}