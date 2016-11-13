#include "stdafx.h"
#if ENGINE_USE_SDL == 0
#include "engine/modules/sdl/WindowManagerImpl.h"
///////////////////////////////////////////////////
#include "engine/modules/sdl/WindowImpl.h"

namespace engine
{
	namespace sdl
	{
		view::Window *WindowManagerImpl::createMainWindowImpl(const view::WindowParameter &,
			const std::string &)
		{
			HARD_ASSERT("Not implemented module");
			return nullptr;
		}

		view::Window *WindowManagerImpl::createFullScreenMainWindowImpl(const uint32_t width, const uint32_t , const std::string &, uint32_t )
		{
			HARD_ASSERT("Not implemented module");
			return nullptr;
		}

		view::Window *WindowManagerImpl::createSecondaryWindowImpl(const view::WindowParameter &,
			const std::string &,
			view::Window *)
		{
			HARD_ASSERT("Not implemented module");
			return nullptr;
		}

		view::Window *WindowManagerImpl::createSecondaryFullScreenWindowImpl(const uint32_t , const uint32_t , const std::string &, uint32_t , view::Window *)
		{
			HARD_ASSERT("Not implemented module");
			return nullptr;
		}

		uint32_t WindowManagerImpl::getMonitorCount() const
		{
			HARD_ASSERT("Not implemented module");
			return 0;
		}

		uint32_t WindowManagerImpl::getMainMonitorId() const
		{
			HARD_ASSERT("Not implemented module");
			return 0;
		}

	}
}
#endif