#include"Object.h"
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include"Physics.h"
#include <Windows.h>
#include<GL/GL.h>
#include<GL/GLU.h>
#include<GL/glut.h>

#include"Camera.h"
#include"System.h"

#include"Collider.h"

class RectTransform;
class Rect;
void Object::setVertices(int size, point3* vertices,point3* vectors)
{
	model->setVectors(size, vectors);
	model->setVertices(size, vertices);
}

void Object::DrawFactory(FaceType type)
{
	switch (type)
	{
	case FaceType::Triangle:
		Draw = new DrawTriangle(this);
		break;
	case FaceType::Rectangular:
		Draw = new DrawRectangular(this);
		break;
	case FaceType::Line:
		Draw = new DrawLine(this);
		break;
	case FaceType::Rect:
		Draw = new DrawRect(this);
		break;
	case FaceType::Text:
		Draw = new DrawFont(this);
		break;

	default:
		printf("error! no type! \n");
		break;
	}
}

Object::Object() : transform(new Transform())
{
	ObjManager.addObj(this);
	collider = NULL;
	isKinetic = false;
	name = "Object";
//	vertices = nullptr;
	//vectors = nullptr;
	Draw = nullptr;
	collider = nullptr;
	texture = nullptr;
	model = nullptr;
	rect = nullptr;
}


void Object::setModel(int size, point3 * vertices, point3 * NormalVec)
{
	if (model) delete(model);
	model = new MODEL(size, vertices, NormalVec);
}
//
//void Object::SetVertices(int size, point3* vertices)
//{
//	this->size = size;
//	if (this->vertices) delete[] this->vertices;
//	this->vertices = new point3[size];
//	memcpy(this->vertices, vertices, sizeof(point3)*size);
//}


Object* ObjManager::objects[100] = { NULL };
//default : Facetype = Rectangular, Origin = (0,0,0)
Object::Object(int size, point3* vertices, point3* vectors) : /*size(size) , */transform(new Transform())
{
	Object();
	DrawFactory(FaceType::Rectangular);
	setVertices(size, vertices,vectors);
	transform->position = Vector3(0, 0, 0);
}

//default : Origin = (0,0,0): transform(new Transform())
Object::Object(int size, point3* vertices, point3* vectors, FaceType type) : /*size(size), */transform(new Transform())
{
	Object();
	DrawFactory(type);
	setVertices(size, vertices, vectors);
	transform->position = Vector3(0, 0, 0);
}

//default : FaceType : Rectangular
Object::Object(int size, point3* vertices,point3* vectors, point3 point) :/* size(size),*/ transform(new Transform())
{
	Object();
	DrawFactory(FaceType::Rectangular);
	setVertices(size, vertices, vectors);

	transform->position = Vector3(point);
}

Object::Object(int size, point3* vertices, point3* vectors, FaceType type, point3 point) : /*size(size), */ transform(new Transform())
{

	Object();
	DrawFactory(type);
	setVertices(size, vertices, vectors);
	transform->position = Vector3(point);
}

Object::~Object() 
{
	ObjManager.delObj(id);
//	if (vertices) delete[] vertices;
//	if (vectors) delete[] vectors;
	if (Draw) delete(Draw);
	if (transform) delete(transform);
	if (collider) delete(collider);
	if (texture) delete(texture);
	if (model) delete(model);
	if (rect) delete(rect);
}
//
//const int Object::getSize() const
//{
//	return size;
//}
//
//point3 * const Object::getVertices() const
//{
//	return vertices;
//}

void Object::picked()
{
}

int ObjManager::num = 0;

int ObjManager::addObj(Object* obj)
{
	if (checkArr())
	{
		newObjects.push(obj);
		objects[available] = obj;
		obj->id = available;
		num++;
		return available++;
	}
	else
	{
		delete(obj);
	}
	return -1;
}

bool ObjManager::checkArr()
{
	if (num >= 100)
		return false;
	
	while (objects[available % 100] != NULL)
	{
		available++;
		available %= 100;
	}
	return true;
}
void ObjManager::delObj(int num)
{
		(this->num)--;
		objects[num] = NULL;
		available = num;
}

Object* const ObjManager::getObj(int id) const
{
	return objects[id];
}

void ObjManager::Draw(int id) const
{
	(objects[id])->draw();
}

bool ObjManager::CheckCollision(int id1, int id2) const
{
	return false;
}

void ObjManager::Selector() const
{
	int count = 0;
	for (int i = 0; i < 100; i++)
	{
		if (count > num) break;
		if (objects[i] && objects[i]->isPicked)
		{
			Object* obj = objects[i];
			glLoadName(obj->id);
			obj->draw();
			glEnd();
		}

		count++;
	}
}

void ObjManager::Selector(int id) const
{
	objects[id]->picked();
	System.picked = objects[id];
}

//소멸자
ObjManager::~ObjManager()
{
	for (int i = 0; i < 100; i++)
	{
		if (objects[i])
		{
				delete(objects[i]);
				objects[i] = NULL;
		}
	}

	glDeleteLists(Text::base, 96);
}

void ObjManager::Loop(void) const
{
	int count = 0;
	int tempCount;

	while (!newObjects.isEmpty())
	{
		newObjects.pop()->Start();
	}

	for (int i = 0; count < num && i < 100; i++)
	{
		if (objects[i])
		{
			objects[i]->move();
			if (objects[i]->collider)
			{
				tempCount = count + 1;
				for (int j = i+1; tempCount < num && j < 100; j++)
				{
					if (objects[j])
					{
						tempCount++;
						if (objects[j]->collider && objects[i]->collider->CheckCollision(objects[j]->collider))
						{
							if (!objects[j]->collider->isTriger && !objects[i]->collider->isTriger)
							{
								objects[i]->collide((objects[j]->collider));
								objects[j]->collide((objects[i]->collider));
							}

							objects[i]->OnCollision((objects[j]->collider));
							objects[j]->OnCollision((objects[i]->collider));
						}
					}
				}
			}

			count++;
			objects[i]->Update();
		}
	}
}

void ObjManager::draw(void) const
{
	int count = 0;

	for(int i = 0; count < num && i < 100; i++)
	{
		if (objects[i])
		{
			objects[i]->draw();
			count++;
		}
	}
}


Rotation* Object::GetRotation()
{
	return &rotation;
}

void Object::setName(const string name)
{
	this->name.assign(name);
}

string Object::getName() const
{
	return name;
}

void Object::SetRotation(Rotation rotation)
{
	memcpy((*this).rotation, rotation, sizeof(Rotation));
}



void Object::draw()
{
	if (Draw != NULL)
		Draw->draw();
}

void Object::move()
{
	if (isKinetic)
		transform->move();
}

void Object::collide(Collider *collider)
{

}

void Object::Start()
{
}

void Object::Update()
{
}

void Object::OnCollision(Collider * collider)
{
}

void Object::setKinetic(const bool isKinetic)
{
	this->isKinetic = isKinetic;
}

//Collider Factory
void Object::SetCollider(ColliderType type, float length, char index)
{
	switch (type)
	{
	case ColliderType::BALL:
		collider = new CircleCollider(this, length);
		break;
	case ColliderType::WALL:
		collider = new WallCollider(this, length, index);
		break;
	}
}

//
//void Object::SetNormalVectors(int size, point3* vectors)
//{
//	this->size = size;
//	if (this->vectors) delete[] this->vectors;
//	this->vectors = new point3[size];
//	memcpy(this->vectors, vectors, sizeof(point3)*size);
//}

int ObjManager::available = 0;

bool ObjManager::ObjQueue::isEmpty() const
{
	return (cursor == end);
}

bool ObjManager::ObjQueue::isFull() const
{

	return (end + 1) % 100 == cursor;
}

Object * ObjManager::ObjQueue::pop()
{
	if (isEmpty()) return nullptr;

	cursor++;
	cursor %= 100;
	return objects[(cursor+99)%100];
}

void ObjManager::ObjQueue::push(Object * obj)
{
	if (isFull()) return;

	objects[end++] = obj;
	end %= 100;
}

ObjManager::ObjQueue ObjManager::newObjects = ObjManager::ObjQueue();
int ObjManager::ObjQueue::cursor = 0;
int ObjManager::ObjQueue::end = 0;

DrawLine::DrawLine(Object * obj)
{
	this->obj = obj;
}

void DrawLine::setStart(Vector3 start)
{
	this->start = start;
}

void DrawLine::setEnd(Vector3 End)
{
	this->end = End;
}

void DrawLine::setColor(const point3 & color)
{
	memcpy(this->color, color, sizeof(point3));
}

void DrawLine::draw()
{
	glDisable(GL_LIGHTING);
	glColor3f(color[0], color[1], color[2]);

	glBegin(GL_LINES);
	glVertex3fv((point3&)start);
	glVertex3fv((point3&)end);

	glEnd();
	glEnable(GL_LIGHTING);

	glColor3f(1, 1, 1);
}

DrawRect::DrawRect(Object *object)
{
	this->obj = object;
}

void DrawRect::draw()
{
	Texture* texture;
	Rect position = obj->rect->position;

	double modelView[16];
	double projection[16];
	int viewPort[4];


	MainCamera* cam = MainCamera::getInstance();
	//prepare conver coordinate

	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetIntegerv(GL_VIEWPORT, viewPort);

	float winX;
	float winY;

	double leftTop[3];
	double leftBottom[3];
	double rightTop[3];
	double rightBottom[3];

	//convert coordinates
	//left Top
	winX = position.x;
	winY = (float)viewPort[3] - (float)position.y;

	//	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor);
	if (gluUnProject(winX, winY, (float)position.depth/1000.f, modelView, projection, viewPort, &leftTop[0], &leftTop[1], &leftTop[2]) == GLU_FALSE) {
		printf("실패\n");
	}

	//right Top
	winX = (float)(position.x + position.width);
	winY = (float)viewPort[3] - (float)position.y;

	//	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor);
	if (gluUnProject(winX, winY, 0.1f, modelView, projection, viewPort, &rightTop[0], &rightTop[1], &rightTop[2]) == GLU_FALSE) {
		printf("실패\n");
	}

	//left Bottom
	winX = (float)position.x;
	winY = (float)viewPort[3] - (float)position.y -(float)position.height;

	//	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor);
	if (gluUnProject(winX, winY, 0.1f, modelView, projection, viewPort, &leftBottom[0], &leftBottom[1], &leftBottom[2]) == GLU_FALSE) {
		printf("실패\n");
	}

	//right Bottom
	winX = (float)(position.x + position.width);
	winY = (float)viewPort[3] - (float)position.y - (float)position.height;

	//	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor);
	if (gluUnProject(winX, winY, 0.1f, modelView, projection, viewPort, &rightBottom[0], &rightBottom[1], &rightBottom[2]) == GLU_FALSE) {
		printf("실패\n");
	}

	glEnd();
	//Draw
	glDisable(GL_LIGHTING);


	if (texture = obj->texture)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->getTexID());
	}

	glBegin(GL_QUAD_STRIP);

	if (texture) glTexCoord2f(0, 1);
	glVertex3dv(leftTop);
	if (texture) glTexCoord2f(1, 1);
	glVertex3dv(rightTop);
	if (texture) glTexCoord2f(0, 0);
	glVertex3dv(leftBottom);
	if (texture)glTexCoord2f(1, 0);
	glVertex3dv(rightBottom);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

GUI::GUI()
{
	this->rect = new RectTransform();
	DrawFactory(FaceType::Rect);
}

Text::Text()
{
	if (rect) delete(rect);
		this->rect = new RectTransform();
	if (Draw) delete(Draw);
	DrawFactory(FaceType::Text);
}

DrawFont::DrawFont(Object *obj)
{
	this->obj = obj;
}

void DrawFont::draw()
{

	Rect position = obj->rect->position;
	Text* obj = (Text*)(this->obj);

	int fontsize = obj->fontSize;
	point3 color;
	memcpy(color, obj->color, sizeof(point3));

	double modelView[16];
	double projection[16];
	int viewPort[4];


	MainCamera* cam = MainCamera::getInstance();
	//prepare conver coordinate

	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetIntegerv(GL_VIEWPORT, viewPort);

	float winX;
	float winY;

	double textPosition[3];

	winX = (float)(position.x);
	winY = (float)viewPort[3] - (float)position.y ;

	//	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor);
	if (gluUnProject(winX, winY, position.depth/1000.f, modelView, projection, viewPort, &textPosition[0], &textPosition[1], &textPosition[2]) == GLU_FALSE) {
		printf("실패\n");
	}

	glEnd();
	//Draw
	glDisable(GL_LIGHTING);
/*

	if (texture = obj->texture)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->getTexID());
	}*/
/*
	glBegin(GL_QUAD_STRIP);

	if (texture) glTexCoord2f(0, 1);
	glVertex3dv(leftTop);
	if (texture) glTexCoord2f(1, 1);
	glVertex3dv(rightTop);
	if (texture) glTexCoord2f(0, 0);
	glVertex3dv(leftBottom);
	if (texture)glTexCoord2f(1, 0);
	glVertex3dv(rightBottom);
	glEnd();

	glDisable(GL_TEXTURE_2D);
*/

	glColor3fv(color);
	glRasterPos3dv(textPosition);

	if (obj->text.data() == NULL) return;
	glPushAttrib(GL_LIST_BIT);
	glListBase(Text::base - 32);
	glCallLists(obj->text.size(), GL_UNSIGNED_BYTE, obj->text.data());
	glPopAttrib();

	glColor3f(1.f,1.f,1.f);
	glEnable(GL_LIGHTING);

}

const HWND Text::hwnd = GetActiveWindow();
const HDC Text::hDC = GetDC(hwnd);
const int Text::base = glGenLists(96);