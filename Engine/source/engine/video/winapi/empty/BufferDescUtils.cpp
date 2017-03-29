#include <stdafx.h>

#include <engine/video/winapi/BufferDescUtils.h>
////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_WINAPI

#include <engine/exceptions/LogicalErrors.h>

#include <engine/video/BufferDesc.h>

namespace engine
{
	namespace winapi
	{
		DXGI_FORMAT BufferDescUtils::EncodeDesc(const BufferDesc &desc)
		{
			HARD_FAIL("Unimplemented module");
			return DXGI_FORMAT();
		}

		DXGI_FORMAT BufferDescUtils::EncodeRGBDesc(const BufferDesc &desc)
		{
			HARD_FAIL("Unimplemented module");
			return DXGI_FORMAT();
		}


		DXGI_FORMAT BufferDescUtils::EncodeSRGBDesc(const BufferDesc &desc)
		{
			HARD_FAIL("Unimplemented module");
			return DXGI_FORMAT();
		}
	}
}
#endif