#include <stdafx.h>

#include <engine/video/glfw/DriverImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_GLFW
#include <engine/view/Window.h>
#include <engine/video/glfw/BufferDescUtils.h>
#include <engine/view/glfw/WindowImpl.h>

#include <GLFW/glfw3.h>

namespace
{
	bool isESProfile(engine::DriverVersion version)
	{
		switch(version)
		{
			case engine::DriverVersion::OpenGL_Core_3_2:
			case engine::DriverVersion::OpenGL_Core_3_3:
			case engine::DriverVersion::OpenGL_Core_4_0:
			case engine::DriverVersion::OpenGL_Core_4_1:
			case engine::DriverVersion::OpenGL_Core_4_2:
			case engine::DriverVersion::OpenGL_Core_4_3:
			case engine::DriverVersion::OpenGL_Core_4_4:
			case engine::DriverVersion::OpenGL_Core_4_5:
			return false;
			break;
			case engine::DriverVersion::OpenGL_ES_2_0:
			case engine::DriverVersion::OpenGL_ES_3_0:
			return true;
			break;
			case engine::DriverVersion::DirectX11:
			default:
			FAIL("Not opengl driver is used");
			break;
		}
		return false;
	}



}

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

		void DriverImpl::initDeviceImpl(const DeviceParameters& params)
		{
			std::pair<int32_t, int32_t> version = getOpenglMajorMinorVersion(params.version);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version.first);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version.second);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			if(isESProfile(params.version))
			{
				glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
			}
			else
			{
				glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			}
		}

		void DriverImpl::initImpl(const DriverInitParameters& params)
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