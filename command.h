#pragma once
#include"Camera.h"
#include"DangsinState.h"

class StateManager;

class Command
{
public:
	virtual void execute() = 0;
};

class DefaultCommand : public Command
{
	virtual void execute() override;
};

//////////////////////Camera Converter
class CameraCommand : public Command
{
protected:
	MainCamera* cam;
public:
	CameraCommand();
	virtual void execute()override = 0;
};
 
class CameraUp : public CameraCommand
{
public:
	virtual void execute()override;
}; 

class CameraDown : public CameraCommand
{
public:
	virtual void execute()override;
}; 

class CameraLeft : public CameraCommand
{
public:
	virtual void execute()override;
};

class CameraRight : public CameraCommand
{
public:
	virtual void execute()override;
};

class CameraZoomIn : public CameraCommand
{
public:
	virtual void execute()override;
};

class CameraZoomOut : public CameraCommand
{
public:
	virtual void execute()override;
};

class CameraReset : public CameraCommand
{
public:
	virtual void execute()override;
};

/////////////state Converter

class StateCvtCommand : public Command
{
protected:
	StateManager* manager;
public:
	StateCvtCommand();
	StateCvtCommand(StateManager *manIn);

	virtual void execute()override = 0;
};

class StateToInput : public StateCvtCommand
{
public:
	StateToInput(StateManager* manIn);
	virtual void execute()override;
};

class StateToSetVector : public StateCvtCommand
{
public:
	StateToSetVector(StateManager* managerIn);
	virtual void execute()override;
};

class StateToQuit : public StateCvtCommand
{
public:
	StateToQuit(StateManager* managerIn);
	virtual void execute()override;
};

class Quit : public Command
{
public:
	virtual void execute()override;
};

class StateContinue : public StateCvtCommand
{
public:
	StateContinue(StateManager* In);
	virtual void execute()override;
};

////////////////////////////cancle Command

class CancleMouseEvent : public StateCvtCommand
{
public:
	CancleMouseEvent(StateManager* In);
	virtual void execute() override;
};



