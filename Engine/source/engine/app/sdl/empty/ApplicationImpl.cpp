#include <stdafx.h>
#include <engine/app/sdl/ApplicationImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_SDL
#include <engine/app/IMain.h>
#include <engine/app/IApplicationParameter.h>

#include <engine/events/sdl/EventManagerImpl.h>

#include <engine/view/sdl/WindowManagerImpl.h>
#include <engine/view/sdl/WindowImpl.h>


namespace engine
{
	namespace sdl
	{ 
		ApplicationImpl::ApplicationImpl(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main)
			:Application(std::move(arguments), std::move(main))
		{
			HARD_FAIL("Inactive module");
		}

		void ApplicationImpl::updateImpl()
		{
			HARD_FAIL("Inactive module");
		}
	}
}

#endif
