#include <stdafx.h>
#include <engine/environmentBuilder/EasyBuilder.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/app/winapi/WinApiApplicationParameter.h>
#include <engine/app/IMain.h>
#include <engine/environmentBuilder/ContextBuilder.h>
#include <engine/environmentBuilder/ApplicationBuilder.h>
#include <engine/environmentBuilder/WindowEnvironmentBuilder.h>
#include <engine/environmentBuilder/EventBuilder.h>
#include <engine/environmentBuilder/BuildFinalizer.h>

#include <engine/ModuleDefinitions.h>


namespace engine
{
	struct EasyBuilderPrivate
	{
		std::unique_ptr<IMain> main;
		std::set<engine::EventBuilder::BasicInputType> inputs;
	};

	EasyBuilder::EasyBuilder(std::unique_ptr<IMain> main)
	{
		_members->main = std::move(main);
	}

	EasyBuilder& EasyBuilder::AddInput(engine::EventBuilder::BasicInputType input)
	{
		_members->inputs.insert(input);
		return *this;
	}

	void EasyBuilder::buildEngine(HINSTANCE hInstance,
								  HINSTANCE hPrevInstance,
								  LPSTR lpCmdLine,
								  int nCmdShow) const
	{
		std::unique_ptr<IApplicationParameter> args(new winapi::WinApiApplicationParameter(hInstance, hPrevInstance, lpCmdLine, nCmdShow));
		buildEngine(std::move(args));
	}

	void EasyBuilder::buildEngine(int argc, char* argv[]) const
	{
		std::unique_ptr<IApplicationParameter> args(new StandardApplicationParameter(argc, argv));
		buildEngine(std::move(args));
	}

	void EasyBuilder::buildEngine(std::unique_ptr<IApplicationParameter> args) const
	{
		ContextBuilder envBuilder({engine::ContextModuleType::WinApi});
		ApplicationBuilder appBuilder = envBuilder.buildForApplication();
		EventBuilder eventBuilder = appBuilder.build(std::move(args), std::move(_members->main));
		WindowEnvironmentBuilder windowBuilder = eventBuilder.build(_members->inputs);
		BuildFinalizer lastStep = windowBuilder.build();
		lastStep.build();
	}

}