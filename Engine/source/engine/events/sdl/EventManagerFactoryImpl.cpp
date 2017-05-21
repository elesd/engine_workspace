#include <stdafx.h>
#include <engine/events/sdl/EventManagerFactoryImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_SDL
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
#else 

#include <engine/events/sdl/empty/EventManagerFactoryImpl.cpp>

#endif
