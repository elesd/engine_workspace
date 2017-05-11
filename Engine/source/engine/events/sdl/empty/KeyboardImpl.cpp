#include <stdafx.h>
#include <engine/events/sdl/KeyboardImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_SDL

namespace engine
{
	namespace sdl
	{
		void KeyboardImpl::handleEvent(const SDL_KeyboardEvent &event)
		{
			HARD_FAIL("Inactive module");
		}

	}
}

#endif
