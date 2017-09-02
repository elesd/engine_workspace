#include <stdafx.h>

#include <engine/video/glfw/BufferDescUtils.h>
////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_GLFW
#include <engine/exceptions/LogicalErrors.h>

#include <engine/video/BufferDesc.h>

#include <boost/optional/optional.hpp>

namespace
{
	enum class BufferTypes
	{
		None = 0,
		Blue = 1,
		Green = 1 << 1,
		Red = 1 << 2,
		Alpha = 1 << 3,
		Depth = 1 << 4,
		Stencil = 1 << 5
	};

	BufferTypes operator|(BufferTypes a, BufferTypes b)
	{
		return BufferTypes(int32_t(a) | int32_t(b));
	}

	BufferTypes operator&(BufferTypes a, BufferTypes b)
	{
		return BufferTypes(int32_t(a) & int32_t(b));
	}

	bool isTypeSet(BufferTypes a, BufferTypes b)
	{
		return (int32_t(a) & int32_t(b)) > 0;
	}

	BufferTypes getFormatType(const engine::BufferDesc &desc)
	{
		using engine::TextureFormat;
		BufferTypes result = BufferTypes::None;
		switch(desc.format)
		{
			case TextureFormat::_R32G32B32A32:				result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue | BufferTypes::Alpha; break;
			case TextureFormat::_R32G32B32:					result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue; break;
			case TextureFormat::_R16G16B16A16:				result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue | BufferTypes::Alpha; break;
			case TextureFormat::_R32G32:					result = BufferTypes::Red | BufferTypes::Green; break;
			case TextureFormat::_R32G8X24:					result = BufferTypes::Red | BufferTypes::Green; break;
			case TextureFormat::_D32_FLOAT_S8X24:			result = BufferTypes::Depth | BufferTypes::Stencil; break;
			case TextureFormat::_R32_FLOAT_X8X24:			result = BufferTypes::Red; break;
			case TextureFormat::_X32_TYPELESS_G8X24_UINT:	result = BufferTypes::Green; break;
			case TextureFormat::_R10G10B10A2:				result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue | BufferTypes::Alpha; break;
			case TextureFormat::_R11G11B10:					result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue; break;
			case TextureFormat::_R8G8B8A8:					result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue | BufferTypes::Alpha; break;
			case TextureFormat::_R16G16:					result = BufferTypes::Red | BufferTypes::Green; break;
			case TextureFormat::_R32:						result = BufferTypes::Red; break;
			case TextureFormat::_D32:						result = BufferTypes::Depth; break;
			case TextureFormat::_R24G8:						result = BufferTypes::Red | BufferTypes::Green; break;
			case TextureFormat::_D24_S8:					result = BufferTypes::Depth | BufferTypes::Stencil; break;
			case TextureFormat::_R24_X8:					result = BufferTypes::Red; break;
			case TextureFormat::_X24_G8:					result = BufferTypes::Green; break;
			case TextureFormat::_R8G8:						result = BufferTypes::Red | BufferTypes::Green; break;
			case TextureFormat::_R16:						result = BufferTypes::Red; break;
			case TextureFormat::_D16:						result = BufferTypes::Depth; break;
			case TextureFormat::_R8:						result = BufferTypes::Red; break;
			case TextureFormat::_A8:						result = BufferTypes::Alpha; break;
			case TextureFormat::_R1:						result = BufferTypes::Red; break;
			case TextureFormat::_R9G9B9E5:					result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue; break;
			case TextureFormat::_R8G8_B8G8:					result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue; break;
			case TextureFormat::_G8R8_G8B8:					result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue; break;
			case TextureFormat::_BC1:						break;
			case TextureFormat::_BC2:						break;
			case TextureFormat::_BC3:						break;
			case TextureFormat::_BC4:						break;
			case TextureFormat::_BC5:						break;
			case TextureFormat::_B5G6R5:					result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue; break;
			case TextureFormat::_B5G5R5A1:					result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue | BufferTypes::Alpha; break;
			case TextureFormat::_B8G8R8A8:					result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue | BufferTypes::Alpha; break;
			case TextureFormat::_B8G8R8X8:					result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue; break;
			case TextureFormat::_R10G10B10_XR_A2:			result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue | BufferTypes::Alpha; break;
			case TextureFormat::_BC6H:						break;
			case TextureFormat::_BC7:						break;
			case TextureFormat::_AYUV:						break;
			case TextureFormat::_Y410:						break;
			case TextureFormat::_Y416:						break;
			case TextureFormat::_NV12:						break;
			case TextureFormat::_P010:						break;
			case TextureFormat::_P016:						break;
			case TextureFormat::_420_OPAQUE:				break;
			case TextureFormat::_YUY2:						break;
			case TextureFormat::_Y210:						break;
			case TextureFormat::_Y216:						break;
			case TextureFormat::_NV11:						break;
			case TextureFormat::_AI44:						break;
			case TextureFormat::_IA44:						break;
			case TextureFormat::_P8:						break;
			case TextureFormat::_A8P8:						break;
			case TextureFormat::_B4G4R4A4:					result = BufferTypes::Red | BufferTypes::Green | BufferTypes::Blue | BufferTypes::Alpha; break;
			default:											break;
		}
		return result;
	}
}

namespace engine
{
	namespace glfw
	{
		BufferDescUtils::GlfwDesc BufferDescUtils::getGlfwDesc(const BufferDesc &desc)
		{
			GlfwDesc result;
			BufferTypes bufferTypes = getFormatType(desc);
			if(bufferTypes == BufferTypes::None)
				throw UnsupportedFeature("Unsupported texture format");

			if(isTypeSet(bufferTypes, BufferTypes::Blue))
			{
				result.blueBits = getBlueBits(desc);
			}
			if(isTypeSet(bufferTypes, BufferTypes::Depth))
			{
				result.depthBits = getDepthBits(desc);
			}
			if(isTypeSet(bufferTypes, BufferTypes::Green))
			{
				result.greenBits = getGreenBits(desc);
			}
			if(isTypeSet(bufferTypes, BufferTypes::Alpha))
			{
				result.alphaBits = getAlphaBits(desc);
			}
			if(isTypeSet(bufferTypes, BufferTypes::Red))
			{
				result.redBits = getRedBits(desc);
			}
			if(isTypeSet(bufferTypes, BufferTypes::Stencil))
			{
				result.stencilBits = getStencilBits(desc);
			}
			result.useSrgb = desc.isSRGB;
			return result;
		}

		int32_t BufferDescUtils::getRedBits(const BufferDesc &desc)
		{
			boost::optional<int32_t> result = 0;
			switch(desc.format)
			{
				case TextureFormat::_R32G32B32A32:				result = 32; break;
				case TextureFormat::_R32G32B32:					result = 32; break;
				case TextureFormat::_R16G16B16A16:				result = 16; break;
				case TextureFormat::_R32G32:					result = 32; break;
				case TextureFormat::_R32G8X24:					result = 32; break;
				case TextureFormat::_D32_FLOAT_S8X24:			break;
				case TextureFormat::_R32_FLOAT_X8X24:			result = 32; break;
				case TextureFormat::_X32_TYPELESS_G8X24_UINT:	break;
				case TextureFormat::_R10G10B10A2:				result = 10; break;
				case TextureFormat::_R11G11B10:					result = 11; break;
				case TextureFormat::_R8G8B8A8:					result = 8; break;
				case TextureFormat::_R16G16:					result = 16; break;
				case TextureFormat::_R32:						result = 32; break;
				case TextureFormat::_D32:						break;
				case TextureFormat::_R24G8:						result = 24; break;
				case TextureFormat::_D24_S8:					break;
				case TextureFormat::_R24_X8:					result = 24; break;
				case TextureFormat::_X24_G8:					break;
				case TextureFormat::_R8G8:						result = 8; break;
				case TextureFormat::_R16:						result = 16; break;
				case TextureFormat::_D16:						break;
				case TextureFormat::_R8:						result = 8; break;
				case TextureFormat::_A8:						break;
				case TextureFormat::_R1:						result = 1; break;
				case TextureFormat::_R9G9B9E5:					result = 9; break;
				case TextureFormat::_R8G8_B8G8:					break;
				case TextureFormat::_G8R8_G8B8:					break;
				case TextureFormat::_BC1:						break;
				case TextureFormat::_BC2:						break;
				case TextureFormat::_BC3:						break;
				case TextureFormat::_BC4:						break;
				case TextureFormat::_BC5:						break;
				case TextureFormat::_B5G6R5:					result = 5; break;
				case TextureFormat::_B5G5R5A1:					result = 5; break;
				case TextureFormat::_B8G8R8A8:					result = 8; break;
				case TextureFormat::_B8G8R8X8:					result = 8; break;
				case TextureFormat::_R10G10B10_XR_A2:			result = 10; break;
				case TextureFormat::_BC6H:						break;
				case TextureFormat::_BC7:						break;
				case TextureFormat::_AYUV:						break;
				case TextureFormat::_Y410:						break;
				case TextureFormat::_Y416:						break;
				case TextureFormat::_NV12:						break;
				case TextureFormat::_P010:						break;
				case TextureFormat::_P016:						break;
				case TextureFormat::_420_OPAQUE:				break;
				case TextureFormat::_YUY2:						break;
				case TextureFormat::_Y210:						break;
				case TextureFormat::_Y216:						break;
				case TextureFormat::_NV11:						break;
				case TextureFormat::_AI44:						break;
				case TextureFormat::_IA44:						break;
				case TextureFormat::_P8:						break;
				case TextureFormat::_A8P8:						break;
				case TextureFormat::_B4G4R4A4:					result = 4; break;
				default:											break;
			}
			if(!result)
			{
				throw UnsupportedFeature("Red bit format is not supported");
			}
			return result.get();
		}

		int32_t BufferDescUtils::getBlueBits(const BufferDesc &desc)
		{
			boost::optional<int32_t> result = 0;
			switch(desc.format)
			{
				case TextureFormat::_R32G32B32A32:				result = 32; break;
				case TextureFormat::_R32G32B32:					result = 32; break;
				case TextureFormat::_R16G16B16A16:				result = 16; break;
				case TextureFormat::_R32G32:					break;
				case TextureFormat::_R32G8X24:					break;
				case TextureFormat::_D32_FLOAT_S8X24:			break;
				case TextureFormat::_R32_FLOAT_X8X24:			break;
				case TextureFormat::_X32_TYPELESS_G8X24_UINT:	break;
				case TextureFormat::_R10G10B10A2:				result = 10; break;
				case TextureFormat::_R11G11B10:					result = 1; break;
				case TextureFormat::_R8G8B8A8:					result = 8; break;
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
				case TextureFormat::_B5G6R5:					result = 5; break;
				case TextureFormat::_B5G5R5A1:					result = 5; break;
				case TextureFormat::_B8G8R8A8:					result = 8; break;
				case TextureFormat::_B8G8R8X8:					result = 8; break;
				case TextureFormat::_R10G10B10_XR_A2:			result = 10; break;
				case TextureFormat::_BC6H:						break;
				case TextureFormat::_BC7:						break;
				case TextureFormat::_AYUV:						break;
				case TextureFormat::_Y410:						break;
				case TextureFormat::_Y416:						break;
				case TextureFormat::_NV12:						break;
				case TextureFormat::_P010:						break;
				case TextureFormat::_P016:						break;
				case TextureFormat::_420_OPAQUE:				break;
				case TextureFormat::_YUY2:						break;
				case TextureFormat::_Y210:						break;
				case TextureFormat::_Y216:						break;
				case TextureFormat::_NV11:						break;
				case TextureFormat::_AI44:						break;
				case TextureFormat::_IA44:						break;
				case TextureFormat::_P8:						break;
				case TextureFormat::_A8P8:						break;
				case TextureFormat::_B4G4R4A4:					result = 4; break;
				default:											break;
			}
			if(!result)
			{
				throw UnsupportedFeature("Blue bit format is not supported");
			}
			return result.get();
		}

		int32_t BufferDescUtils::getGreenBits(const BufferDesc &desc)
		{
			boost::optional<int32_t> result = 0;
			switch(desc.format)
			{
				case TextureFormat::_R32G32B32A32:				result = 32; break;
				case TextureFormat::_R32G32B32:					result = 32; break;
				case TextureFormat::_R16G16B16A16:				result = 16; break;
				case TextureFormat::_R32G32:					result = 32; break;
				case TextureFormat::_R32G8X24:					result = 8; break;
				case TextureFormat::_D32_FLOAT_S8X24:			break;
				case TextureFormat::_R32_FLOAT_X8X24:			break;
				case TextureFormat::_X32_TYPELESS_G8X24_UINT:	result = 8; break;
				case TextureFormat::_R10G10B10A2:				result = 10; break;
				case TextureFormat::_R11G11B10:					result = 11; break;
				case TextureFormat::_R8G8B8A8:					result = 8; break;
				case TextureFormat::_R16G16:					result = 16; break;
				case TextureFormat::_R32:						break;
				case TextureFormat::_D32:						break;
				case TextureFormat::_R24G8:						result = 8; break;
				case TextureFormat::_D24_S8:					break;
				case TextureFormat::_R24_X8:					break;
				case TextureFormat::_X24_G8:					break;
				case TextureFormat::_R8G8:						result = 8; break;
				case TextureFormat::_R16:						break;
				case TextureFormat::_D16:						break;
				case TextureFormat::_R8:						break;
				case TextureFormat::_A8:						break;
				case TextureFormat::_R1:						break;
				case TextureFormat::_R9G9B9E5:					result = 9; break;
				case TextureFormat::_R8G8_B8G8:					result = 8; break;
				case TextureFormat::_G8R8_G8B8:					result = 8; break;
				case TextureFormat::_BC1:						break;
				case TextureFormat::_BC2:						break;
				case TextureFormat::_BC3:						break;
				case TextureFormat::_BC4:						break;
				case TextureFormat::_BC5:						break;
				case TextureFormat::_B5G6R5:					result = 5; break;
				case TextureFormat::_B5G5R5A1:					result = 5; break;
				case TextureFormat::_B8G8R8A8:					result = 8; break;
				case TextureFormat::_B8G8R8X8:					result = 8; break;
				case TextureFormat::_R10G10B10_XR_A2:			result = 10; break;
				case TextureFormat::_BC6H:						break;
				case TextureFormat::_BC7:						break;
				case TextureFormat::_AYUV:						break;
				case TextureFormat::_Y410:						break;
				case TextureFormat::_Y416:						break;
				case TextureFormat::_NV12:						break;
				case TextureFormat::_P010:						break;
				case TextureFormat::_P016:						break;
				case TextureFormat::_420_OPAQUE:				break;
				case TextureFormat::_YUY2:						break;
				case TextureFormat::_Y210:						break;
				case TextureFormat::_Y216:						break;
				case TextureFormat::_NV11:						break;
				case TextureFormat::_AI44:						break;
				case TextureFormat::_IA44:						break;
				case TextureFormat::_P8:						break;
				case TextureFormat::_A8P8:						break;
				case TextureFormat::_B4G4R4A4:					result = 4; break;
				default:											break;
			}
			if(!result)
			{
				throw UnsupportedFeature("Green bit format is not supported");
			}
			return result.get();
		}

		int32_t BufferDescUtils::getAlphaBits(const BufferDesc &desc)
		{
			boost::optional<int32_t> result = 0;
			switch(desc.format)
			{
				case TextureFormat::_R32G32B32A32:				result = 32; break;
				case TextureFormat::_R32G32B32:					break;
				case TextureFormat::_R16G16B16A16:				result = 16; break;
				case TextureFormat::_R32G32:					break;
				case TextureFormat::_R32G8X24:					break;
				case TextureFormat::_D32_FLOAT_S8X24:			break;
				case TextureFormat::_R32_FLOAT_X8X24:			break;
				case TextureFormat::_X32_TYPELESS_G8X24_UINT:	break;
				case TextureFormat::_R10G10B10A2:				result = 2; break;
				case TextureFormat::_R11G11B10:					break;
				case TextureFormat::_R8G8B8A8:					result = 8; break;
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
				case TextureFormat::_A8:						result = 8; break;
				case TextureFormat::_R1:						break;
				case TextureFormat::_R9G9B9E5:					break;
				case TextureFormat::_R8G8_B8G8:					break;
				case TextureFormat::_G8R8_G8B8:					break;
				case TextureFormat::_BC1:						break;
				case TextureFormat::_BC2:						break;
				case TextureFormat::_BC3:						break;
				case TextureFormat::_BC4:						break;
				case TextureFormat::_BC5:						break;
				case TextureFormat::_B5G6R5:					break;
				case TextureFormat::_B5G5R5A1:					result = 1; break;
				case TextureFormat::_B8G8R8A8:					result = 8; break;
				case TextureFormat::_B8G8R8X8:					break;
				case TextureFormat::_R10G10B10_XR_A2:			result = 2; break;
				case TextureFormat::_BC6H:						break;
				case TextureFormat::_BC7:						break;
				case TextureFormat::_AYUV:						break;
				case TextureFormat::_Y410:						break;
				case TextureFormat::_Y416:						break;
				case TextureFormat::_NV12:						break;
				case TextureFormat::_P010:						break;
				case TextureFormat::_P016:						break;
				case TextureFormat::_420_OPAQUE:				break;
				case TextureFormat::_YUY2:						break;
				case TextureFormat::_Y210:						break;
				case TextureFormat::_Y216:						break;
				case TextureFormat::_NV11:						break;
				case TextureFormat::_AI44:						break;
				case TextureFormat::_IA44:						break;
				case TextureFormat::_P8:						break;
				case TextureFormat::_A8P8:						result = 8; break;
				case TextureFormat::_B4G4R4A4:					break;
				default:											break;
			}
			if(!result)
			{
				throw UnsupportedFeature("Alpha bit format is not supported");
			}
			return result.get();
		}

		int32_t BufferDescUtils::getStencilBits(const BufferDesc &desc)
		{
			boost::optional<int32_t> result = 0;
			switch(desc.format)
			{
				case TextureFormat::_R32G32B32A32:				break;
				case TextureFormat::_R32G32B32:					break;
				case TextureFormat::_R16G16B16A16:				break;
				case TextureFormat::_R32G32:					break;
				case TextureFormat::_R32G8X24:					break;
				case TextureFormat::_D32_FLOAT_S8X24:			result = 8; break;
				case TextureFormat::_R32_FLOAT_X8X24:			break;
				case TextureFormat::_X32_TYPELESS_G8X24_UINT:	break;
				case TextureFormat::_R10G10B10A2:				break;
				case TextureFormat::_R11G11B10:					break;
				case TextureFormat::_R8G8B8A8:					break;
				case TextureFormat::_R16G16:					break;
				case TextureFormat::_R32:						break;
				case TextureFormat::_D32:						break;
				case TextureFormat::_R24G8:						break;
				case TextureFormat::_D24_S8:					result = 8; break;
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
				case TextureFormat::_B5G6R5:					break;
				case TextureFormat::_B5G5R5A1:					break;
				case TextureFormat::_B8G8R8A8:					break;
				case TextureFormat::_B8G8R8X8:					break;
				case TextureFormat::_R10G10B10_XR_A2:			break;
				case TextureFormat::_BC6H:						break;
				case TextureFormat::_BC7:						break;
				case TextureFormat::_AYUV:						break;
				case TextureFormat::_Y410:						break;
				case TextureFormat::_Y416:						break;
				case TextureFormat::_NV12:						break;
				case TextureFormat::_P010:						break;
				case TextureFormat::_P016:						break;
				case TextureFormat::_420_OPAQUE:				break;
				case TextureFormat::_YUY2:						break;
				case TextureFormat::_Y210:						break;
				case TextureFormat::_Y216:						break;
				case TextureFormat::_NV11:						break;
				case TextureFormat::_AI44:						break;
				case TextureFormat::_IA44:						break;
				case TextureFormat::_P8:						break;
				case TextureFormat::_A8P8:						break;
				case TextureFormat::_B4G4R4A4:					break;
				default:											break;
			}
			if(!result)
			{
				throw UnsupportedFeature("Stencil bit format is not supported");
			}
			return result.get();
		}

		int32_t BufferDescUtils::getDepthBits(const BufferDesc &desc)
		{
			boost::optional<int32_t> result = 0;
			switch(desc.format)
			{
				case TextureFormat::_R32G32B32A32:				break;
				case TextureFormat::_R32G32B32:					break;
				case TextureFormat::_R16G16B16A16:				break;
				case TextureFormat::_R32G32:					break;
				case TextureFormat::_R32G8X24:					break;
				case TextureFormat::_D32_FLOAT_S8X24:			result = 32; break;
				case TextureFormat::_R32_FLOAT_X8X24:			break;
				case TextureFormat::_X32_TYPELESS_G8X24_UINT:	break;
				case TextureFormat::_R10G10B10A2:				break;
				case TextureFormat::_R11G11B10:					break;
				case TextureFormat::_R8G8B8A8:					break;
				case TextureFormat::_R16G16:					break;
				case TextureFormat::_R32:						break;
				case TextureFormat::_D32:						result = 32; break;
				case TextureFormat::_R24G8:						break;
				case TextureFormat::_D24_S8:					result = 24; break;
				case TextureFormat::_R24_X8:					break;
				case TextureFormat::_X24_G8:					break;
				case TextureFormat::_R8G8:						break;
				case TextureFormat::_R16:						break;
				case TextureFormat::_D16:						result = 16; break;
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
				case TextureFormat::_B5G6R5:					break;
				case TextureFormat::_B5G5R5A1:					break;
				case TextureFormat::_B8G8R8A8:					break;
				case TextureFormat::_B8G8R8X8:					break;
				case TextureFormat::_R10G10B10_XR_A2:			break;
				case TextureFormat::_BC6H:						break;
				case TextureFormat::_BC7:						break;
				case TextureFormat::_AYUV:						break;
				case TextureFormat::_Y410:						break;
				case TextureFormat::_Y416:						break;
				case TextureFormat::_NV12:						break;
				case TextureFormat::_P010:						break;
				case TextureFormat::_P016:						break;
				case TextureFormat::_420_OPAQUE:				break;
				case TextureFormat::_YUY2:						break;
				case TextureFormat::_Y210:						break;
				case TextureFormat::_Y216:						break;
				case TextureFormat::_NV11:						break;
				case TextureFormat::_AI44:						break;
				case TextureFormat::_IA44:						break;
				case TextureFormat::_P8:						break;
				case TextureFormat::_A8P8:						break;
				case TextureFormat::_B4G4R4A4:					break;
				default:											break;
			}
			if(!result)
			{
				throw UnsupportedFeature("Depth bit format is not supported");
			}
			return result.get();
		}
	}
}

#endif
