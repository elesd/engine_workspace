#include <stdafx.h>

#include <engine/video/sdl/DriverImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_SDL
#include <engine/exceptions/LogicalErrors.h>

#include <engine/view/Window.h>
#include <engine/view/sdl/WindowImpl.h>
#include <engine/video/sdl/BufferDescUtils.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace engine
{
	namespace sdl
	{
		struct DriverImplPrivate
		{
			SDL_Renderer* renderer = nullptr;
		};

		DriverImpl::DriverImpl() 
			: _members(new DriverImplPrivate())
		{
			
		}
		DriverImpl::~DriverImpl()
		{
			if(_members->renderer)
			{
				SDL_DestroyRenderer(_members->renderer);
			}
			delete _members;
			_members = nullptr;
		}

		void DriverImpl::initImpl(const DriverInitParameters& params, Window *window)
		{
			SDL_Window *sdlWindow = static_cast<WindowImpl*>(window)->getSDLWindow();
			SDL_DisplayMode currentMode;
			currentMode.h = window->getHeight();
			currentMode.w = window->getWidth();
			currentMode.driverdata = 0;
			currentMode.refresh_rate = params.sampleCount;
			currentMode.format = BufferDescUtils::getSdlPixelFormat(params.description);
			int32_t result = SDL_SetWindowDisplayMode(sdlWindow, &currentMode);

			_members->renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
			if(result != 0)
			{
				throw InitializationError("SDL Window cannot be set up because of sdl internal error.");
			}
		}

		void DriverImpl::swapBufferImpl()
		{
			SDL_Window *sdlWindow = static_cast<WindowImpl*>(getWindow())->getSDLWindow();
			SDL_GL_SwapWindow(sdlWindow);
		}

		void DriverImpl::setViewPortImpl(int32_t x, int32_t y, int32_t width, int32_t height)
		{
			SDL_Window *sdlWindow = static_cast<WindowImpl*>(getWindow())->getSDLWindow();

			SDL_Rect viewport;
			viewport.x = x;
			viewport.y = y;
			viewport.w = width;
			viewport.h = height;

			// Sets the viewport so that SDL uses it
			SDL_RenderSetViewport(_members->renderer, &viewport);
		}

	}
}
#else

#include <engine/video/sdl/empty/DriverImpl.cpp>

#endif
