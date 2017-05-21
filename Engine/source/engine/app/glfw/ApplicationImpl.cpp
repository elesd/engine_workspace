#include <stdafx.h>
#include <engine/app/glfw/ApplicationImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_GLFW

#include <engine/app/IMain.h>
#include <engine/app/IApplicationParameter.h>

#include <GLFW/glfw3.h>

namespace engine
{
	namespace glfw
	{
		ApplicationImpl::ApplicationImpl(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main)
			:Application(std::move(arguments), std::move(main))
		{
		}

		void ApplicationImpl::updateImpl()
		{
			glfwPollEvents();
		}
	}
}
#else 

#include <engine/app/glfw/empty/ApplicationImpl.cpp>

#endif
