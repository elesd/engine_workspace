#include <stdafx.h>
#include <engine/events/EventManagerFactory.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/environmentBuilder/EventBuilder.h>
#include <engine/events/EventManager.h>
#include <engine/events/EventSourceBase.h>

#include <engine/exceptions/LogicalErrors.h>
namespace engine
{

	struct EventManagerFactoryPrivate
	{
		EventManagerFactoryPrivate(const std::set<BasicInputType> &basicInputs)
			: basicInputs(basicInputs)

		{	}
		std::set<BasicInputType> basicInputs;
	};

	EventManagerFactory::EventManagerFactory(const std::set<BasicInputType> &basicInputs)
		:_members(new EventManagerFactoryPrivate(basicInputs))
	{
	}

	EventManagerFactory::~EventManagerFactory()
	{
		delete _members;
	}

	void EventManagerFactory::initBasicInputs(EventManager *eventManager, const std::set<BasicInputType> &basicInputs) const
	{
		for(BasicInputType inputType : basicInputs)
		{
			std::unique_ptr<EventSourceBase> input = createEventHandler(inputType);
			eventManager->addEventSource(std::move(input));
		}
	}

	std::unique_ptr<EventSourceBase> EventManagerFactory::createEventHandler(BasicInputType type) const
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

//	std::unique_ptr<EventSourceBase> EventManagerFactory::createMouse() const
//	{
//		std::unique_ptr<EventSourceBase> result;
//		switch(_members->windowModule)
//		{
//			case ContextModuleType::Glfw: result = std::make_unique<glfw::MouseImpl>(); break;
//			case ContextModuleType::Sdl: // TODO
//				break;
//			case ContextModuleType::WinApi: result = std::make_unique<winapi::MouseImpl>();
//		}
//		ASSERT(result);
//		return result;
//	}
//
//	std::unique_ptr<EventSourceBase> EventManagerFactory::createKeyboard() const
//	{
//		std::unique_ptr<EventSourceBase> result;
//		switch(_members->windowModule)
//		{
//			case ContextModuleType::Glfw: result = std::make_unique<glfw::KeyboardImpl>(); break;
//			case ContextModuleType::Sdl: // TODO
//				break;
//			case ContextModuleType::WinApi: result = std::make_unique<winapi::KeyboardImpl>();
//		}
//		ASSERT(result);
//		return result;
//	}

	std::unique_ptr<EventManager> EventManagerFactory::createEventManager()
	{
		std::unique_ptr<EventManager> result;
		result = createEventManagerImpl();
//		switch(_members->windowModule)
//		{
//			case ContextModuleType::Glfw: result = std::make_unique<glfw::EventManagerImpl>(); break;
//			case ContextModuleType::Sdl: // TODO
//				break;
//			case ContextModuleType::WinApi: result = std::make_unique<winapi::EventManagerImpl>();
//		}
		ASSERT(result);
		initBasicInputs(result.get(), _members->basicInputs);
		return result;
	}
}
