#pragma once
class Vector3;


static class Input
{
private:
	static float mousePositionX;
	static float mousePositionY;

	static bool LeftButton;
	static bool RightButton;

	static bool LeftButtonDown;
	static bool RightButtonDown;

	static bool LeftButtonUp;
	static bool RightButtonUp;

	static unsigned char keyboard;
	static bool Button;
public:

	bool isLeftDown();
	bool isRightDown();

	bool isLeftButton();
	bool isRightButton();

	bool isLeftUp();
	bool isRightUp();

	void LeftDown();
	void RightDown();

	void LeftUp();
	void RightUp();

	void LeftUpEnd();
	void RightUpEnd();

	void LeftDownEnd();
	void RightDownEnd();

	void setMousePosition(float x, float y);
	void KeyButton(unsigned char a);
	void KeyFree();

	unsigned char getButton();

	bool isButton();
	Vector3 getMousePosition() const; 
}Input;