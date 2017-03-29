#include <stdafx.h>

#include <engine/video/sdl/BufferDescUtils.h>
////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_SDL

#include <engine/exceptions/LogicalErrors.h>

#include <engine/video/BufferDesc.h>

namespace engine
{
	namespace sdl
	{
		uint32_t BufferDescUtils::getSdlPixelFormat(const BufferDesc &desc)
		{
			HARD_FAIL("Unimplemented module");
			return 0;
		}

	}
}
#endif