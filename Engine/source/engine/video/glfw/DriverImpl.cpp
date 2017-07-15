#include <stdafx.h>

#include <engine/video/glfw/DriverImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_GLFW
#include <engine/view/Window.h>
#include <engine/video/glfw/BufferDescUtils.h>
#include <engine/view/glfw/WindowImpl.h>

#include <GLFW/glfw3.h>

namespace engine
{
	namespace glfw
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
			BufferDescUtils::GlfwDesc desc = BufferDescUtils::getGlfwDesc(params.description);
			if(desc.redBits > 0)
			{
				glfwWindowHint(GLFW_RED_BITS, desc.redBits);
			}
			if(desc.greenBits > 0)
			{
				glfwWindowHint(GLFW_GREEN_BITS, desc.greenBits);
			}
			if(desc.blueBits > 0)
			{
				glfwWindowHint(GLFW_BLUE_BITS, desc.blueBits);
			}
			if(desc.alphaBits > 0)
			{
				glfwWindowHint(GLFW_ALPHA_BITS, desc.alphaBits);
			}
			if(desc.stencilBits > 0)
			{
				glfwWindowHint(GLFW_STENCIL_BITS, desc.stencilBits);
			}
			if(desc.depthBits > 0)
			{
				glfwWindowHint(GLFW_DEPTH_BITS, desc.depthBits);
			}

			glfwWindowHint(GLFW_REFRESH_RATE, params.sampleCount);
		}

		void DriverImpl::swapBufferImpl()
		{
			WindowImpl* window = static_cast<WindowImpl*>(getWindow());
			glfwSwapBuffers(window->getGlfwWindow());
		}
	}
}
#else

#include <engine/video/glfw/empty/DriverImpl.cpp>

#endif