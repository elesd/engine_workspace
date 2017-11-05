#include <stdafx.h>
#include <engine/environmentBuilder/EventBuilder.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/ModuleDefinitions.h>

#include <engine/app/Application.h>

#include <engine/environmentBuilder/WindowEnvironmentBuilder.h>

#include <engine/events/EventManager.h>
#include <engine/events/EventSourceBase.h>
#include <engine/events/EventManagerFactory.h>

#include <engine/events/glfw/EventManagerFactoryImpl.h>
#include <engine/events/winapi/EventManagerFactoryImpl.h>
#include <engine/events/sdl/EventManagerFactoryImpl.h>

#include <engine/exceptions/LogicalErrors.h>


namespace engine
{
	struct EventBuilderPrivate
	{
		EventBuilderPrivate(const ContextModuleType windowModule, Application *app)
			: windowModule(windowModule), application(app)
		{	}
		ContextModuleType windowModule;
		Application *application;
	};

	EventBuilder::EventBuilder(const ContextModuleType windowModule, Application *app)
		:_members(new EventBuilderPrivate(windowModule, app))
	{
	}

	EventBuilder::EventBuilder(EventBuilder &&o)
	{
		_members = o._members;
		o._members = nullptr;
	}

	EventBuilder::~EventBuilder()
	{
		delete _members;
	}

	WindowEnvironmentBuilder EventBuilder::build(const std::set<BasicInputType> &basicInputs)
	{
		std::unique_ptr<EventManagerFactory> factory;
#if ENGINE_USE_GLFW
		HARD_ASSERT(_members->windowModule == ContextModuleType::Glfw);
		factory.reset(new glfw::EventManagerFactoryImpl(basicInputs));
#elif ENGINE_USE_SDL
		HARD_ASSERT(_members->windowModule == ContextModuleType::Sdl);
		factory.reset(new sdl::EventManagerFactoryImpl(basicInputs));
#elif ENGINE_USE_WINAPI
		HARD_ASSERT(_members->windowModule == ContextModuleType::WinApi);
		factory.reset(new winapi::EventManagerFactoryImpl(basicInputs));
#else
		HARD_FAIL("Unknown window context module");
#endif
		return WindowEnvironmentBuilder(_members->windowModule, std::move(factory));
	}

	WindowEnvironmentBuilder EventBuilder::skip()
	{
		return WindowEnvironmentBuilder(_members->windowModule, nullptr);
	}
}
