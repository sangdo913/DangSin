#include"input.h"
#include"Physics.h"
#include"stdio.h"
#include<iostream>
using namespace std;
bool Input::LeftButton =false;
bool Input::RightButton = false;

bool Input::LeftButtonDown = false;
bool Input::RightButtonDown = false;

bool Input::LeftButtonUp = false;
bool Input::RightButtonUp = false;
bool Input::isLeftDown()
{
	return LeftButtonDown;
}

bool Input::isRightDown()
{
	return RightButtonDown;
}


bool Input::isLeftButton()
{
	return LeftButton;
}

bool Input::isRightButton()
{
	return RightButton;
}

bool Input::isLeftUp()
{
	return LeftButtonUp;
}

bool Input::isRightUp()
{
	return RightButtonUp;
}

void Input::LeftDown()
{
	LeftButtonDown = true;
	LeftButton = true;
}

void Input::RightDown()
{
	RightButtonDown = true;
	RightButton = true;
}

void Input::LeftUp()
{
	LeftButtonUp = true;
	LeftButton = false;
}

void Input::RightUp()
{
	RightButton = false;
	RightButtonUp = true;
}

void Input::LeftUpEnd()
{
	LeftButtonUp = false;
}

void Input::RightUpEnd()
{
	RightButtonUp = false;
}

void Input::LeftDownEnd()
{
	LeftButtonDown = false;
}

void Input::RightDownEnd()
{
	RightButtonDown = false;
}

void Input::setMousePosition(float x, float y)
{
	mousePositionX = x;
	mousePositionY = y;
}

void Input::KeyButton(unsigned char a)
{
	keyboard = a;
	Button = true;
}

void Input::KeyFree()
{
	Button = false;
}

unsigned char Input::getButton()
{
	KeyFree();
	return keyboard;
}

bool Input::isButton()
{
	return Button;
}

Vector3 Input::getMousePosition() const
{
	return Vector3(mousePositionX, mousePositionY, 0);
}

float Input::mousePositionX = 0;
float Input::mousePositionY = 0;
unsigned char Input::keyboard = 0;
bool Input::Button = false;