#include <stdafx.h>

#include <engine/video/sdl/DriverImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_SDL
#include <engine/exceptions/LogicalErrors.h>

#include <engine/view/Window.h>
#include <engine/view/sdl/WindowImpl.h>
#include <engine/video/sdl/BufferDescUtils.h>

#include <SDL2/SDL.h>

namespace engine
{
	namespace sdl
	{
		struct DriverImplPrivate
		{
		};

		DriverImpl::DriverImpl() 
		{
			
		}
		DriverImpl::~DriverImpl()
		{
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
			if(result != 0)
			{
				throw InitializationError("SDL Window cannot be set up because of sdl internal error.");
			}
		}
	}
}
#endif
