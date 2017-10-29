#pragma once
#include"Physics.h"
#include"Line.h"
#include"DangsinState.h"
#include"Command.h"
class Doing;
class StateManager;
class MouseEvent;
class Command;
struct DangSinInfo;
class IState
{
protected:
	MouseEvent* mEvent;
public:
	virtual void action();
	virtual void action(int x, int y);
	virtual void end();

	virtual ~IState()= 0;
};


class STATE: public IState
{
private:
	IState *state;
	bool isDestroy;

	void Destroy();
public:
	STATE(IState *state);
	~STATE();

	void setState(IState *state);
	virtual void action() override;
	virtual void action(int x, int y) override;
	virtual void end() override;

};


class MouseLeft : public IState
{
private:
	Object* picked;
	Vector3 globalPoint;
	Vector3 direction;

	MouseEvent* mEvent;
	DangSinInfo * info;

	const float MAXLINE = 1000.f;
	Vector3 reflect_point[5];
	double viewport[4];
	double projection[16];
	double modelView[16];
	int viewPort[4];

	double wx, wy, wz;
	int count_reflect;

	Line* line[5];

	bool isStart;

	void lineTrace(Vector3* In1, Vector3* In2);
	float lineBallDistance(Vector3 *start, Vector3 *end, Vector3 *ball);
	bool planEq(Vector3 start, Vector3 ball, Vector3 X);
	void lineBall(Vector3 &start, Vector3 &end, Vector3 &reflect_point, Vector3 &ball);
	void lineWall(Vector3 start,Vector3 &line_end);

public:
	MouseLeft(int x, int y);
	MouseLeft();
	~MouseLeft();
	MouseLeft(Object* obj);
	MouseLeft(MouseEvent* mEvent);
	virtual void action() override;
	virtual void end() override;

	void setpicked(Object* obj);


	Vector3& getDirection();
};

class LeftSetForce : public IState
{
private:
	Doing* state;
	int previousX;

	const float rate = 0.01f;

	float moveX;
public:
	LeftSetForce(Doing* state, MouseEvent * mEvent);
	~LeftSetForce();
	virtual void action() override;
	virtual void end() override;
	void set(int x);

};
class MouseInput : public IState
{
private:
	int x;
	int y;

	float moveX;
	float moveY;
public:
	MouseInput(int x, int y);
	MouseInput();
	~MouseInput();

	virtual void action(int x, int y) override;
	virtual void action() override;
	virtual void end() override;

	void set(int x, int y);
};

class Simulation : public IState
{
public:
	virtual void action() override;

	~Simulation();
};

class Default : public IState
{
public:
	~Default();
	virtual void action() override;
};


//////////////////Event

//추상 클래스
enum class EventType
{
	Mouse = 0,
	Keyboard,
	size
};

class IEvent
{
protected:
	StateManager* manager;
public:
	IEvent();
	virtual ~IEvent();
	
	StateManager* getManager();
	void setManager(StateManager* manager);
	virtual void action() = 0;
	virtual void end() = 0;
};

class DefaultEvent : public IEvent
{
	virtual void action() override;
	virtual void end() override;
};
class MouseEvent : public IEvent
{
protected:
	IState* mouseLeft;
	IState* mouseRight;

public:
	MouseEvent();
	~MouseEvent();
	void setMouseLeft(IState* Left);
	void setMouseRight(IState* Right);

	virtual void action() override = 0;
	virtual void end() override = 0;

	void deleteMouseEvents();
};

class KeyBoardEvent : public IEvent
{
protected:
	Command** command;

public:
	KeyBoardEvent();
	virtual ~KeyBoardEvent();
	void setKeyBoard(unsigned char key,Command * command);
	void deleteKey(unsigned char key);


	virtual void action()override;
	virtual void end() override;
};

/////////////////////////////

class SetVector : public MouseEvent
{
private:
	Vector3 vector;
public:
	SetVector();
	SetVector(StateManager*);
	virtual void action() override;
	virtual void end() override;

	~SetVector();
};


class SetForce : public MouseEvent
{
private:

	float percent;
	Vector3 direction;

	GUI* gage;
	GUI* backGround;

public:
	SetForce(StateManager*);
	~SetForce();
	virtual void action()override;
	virtual void end()override;
};

class MouseEventBasic : public MouseEvent
{
private:
	IState* leftFunc;
	IState* rightFunc;
	IState* leftDefault;
	IState* rightDefault;

public:
	MouseEventBasic(StateManager* in);
	virtual ~MouseEventBasic();
	void setLeftFunc(IState* in);
	void setLeftDefault(IState* in);
	void setRightFunc(IState* in);
	void setRightDefault(IState* in);

	virtual void setMouseLeftFunc(IState* in);
	virtual void setMouseRightFunc(IState* in);

	virtual void leftUp();
	virtual void rightUp();
	virtual void leftDown();
	virtual void rightDown();
	virtual void action() override;
	virtual void end() override;
};


class MouseEnd : public MouseEvent
{
private:
public:
	MouseEnd(StateManager* manager);
	virtual void action()override;
	virtual void end()override;
};

class LeftMoveBall : public IState
{
private:

	double projection[16];
	double modelView[16];
	int viewPort[4];
	double wx, wy, wz;
	Object* picked;
public:
	LeftMoveBall(MouseEvent* manager);
	virtual void action()override;
	virtual void end()override;
};


class KeyBoardEvent_Basic : public KeyBoardEvent
{
public:
	KeyBoardEvent_Basic(StateManager* manager);
	~KeyBoardEvent_Basic();
};
