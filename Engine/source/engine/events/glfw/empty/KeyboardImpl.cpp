#include <stdafx.h>
#include <engine/events/glfw/KeyboardImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_GLFW


namespace engine
{
	namespace glfw
	{
		bool KeyboardImpl::handleKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mods)
		{
			HARD_FAIL("Inactive module");
			return false;
		}

		bool KeyboardImpl::handleKeyUpEvent(int32_t key)
		{
			HARD_FAIL("Inactive module");
			return false;
		}

		bool KeyboardImpl::handleKeyDownEvent(int32_t key)
		{
			HARD_FAIL("Inactive module");
			return false;
		}
	}
}

#endif
