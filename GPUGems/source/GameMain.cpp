#include "stdafx.h"

#include "engine/app/Application.h"
#include "engine/view/WindowManager.h"
#include "engine/app/StandardApplicationParameter.h"
#include "engine/app/IMain.h"
#include "engine/ModuleDefinitions.h"
#include "engine/environmentBuilder/ContextBuilder.h"
#include "engine/environmentBuilder/ApplicationBuilder.h"
#include "engine/environmentBuilder/WindowEnvironmentBuilder.h"
#include "engine/environmentBuilder/BuildFinalizer.h"


class TestMain: public engine::app::IMain
{
public:
	void load()
	{
		using engine::Context;
		engine::view::Window *mainWindow = Context::getInstance()->getWindowManager()->createFullScreenMainWindow(640, 480, "TestWindow", 0);
 		//engine::view::Window *mainWindow = Context::getInstance()->getWindowManager()->createMainWindow(engine::WindowParameter(100, 200, 640, 480), "TestWindow");
	//	engine::view::Window *second = Context::getInstance()->getWindowManager()->createSecondaryWindow(engine::WindowParameter(180, 200, 640, 480), "TestWindow", mainWindow);
		ASSERT(mainWindow != nullptr);


	}

	void update()
	{

	}

	void render()
	{

	}
};
#if USE_WINAPI == 0
void buildEngine(int argc, char* argv[])
{
	using engine::environmentBuilder::ContextBuilder;
	using engine::environmentBuilder::ApplicationBuilder;
	using engine::environmentBuilder::WindowEnvironmentBuilder;
	using engine::environmentBuilder::BuildFinalizer;
	using engine::app::StandardApplicationParameter;
	using engine::app::IApplicationParameter;

	ContextBuilder envBuilder({engine::ContextModuleType::Sdl});
	ApplicationBuilder appBuilder = envBuilder.buildForApplication();
	std::unique_ptr<IApplicationParameter> args(new StandardApplicationParameter(argc, argv));
	WindowEnvironmentBuilder windowBuilder = appBuilder.build(std::move(args), std::unique_ptr<engine::app::IMain>(new TestMain()));
	BuildFinalizer lastStep = windowBuilder.build();
	lastStep.build();
}

int main(int argc, char* argv[])
{
	buildEngine(argc, argv);

	engine::app::Application *app = engine::Context::getInstance()->getApplication();
	app->start();
	while(app->isActive())
	{
		app->update();
		app->render();
	}

	return 0;
}
#else
#include <Windows.h>
#include "engine/modules/winapi/WinApiApplicationParameter.h"

void buildEngine(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	using engine::environmentBuilder::ContextBuilder;
	using engine::environmentBuilder::ApplicationBuilder;
	using engine::environmentBuilder::WindowEnvironmentBuilder;
	using engine::environmentBuilder::BuildFinalizer;
	using engine::winapi::WinApiApplicationParameter;
	using engine::app::IApplicationParameter;

	ContextBuilder envBuilder({engine::ContextModuleType::WinApi});
	ApplicationBuilder appBuilder = envBuilder.buildForApplication();
	std::unique_ptr<IApplicationParameter> args(new WinApiApplicationParameter(hInstance, hPrevInstance, lpCmdLine, nCmdShow));
	WindowEnvironmentBuilder windowBuilder = appBuilder.build(std::move(args), std::unique_ptr<engine::app::IMain>(new TestMain()));
	BuildFinalizer lastStep = windowBuilder.build();
	lastStep.build();
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	buildEngine(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	engine::app::Application *app = engine::Context::getInstance()->getApplication();
	app->start();
	while(app->isActive())
	{
		app->update();
		app->render();
	}

	return 0;
}

#endif


