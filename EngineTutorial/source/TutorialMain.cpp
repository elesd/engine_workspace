#include "stdafx.h"

#include <engine/app/Application.h>
#include <engine/environmentBuilder/EventBuilder.h>
#include <engine/environmentBuilder/EasyBuilder.h>
#include <engine/fileSystem/FileSystem.h>
#include <engine/ModuleDefinitions.h>

#include <TestMain.h>


#if TUTORIAL_USE_WINAPI == 0


int main(int argc, char* argv[])
{
	std::unique_ptr<engine::IMain> main(new TestMain());
	engine::EasyBuilder builder(std::move(main), engine::ContextModuleType::Glfw);
	builder.AddInput(engine::BasicInputType::Keyboard)
		   .AddInput(engine::BasicInputType::Mouse);
	engine::FileSystemSettings settings;
	settings.workingDirectory = "..\\data\\";
	builder.setFileSystemSetting(settings);
	engine::Application *app = builder.buildEngine(argc, argv);
	app->run();
	return 0;
}
#else

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	std::unique_ptr<engine::IMain> main(new TestMain());
	engine::EasyBuilder builder(std::move(main), engine::ContextModuleType::WinApi);
	builder.AddInput(engine::BasicInputType::Keyboard)
		   .AddInput(engine::BasicInputType::Mouse);
	engine::FileSystemSettings settings;
	settings.workingDirectory = "..\\data\\";
	builder.setFileSystemSetting(settings);
	engine::Application *app = builder.buildEngine(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	app->run();

	return 0;
}

#endif


