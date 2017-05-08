#include <stdafx.h>
#include <engine/events/glfw/EventManagerFactoryImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_GLFW
#include <engine/events/EventSourceBase.h>
#include <engine/events/EventManager.h>

namespace engine
{
	namespace glfw
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
