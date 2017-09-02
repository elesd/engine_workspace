#include <stdafx.h>

#include <engine/video/sdl/BufferDescUtils.h>
////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_SDL

#include <engine/exceptions/LogicalErrors.h>

#include <engine/video/BufferDesc.h>

#include <boost/optional/optional.hpp>

#include <SDL2/SDL.h>

namespace engine
{
	namespace sdl
	{
		uint32_t BufferDescUtils::getSdlPixelFormat(const BufferDesc &desc)
		{
			if(desc.isSRGB)
				throw UnsupportedFeature("SDL does not support srgb pixel format");
			boost::optional<int32_t> result = 0;
			switch(desc.format)
			{
				case TextureFormat::_R32G32B32A32:				break;
				case TextureFormat::_R32G32B32:					break;
				case TextureFormat::_R16G16B16A16:				break;
				case TextureFormat::_R32G32:					break;
				case TextureFormat::_R32G8X24:					break;
				case TextureFormat::_D32_FLOAT_S8X24:			break;
				case TextureFormat::_R32_FLOAT_X8X24:			break;
				case TextureFormat::_X32_TYPELESS_G8X24_UINT:	break;
				case TextureFormat::_R10G10B10A2:				break;
				case TextureFormat::_R11G11B10:					break;
				case TextureFormat::_R8G8B8A8:					result = SDL_PIXELFORMAT_RGBA8888; break;
				case TextureFormat::_R16G16:					break;
				case TextureFormat::_R32:						break;
				case TextureFormat::_D32:						break;
				case TextureFormat::_R24G8:						break;
				case TextureFormat::_D24_S8:					break;
				case TextureFormat::_R24_X8:					break;
				case TextureFormat::_X24_G8:					break;
				case TextureFormat::_R8G8:						break;
				case TextureFormat::_R16:						break;
				case TextureFormat::_D16:						break;
				case TextureFormat::_R8:						break;
				case TextureFormat::_A8:						break;
				case TextureFormat::_R1:						break;
				case TextureFormat::_R9G9B9E5:					break;
				case TextureFormat::_R8G8_B8G8:					break;
				case TextureFormat::_G8R8_G8B8:					break;
				case TextureFormat::_BC1:						break;
				case TextureFormat::_BC2:						break;
				case TextureFormat::_BC3:						break;
				case TextureFormat::_BC4:						break;
				case TextureFormat::_BC5:						break;
				case TextureFormat::_B5G6R5:					result = SDL_PIXELFORMAT_RGB565; break;
				case TextureFormat::_B5G5R5A1:					result = SDL_PIXELFORMAT_BGRA5551; break;
				case TextureFormat::_B8G8R8A8:					result = SDL_PIXELFORMAT_BGRA8888; break;
				case TextureFormat::_B8G8R8X8:					result = SDL_PIXELFORMAT_BGRX8888; break;
				case TextureFormat::_R10G10B10_XR_A2:			break;
				case TextureFormat::_BC6H:						break;
				case TextureFormat::_BC7:						break;
				case TextureFormat::_AYUV:						break;
				case TextureFormat::_Y410:						break;
				case TextureFormat::_Y416:						break;
				case TextureFormat::_NV12:						result = SDL_PIXELFORMAT_NV12; break;
				case TextureFormat::_P010:						break;
				case TextureFormat::_P016:						break;
				case TextureFormat::_420_OPAQUE:				break;
				case TextureFormat::_YUY2:						result = SDL_PIXELFORMAT_YUY2; break;
				case TextureFormat::_Y210:						break;
				case TextureFormat::_Y216:						break;
				case TextureFormat::_NV11:						break;
				case TextureFormat::_AI44:						break;
				case TextureFormat::_IA44:						break;
				case TextureFormat::_P8:						break;
				case TextureFormat::_A8P8:						break;
				case TextureFormat::_B4G4R4A4:					result = SDL_PIXELFORMAT_BGRA4444; break;
				default:											break;
			}
			if(!result)
			{
				throw UnsupportedFeature("Unsupported pixel format");
			}
			return result.get();
		}

	}
}

#endif