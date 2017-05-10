#include <stdafx.h>
#include <engine/events/winapi/EventManagerFactoryImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_WINAPI

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
			HARD_FAIL("Inactive module");
		}

		std::unique_ptr<EventSourceBase> EventManagerFactoryImpl::createMouse() const
		{
			HARD_FAIL("Inactive module");
			return nullptr;
		}

		std::unique_ptr<EventSourceBase> EventManagerFactoryImpl::createKeyboard() const
		{
			HARD_FAIL("Inactive module");
			return nullptr;
		}

		std::unique_ptr<EventManager> EventManagerFactoryImpl::createEventManagerImpl()
		{
			HARD_FAIL("Inactive module");
			return nullptr;
		}
	}
}
#endif
