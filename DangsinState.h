#pragma once
#include"Headers.h"

class CIRCLE;
class STATE;
class MouseLeft;
class MouseEvent;
class IEvent;
enum class EventType;

class StateManager;
class Doing;
class IDangSinState;
class InputPosition;
class EndState;

struct DangSinInfo;

class StateManager :public Object
{
public:
	enum class State
	{
		Input = 0,
		Simulation,
		Quit
	};

private:
	IDangSinState* nowState;

	InputPosition* const inputState;
	Doing* const doingState;
	EndState* const endState;

	struct DangSinInfo* const info;
	IEvent** events;

public:

	StateManager();
	
	virtual void Start() override;
	virtual void Update() override;
	
	void changeState(State state);
	void changeState(IDangSinState *state);

	//MouseEvent* getMouseEvent();
	IEvent* getEvent(EventType type);
	IDangSinState* getNowState();

	//void setMouseEvent(MouseEvent* mouseEvent);
	void setEvent(EventType type, IEvent* Event);
	void mouseAction();

	DangSinInfo* getInfo();

	~StateManager();
};

class IDangSinState
{
protected:
	StateManager* manager;
	IDangSinState* nextState;
public:
	virtual void start();
	virtual void action();
	virtual void end();

	void setNextState(IDangSinState* state);
};

class Doing : public IDangSinState
{
private:
	Object* picked;

	float percentage;
	bool Started;
	bool vectorSet;

	Vector3 direction;
	DangSinInfo *info;

public:
	Doing(StateManager* manager,  DangSinInfo * info);
	~Doing();
	virtual void start() override;
	virtual void action() override;
	virtual void end() override;

	void setForce();

	void setDirection(Vector3& direction, Object* picked);
	Object* getPicked();
	Vector3& getDirection();

	void setPercentage(float percentage);

	float getPercentage();
};

class InputPosition : public IDangSinState
{
private:

	DangSinInfo* info;
	Text * text;

	bool isPrepared;
public:
	InputPosition(StateManager * manager, DangSinInfo* info);

	virtual void start() override;
	virtual void action() override;
	virtual void end() override;
};

class EndState : public IDangSinState
{
private:
	Text *t;
	Text *t2;
	Text *t3;
	Text *t4;
public:
	EndState(StateManager * manager);

	virtual void start() override;
	virtual void action() override;
	virtual void end() override;
};


struct DangSinInfo
{
	CIRCLE* red;
	CIRCLE* yellow;
	CIRCLE* white;

	GUI* gage;
	GUI* backGround;

	const float radius = 3.075f;
	const float e = 0.6f;


	Vector3 initRed;
	Vector3 initWhite;
	Vector3 initYellow;
};