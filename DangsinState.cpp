#include "DangsinState.h"
#include "state.h"
#include"Physics.h"
#include<iostream>
#include"Command.h"
class SetVector;
class KeyBoardEvent;

void IDangSinState::start()
{
}

void IDangSinState::action()
{
}

void IDangSinState::end()
{
}

void IDangSinState::setNextState(IDangSinState * state)
{
	nextState = state;
}

StateManager::StateManager() : info(new DangSinInfo()) ,inputState(new InputPosition(this, info)), doingState(new Doing(this, info)), endState(new EndState(this))
{
	events = new IEvent*[(int)EventType::size];
}

void StateManager::Start()
{
	for (int i = 0; i <(int)EventType::size; i++) events[i] = new DefaultEvent();
	delete(events[(int)EventType::Keyboard]);


	events[(int)EventType::Keyboard] =  new KeyBoardEvent_Basic(this);

	nowState = inputState;

	nowState->start();

	inputState->setNextState(doingState);
	doingState->setNextState(endState);
}

void StateManager::Update()
{
	if(nowState)	nowState->action();
	else
	{
	}

	for (int i = 0; i < (int)EventType::size; i++)
	{
		events[i]->action();
	}
}

void StateManager::changeState(State state)
{
	switch (state)
	{
	case State::Input:
		inputState->start();
		nowState = inputState;
		break;
	case State::Simulation:
		doingState->start();
		nowState = doingState;
		break;
	case State::Quit:
		exit(0);
		break;
	}
}

void StateManager::changeState(IDangSinState * state)
{
	nowState = state;
}


IEvent * StateManager::getEvent(EventType type)
{
	return events[(int)type];
}

IDangSinState * StateManager::getNowState()
{
	return nowState;
}

void StateManager::setEvent(EventType type, IEvent * Event)
{
	delete(events[(int)type]);
	events[(int)type] = Event;
}

void StateManager::mouseAction()
{
	events[(int)EventType::Mouse]->action();
}

DangSinInfo * StateManager::getInfo()
{
	return info;
}

StateManager::~StateManager()
{
	if (inputState) delete(inputState);
	if (doingState) delete(doingState);
	if (info) delete(info);

	for (int i = 0; i < (int)EventType::size; i++)
	{
		delete (events[i]);
		events[i] = nullptr;
	}
}

InputPosition::InputPosition(StateManager * manager, DangSinInfo* info)
{
	this->manager = manager;
	isPrepared = false;
}

void InputPosition::start()
{
	MouseEventBasic* even = new MouseEventBasic(manager);
	even->setLeftFunc(new LeftMoveBall(even));
	even->setRightFunc(new MouseInput());

	this->manager->setEvent(EventType::Mouse, even);

	/////////////////////create Process
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));


	fflush(stdin);
	if (!CreateProcess(NULL, "client.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		printf("CreateProcess failed (%d)\n", GetLastError());
		
		exit(-1);
		return;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	FILE* fp;
	fopen_s(&fp, "out.txt","r");

	float ballCoord[3][2];
	if (fp)
	{
		for (int i = 0; i < 6; i++)
			fscanf_s(fp, "%f", &ballCoord[i / 2][i % 2]);

		const int X = 1;
		const int Z = 0;
		const int RED = 2;
		const int WHITE = 1;
		const int YELLOW = 0;

		/////////////////////////////////////
		this->info = manager->getInfo();
		float height = info->radius;

		info->initRed.x = ballCoord[RED][X];
		info->initRed.y = height;
		info->initRed.z = ballCoord[RED][Z];

		info->initYellow.x = ballCoord[YELLOW][X];
		info->initYellow.y = height;
		info->initYellow.z = ballCoord[YELLOW][Z];

		if (ballCoord[WHITE][X] > 122.4f || ballCoord[WHITE][X] < -122.4f) ballCoord[WHITE][X] = 10.0f;
		if (ballCoord[WHITE][Z] > 61.2f || ballCoord[WHITE][Z] < -61.2f) ballCoord[WHITE][Z] = 10.0f;

		info->initWhite.x = ballCoord[WHITE][X];
		info->initWhite.y = height;
		info->initWhite.z = ballCoord[WHITE][Z];
	}

	else
	{
		Vector3 point = { -4.f,0,0 };
		info->initRed = point;

		point.x += 4.f;
		info->initYellow = point;
		point.x += 4.f;

		cout << point;
		info->initWhite = point;
	}


	fclose(fp);
	float width ;
	float screenHeight;

	int viewPort[4];
	glGetIntegerv(GL_VIEWPORT, viewPort);

	width = (float)viewPort[2];
	screenHeight = (float)viewPort[3];

	text = new Text();
	text->text = "Set Direction : D";
	text->rect->position.x = width*0.1f;
	text->rect->position.y = screenHeight*0.05f;
	text->rect->position.width = width*0.3f;
	text->rect->position.height = screenHeight*0.2f;
	text->rect->position.depth = 900.f;

	//카메라 초기화
	MainCamera::getInstance()->transform->position = Vector3(0, 270, 0);
	MainCamera::getInstance()->transform->resetRotate();//
	MainCamera::getInstance()->transform->rotate(90, -0, -90);
	if (!isPrepared)
	{
		info->red = new CIRCLE((point3&)(Vector3(0,0,0)));
		info->yellow = new CIRCLE((point3&)(Vector3(0, 0, 0)));
		info->white = new CIRCLE((point3&)(Vector3(0, 0, 0)));

		unsigned char*image = new unsigned char[512 * 512 * 3];

		for (int i = 0; i < 512 * 512 * 3; i += 3)
		{
			image[i] = 255;
			image[i + 1] = 0;
			image[i + 2] = 0;
		}

		WALL *XWall1 = new WALL(Vector3(-122.4f, 0, 0), (char)0x00, -122.4f);
		XWall1->setName("XWALL");
		WALL *XWall2 = new WALL(Vector3(122.4f, 0, 0), (char)0x01, 122.4f);
		XWall2->setName("XWALL");
		WALL *YWall1 = new WALL(Vector3(0, 0, -61.2f), (char)0x20, -61.2f);
		YWall1->setName("ZWALL");
		WALL *YWall2 = new WALL(Vector3(0, 0, 61.2f), (char)0x21, 61.2f);
		YWall2->setName("ZWALL");

		info->red->transform->setFriction(0.005f);
		info->red->transform->setWeight(0.25f);
		info->red->setName("CIRCLE");
		info->red->texture = new Texture(image, 512, 512, 3);
		info->red->setKinetic(true);
		info->red->setE(info->e);



		for (int i = 0; i < 512 * 512 * 3; i += 3)
		{
			image[i] = 255;
			image[i + 1] = 255;
			image[i + 2] = 0;
		}


		info->yellow->transform->setFriction(0.005f);
		info->yellow->transform->setWeight(0.25f);
		info->yellow->setName("CIRCLE");
		info->yellow->texture = new Texture(image, 512, 512, 3);
		info->yellow->setKinetic(true);
		info->yellow->setE(info->e);
		for (int i = 0; i < 512 * 512 * 3; i += 3)
		{
			image[i] = 255;
			image[i + 1] = 255;
			image[i + 2] = 255;
		}

		info->white->transform->setFriction(0.005f);
		info->white->transform->setWeight(0.25f);
		info->white->setName("CIRCLE");
		info->white->texture = new Texture(image, 512, 512, 3);
		info->white->setE(info->e);
		info->white->setKinetic(true);


		info->red->isPicked = true;
		info->white->isPicked = true;
		info->yellow->isPicked = true;


		point3 edge1 = { -122.4f ,0,  -61.2f };
		point3 edge2 = { -122.4f ,0,  61.2f };
		point3 edge3 = { 122.4f ,0,  -61.2f };
		point3 edge4 = { 122.4f ,0,  61.2f };

		point3 up = { 0,1,0 };
		unsigned char texture[12] = { 0,255,0,0,255,0,0,255,0,0,255,0 };
		FLOOR *floor = new FLOOR(edge2, edge1, edge4, edge3, texture);

		isPrepared = true;



	}


	this->info = manager->getInfo();
	Transform* red = info->red->transform;
	Transform* white = info->white->transform;
	Transform* yellow = info->yellow->transform;


	red->position = info->initRed;
	white->position = info->initWhite;
	yellow->position = info->initYellow;

	info->red->collider->isTriger = true;
	info->yellow->collider->isTriger = true;
	info->red->collider->isTriger = true;
}

void InputPosition::action()
{
	if (Input.getButton() == 'd' || Input.getButton() == 'D')
	{
		delete(text);
		text = nullptr;
		end();
	}
}

void InputPosition::end()
{
	nextState->start();
	manager->changeState(nextState);

}

void Doing::start()
{
	Started = false;
	System.pickedCheck = true;
	this->info = manager->getInfo();

	Transform* red = info->red->transform;
	Transform* white = info->white->transform;
	Transform* yellow = info->yellow->transform;

	red->position = info->initRed;
	white->position = info->initWhite;
	yellow->position = info->initYellow;

	red->setVelocity(Vector3(0, 0, 0));
	yellow->setVelocity(Vector3(0, 0, 0));
	white->setVelocity(Vector3(0, 0, 0));


	info->red->collider->isTriger = false;
	info->white->collider->isTriger = false;
	info->yellow->collider->isTriger = false;

	this->manager->setEvent(EventType::Mouse, new SetVector(manager));

	vectorSet = false;
	info->gage = nullptr;
	info->backGround = nullptr;
	percentage = 0.f;
}

Doing::Doing(StateManager * manager, DangSinInfo * info)
{
	this->manager = manager;
}

Doing::~Doing()
{
}

void Doing::action()
{
	float redVelocity = Vector3::length(info->red->transform->getVelocity());
	float whiteVelocity = Vector3::length(info->white->transform->getVelocity());
	float yellowVelocity = Vector3::length(info->yellow->transform->getVelocity());

	if (vectorSet)
	{
		if (info->gage == nullptr && info->backGround == nullptr)
		{
			System.pickedCheck = false;
			//////////////////////////////////////////set Texture
			unsigned char rectImg[512][512][3];

			rectImg[0][0][0] = 255;
			rectImg[0][0][1] = 0;
			rectImg[0][0][2] = 0;

			rectImg[511][0][0] = 255;
			rectImg[511][0][1] = 122;
			rectImg[511][0][2] = 122;

			rectImg[0][511][0] = 255;
			rectImg[0][511][1] = 122;
			rectImg[0][511][2] = 122;

			rectImg[511][511][0] = 255;
			rectImg[511][511][1] = 255;
			rectImg[511][511][2] = 255;

			for (int i = 0; i < 512; i++)
			{
				for (int k = 0; k < 3; k++)
				{
					rectImg[0][i][k] = rectImg[0][0][k] + (unsigned char)((float)i / 511.f*(float)(rectImg[0][511][k] - rectImg[0][0][k]));
					rectImg[511][i][k] = rectImg[511][0][k] + (unsigned char)((float)i / 511.f*(float)(rectImg[511][511][k] - rectImg[511][0][k]));
					rectImg[i][0][k] = rectImg[0][0][k] + (unsigned char)((float)i / 511.f*(float)(rectImg[511][0][k] - rectImg[0][0][k]));
					rectImg[i][511][k] = rectImg[0][511][k] + (unsigned char)((float)i / 511.f*(float)(rectImg[511][511][k] - rectImg[0][511][k]));
				}
			}

			for (int i = 1; i < 511; i++)
			{
				for (int j = 1; j < 511; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						rectImg[i][j][k] = (unsigned char)(((float)i / (float)511.f*(float)(rectImg[511][j][k] - rectImg[0][j][k]) + (float)(rectImg[0][j][k]))*(float)i / (float)(i + j)
							+
							((float)j / (float)(i + j)*((float)(rectImg[i][511][k] - rectImg[i][0][k]) + (float)rectImg[i][0][k])));
					}
				}
			}


			//////////////////////////////////////////////

			info->gage = new GUI();
			info->backGround = new GUI();

			float width = System.screen.width;
			float height = System.screen.height;

			info->gage->setName("gage");
			info->backGround->setName("backGround");

			RectTransform* rect = info->gage->rect;
			rect->position.x = width*0.35f;
			rect->position.width = (int)(width*0.3f);
			rect->position.y = height*0.7f;
			rect->position.height = height*0.1f;
			rect->position.depth = 10;

			
			info->gage->texture = new Texture(&rectImg[0][0][0], 512, 512, 3);

			for (int i = 0; i < 512; i++)
				for (int j = 0; j < 512; j++)
					for (int k = 0; k < 3; k++)
						rectImg[i][j][k] = (unsigned char)122;

			rect = info->backGround->rect;
			rect->position.x = width*0.35f;
			rect->position.width = (int)width*0.3f;
			rect->position.y = height*0.7f;
			rect->position.height = height*0.1f;
			rect->position.depth = 100;

			info->backGround->texture = new Texture(&rectImg[0][0][0], 512, 512, 3);
		}


		if(!Started&& info->gage)info->gage->rect->position.width = (int)(System.screen.width*percentage*0.3f);
		
	}	

	if (Started && redVelocity == 0 && whiteVelocity == 0 && yellowVelocity == 0)
	{
		
		/////////////test doing::start, doing::action, circle 멤버변수, 생성자, 소멸자 collide, MOUSELEFT::linetrace도 함께 가기 
		//info->red->test->line[info->red->test->lineCount].setEnd(info->red->transform->position);
		//info->yellow->test->line[info->yellow->test->lineCount].setEnd(info->yellow->transform->position);
		//info->white->test->line[info->white->test->lineCount].setEnd(info->white->transform->position);
		///////////////////////
		end();
	}
}

void Doing::end()
{
	nextState->start();
	manager->changeState(nextState);
}

void Doing::setForce()
{
	delete(info->gage);
	delete(info->backGround);

	info->gage = nullptr;
	info->backGround = nullptr;
	vectorSet = false;
	Started = true;
}

void Doing::setDirection(Vector3 & direction, Object* picked)
{
	this->direction = direction;
	this->picked = picked;
	vectorSet = true;
}

Object * Doing::getPicked()
{
	return picked;
}

Vector3 & Doing::getDirection()
{
	return direction;
	// TODO: 여기에 반환 구문을 삽입합니다.
}

void Doing::setPercentage(float percentage)
{
	this->percentage = percentage;
}

float Doing::getPercentage()
{
	return percentage;
}


//StateManager* manager = new StateManager();

EndState::EndState(StateManager * manager)
{
	this->manager = manager;
}

void EndState::start()
{
	t = new Text();
	float height = System.screen.height;
	float width = System.screen.width;

	float textWidth = width*0.1f;
	float textHeight = height * 0.05f;

	t->text = "ReStart : R";
	t->rect->position.x =textWidth;
	t->rect->position.y = textHeight;
	t->rect->position.width = width*0.3f;
	t->rect->position.height = height*0.2f;
	t->rect->position.depth = 1.f;

	t2 = new Text();
	t2->text = "RePlace : T";
	t2->rect->position.x = textWidth;
	t2->rect->position.y = textHeight*2;
	t2->rect->position.width = width*0.3f;
	t2->rect->position.height = height*0.2f;
	t2->rect->position.depth = 1.f;

	t3 = new Text();
	t3->text = "Quit : Q";
	t3->rect->position.x = textWidth;
	t3->rect->position.y = textHeight*4;
	t3->rect->position.width = width*0.3f;
	t3->rect->position.height = height*0.2;;
	t3->rect->position.depth = 1.f;	

	t4 = new Text();
	t4->text = "Continue: C";
	t4->rect->position.x = textWidth;
	t4->rect->position.y = textHeight * 3;
	t4->rect->position.width = width*0.3f;
	t4->rect->position.height = height*0.2;;
	t4->rect->position.depth = 1.f;

	memcpy(t->color, (point3&)Vector3(0.f, 0.f, 0.f), sizeof(point3));
	memcpy(t2->color, (point3&)Vector3(0.f, 0.f, 0.f), sizeof(point3));
	memcpy(t3->color, (point3&)Vector3(0.f, 0.f, 0.f), sizeof(point3));
	memcpy(t4->color, (point3&)Vector3(0.f, 0.f, 0.f), sizeof(point3));

	KeyBoardEvent* keyEvent =  (KeyBoardEvent*)manager->getEvent(EventType::Keyboard);
	keyEvent->setKeyBoard('r', new StateToSetVector(manager));
	keyEvent->setKeyBoard('R', new StateToSetVector(manager));
	keyEvent->setKeyBoard('T', new StateToInput(manager));
	keyEvent->setKeyBoard('t', new StateToInput(manager));
	keyEvent->setKeyBoard('c', new StateContinue(manager));
	keyEvent->setKeyBoard('C', new StateContinue(manager));
	keyEvent->setKeyBoard('Q', new Quit());
	keyEvent->setKeyBoard('q', new Quit());

	keyEvent->deleteKey('w');
	keyEvent->deleteKey('W');
	keyEvent->deleteKey('a');
	keyEvent->deleteKey('A');
	keyEvent->deleteKey('s');
	keyEvent->deleteKey('S');
	keyEvent->deleteKey('d');
	keyEvent->deleteKey('D');
	keyEvent->deleteKey('=');
	keyEvent->deleteKey('+');
	keyEvent->deleteKey('-');
	keyEvent->deleteKey('_');
	keyEvent->deleteKey(' ');
	keyEvent->deleteKey(VK_ESCAPE);

	manager->setEvent(EventType::Mouse, new DefaultEvent());
}

void EndState::action()
{
}

void EndState::end()
{

	KeyBoardEvent* keyEvent = (KeyBoardEvent*)manager->getEvent(EventType::Keyboard);
	keyEvent->deleteKey('r');
	keyEvent->deleteKey('R');
	keyEvent->deleteKey('t');
	keyEvent->deleteKey('T');
	keyEvent->deleteKey('q');
	keyEvent->deleteKey('Q');
	keyEvent->deleteKey('c');
	keyEvent->deleteKey('C');

	keyEvent->setKeyBoard('w', new CameraUp());
	keyEvent->setKeyBoard('W', new CameraUp());
	keyEvent->setKeyBoard('A', new CameraLeft());
	keyEvent->setKeyBoard('a', new CameraLeft()); 
	keyEvent->setKeyBoard('s', new CameraDown());
	keyEvent->setKeyBoard('S', new CameraDown());
	keyEvent->setKeyBoard('d', new CameraRight());
	keyEvent->setKeyBoard('D', new CameraRight());
	keyEvent->setKeyBoard('-', new CameraZoomOut());
	keyEvent->setKeyBoard('_', new CameraZoomOut());
	keyEvent->setKeyBoard('+', new CameraZoomIn());
	keyEvent->setKeyBoard('=', new CameraZoomIn());
	if (t)
	keyEvent->setKeyBoard(' ', new CameraReset());

	{
		delete(t);
		t = nullptr;
	}
	if (t2)
	{
		delete(t2);
		t2 = nullptr;
	}
	if (t3)
	{
		delete(t3);
		t3 = nullptr;
	}

	if (t4)
	{
		delete(t4);
		t4 = nullptr;
	}

}
