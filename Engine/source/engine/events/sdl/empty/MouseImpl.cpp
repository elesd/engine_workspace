#include <stdafx.h>
#include <engine/events/sdl/MouseImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if !ENGINE_USE_SDL
#include <engine/Context.h>
#include <engine/events/EventManager.h>

namespace engine
{
	namespace sdl
	{
		void MouseImpl::handleMoveEvent(const SDL_MouseMotionEvent& event)
		{
			HARD_FAIL("Inactive module");
		}

		void MouseImpl::handleClickEvent(const SDL_MouseButtonEvent& event)
		{
			HARD_FAIL("Inactive module");
		}

		void MouseImpl::handleScrollEvent(const SDL_MouseWheelEvent& event)
		{
			HARD_FAIL("Inactive module");
		}
	}
}

#endif
