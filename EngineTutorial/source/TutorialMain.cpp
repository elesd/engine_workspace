#include "stdafx.h"

#include <engine/app/Application.h>
#include <engine/app/StandardApplicationParameter.h>
#include <engine/app/IMain.h>

#include <engine/events/EventManager.h>
#include <engine/events/Mouse.h>
#include <engine/events/Keyboard.h>

#include <engine/environmentBuilder/ContextBuilder.h>
#include <engine/environmentBuilder/ApplicationBuilder.h>
#include <engine/environmentBuilder/WindowEnvironmentBuilder.h>
#include <engine/environmentBuilder/EventBuilder.h>
#include <engine/environmentBuilder/BuildFinalizer.h>

#include <engine/ModuleDefinitions.h>

#include <engine/signalSlot/SignalManager.h>
#include <engine/signalSlot/SlotHolder.h>

#include <engine/view/WindowManager.h>
#if TUTORIAL_USE_WINAPI
#include <Windows.h>
#endif
namespace
{
	void LogToStream(std::ostringstream &os, const std::string &format)
	{
		os << format << std::endl;
	}

	template<class T, class ...Args>
	void LogToStream(std::ostringstream &os, const std::string &format,  T value, Args... args)
	{
		size_t pos = format.find('%');
		if(pos != std::string::npos)
		{
			std::string firstPart = format.substr(0, pos);
			os << firstPart << value;
			if(pos + 1 < format.size())
			{
				std::string secondPart = format.substr(pos + 1);
				LogToStream(os, secondPart, args...);
			}
			else
			{
				os << std::endl;
			}
		}
	}
}
#if TUTORIAL_USE_WINAPI

namespace
{
	template<class ...Args>
	void Log(const std::string &format, Args... params)
	{
		std::ostringstream os;
		LogToStream(os, format, params...);
		std::string str = os.str();
		OutputDebugString(str.c_str());
	}
}
#endif

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
#if TUTORIAL_USE_WINAPI == 0
void buildEngine(int argc, char* argv[])
{
	using engine::ContextBuilder;
	using engine::ApplicationBuilder;
	using engine::WindowEnvironmentBuilder;
	using engine::BuildFinalizer;
	using engine::StandardApplicationParameter;
	using engine::IApplicationParameter;

	ContextBuilder envBuilder({ engine::ContextModuleType::Glfw });
	ApplicationBuilder appBuilder = envBuilder.buildForApplication();
	std::unique_ptr<IApplicationParameter> args(new StandardApplicationParameter(argc, argv));
	WindowEnvironmentBuilder windowBuilder = appBuilder.build(std::move(args), std::unique_ptr<engine::IMain>(new TestMain()));
	BuildFinalizer lastStep = windowBuilder.build();
	lastStep.build();
}

int main(int argc, char* argv[])
{
	buildEngine(argc, argv);

	engine::Application *app = engine::Context::getInstance()->getApplication();
	app->start();
	while(app->isActive())
	{
		app->update();
		app->render();
	}

	return 0;
}
#else
#include "engine/app/winapi/WinApiApplicationParameter.h"

void buildEngine(HINSTANCE hInstance,
				 HINSTANCE hPrevInstance,
				 LPSTR lpCmdLine,
				 int nCmdShow)
{
	using engine::ContextBuilder;
	using engine::ApplicationBuilder;
	using engine::WindowEnvironmentBuilder;
	using engine::BuildFinalizer;
	using engine::winapi::WinApiApplicationParameter;
	using engine::IApplicationParameter;
	using engine::EventBuilder;

	ContextBuilder envBuilder({ engine::ContextModuleType::WinApi });
	ApplicationBuilder appBuilder = envBuilder.buildForApplication();
	std::unique_ptr<IApplicationParameter> args(new WinApiApplicationParameter(hInstance, hPrevInstance, lpCmdLine, nCmdShow));

	EventBuilder eventBuilder = appBuilder.build(std::move(args), std::unique_ptr<engine::IMain>(new TestMain()));
	WindowEnvironmentBuilder windowBuilder = eventBuilder.build({ engine::EventBuilder::BasicInputType::Keyboard, engine::EventBuilder::BasicInputType::Mouse });
	BuildFinalizer lastStep = windowBuilder.build();
	lastStep.build();
}

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{  
	buildEngine(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	engine::Application *app = engine::Context::getInstance()->getApplication();
	app->start();
	while(app->isActive())
	{
		app->update();
		app->render();
	}

	return 0;
}

#endif


