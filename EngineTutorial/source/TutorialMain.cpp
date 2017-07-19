#include "stdafx.h"

#include <engine/app/Application.h>
#include <engine/environmentBuilder/EventBuilder.h>
#include <engine/environmentBuilder/EasyBuilder.h>
#include <engine/fileSystem/FileSystem.h>
#include <engine/ModuleDefinitions.h>

#include <engine/view/Console.h>

#include <TestMain.h>

namespace
{
#if TUTORIAL_USE_GLFW
	engine::ContextModuleType windowModule = engine::ContextModuleType::Glfw;
#else
	engine::ContextModuleType windowModule = engine::ContextModuleType::Sdl;
#endif
///////////////////////////////////////////////////////////////////////////////////

	void setupCommonSetting(engine::EasyBuilder& builder)
	{
		builder.AddInput(engine::BasicInputType::Keyboard)
			.AddInput(engine::BasicInputType::Mouse);
		engine::FileSystemSettings settings;
		settings.workingDirectory = "..\\data\\";
		builder.setFileSystemSetting(settings);
	}
}

#if TUTORIAL_USE_WINAPI == 0

int main(int argc, char* argv[])
{
	std::unique_ptr<engine::IMain> main(new TestMain());
	engine::EasyBuilder builder(std::move(main), windowModule);
	setupCommonSetting(builder);
	engine::Application *app = builder.buildEngine(argc, argv);
	engine::Context::console()->print("Application starts");
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
	setupCommonSetting(builder);
	engine::Application *app = builder.buildEngine(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	engine::Context::console()->print("Application starts");
	app->run();

	return 0;
}

#endif


