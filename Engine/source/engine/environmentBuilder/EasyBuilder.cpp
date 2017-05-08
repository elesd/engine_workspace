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
		std::set<engine::BasicInputType> inputs;
		engine::ContextModuleType windowModule;
	};

	EasyBuilder::EasyBuilder(std::unique_ptr<IMain> &&main, engine::ContextModuleType windowModul)
		:_members(new EasyBuilderPrivate())
	{
		_members->main = std::move(main);
		_members->windowModule = windowModul;
	}

	EasyBuilder::~EasyBuilder()
	{
		delete _members;
	}

	EasyBuilder& EasyBuilder::AddInput(engine::BasicInputType input)
	{
		_members->inputs.insert(input);
		return *this;
	}

	Application* EasyBuilder::buildEngine(HINSTANCE hInstance,
								  HINSTANCE hPrevInstance,
								  LPSTR lpCmdLine,
								  int nCmdShow) const
	{
		ASSERT(_members->windowModule == ContextModuleType::WinApi);
		std::unique_ptr<IApplicationParameter> args(new winapi::WinApiApplicationParameter(hInstance, hPrevInstance, lpCmdLine, nCmdShow));
		buildEngine(std::move(args));
		return Context::getInstance()->getApplication();
	}

	Application* EasyBuilder::buildEngine(int argc, char* argv[]) const
	{
		ASSERT(_members->windowModule == ContextModuleType::Sdl
		|| _members->windowModule == ContextModuleType::Glfw);
		std::unique_ptr<IApplicationParameter> args(new StandardApplicationParameter(argc, argv));
		buildEngine(std::move(args));
		return Context::getInstance()->getApplication();
	}

	void EasyBuilder::buildEngine(std::unique_ptr<IApplicationParameter> args) const
	{
		ContextBuilder envBuilder({_members->windowModule});
		ApplicationBuilder appBuilder = envBuilder.buildForApplication();
		EventBuilder eventBuilder = appBuilder.build(std::move(args), std::move(_members->main));
		WindowEnvironmentBuilder windowBuilder = eventBuilder.build(_members->inputs);
		BuildFinalizer lastStep = windowBuilder.build();
		lastStep.build();
	}

}
