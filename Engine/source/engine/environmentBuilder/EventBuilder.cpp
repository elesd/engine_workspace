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
		switch(_members->windowModule)
		{
			case ContextModuleType::Glfw: factory.reset(new glfw::EventManagerFactoryImpl(basicInputs)); break;
			case ContextModuleType::WinApi: // TODO
			case ContextModuleType::Sdl: //TODO
			default: HARD_FAIL("Not implemented");
		}
		setEventManagerFactory(_members->application, std::move(factory));
		return WindowEnvironmentBuilder(_members->windowModule);
	}

	WindowEnvironmentBuilder EventBuilder::skip()
	{
		return WindowEnvironmentBuilder(_members->windowModule);
	}
}
