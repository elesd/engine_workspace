#include <stdafx.h>
#include <TestMain.h>
///////////////////////////////////////////////////////////////////////////////
#include <engine/app/Application.h>
#include <engine/events/EventManager.h>
#include <engine/events/Mouse.h>
#include <engine/events/Keyboard.h>
#include <engine/Context.h>
#include <engine/view/WindowManager.h>

#include <Log.h>


void TestMain::load()
{
	using engine::Context;
	//engine::view::Window *mainWindow = Context::getInstance()->getWindowManager()->createFullScreenMainWindow(640, 480, "TestWindow", 0);
	engine::Window *mainWindow = Context::getInstance()->getApplication()->getWindowManager()->createMainWindow(engine::WindowParameter(100, 200, 640, 480), "TestWindow");
	//	engine::view::Window *second = Context::getInstance()->getWindowManager()->createSecondaryWindow(engine::WindowParameter(180, 200, 640, 480), "TestWindow", mainWindow);
	ASSERT(mainWindow != nullptr);

	auto mouses = Context::getInstance()->getApplication()->getEventManager()->findEventSource<engine::Mouse>();
	auto mouse = mouses.front();
	CONNECT_SIGNAL(mouse, leftButtonPressed,
				   this, onMouseLeftDown);
	CONNECT_SIGNAL(mouse, leftButtonReleased,
				   this, onMouseLeftUp);
	CONNECT_SIGNAL(mouse, rightButtonPressed,
				   this, onMouseRightDown);
	CONNECT_SIGNAL(mouse, rightButtonReleased,
				   this, onMouseRightUp);
	CONNECT_SIGNAL(mouse, middleButtonPressed,
				   this, onMouseMiddleDown);
	CONNECT_SIGNAL(mouse, middleButtonReleased,
				   this, onMouseMiddleUp);
	CONNECT_SIGNAL(mouse, moved,
				   this, onMouseMoved);
	CONNECT_SIGNAL(mouse, scrolled,
				   this, onMouseWheel);
	auto keyboards = Context::getInstance()->getApplication()->getEventManager()->findEventSource<engine::Keyboard>();
	auto keyboard = keyboards.front();
	CONNECT_SIGNAL(keyboard, keyPressed,
				   this, onKeyPressed);
	CONNECT_SIGNAL(keyboard, keyReleased,
				   this, onKeyReleased);

}

void TestMain::update()
{
	ASSERT(_CrtCheckMemory());
}

void TestMain::render()
{

}

void TestMain::onMouseMoved(int x, int y)
{
	Log("onMouseMoved % %", x, y);
}

void TestMain::onMouseWheel(int x, int y, int w)
{
	Log("onMouseWheel % % %", x, y, w);
}

void TestMain::onMouseLeftDown(int x, int y)
{
	Log("onMouseLeftDown % %", x, y);
}
void TestMain::onMouseRightDown(int x, int y)
{
	Log("onMouseRightDown % %", x, y);
}
void TestMain::onMouseMiddleDown(int x, int y)
{
	Log("onMouseMiddleDown % %", x, y);
}
void TestMain::onMouseLeftUp(int x, int y)
{
	Log("onMouseLeftUp % %", x, y);
}
void TestMain::onMouseRightUp(int x, int y)
{
	Log("onMouseRightUp % %", x, y);
}
void TestMain::onMouseMiddleUp(int x, int y)
{
	Log("onMouseMiddleUp % %", x, y);
}
void TestMain::onKeyPressed(engine::KeyboardButton button)
{
	Log("onKeyPressed %", engine::Keyboard::KeyboardButtonToString(button));
}
void TestMain::onKeyReleased(engine::KeyboardButton button)
{
	Log("onKeyReleased %", engine::Keyboard::KeyboardButtonToString(button));
}

engine::ISignalManager* TestMain::getSignalManager() const
{
	return engine::Context::getInstance()->getApplication()->getEventManager()->getEventsSignalManager();
}