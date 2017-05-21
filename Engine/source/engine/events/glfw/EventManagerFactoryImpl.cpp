#include <stdafx.h>
#include <engine/events/glfw/EventManagerFactoryImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_GLFW
#include <engine/events/glfw/MouseImpl.h>
#include <engine/events/glfw/KeyboardImpl.h>
#include <engine/events/glfw/EventManagerImpl.h>

namespace engine
{
	namespace glfw
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

#include <engine/events/glfw/empty/EventManagerFactoryImpl.cpp>

#endif
