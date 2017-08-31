#include <stdafx.h>
#include <TestMain.h>
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

struct TestMainPrivate
{
	engine::Window* mainWindow = nullptr;
	std::unique_ptr<engine::StateStack> stateStack;
};

TestMain::TestMain()
	:_members(new TestMainPrivate())
{

}

TestMain::~TestMain()
{
	delete _members;
	_members = nullptr;
}

void TestMain::setStartState(std::unique_ptr<engine::StateBase> &&state)
{
	ASSERT(_members->stateStack->isEmpty());
	_members->stateStack->pushState(std::move(state));
}

void TestMain::load()
{
	using engine::Context;
	//engine::view::Window *mainWindow = Context::windowManager()->createFullScreenMainWindow(640, 480, "TestWindow", 0);
	_members->mainWindow = Context::windowManager()->createMainWindow(engine::WindowParameter(100, 200, 640, 480), "TestWindow");
	ASSERT(_members->mainWindow != nullptr);
	_members->stateStack = std::make_unique<engine::StateStack>();
	std::unique_ptr<states::TutorialStep03> firstStep(new states::TutorialStep03(_members->mainWindow));
	_members->stateStack->pushState(std::move(firstStep));
}

void TestMain::update()
{
	ASSERT(_CrtCheckMemory());
	_members->stateStack->update();
}

engine::ISignalManager* TestMain::getSignalManager() const
{
	return _members->mainWindow->getEventManager()->getEventsSignalManager();
}
