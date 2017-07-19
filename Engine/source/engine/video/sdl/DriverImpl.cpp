#include <stdafx.h>

#include <engine/video/sdl/DriverImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_SDL
#include <engine/Context.h>

#include <engine/exceptions/LogicalErrors.h>

#include <engine/view/Window.h>
#include <engine/view/Console.h>
#include <engine/view/sdl/WindowImpl.h>
#include <engine/video/sdl/BufferDescUtils.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace
{
	SDL_GLprofile getProfile(engine::DriverVersion version)
	{
		switch(version)
		{
			case engine::DriverVersion::OpenGL_Core_3_2:
			case engine::DriverVersion::OpenGL_Core_3_3:
			case engine::DriverVersion::OpenGL_Core_4_0:
			case engine::DriverVersion::OpenGL_Core_4_1:
			case engine::DriverVersion::OpenGL_Core_4_2:
			case engine::DriverVersion::OpenGL_Core_4_3:
			return SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_CORE;
			break;
			case engine::DriverVersion::OpenGL_ES_2_0:
			case engine::DriverVersion::OpenGL_ES_3_0:
			return SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_ES;
			break;
			case engine::DriverVersion::DirectX11:
			default:
			FAIL("Unknown opengl version.");
			break;
		}
		return SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_CORE;
	}
}

namespace engine
{
	namespace sdl
	{
		struct DriverImplPrivate
		{
		};

		DriverImpl::DriverImpl() 
			: _members(new DriverImplPrivate())
		{
			
		}
		DriverImpl::~DriverImpl()
		{
			delete _members;
			_members = nullptr;
		}

		void DriverImpl::initDeviceImpl(const DeviceParameters& params)
		{
			std::pair<int32_t, int32_t> version = getOpenglMajorMinorVersion(params.version);
			SDL_GLprofile profile = getProfile(params.version);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, profile);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, version.first);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, version.second);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		}

		void DriverImpl::initImpl(const DriverInitParameters& params)
		{
			Window* window = getWindow();
			SDL_Window *sdlWindow = static_cast<WindowImpl*>(getWindow())->getSDLWindow();
			SDL_DisplayMode currentMode;
			currentMode.h = window->getHeight();
			currentMode.w = window->getWidth();
			currentMode.driverdata = 0;
			currentMode.refresh_rate = params.sampleCount;
			currentMode.format = BufferDescUtils::getSdlPixelFormat(params.description);
			int32_t result = SDL_SetWindowDisplayMode(sdlWindow, &currentMode);

			setViewPort(0, 0, window->getWidth(), window->getHeight());
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

	}
}
#else

#include <engine/video/sdl/empty/DriverImpl.cpp>

#endif
