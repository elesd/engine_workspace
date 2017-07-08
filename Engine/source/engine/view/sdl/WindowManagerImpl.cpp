#include <stdafx.h>
#if ENGINE_USE_SDL
#include <engine/view/sdl/WindowManagerImpl.h>
///////////////////////////////////////////////////
#include <engine/view/sdl/WindowImpl.h>

#include <engine/render/RenderContext.h>

#include <engine/video/Driver.h>
#include <engine/video/sdl/DriverImpl.h>

#include <engine/video/glew/BufferObjectFactoryImpl.h>

#include <SDL2/SDL.h>
namespace engine
{
	namespace sdl
	{
		Window *WindowManagerImpl::createMainWindowImpl(const WindowParameter &parameters,
															  const std::string &title)
		{
			SDL_Window *window = SDL_CreateWindow(title.c_str(), parameters.x, parameters.y, parameters.width, parameters.height, SDL_WindowFlags::SDL_WINDOW_OPENGL);
			std::unique_ptr<WindowImpl> result;
			if(window)
			{
				result.reset(new WindowImpl(this, std::move(window), parameters, title));
			}
			return result.release();
		}

		Window *WindowManagerImpl::createFullScreenMainWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId)
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
				result.reset(new WindowImpl(this, std::move(window), title));
			}
			return result.release();
		}

		Window *WindowManagerImpl::createSecondaryWindowImpl(const WindowParameter &parameters,
																   const std::string &title,
																   Window *mainWindow)
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

		Window *WindowManagerImpl::createSecondaryFullScreenWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, Window *mainWindow)
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

		std::unique_ptr<RenderContext> WindowManagerImpl::createRenderContext(const RenderContextParameters &params, Window *window) const
		{
			std::unique_ptr<Driver> driver(new sdl::DriverImpl());
			std::unique_ptr<glew::BufferObjectFactoryImpl> bufferObjectFactory(new glew::BufferObjectFactoryImpl(driver.get()));
			std::unique_ptr<RenderContext> context(new RenderContext(std::move(driver), std::move(bufferObjectFactory)));
			context->init(params, window);
			return context;
		}

		WindowImpl *WindowManagerImpl::findWindowBySDLId(uint32_t id) const
		{
			std::vector<Window*> allWindow = getAllWindows();
			SDL_Window *sdlWindow = SDL_GetWindowFromID(id);
			if(sdlWindow == nullptr)
			{
				return nullptr;
			}
			for(Window *window : allWindow)
			{
				WindowImpl *w = static_cast<WindowImpl*>(window);
				if(w->getSDLWindow() == sdlWindow)
					return w;
			}
			return nullptr;
		}

		void WindowManagerImpl::handleEvent(const SDL_WindowEvent& event)
		{
			WindowImpl *window = findWindowBySDLId(event.windowID);
			if(window)
			{
				window->handleEvent(event);
			}
		}
	}
}
#else 

#include <engine/view/sdl/empty/WindowManagerImpl.cpp>

#endif
