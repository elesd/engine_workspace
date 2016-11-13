#include "stdafx.h"
#if ENGINE_USE_GLFW == 0
#include "engine/modules/glfw/WindowManagerImpl.h"
///////////////////////////////////////////////////
#include "engine/modules/glfw/WindowImpl.h"

namespace engine
{
	namespace glfw
	{
		view::Window *WindowManagerImpl::createMainWindowImpl(const view::WindowParameter &,
			const std::string &)
		{
			HARD_FAIL("Not implemented module");
			return nullptr;
		}
		
		view::Window *WindowManagerImpl::createFullScreenMainWindowImpl(const uint32_t, const uint32_t, const std::string &, uint32_t )
		{
			HARD_FAIL("Not implemented module");
			return nullptr;
		}

		view::Window *WindowManagerImpl::createSecondaryWindowImpl(const view::WindowParameter &,
			const std::string &,
			view::Window *)
		{
			HARD_FAIL("Not implemented module");
			return nullptr;
		}

		view::Window *WindowManagerImpl::createSecondaryFullScreenWindowImpl(const uint32_t , const uint32_t , const std::string &, uint32_t , view::Window *)
		{
			HARD_FAIL("Not implemented module");
			return nullptr;
		}

		uint32_t WindowManagerImpl::getMonitorCount() const
		{
			HARD_FAIL("Not implemented module");
			return 0;
		}

		uint32_t WindowManagerImpl::getMainMonitorId() const
		{
			HARD_FAIL("Not implemented module");
			return 0;
		}

	}
}
#endif