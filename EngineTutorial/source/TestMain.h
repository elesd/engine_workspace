#pragma once
#include <engine/app/IMain.h>
#include <engine/signalSlot/SlotHolder.h>


class TestMain : public engine::IMain,
	public engine::SlotHolder
{
public:
	void load()
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

	void update()
	{
		ASSERT(_CrtCheckMemory());
	}

	void render()
	{

	}

	void onMouseMoved(int x, int y)
	{
		Log("onMouseMoved % %", x, y);
	}

	void onMouseWheel(int x, int y, int w)
	{
		Log("onMouseWheel % % %", x, y, w);
	}

	void onMouseLeftDown(int x, int y)
	{
		Log("onMouseLeftDown % %", x, y);
	}
	void onMouseRightDown(int x, int y)
	{
		Log("onMouseRightDown % %", x, y);
	}
	void onMouseMiddleDown(int x, int y)
	{
		Log("onMouseMiddleDown % %", x, y);
	}
	void onMouseLeftUp(int x, int y)
	{
		Log("onMouseLeftUp % %", x, y);
	}
	void onMouseRightUp(int x, int y)
	{
		Log("onMouseRightUp % %", x, y);
	}
	void onMouseMiddleUp(int x, int y)
	{
		Log("onMouseMiddleUp % %", x, y);
	}
	void onKeyPressed(engine::KeyboardButton button)
	{
		Log("onKeyPressed %", engine::Keyboard::KeyboardButtonToString(button));
	}
	void onKeyReleased(engine::KeyboardButton button)
	{
		Log("onKeyReleased %", engine::Keyboard::KeyboardButtonToString(button));
	}

	engine::ISignalManager* getSignalManager() const override
	{
		return engine::Context::getInstance()->getApplication()->getEventManager()->getEventsSignalManager();
	}
};