#include <stdafx.h>
#if ENGINE_USE_WINAPI == 0

#include <engine/view/winapi/WindowManagerImpl.h>
///////////////////////////////////////////////////

#include <engine/render/RenderContext.h>
#include <engine/video/Driver.h>

namespace engine
{
	namespace winapi
	{

		WindowManagerImpl::WindowManagerImpl()
		{
			HARD_FAIL("Inactive module");
		}

		WindowManagerImpl::~WindowManagerImpl()
		{
			HARD_FAIL("Inactive module");
		}

		Window *WindowManagerImpl::createMainWindowImpl(const WindowParameter &, const std::string &)
		{
			HARD_FAIL("Inactive module");
			return nullptr;
		}

		Window *WindowManagerImpl::createFullScreenMainWindowImpl(const uint32_t , const uint32_t , const std::string &, uint32_t)
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

		void WindowManagerImpl::RegisterWindowClass()
		{
			HARD_FAIL("Inactive module");
		}

		std::unique_ptr<RenderContext> WindowManagerImpl::createRenderContext(const RenderContextParameters &params, Window *window) const
		{
			HARD_FAIL("Inactive module");
			return nullptr;
		}
		std::unique_ptr<RenderContext> WindowManagerImpl::preCreateRenderContext(const RenderContextParameters &) const
		{
			HARD_FAIL("Inactive module");
			return nullptr;
		}

		void WindowManagerImpl::postCreateRenderContext(RenderContext* renderContext, const RenderContextParameters& params, Window* window) const
		{
			HARD_FAIL("Inactive module");
		}
	}
}
#endif