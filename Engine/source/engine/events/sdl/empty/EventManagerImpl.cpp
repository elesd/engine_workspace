#include <stdafx.h>
#include <engine/events/sdl/EventManagerImpl.h>

#if !ENGINE_USE_SDL
#include <engine/app/Application.h>

#include <engine/events/sdl/MouseImpl.h>
#include <engine/events/sdl/KeyboardImpl.h>
#include <engine/events/EventManager.h>

#include <engine/Context.h>

namespace engine
{
	namespace sdl
	{

		void EventManagerImpl::handleEvent(const SDL_KeyboardEvent& event)
		{
			HARD_FAIL("Inactive module");
		}

		void EventManagerImpl::handleEvent(const SDL_MouseMotionEvent& event)
		{
			HARD_FAIL("Inactive module");
		}

		void EventManagerImpl::handleEvent(const SDL_MouseButtonEvent& event)
		{
			HARD_FAIL("Inactive module");
		}

		void EventManagerImpl::handleEvent(const SDL_MouseWheelEvent& event)
		{
			HARD_FAIL("Inactive module");
		}

	}
}
#endif
