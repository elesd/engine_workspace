#include "stdafx.h"
#if ENGINE_USE_SDL == 0
#include "engine/view/sdl/WindowImpl.h"
/////////////////////////////////////////

namespace engine
{
	namespace view
	{
		namespace sdl
		{

			WindowImpl::WindowImpl(SDL_Window *, const view::WindowParameter &, const std::string &)
				: view::Window()
			{
				HARD_FAIL("Not implemented module");
			}

			WindowImpl::WindowImpl(SDL_Window *, const std::string &)
				: view::Window()
			{
				HARD_FAIL("Not implemented module");
			}

			WindowImpl::~WindowImpl()
			{
				HARD_FAIL("Not implemented module");
			}

			WindowImpl::operator bool() const
			{
				HARD_FAIL("Not implemented module");
				return false;
			}

			void WindowImpl::setPositionImp(int32_t, int32_t)
			{
				HARD_FAIL("Not implemented module");
			}

			void WindowImpl::setWidthImpl(uint32_t)
			{
				HARD_FAIL("Not implemented module");
			}

			void WindowImpl::setHeightImpl(uint32_t)
			{
				HARD_FAIL("Not implemented module");
			}

			void WindowImpl::setSizeImpl(uint32_t, uint32_t)
			{
				HARD_FAIL("Not implemented module");
			}

			SDL_Window *WindowImpl::getSDLWindow()
			{
				HARD_FAIL("Not implemented module");
				return nullptr;
			}
		}
	}
}
#endif