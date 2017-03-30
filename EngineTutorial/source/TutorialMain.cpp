#include "stdafx.h"

#include <engine/app/StandardApplicationParameter.h>

#include <engine/app/Application.h>

#include <engine/environmentBuilder/ContextBuilder.h>
#include <engine/environmentBuilder/ApplicationBuilder.h>
#include <engine/environmentBuilder/WindowEnvironmentBuilder.h>
#include <engine/environmentBuilder/EventBuilder.h>
#include <engine/environmentBuilder/BuildFinalizer.h>

#include <engine/ModuleDefinitions.h>

#include <TestMain.h>


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


