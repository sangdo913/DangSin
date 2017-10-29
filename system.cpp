#include"state.h"
#include"System.h"
#include"Camera.h"
#include"Physics.h"
#include"Input.h"
#include<iostream>
#include <Windows.h>
#include<GL/GL.h>
#include<GL/GLU.h>
#include<GL/glut.h>
#include<GL/GLAUX.h>
class Object;
using namespace std;




//STATE *const System::state = new STATE(new Default());

System::Screen System::screen = System::Screen();
const float System::frame = 6.0f;

bool System::isDestroy = false;

void System::Destory()
{
	if (!isDestroy)
	{
	//	delete state;
		isDestroy = true;
	}
}
System::~System()
{
	Destory();
}

//STATE * const System::getState() const
//{
//	return state;
//}

//============================ System ======================================

MainCamera* MainCamera::Singleton::Instance = new MainCamera(Vector3(0, 160, 165));




MainCamera::MainCamera()
{
}

MainCamera::MainCamera(Vector3 vector) 
{
	transform->position = vector;
}

MainCamera::~MainCamera() 
{
	delete transform;
}
MainCamera* MainCamera::getInstance()
{
	return Singleton.Instance;
}

IState::~IState()
{
	
}

void MainCamera::ToGlobal(float &x, float &y, float &z)
{
	MainCamera *camera = getInstance();
	Vector3 unitX = *((camera->transform)->GetLeft());
	Vector3 unitY = *(camera->transform->GetUp());
	Vector3 forward = *(camera->transform->Getforward());
	Vector3 mousePosition = Input.getMousePosition();

	float xFromCenter =(mousePosition.x - System.screen.width / 2)/System.screen.width;
	float yFromCenter = (System.screen.width / 2 - mousePosition.y)/System.screen.height;

	x = camera->transform->position.x + (-1.0f)*unitX.x *xFromCenter + unitY.x * yFromCenter + forward.x;
	y = camera->transform->position.y + (-1.0f)*unitX.y *xFromCenter + unitY.y * yFromCenter + forward.y;
	z = camera->transform->position.z + (-1.0f)*unitX.z *xFromCenter + unitY.z * yFromCenter + forward.z;


	//GLdouble projection[16];
	//GLdouble modelView[16];
	//GLint viewPort[4];

	//glGetDoublev(GL_PROJECTION_MATRIX, projection);
	//glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	//glGetIntegerv(GL_VIEWPORT, viewPort);

	//GLfloat zCursor, winX, winY;
	//Vector3 pos(Input.getMousePosition());
	//winX = (float)pos.x;
	//winY = (float)viewPort[3] - (float)pos.y;
	//glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor);
	//double wx, wy, wz;
	////if (gluUnProject(winX, winY, zCursor, modelView, projection, viewPort, &wx, &wy, &wz) == GLU_FALSE) {
	////	printf("½ÇÆÐ\n");
	////}
	//gluUnProject(winX, winY, zCursor, modelView, projection, viewPort, &wx, &wy, &wz);
	//x = (float)wx;
	//y = (float)wy;
	//z = (float)wz;
}

void MainCamera::ToGlobal(int &x, int &y)
{
	MainCamera camera = *(getInstance());

	Vector3 unitX = *((camera.transform)->GetLeft());
	Vector3 minusUnitY = *(camera.transform->GetUp());

	x = 
		
		(int)(camera.transform->position.x*unitX.x - camera.transform->position.y * minusUnitY.x);
	y = (int)(camera.transform->position.x*unitX.y - camera.transform->position.y * minusUnitY.y);

}
void MainCamera::ToGlobal(double &x, double &y)
{
	MainCamera camera = *(getInstance());

	Vector3 unitX = *((camera.transform)->GetLeft());
	Vector3 minusUnitY = *(camera.transform->GetUp());
	x = (camera.transform->position.x-System.screen.width/2)*camera.transform->position.x - camera.transform->position.y * minusUnitY.x;
	y = camera.transform->position.x*unitX.y - camera.transform->position.y * minusUnitY.y;
}

Object* System::picked = NULL;
bool System::pickedCheck = false;