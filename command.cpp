#include "command.h"

CameraCommand::CameraCommand()
{
	cam = MainCamera::getInstance();
}

void CameraUp::execute()
{
	cam->goUp();
}

void CameraDown::execute()
{
	cam->goDown();
}

void CameraLeft::execute()
{
	cam->goLeft();
}

void CameraRight::execute()
{
	cam->goRight();
}

StateCvtCommand::StateCvtCommand(StateManager * manager)
{
	this->manager = manager;
}

StateToInput::StateToInput(StateManager * manIn)
{
	manager = manIn;
}

void StateToInput::execute()
{
	IDangSinState* oldState = manager->getNowState();
	manager->changeState(StateManager::State::Input);
	oldState->end();
}

StateCvtCommand::StateCvtCommand()
{
}

StateToSetVector::StateToSetVector(StateManager * managerIn)
{
	manager = managerIn;
	
}

void StateToSetVector::execute()
{
	IDangSinState* oldState = manager->getNowState();
	manager->changeState(StateManager::State::Simulation);
	oldState->end();
}

StateToQuit::StateToQuit(StateManager * managerIn)
{
	manager = managerIn;
}

void StateToQuit::execute()
{
	manager->getNowState()->end();
	manager->changeState(StateManager::State::Quit);
}

void CameraZoomIn::execute()
{
	cam->ZoomIn();
}

void CameraZoomOut::execute()
{
	cam->ZoomOut();
}

void CameraReset::execute()
{
	cam->transform->position = Vector3(0, 270, 0);
	cam->transform->resetRotate();
	cam->transform->rotate(90, 0, -90);
}

void DefaultCommand::execute()
{
	return;
}

CancleMouseEvent::CancleMouseEvent(StateManager * In)
{
	manager = In;
}

void CancleMouseEvent::execute()
{
	((MouseEvent*)manager->getEvent((EventType::Mouse)))->deleteMouseEvents();
	KeyBoardEvent* keyEvent = (KeyBoardEvent*)(manager->getEvent(EventType::Keyboard));
	manager->changeState(StateManager::State::Simulation);
	keyEvent->deleteKey(VK_ESCAPE);
}

void Quit::execute()
{
	exit(0);

}

StateContinue::StateContinue(StateManager * In)
{
	manager = In;
}

void StateContinue::execute()
{
	DangSinInfo* info = manager->getInfo();
	info->initRed = info->red->transform->position;
	info->initWhite = info->white->transform->position;
	info->initYellow = info->yellow->transform->position;

	IDangSinState* oldState = manager->getNowState();
	manager->changeState(StateManager::State::Simulation);
	oldState->end();
}
