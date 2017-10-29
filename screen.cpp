#include"system.h"
System::Screen::Screen(float x, float y) : width(x), height(y)
{

}

System::Screen::Screen() : width(0), height(0)
{
}

void System::Screen::setScreen(float width, float height)
{
	(*this).width = width;
	(*this).height = height;
}