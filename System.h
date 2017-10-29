#pragma once
class STATE;

using namespace std;

class Object;

static class System
{
private:
	class Screen
	{
	public:
		float width;
		float height;


		Screen(float x, float y);
		Screen();

		void setScreen(float, float);
	};

	static bool isDestroy;

	//static STATE* const state;

	void Destory();


public:
	static Screen screen;
	static const float frame;
	static bool pickedCheck;
//	STATE* const getState() const ;

	static Object* picked;


	~System();
}System;