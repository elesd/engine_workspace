#include <stdafx.h>
#if ENGINE_USE_GLFW == 0
#include <engine/view/glfw/WindowManagerImpl.h>
///////////////////////////////////////////////////
#include <engine/view/glfw/WindowImpl.h>

#include <engine/render/RenderContext.h>

namespace engine
{
	namespace glfw
	{
		Window *WindowManagerImpl::createMainWindowImpl(const WindowParameter &,
															  const std::string &)
		{
			HARD_FAIL("Inactive module");
			return nullptr;
		}

		Window *WindowManagerImpl::createFullScreenMainWindowImpl(const uint32_t, const uint32_t, const std::string &, uint32_t)
		{
			HARD_FAIL("Inactive module");
			return nullptr;
		}

		Window *WindowManagerImpl::createSecondaryWindowImpl(const WindowParameter &,
																   const std::string &,
																   Window *)
		{
			HARD_FAIL("Inactive module");
			return nullptr;
		}

		Window *WindowManagerImpl::createSecondaryFullScreenWindowImpl(const uint32_t, const uint32_t, const std::string &, uint32_t, Window *)
		{
			HARD_FAIL("Inactive module");
			return nullptr;
		}

		uint32_t WindowManagerImpl::getMonitorCount() const
		{
			HARD_FAIL("Inactive module");
			return 0;
		}

		uint32_t WindowManagerImpl::getMainMonitorId() const
		{
			HARD_FAIL("Inactive module");
			return 0;
		}

		std::unique_ptr<RenderContext> WindowManagerImpl::createRenderContext(const RenderContextParameters &, Window *) const
		{
			FAIL("Inactive module");
			return nullptr;
		}
	}
}
#endif