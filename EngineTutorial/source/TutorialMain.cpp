#include "stdafx.h"

#include <engine/app/Application.h>
#include <engine/environmentBuilder/EasyBuilder.h>

#include <TestMain.h>


#if TUTORIAL_USE_WINAPI == 0


int main(int argc, char* argv[])
{
	engine::EasyBuilder builder(std::make_unique<TestMain>());
	builder.AddInput(engine::EventBuilder::BasicInputType::Keyboard)
		   .AddInput(engine::EventBuilder::BasicInputType::Mouse);
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
	engine::EasyBuilder builder(std::move(main));
	builder.AddInput(engine::EventBuilder::BasicInputType::Keyboard)
		   .AddInput(engine::EventBuilder::BasicInputType::Mouse);
	engine::Application *app = builder.buildEngine(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	app->run();

	return 0;
}

#endif


