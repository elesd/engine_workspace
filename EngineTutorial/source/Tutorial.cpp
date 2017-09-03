#include <stdafx.h>
#include <Tutorial.h>
///////////////////////////////////////////////////////////////////////////////
#include <engine/Context.h>

#include <engine/app/Application.h>

#include <engine/fileSystem/FileSystem.h>

#include <engine/events/EventManager.h>
#include <engine/events/Mouse.h>
#include <engine/events/Keyboard.h>

#include <engine/render/RenderContext.h>

#include <engine/stateStack/StateStack.h>

#include <engine/view/WindowManager.h>

#include <states/TutorialStep01.h>
#include <states/TutorialStep02.h>
#include <states/TutorialStep03.h>
#include <RenderDefinitions.h>


void Tutorial::updateGame()
{
	ASSERT(_CrtCheckMemory());
}

Tutorial::WindowCreationParameter Tutorial::getWindowCreationParameters()
{
	return WindowCreationParameter::create(engine::WindowParameter(100, 200, 640, 480), "TestWindow");
}

std::unique_ptr<engine::StateBase> Tutorial::createStartState(engine::Window* mainWindow)
{
	std::unique_ptr<engine::StateBase> step01(new states::TutorialStep01(mainWindow));
	std::unique_ptr<engine::StateBase> step02(new states::TutorialStep02(mainWindow));
	std::unique_ptr<engine::StateBase> step03(new states::TutorialStep03(mainWindow));
	return step03;
}
