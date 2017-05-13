#include <stdafx.h>
#if ENGINE_USE_SDL == 0
#include <engine/view/sdl/WindowImpl.h>
/////////////////////////////////////////

namespace engine
{
	namespace sdl
	{

		WindowImpl::WindowImpl(WindowManager *windowManager, SDL_Window *, const WindowParameter &, const std::string &)
			: Window(windowManager)
		{
			HARD_FAIL("Inactive module");
		}

		WindowImpl::WindowImpl(WindowManager *windowManager, SDL_Window *, const std::string &)
			: Window(windowManager)
		{
			HARD_FAIL("Inactive module");
		}

		WindowImpl::~WindowImpl()
		{
			HARD_FAIL("Inactive module");
		}

		WindowImpl::operator bool() const
		{
			HARD_FAIL("Inactive module");
			return false;
		}

		void WindowImpl::setPositionImp(int32_t, int32_t)
		{
			HARD_FAIL("Inactive module");
		}

		void WindowImpl::setWidthImpl(uint32_t)
		{
			HARD_FAIL("Inactive module");
		}

		void WindowImpl::setHeightImpl(uint32_t)
		{
			HARD_FAIL("Inactive module");
		}

		void WindowImpl::setSizeImpl(uint32_t, uint32_t)
		{
			HARD_FAIL("Inactive module");
		}

		SDL_Window *WindowImpl::getSDLWindow()
		{
			HARD_FAIL("Inactive module");
			return nullptr;
		}
	}
}
#endif