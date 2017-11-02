#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <math.h>

#include "Ball.h"
#include "Physics.h"

#define RADIUS 5

float GameObject::HEIGHT = 400;
float GameObject::WIDTH = 400;
float GameObject::originX = 50;
float GameObject::originY = 50;


Ball::Ball()
{
}

Ball::Ball(Vector3 pos):GameObject(pos)
{
}


Ball::~Ball()
{
}

void Ball::move()
{
	this->transform->position.x += this->transform->velocity.x;
	this->transform->position.y += this->transform->velocity.y;
	this->transform->velocity.x -= 0.001*(this->transform->velocity.x);//수정 필요함. initial 속도 따로 저장해서 감소시키기.
	this->transform->velocity.y -= 0.001*(this->transform->velocity.y);//수정 필요함
	if (fabs(this->transform->velocity.x) < 0.005) this->transform->velocity.x = 0;
	if (fabs(this->transform->velocity.y) < 0.005) this->transform->velocity.y = 0;
	/*운동량_질량 = 50;*/
	this->transform->p = Vector3(50 * this->transform->velocity.x, 50 * this->transform->velocity.y, 50 * this->transform->velocity.z);
}

void Ball::BoundaryCollision()
{
	if (this->transform->position.x <= originX) {
		this->transform->position.x = originX;
		this->transform->velocity.x = -this->transform->velocity.x;
	}
	else if (this->transform->position.x >= originX + WIDTH) {
		this->transform->position.x = originX + WIDTH;
		this->transform->velocity.x = -this->transform->velocity.x;
	}
	if (this->transform->position.y <= originY) {
		this->transform->position.y = originY;
		this->transform->velocity.y = -this->transform->velocity.y;
	}
	else if (this->transform->position.y >= originY + HEIGHT) {
		this->transform->position.y = originY + HEIGHT;
		this->transform->velocity.y = -this->transform->velocity.y;
	}
}

void Ball::collise(Ball &A,Ball &B)//this가 A,B에게 운동량 전달
{
	if (sqrt((A.transform->position.x - this->transform->position.x)*(A.transform->position.x - this->transform->position.x) +
			(A.transform->position.y - this->transform->position.y)*(A.transform->position.y - this->transform->position.y)) <= 2*RADIUS) {
		A.transform->velocity.x += 0.5*(this->transform->velocity.x);
		A.transform->velocity.y += 0.5*(this->transform->velocity.y);
		A.transform->velocity.z += 0.5*(this->transform->velocity.z);

		this->transform->velocity.x = -0.5*this->transform->velocity.x;
		this->transform->velocity.y = -0.5*this->transform->velocity.y;
		this->transform->velocity.z = -0.5*this->transform->velocity.z;
	}
	else if (sqrt((B.transform->position.x - this->transform->position.x)*(B.transform->position.x - this->transform->position.x) +
			(B.transform->position.y - this->transform->position.y)*(B.transform->position.y - this->transform->position.y)) <= 2*RADIUS) {
		B.transform->velocity.x += 0.5*(this->transform->velocity.x);
		B.transform->velocity.y += 0.5*(this->transform->velocity.y);
		B.transform->velocity.z += 0.5*(this->transform->velocity.z);

		this->transform->velocity.x = -0.5*this->transform->velocity.x;
		this->transform->velocity.y = -0.5*this->transform->velocity.y;
		this->transform->velocity.z = -0.5*this->transform->velocity.z;
	}
}

void Ball::Draw()
{
	glVertex3f(this->transform->position.x, this->transform->position.y, this->transform->position.z);
}

GameObject::GameObject()
{
	transform = new Transform();
	//Collider = new GameObject();
	//vertexes[] =
}

GameObject::GameObject(Vector3 pos)
{
	transform = new Transform(pos);
	//Collider = new GameObject();
	//vertexes[] =
}

GameObject::~GameObject()
{
}

void GameObject::move()
{
}

void GameObject::collise()
{
}

Wall::Wall()
{
}

Wall::~Wall()
{
}

void Wall::Draw()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
		glVertex2f(GameObject::originX, GameObject::originY);
		glVertex2f(GameObject::originX + GameObject::WIDTH, GameObject::originY);
		glVertex2f(GameObject::originX + GameObject::WIDTH, GameObject::originY + GameObject::HEIGHT);
		glVertex2f(GameObject::originX, GameObject::originY + GameObject::HEIGHT);
	glEnd();
}
