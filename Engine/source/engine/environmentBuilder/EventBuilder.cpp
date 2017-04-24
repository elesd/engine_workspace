#include <stdafx.h>
#include <engine/environmentBuilder/EventBuilder.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/ModuleDefinitions.h>

#include <engine/environmentBuilder/WindowEnvironmentBuilder.h>

#include <engine/events/EventManager.h>
#include <engine/events/EventSourceBase.h>

#include <engine/exceptions/LogicalErrors.h>

#include <engine/events/glfw/EventManagerImpl.h>
#include <engine/events/glfw/MouseImpl.h>
#include <engine/events/glfw/KeyboardImpl.h>

#include <engine/events/winapi/EventManagerImp.h>
#include <engine/events/winapi/MouseImpl.h>
#include <engine/events/winapi/KeyboardImpl.h>

namespace engine
{
	struct EventBuilderPrivate
	{
		EventBuilderPrivate(const ContextModuleType windowModule)
			: windowModule(windowModule)
		{	}
		ContextModuleType windowModule;
		std::unique_ptr<EventManager> eventManager;
	};

	EventBuilder::EventBuilder(const ContextModuleType windowModule)
		:_members(new EventBuilderPrivate(windowModule))
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
		_members->eventManager = createEventManager();
		initBasicInputs(basicInputs);
		setEventManager(std::move(_members->eventManager));
		return WindowEnvironmentBuilder(_members->windowModule);
	}

	WindowEnvironmentBuilder EventBuilder::skip()
	{
		return WindowEnvironmentBuilder(_members->windowModule);
	}

	void EventBuilder::initBasicInputs(const std::set<BasicInputType> &basicInputs) const
	{
		for(BasicInputType inputType : basicInputs)
		{
			std::unique_ptr<EventSourceBase> input = createEventHandler(inputType);
			_members->eventManager->addEventSource(std::move(input));
		}
	}

	std::unique_ptr<EventSourceBase> EventBuilder::createEventHandler(BasicInputType type) const
	{
		std::unique_ptr<EventSourceBase> result;
		switch(type)
		{
			case BasicInputType::Keyboard: result = createKeyboard(); break;
			case BasicInputType::Mouse:    result = createMouse(); break;
			default: throw InitializationError("Unexpected basic input type");
		}
		return result;
	}

	std::unique_ptr<EventSourceBase> EventBuilder::createMouse() const
	{
		std::unique_ptr<EventSourceBase> result;
		switch(_members->windowModule)
		{
			case ContextModuleType::Glfw: result = std::make_unique<glfw::MouseImpl>(); break;
			case ContextModuleType::Sdl: // TODO
				break;
			case ContextModuleType::WinApi: result = std::make_unique<winapi::MouseImpl>();
		}
		ASSERT(result);
		return result;
	}

	std::unique_ptr<EventSourceBase> EventBuilder::createKeyboard() const
	{
		std::unique_ptr<EventSourceBase> result;
		switch(_members->windowModule)
		{
			case ContextModuleType::Glfw: result = std::make_unique<glfw::KeyboardImpl>(); break;
			case ContextModuleType::Sdl: // TODO
				break;
			case ContextModuleType::WinApi: result = std::make_unique<winapi::KeyboardImpl>();
		}
		ASSERT(result);
		return result;
	}

	std::unique_ptr<EventManager> EventBuilder::createEventManager()
	{
		std::unique_ptr<EventManager> result;
		switch(_members->windowModule)
		{
			case ContextModuleType::Glfw: result = std::make_unique<glfw::EventManagerImpl>(); break;
			case ContextModuleType::Sdl: // TODO
				break;
			case ContextModuleType::WinApi: result = std::make_unique<winapi::EventManagerImpl>();
		}
		ASSERT(result);
		return result;
	}
}
