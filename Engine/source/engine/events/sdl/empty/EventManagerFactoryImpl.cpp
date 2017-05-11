#include <stdafx.h>
#include <engine/events/sdl/EventManagerFactoryImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_SDL
#include <engine/events/sdl/MouseImpl.h>
#include <engine/events/sdl/KeyboardImpl.h>
#include <engine/events/sdl/EventManagerImpl.h>

namespace engine
{
	namespace sdl
	{

		EventManagerFactoryImpl::EventManagerFactoryImpl(const std::set<BasicInputType> &basicInputs)
			: EventManagerFactory(basicInputs)
		{
			HARD_FAIL("Inactive module");
			return nullptr;
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
