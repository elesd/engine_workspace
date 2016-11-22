#include "stdafx.h"
#if ENGINE_USE_SDL
#include "engine/modules/sdl/WindowManagerImpl.h"
///////////////////////////////////////////////////
#include "engine/modules/sdl/WindowImpl.h"

#include "SDL2/SDL.h"

#include "engine/video/Driver.h"

namespace engine
{
	namespace view
	{
		namespace sdl
		{
			view::Window *WindowManagerImpl::createMainWindowImpl(const view::WindowParameter &parameters,
																  const std::string &title)
			{
				SDL_Window *window = SDL_CreateWindow(title.c_str(), parameters.x, parameters.y, parameters.width, parameters.height, SDL_WindowFlags::SDL_WINDOW_OPENGL);
				std::unique_ptr<WindowImpl> result;
				if(window)
				{
					result.reset(new WindowImpl(std::move(window), parameters, title));
				}
				return result.release();
			}

			view::Window *WindowManagerImpl::createFullScreenMainWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId)
			{
				ASSERT(monitorId < getMonitorCount());
				SDL_Rect rect;
				SDL_GetDisplayBounds(monitorId, &rect);
				SDL_Window *window = SDL_CreateWindow(title.c_str(), rect.x, rect.y, rect.w, rect.h, SDL_WindowFlags::SDL_WINDOW_OPENGL);
				std::unique_ptr<WindowImpl> result;
				if(window)
				{
					SDL_GLContext context = SDL_GL_CreateContext(window);
					SDL_GL_MakeCurrent(window, context);
					result.reset(new WindowImpl(std::move(window), title));
				}
				return result.release();
			}

			view::Window *WindowManagerImpl::createSecondaryWindowImpl(const view::WindowParameter &parameters,
																	   const std::string &title,
																	   view::Window *mainWindow)
			{
				SDL_Window *window = SDL_CreateWindow(title.c_str(), parameters.x, parameters.y, parameters.width, parameters.height, SDL_WindowFlags::SDL_WINDOW_OPENGL);
				std::unique_ptr<WindowImpl> result;
				if(window)
				{
					WindowImpl *sdlMainWindow = static_cast<WindowImpl*>(mainWindow);
					SDL_GLContext context = SDL_GL_CreateContext(sdlMainWindow->getSDLWindow());
					SDL_GL_MakeCurrent(window, context);
				}
				return result.release();
			}

			view::Window *WindowManagerImpl::createSecondaryFullScreenWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, view::Window *mainWindow)
			{
				ASSERT(monitorId < getMonitorCount());
				SDL_Rect rect;
				SDL_GetDisplayBounds(monitorId, &rect);
				SDL_Window *window = SDL_CreateWindow(title.c_str(), rect.x, rect.y, width, height, SDL_WindowFlags::SDL_WINDOW_OPENGL);
				std::unique_ptr<WindowImpl> result;
				if(window)
				{
					WindowImpl *sdlMainWindow = static_cast<WindowImpl*>(mainWindow);
					SDL_GLContext context = SDL_GL_CreateContext(sdlMainWindow->getSDLWindow());
					SDL_GL_MakeCurrent(window, context);
				}
				return result.release();
			}

			uint32_t WindowManagerImpl::getMonitorCount() const
			{
				int count = 0;
				count = SDL_GetNumVideoDisplays();
				return count;
			}

			uint32_t WindowManagerImpl::getMainMonitorId() const
			{
				ASSERT(getMonitorCount() > 0);
				return 0;
			}

			std::unique_ptr<video::Driver> WindowManagerImpl::createDriverForWindow(const video::DriverInitParameters &params, Window *) const 
			{
				HARD_FAIL("Not implemented");
				return nullptr;
			}
		}
	}
}
#endif