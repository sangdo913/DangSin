#include"Camera.h"
#include"state.h"
#include"System.h"
#include"Physics.h"
#include"Input.h"
#include<iostream>
#include <Windows.h>
#include<GL/GL.h>
#include<GL/GLU.h>
#include<GL/glut.h>
#include<GL/GLAUX.h>
#include"Object.h"
using namespace std;

void IState::action()
{}

void IState::action(int x, int y)
{}

void IState::end() { ; }


void STATE::setState(IState *state)
{
	if((*this).state != NULL)
		delete ((*this).state);

	(*this).state = state;
}

void STATE::end()
{
	state->end();
}


void STATE::action()
{
	state->action();
}
void STATE::action(int x, int y)
{
	state->action(x,y);
}

void STATE::Destroy()
{
	if (!isDestroy)
	{
		delete state;
		isDestroy = true;
	}
}

STATE::STATE(IState *state)
{
	if ((*this).state != NULL)
		delete state;

	isDestroy = false;
	(*this).state = state;
}


STATE::~STATE()
{
	/*if(state != nullptr)
		delete state;*/

	Destroy();
}
MouseInput::~MouseInput()
{
	moveX = 0;
	moveY = 0;
}

//마우스의 이동 거리를 나타낸다.
void MouseInput::action(int viewX, int viewY )
{

	x = viewX;
	y = viewY;
}

void MouseInput::action()
{
	float rateX = 180.0f / System.screen.width;
	float rateY = 180.0f / System.screen.height;

	MainCamera *mainCamera = MainCamera::getInstance();

	Vector3 mPosition = Input.getMousePosition();
	moveX =   mPosition.x- (float)x;
	moveY = mPosition.y- (float)y ;
	//Vector3 pos = mainCamera->transform->position;


	moveX *= rateX;
	moveY *= rateY;

	mainCamera->rotate(moveX, -moveY);
}


void MouseInput::set(int x, int y)
{
	(*this).x = x;
	(*this).y = y;
}

MouseInput::MouseInput(int x, int y)
{
	moveX = 0;
	moveY = 0;
	(*this).x = x;
	(*this).y = y;
}

MouseInput::MouseInput()
{
	moveX = 0;
	moveY = 0;
}

void MouseInput::end()
{
}

void Simulation::action()
{
	
}

void Default::action()
{
}


Default::~Default()
{

}

Simulation::~Simulation()
{

}

void MouseLeft::lineTrace(Vector3* start_point,Vector3* line_end)
{
	const float RADIUS = info->radius;
	Vector3 start = *start_point;
	start.y = 0;
	line_end->y = 0;
	Object* redBall = info->red;
	Object* whiteBall = info->white;
	Object* yellowBall = info->yellow;

	Object* ball1 ;
	Object* ball2 ;
	ball1 = picked == redBall ? whiteBall : redBall;
	ball2 = ball1 != redBall ? yellowBall : (picked == yellowBall ? whiteBall:yellowBall);

	Vector3 pickedPosition = picked->transform->position;
	Vector3 ball1Position = ball1->transform->position;
	Vector3 ball2Position = ball2->transform->position;

	Vector3 temp_end = *line_end;
	temp_end.y = 0;
	pickedPosition.y = 0;
	ball1Position.y = 0;
	ball2Position.y = 0;
	
	for (; count_reflect <5; count_reflect++) {
			float d1=  lineBallDistance(&start, &temp_end, &(ball1Position));
			float d2= lineBallDistance(&start, &temp_end, &(ball2Position));

			float distance2Ball1 = start.distance(ball1Position);
			float distance2Ball2 = start.distance(ball2Position);
			
			bool check1 = (d1 < (2.f * RADIUS)) && (planEq(start, ball1Position, temp_end)) && (distance2Ball1> 2.f * RADIUS);
			bool check2 = (d2 < (2.f * RADIUS)) && (planEq(start, ball2Position, temp_end)) && (distance2Ball2 >2.f * RADIUS);
	
			if (check1 && check2)
			{
				distance2Ball1 > distance2Ball2 ? 
					lineBall(start, temp_end, reflect_point[count_reflect], ball2Position)
												:
					lineBall(start, temp_end, reflect_point[count_reflect], (ball1Position));
			}

			else {
				if (check1) {//
					lineBall(start, temp_end, reflect_point[count_reflect], (ball1Position));
				}
				else if (check2) {//
																	
					lineBall(start, temp_end, reflect_point[count_reflect], ball2Position);
				}
				/*Wall collision 8가지 경우*/
				else
				{
					lineWall(start, temp_end);
				}
			}
			//여기서 reflect_point[count_reflect] 를 중심으로하는 당구공(반투명?) 그려주면 더 좋을 듯.

			reflect_point[count_reflect].y = RADIUS;
			start.y = RADIUS;

			line[count_reflect]->setStart(start);
			line[count_reflect]->setEnd(reflect_point[count_reflect]);

			////test //doing::start, doing::action, circle 멤버변수, 생성자, 소멸자 collide, MOUSELEFT::linetrace도 함께 가기 
			//((CIRCLE*)picked)->test->way[count_reflect].setStart(start);
			//((CIRCLE*)picked)->test->way[count_reflect].setEnd(reflect_point[count_reflect]);
			/////
			start = reflect_point[count_reflect];

			start.y = 0;

		}
	
	glutPostRedisplay();
}

float MouseLeft::lineBallDistance(Vector3 * start, Vector3 * end, Vector3 * ball)
{
	float a = end->z - start->z;
	float b = start->x - end->x;

	float c = (0 - a*end->x - b*end->z);
	float distance;
	distance = fabs(a*ball->x + b*ball->z + c) / sqrt(a*a + b*b);
	return distance;
}

bool MouseLeft::planEq(Vector3 start, Vector3 ball, Vector3 X)
{
	Vector3 n = ball - start;
	Vector3 ap = X - start;
	if (((n.x*ap.x) + (n.z*ap.z)) > 0) return true;//0보다 크면1
	else return false;
}

void MouseLeft::lineBall(Vector3& start, Vector3&  end, Vector3 & reflect_point, Vector3 & ball)
{
	float d1 = lineBallDistance(&start, &end, &ball);
	float D = start.distance(ball);
	const float RADIUS = info->radius;
	reflect_point = start + ((end - start).normalize()*(sqrt(D*D - d1*d1)));

	Vector3 tempdir = ball - reflect_point;
	tempdir.normalize();
	//reflect_point = d1 >= RADIUS ? 
	reflect_point  = start + ((end - start).normalize()*(sqrt(D*D - d1*d1) - sqrt(4.f * RADIUS*RADIUS - d1*d1)));// : 
		//start + ((end - start).normalize()*(sqrt(D*D - d1*d1) - sqrt(RADIUS*RADIUS - d1*d1) - RADIUS));

	if (reflect_point.distance(ball) > 2.f * RADIUS)
	{
		
		reflect_point = ball + (reflect_point - ball).normalize() * 2.f * RADIUS*0.99f;
	}

	Vector3 thisdir = end - reflect_point;
	tempdir = ball - reflect_point;
	tempdir.normalize();
	end = reflect_point + (thisdir - tempdir*((thisdir.x*tempdir.x + thisdir.z*tempdir.z))*info->e)*MAXLINE;
}

void MouseLeft::lineWall(Vector3 start,Vector3 &line_end)
{
	/*벽좌표*/
	float RIGHTWALL = 122.4f;
	float LEFTWALL = -122.4f;
	float TOPWALL = 61.2f;
	float BOTTOMWALL = -61.2f;
	const float RADIUS = info->radius;
	
	if (line_end.x > RIGHTWALL - RADIUS) {
		reflect_point[count_reflect] = start + ((line_end - start) / (line_end.x - start.x)) *(RIGHTWALL - RADIUS - start.x);
		line_end = reflect_point[count_reflect] + Vector3(((reflect_point[count_reflect] - start).x*(-1)), 0, (reflect_point[count_reflect] - start).z).normalize()*MAXLINE;
		if (reflect_point[count_reflect].z < BOTTOMWALL + RADIUS) {
			reflect_point[count_reflect] = start + ((reflect_point[count_reflect] - start) / (start.z - reflect_point[count_reflect].z))*(start.z - BOTTOMWALL - RADIUS);
			line_end = reflect_point[count_reflect] + Vector3((reflect_point[count_reflect] - start).x, 0, (reflect_point[count_reflect] - start).z*(-1)).normalize()*MAXLINE;
		}
		else if (reflect_point[count_reflect].z > TOPWALL - RADIUS) {
			reflect_point[count_reflect] = start + ((reflect_point[count_reflect] - start) / (reflect_point[count_reflect].z - start.z)) *(TOPWALL - RADIUS - start.z);
			line_end = reflect_point[count_reflect] + Vector3(((reflect_point[count_reflect] - start).x), 0, (reflect_point[count_reflect] - start).z*(-1)).normalize()*MAXLINE;
		
		}
	}
	else if (line_end.x < LEFTWALL + RADIUS) {
		reflect_point[count_reflect] = start + ((line_end - start) / (start.x - line_end.x))*(start.x - LEFTWALL - RADIUS);
		line_end = reflect_point[count_reflect] + Vector3((reflect_point[count_reflect] - start).x*(-1), 0, (reflect_point[count_reflect] - start).z).normalize()*MAXLINE;
	
		if (reflect_point[count_reflect].z < BOTTOMWALL + RADIUS) {
			reflect_point[count_reflect] = start + ((reflect_point[count_reflect] - start) / (start.z - reflect_point[count_reflect].z))*(start.z - BOTTOMWALL - RADIUS);
			line_end = reflect_point[count_reflect] + Vector3(((reflect_point[count_reflect] - start).x), 0, (reflect_point[count_reflect] - start).z*(-1)).normalize()*MAXLINE;
	
		}
		else if (reflect_point[count_reflect].z > TOPWALL - RADIUS) {
			reflect_point[count_reflect] = start + ((reflect_point[count_reflect] - start) / (reflect_point[count_reflect].z - start.z)) *(TOPWALL - RADIUS - start.z);
			line_end = reflect_point[count_reflect] + Vector3(((reflect_point[count_reflect] - start).x), 0, (reflect_point[count_reflect] - start).z*(-1)).normalize()*MAXLINE;
	
		}
	}
	else if (line_end.z > TOPWALL - RADIUS) {
		reflect_point[count_reflect] = start + ((line_end - start) / (line_end.z - start.z)) *(TOPWALL - 0 - start.z);
		line_end = reflect_point[count_reflect] + Vector3(((reflect_point[count_reflect] - start).x), 0, (reflect_point[count_reflect] - start).z*(-1)).normalize()*MAXLINE;
	
		if (reflect_point[count_reflect].x > RIGHTWALL - RADIUS) {
			reflect_point[count_reflect] = start + ((reflect_point[count_reflect] - start) / (reflect_point[count_reflect].x - start.x)) *(RIGHTWALL - RADIUS - start.x);
			line_end = reflect_point[count_reflect] + Vector3(((reflect_point[count_reflect] - start).x*(-1)), 0, (reflect_point[count_reflect] - start).z).normalize()*MAXLINE;
		
		}
		else if (reflect_point[count_reflect].x < LEFTWALL + RADIUS) {
			reflect_point[count_reflect] = start + ((reflect_point[count_reflect] - start) / (start.x - reflect_point[count_reflect].x))*(start.x - LEFTWALL - RADIUS);
			line_end = reflect_point[count_reflect] + Vector3((reflect_point[count_reflect] - start).x*(-1), 0, (reflect_point[count_reflect] - start).z).normalize()*MAXLINE;
		
		}
	}
	else if (line_end.z < BOTTOMWALL + RADIUS) {
		reflect_point[count_reflect] = start + ((line_end - start) / (start.z - line_end.z))*(start.z - BOTTOMWALL - RADIUS);
		line_end = reflect_point[count_reflect] + Vector3((reflect_point[count_reflect] - start).x, 0, (reflect_point[count_reflect] - start).z*(-1)).normalize()*MAXLINE;
		
		if (reflect_point[count_reflect].x > RIGHTWALL - RADIUS) {
			reflect_point[count_reflect] = start + ((reflect_point[count_reflect] - start) / (reflect_point[count_reflect].x - start.x)) *(RIGHTWALL - RADIUS - start.x);
			line_end = reflect_point[count_reflect] + Vector3(((reflect_point[count_reflect] - start).x*(-1)), 0, (reflect_point[count_reflect] - start).z).normalize()*MAXLINE;
		
		}
		else if (reflect_point[count_reflect].x < LEFTWALL + RADIUS) {
			reflect_point[count_reflect] = start + ((reflect_point[count_reflect] - start) / (start.x - reflect_point[count_reflect].x))*(start.x - LEFTWALL - RADIUS);
			line_end = reflect_point[count_reflect] + Vector3((reflect_point[count_reflect] - start).x*(-1),0, (reflect_point[count_reflect] - start).z).normalize()*MAXLINE;
		
		}
	}
}

MouseLeft::MouseLeft(int x, int y)
{
	isStart = true;
	globalPoint = Vector3(x, y,0);
}

MouseLeft::MouseLeft()
{
}

MouseLeft::~MouseLeft()
{
	for (int i = 0; i < 5; i++)
	{
			delete(line[i]);
			line[i] = nullptr;
	}
}

MouseLeft::MouseLeft(Object * obj)
{
	line[0] = new Line();
	this->picked = obj;

	info = mEvent->getManager()->getInfo();

	Transform* t = picked->transform;
	line[0]->setStart(Vector3(t->position.x, t->position.y, t->position.z));
	line[0]->setEnd(Vector3(t->position.x, t->position.y, t->position.z));
	line[0]->setColor((point3&)(Vector3(1, 1, 1.0f)));

	for (int i = 1; i < 5; i++)
	{
		line[i] = new Line();
		line[i]->setStart(Vector3(0,0,0));
		line[i]->setEnd(Vector3(0,0,0));
		line[i]->setColor((point3&)(Vector3(1, 1, 1.0f)));

	}


}

MouseLeft::MouseLeft(MouseEvent * mEvent)
{
	this->mEvent = mEvent;
	StateManager* manager = mEvent->getManager();
	info = manager->getInfo();
	((KeyBoardEvent*)manager->getEvent(EventType::Keyboard))->setKeyBoard(VK_ESCAPE, new CancleMouseEvent(manager));
	for (int i = 0; i < 5; i++)
	{
		line[i] = new Line();
		line[i]->setStart(Vector3(0, 0, 0));
		line[i]->setEnd(Vector3(0, 0, 0));
		line[i]->setColor((point3&)(Vector3(1, 1, 1.0f)));
	}
}

void MouseLeft::action()
{

	MainCamera* cam = MainCamera::getInstance();
	DangSinInfo* info = mEvent->getManager()->getInfo();
	const float ballRad = info->radius;

	Vector3 pickedPosition = picked->transform->position;

	glGetIntegerv(GL_VIEWPORT, viewPort);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);

	GLfloat zCursor, winX, winY;
	winX = (float)Input.getMousePosition().x;
	winY = (float)viewPort[3] - (float)Input.getMousePosition().y;
	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor);


	if (gluUnProject(winX, winY, 0.1f, modelView, projection, viewPort, &wx, &wy, &wz) == GLU_FALSE) {
		printf("실패\n");
	}

	///////////////////////////set other line
	
	//////////////////////////////cal ray from screen to board
	double boardX;
	double boardY;
	double boardZ;

	// get board coordinate
	if (gluUnProject(winX, winY, 0.5, modelView, projection, viewPort, &boardX, &boardY, &boardZ) == GLU_FALSE)
	{
		printf("실패\n");
	}



	//set scrVector Screen Coordinate - board Coordinate
	Vector3 scrVec;

	scrVec.x = (float)(wx - boardX);
	scrVec.y = (float)(wy - boardY);
	scrVec.z = (float)(wz - boardZ);

	//calculate x and z when y = 3.075

	Vector3 camPosition = cam->transform->position;


	//set force

	// it need other way to calculate
	if (scrVec.y == 0)
	{
		return;
	}
	float temp = ballRad - camPosition.y / scrVec.y;

	Vector3 force;


	force.x = scrVec.x * temp + camPosition.x;
	force.z = scrVec.z * temp + camPosition.z;
	force.y = ballRad;

	force = force - picked->transform->position;

	force.normalize();

	direction = force;

	Vector3 line_end;

	line_end = pickedPosition + direction * MAXLINE;

	count_reflect = 0;
	lineTrace(&pickedPosition, &line_end);
}

void MouseLeft::end()
{
	for (int i = 0; i < 5; i++)
	{
			delete(line[i]);
			line[i] = nullptr;

	}
	const float ballRad = info->radius; // radius of the ball

	MainCamera *cam = MainCamera::getInstance();
/*
	globalVector.x = globalPoint.x - (forward->x)/(forward->y)*globalPoint.y;
	globalVector.z = globalPoint.z - (forward->z) / (forward->y)*globalPoint.y;
	globalVector.y = 3.075;*/

	// set scrVector toward screen
	GLfloat winX, winY;

	winX = (float)Input.getMousePosition().x;
	winY = (float)viewPort[3] - (float)Input.getMousePosition().y;
	double boardX;
	double boardY;
	double boardZ;

	// get screen Coordinate
	if (gluUnProject(winX, winY, 0, modelView, projection, viewPort, &wx, &wy, &wz) == GLU_FALSE) {
		printf("실패\n");
	}

	// get board coordinate
	if (gluUnProject(winX, winY, 0.5, modelView, projection, viewPort, &boardX, &boardY, &boardZ) == GLU_FALSE)
	{
		printf("실패\n");
	}



	//set scrVector Screen Coordinate - board Coordinate
	Vector3 scrVec;

	scrVec.x = (float)(wx - boardX);
	scrVec.y = (float)(wy - boardY);
	scrVec.z = (float)(wz - boardZ);

	//calculate x and z when y = 3.075

	Vector3 camPosition = cam->transform->position;


	//set force

	// it need other way to calculate
	if (scrVec.y == 0)
	{
		return;
	}
	float temp = ballRad - camPosition.y/scrVec.y;

	Vector3 force;


	force.x = scrVec.x * temp + camPosition.x;
	force.z = scrVec.z * temp + camPosition.z;
	force.y = ballRad;

	force = force - picked->transform->position;

	force.normalize();

	direction = force;
	
	////////////////// end
	StateManager* manager = mEvent->getManager();

	Doing* doing = (Doing*)(manager)->getNowState();
	doing->setDirection(direction,picked);
	
	
	
	this->mEvent->end();

}

void MouseLeft::setpicked(Object * obj)
{
	this->picked = obj;
	Transform* t = picked->transform;
	line[0]->setStart(Vector3(t->position.x, t->position.y, t->position.z));
	line[0]->setEnd(Vector3(t->position.x, t->position.y, t->position.z));
	line[0]->setColor((point3&)(Vector3(1, 1, 1.0f)));
}


Vector3 & MouseLeft::getDirection()
{
	return (Vector3&)direction;
	// TODO: 여기에 반환 구문을 삽입합니다.
}

MouseEvent::MouseEvent()
{
	mouseLeft = new Default();
	mouseRight = new Default();
}

MouseEvent::~MouseEvent()
{
}

void MouseEvent::setMouseLeft(IState * Left)
{
	if (this->mouseLeft) delete(this->mouseLeft);
	mouseLeft = Left;
}

void MouseEvent::setMouseRight(IState *Right)
{
	if (mouseRight) delete(mouseRight);
	mouseRight = Right;
}

void MouseEvent::deleteMouseEvents()
{
	delete(mouseLeft);
	delete(mouseRight);
	mouseLeft = nullptr;
	mouseRight = nullptr;
}

SetVector::SetVector()
{
	mouseLeft = new Default();
	mouseRight = new Default();

}

SetVector::SetVector(StateManager* manager)
{
	this->manager = manager;
	mouseLeft = new Default();
	mouseRight = new Default();
}

void SetVector::action()
{
	//마우스 조작 중 계속 실행
	mouseRight->action();
	mouseLeft->action();

	Vector3 mPosition = Input.getMousePosition();

	//오른쪽 마우스 클릭시 카메라 조작 활성화
	if (Input.isRightDown())
	{
			MouseInput* input = new MouseInput();
			input->set(mPosition.x, mPosition.y);
			setMouseRight(input);
	}

	else if (Input.isRightUp())
	{
		mouseRight->end();
		setMouseRight(new Default());
	}


	else if (Input.isLeftDown())
	{
		if (System.picked != nullptr && System.picked->getName().compare("CIRCLE") == 0)
		{
			MouseLeft* left = new MouseLeft(this);
			left->setpicked(System.picked);
			setMouseLeft(left);
		}
	}

	else if (Input.isLeftUp())
	{
		mouseLeft->end();
		return;
	}


	//마우스 위치 변경
	if (Input.isRightButton())((mouseRight))->action(mPosition.x, mPosition.y);
}

void SetVector::end()
{
	delete(mouseLeft);
	delete(mouseRight);

	manager->setEvent(EventType::Mouse, new SetForce(manager));

	return;
}

SetVector::~SetVector()
{
}

SetForce::SetForce(StateManager *manager)
{
	this->manager = manager;
}

SetForce::~SetForce()
{
	Object* gage = manager->getInfo()->gage;
	Object* backGround = manager->getInfo()->backGround;

	delete(gage);
	delete(backGround);

	gage = nullptr;
	backGround = nullptr;
}

void SetForce::action()
{
	//마우스 조작 중 계속 실행
	mouseRight->action();
	mouseLeft->action();

	//마우스 위치
	Vector3 mPosition = Input.getMousePosition();

	//오른쪽 마우스 클릭시 카메라 조작 활성화
	if (Input.isRightDown())
	{
		MouseInput* input = new MouseInput();
		input->set(mPosition.x, mPosition.y);
		setMouseRight(input);
	}

	else if (Input.isRightUp())
	{
		mouseRight->end();
		setMouseRight(new Default());
	}


	else if (Input.isLeftDown())
	{
		float width = System.screen.width;
		float height = System.screen.height;
		if ((mPosition.x > width* 0.35f&&mPosition.x<width * 0.65f && mPosition.y > height*0.7f && mPosition.y < height*0.8f))
		{
			LeftSetForce* left = new LeftSetForce((Doing*)(manager->getNowState()),this);
			setMouseLeft(left);
		}
	}

	else if (Input.isLeftUp())
	{
		mouseLeft->end();
		return;
	}


	//마우스 위치 변경
	if (Input.isRightButton())((mouseRight))->action(mPosition.x, mPosition.y);
}

void SetForce::end()
{
	delete mouseLeft;
	delete mouseRight;
	manager->setEvent(EventType::Mouse, new MouseEnd(manager));
	return;
}

LeftSetForce::LeftSetForce(Doing * state, MouseEvent * mEvent)
{
	this->mEvent = mEvent;
	this->state = state;
	StateManager* manager = mEvent->getManager();
}

LeftSetForce::~LeftSetForce()
{
}

void LeftSetForce::action()
{
	Vector3 mPosition = Input.getMousePosition();

	float width = System.screen.width;
	float percentage = ((float)mPosition.x - width*0.35f) / width/0.3f;

	if (percentage <= 0) percentage = 0.f;
	else if (percentage > 1.f) percentage = 1.f;

	if(state)state->setPercentage(percentage);
}

void LeftSetForce::end()
{
	const float maxForceLength = 3.f;
	Object* picked = state->getPicked();
	Vector3 direction = state->getDirection();
	float percent = state->getPercentage();


	picked->transform->potentiate(direction*percent*maxForceLength);
	this->state->setForce();

	mEvent->end();
	return;
}

void LeftSetForce::set(int x)
{
	this->previousX = x;
}

MouseEnd::MouseEnd(StateManager * manager)
{
	this->manager = manager;
}

void MouseEnd::action()
{
	mouseRight->action();

	//마우스 위치
	Vector3 mPosition = Input.getMousePosition();

	//오른쪽 마우스 클릭시 카메라 조작 활성화
	if (Input.isRightDown())
	{
		MouseInput* input = new MouseInput();
		input->set(mPosition.x, mPosition.y);
		setMouseRight(input);
	}

	else if (Input.isRightUp())
	{
		mouseRight->end();
		setMouseRight(new Default());
	}


	//마우스 위치 변경
	if (Input.isRightButton())((mouseRight))->action(mPosition.x, mPosition.y);
}

void MouseEnd::end()
{
}

IEvent::IEvent()
{
}

IEvent::~IEvent()
{
}

StateManager * IEvent::getManager()
{
	return manager;
}

void IEvent::setManager(StateManager * manager)
{
	this->manager = manager;
}

KeyBoardEvent::KeyBoardEvent()
{
}

KeyBoardEvent::~KeyBoardEvent()
{
	for (int i = 0; i < sizeof(char); i++)
	{
		delete(command[i]);
	}
	delete (command);

}

void KeyBoardEvent::setKeyBoard(unsigned char key,Command * command)
{
	delete (this->command[(int)key]);

		this->command[(int)key] = command;
}

void KeyBoardEvent::deleteKey(unsigned char key)
{
		delete(command[(int)key]);
		command[(int)key] = new DefaultCommand();
}

void KeyBoardEvent::action()
{
	if(Input.isButton() && command) command[(int)(Input.getButton())]->execute();
}

void KeyBoardEvent::end()
{
}

void DefaultEvent::action()
{
}

void DefaultEvent::end()
{
}

KeyBoardEvent_Basic::KeyBoardEvent_Basic(StateManager * manager)
{
	this->manager = manager;

	command = new Command *[256];

	for (int i = 0; i < 256; i++)
	{
		command[i] = new DefaultCommand();
	}
	command[(int)'w'] = new CameraUp();
	command[(int)'W'] = new CameraUp();
	command[(int)'a'] = new CameraLeft();
	command[(int)'A'] = new CameraLeft();
	command[(int)'s'] = new CameraDown();
	command[(int)'S'] = new CameraDown();
	command[(int)'d'] = new CameraRight();
	command[(int)'D'] = new CameraRight();
	command[(int)'-'] = new CameraZoomOut();
	command[(int)'_'] = new CameraZoomOut();
	command[(int)'+'] = new CameraZoomIn();
	command[(int)'='] = new CameraZoomIn();
	command[(int)' '] = new CameraReset();
}

KeyBoardEvent_Basic::~KeyBoardEvent_Basic()
{
}

LeftMoveBall::LeftMoveBall(MouseEvent * in)
{
	mEvent = in;
	System.pickedCheck = true;
}

void LeftMoveBall::action()
{
	float ballRad = mEvent->getManager()->getInfo()->radius;
	MainCamera* cam = MainCamera::getInstance();
	DangSinInfo* info = mEvent->getManager()->getInfo();
	

	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetIntegerv(GL_VIEWPORT, viewPort);

	GLfloat zCursor, winX, winY;
	winX = (float)Input.getMousePosition().x;
	winY = (float)viewPort[3] - (float)Input.getMousePosition().y;
	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor);


	if (gluUnProject(winX, winY, 0.1f, modelView, projection, viewPort, &wx, &wy, &wz) == GLU_FALSE) {
		printf("실패\n");
	}

	double boardX;
	double boardY;
	double boardZ;

	// get board coordinate
	if (gluUnProject(winX, winY, 0.5, modelView, projection, viewPort, &boardX, &boardY, &boardZ) == GLU_FALSE)
	{
		printf("실패\n");
	}



	//set scrVector Screen Coordinate - board Coordinate
	Vector3 scrVec;

	scrVec.x = (float)(wx - boardX);
	scrVec.y = (float)(wy - boardY);
	scrVec.z = (float)(wz - boardZ);

	//calculate x and z when y = 3.075

	Vector3 camPosition = cam->transform->position;

	//set force

	// it need other way to calculate
	if (scrVec.y == 0)
	{
		return;
	}
	float temp = ballRad - camPosition.y / scrVec.y;

	Vector3 mPosition;


	mPosition.x = scrVec.x * temp + camPosition.x;
	mPosition.z = scrVec.z * temp + camPosition.z;
	mPosition.y = ballRad;
	float radius = info->radius;
	mPosition.x = mPosition.x < -122.4f + radius ? -121.f + radius : mPosition.x > 121.f - radius ? 121.f - radius : mPosition.x;
	mPosition.z = mPosition.z < -59.5f + radius ? -59.5f + radius : mPosition.z > 59.5f - radius ? 59.5f - radius : mPosition.z;

	picked = System.picked;
	info->red == picked ? info->initRed = mPosition : info->white == picked ? info->initWhite = mPosition : info->initYellow = mPosition;
	picked->transform->position = mPosition;
}

void LeftMoveBall::end()
{
	picked = nullptr;
	System.pickedCheck = false;
	mEvent->end();
}

MouseEventBasic::MouseEventBasic(StateManager * in)
{
	manager = in;
	leftDefault = new Default();
	rightDefault = new Default();
}

MouseEventBasic::~MouseEventBasic()
{
	delete(leftFunc);
	delete(rightFunc);
	delete(leftDefault);
	delete(rightDefault);
}

void MouseEventBasic::setLeftFunc(IState * in)
{
	leftFunc = in;
}

void MouseEventBasic::setLeftDefault(IState * in)
{
	leftDefault = in;
}

void MouseEventBasic::setRightFunc(IState * in)
{
	rightFunc = in;
}

void MouseEventBasic::setRightDefault(IState * in)
{
	rightDefault = in;
}

void MouseEventBasic::setMouseLeftFunc(IState * in)
{
	mouseLeft = in;
}

void MouseEventBasic::setMouseRightFunc(IState * in)
{
	mouseRight = in;
}

void MouseEventBasic::leftUp()
{
	mouseLeft = leftDefault;
	return;
}

void MouseEventBasic::rightUp()
{
	mouseRight->end();
	setMouseRightFunc(rightDefault);
}

void MouseEventBasic::leftDown()
{
	if (System.picked != nullptr && System.picked->getName().compare("CIRCLE") == 0)
	{
		setMouseLeftFunc(leftFunc);
	}
}

void MouseEventBasic::rightDown()
{
	Vector3 mPosition = Input.getMousePosition();
	((MouseInput*)rightFunc)->set(mPosition.x, mPosition.y);
	setMouseRightFunc(rightFunc);
}

void MouseEventBasic::action()
{
	//마우스 조작 중 계속 실행
	mouseRight->action();
	mouseLeft->action();

	Vector3 mPosition = Input.getMousePosition();
	//오른쪽 마우스 클릭시 카메라 조작 활성화
	if (Input.isRightDown())
	{
		rightDown();
	}

	else if (Input.isRightUp())
	{
		rightUp();
	}


	else if (Input.isLeftDown())
	{
		leftDown();
	}

	else if (Input.isLeftUp())
	{
		leftUp();
	}


	//마우스 위치 변경
	if (Input.isRightButton())((mouseRight))->action(mPosition.x, mPosition.y);
}

void MouseEventBasic::end()
{
	manager->setEvent(EventType::Mouse, new SetVector(manager));
}
