#include <stdafx.h>
#include <engine/events/winapi/EventManagerFactoryImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_WINAPI

#include <engine/events/winapi/MouseImpl.h>
#include <engine/events/winapi/KeyboardImpl.h>
#include <engine/events/winapi/EventManagerImpl.h>

namespace engine
{
	namespace winapi
	{

		EventManagerFactoryImpl::EventManagerFactoryImpl(const std::set<BasicInputType> &basicInputs)
			: EventManagerFactory(basicInputs)
		{

		}

		std::unique_ptr<EventSourceBase> EventManagerFactoryImpl::createMouse() const
		{
			return std::make_unique<MouseImpl>();
		}

		std::unique_ptr<EventSourceBase> EventManagerFactoryImpl::createKeyboard() const
		{
			return std::make_unique<KeyboardImpl>();
		}

		std::unique_ptr<EventManager> EventManagerFactoryImpl::createEventManagerImpl()
		{
			return std::make_unique<EventManagerImpl>();
		}
	}
}

#endif
