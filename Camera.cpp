#include"Camera.h"
#include"Physics.h"
#include<iostream>
using namespace std;

Camera::Camera() : transform(new Transform())
{
}

Camera::Camera(Vector3 position) : transform(new Transform(position))
{
}

Camera::~Camera()
{
	delete transform;
}

void Camera::rotate(float xAngle, float yAngle)
{
	transform->rotate(-yAngle, -xAngle, 0);
}

void Camera::goUp()
{
	if(transform)transform->position = transform->position + *(transform->GetUp())*cameraSpeed;
}

void Camera::goDown()
{

	if (transform)transform->position = transform->position - *(transform->GetUp())*cameraSpeed;
}

void Camera::setProjection(const double * const projection)
{
	memcpy(this->projection, projection, sizeof(double) * 16);
}

void Camera::setmodelView(const double *const modelView)
{
	memcpy(this->modelView, modelView, sizeof(double) * 16);
}

void Camera::setviewPort(const int * const viewPort)
{
	memcpy(this->viewPort, viewPort, sizeof(int) * 4);
}

void Camera::getProjection(double projection[16]) const
{
	memcpy(projection, this->projection, sizeof(double) * 16);
}

void Camera::getModelView(double modelView[16]) const
{
	memcpy(modelView, this->modelView, sizeof(double) * 16);
}

void Camera::getviewPort(int viewPort[4]) const
{
	memcpy(viewPort, this->viewPort, sizeof(int) * 4);
}

void Camera::resetRotation()
{
}

void Camera::goLeft()
{
	if (transform)transform->position = transform->position + *(transform->GetLeft())*cameraSpeed;
}

void Camera::goRight()
{
	if (transform)transform->position = transform->position - *(transform->GetLeft())*cameraSpeed;
}

void Camera::ZoomIn()
{
	if (transform)transform->position = transform->position + *(transform->Getforward())*cameraSpeed;
}

void Camera::ZoomOut()
{
	if (transform)transform-> position = transform->position - *(transform->Getforward())*cameraSpeed;
}

