#include <stdafx.h>

#include <engine/video/glfw/BufferDescUtils.h>
////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_GLFW
#include <engine/exceptions/LogicalErrors.h>

#include <engine/video/BufferDesc.h>

namespace engine
{
	namespace glfw
	{
		BufferDescUtils::GlfwDesc BufferDescUtils::getGlfwDesc(const BufferDesc &desc)
		{
			GlfwDesc result;
			HARD_FAIL("Unimplemented module");
			return result;
		}

		int32_t BufferDescUtils::getRedBits(const BufferDesc &desc)
		{
			HARD_FAIL("Unimplemented module");
			return 0;
		}

		int32_t BufferDescUtils::getBlueBits(const BufferDesc &desc)
		{
			HARD_FAIL("Unimplemented module");
			return 0;
		}

		int32_t BufferDescUtils::getGreenBits(const BufferDesc &desc)
		{
			HARD_FAIL("Unimplemented module");
			return 0;
		}

		int32_t BufferDescUtils::getAlphaBits(const BufferDesc &desc)
		{
			HARD_FAIL("Unimplemented module");
			return 0;
		}

		int32_t BufferDescUtils::getStencilBits(const BufferDesc &desc)
		{
			HARD_FAIL("Unimplemented module");
			return 0;
		}

		int32_t BufferDescUtils::getDepthBits(const BufferDesc &desc)
		{
			HARD_FAIL("Unimplemented module");
			return 0;
		}
	}
}
#endif