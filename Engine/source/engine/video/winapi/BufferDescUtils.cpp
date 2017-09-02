#include <stdafx.h>

#include <engine/video/winapi/BufferDescUtils.h>
////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_WINAPI
#include <engine/exceptions/LogicalErrors.h>

#include <engine/video/BufferDesc.h>

#include <boost/optional/optional.hpp>

#include <d3d11.h>

namespace engine
{
	namespace winapi
	{
		DXGI_FORMAT BufferDescUtils::EncodeDesc(const BufferDesc &desc)
		{
			DXGI_FORMAT result = DXGI_FORMAT_UNKNOWN;
			if(desc.isSRGB)
			{
				result = EncodeSRGBDesc(desc);
			}
			else
			{
				result = EncodeRGBDesc(desc);
			}
			return result;
		}

		DXGI_FORMAT BufferDescUtils::EncodeRGBDesc(const BufferDesc &desc)
		{
			boost::optional<DXGI_FORMAT> result = DXGI_FORMAT_UNKNOWN;
			switch(desc.format)
			{
				case TextureFormat::_R32G32B32A32:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_R32G32B32A32_TYPELESS; break;
						case BufferType::Float:				result = DXGI_FORMAT_R32G32B32A32_FLOAT; break;
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_R32G32B32A32_UINT; break;
						case BufferType::SignedInteger:		result = DXGI_FORMAT_R32G32B32A32_SINT; break;
					}
					break;
				case TextureFormat::_R32G32B32:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_R32G32B32_TYPELESS; break;
						case BufferType::Float:				result = DXGI_FORMAT_R32G32B32_FLOAT; break;
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_R32G32B32_UINT; break;
						case BufferType::SignedInteger:		result = DXGI_FORMAT_R32G32B32_SINT; break;
					}
					break;
				case TextureFormat::_R16G16B16A16:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_R16G16B16A16_TYPELESS; break;
						case BufferType::Float:				result = DXGI_FORMAT_R16G16B16A16_FLOAT; break;
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_R16G16B16A16_UNORM; break;
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_R16G16B16A16_UINT; break;
						case BufferType::SignedNormalized:	result = DXGI_FORMAT_R16G16B16A16_SNORM; break;
						case BufferType::SignedInteger:		result = DXGI_FORMAT_R16G16B16A16_SINT; break;
					}
					break;
				case TextureFormat::_R32G32:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_R32G32_TYPELESS; break;
						case BufferType::Float:				result = DXGI_FORMAT_R32G32_FLOAT; break;
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_R32G32_UINT; break;
						case BufferType::SignedInteger:		result = DXGI_FORMAT_R32G32_SINT; break;
					}
					break;
				case TextureFormat::_R32G8X24:
					switch(desc.type)
					{
						case BufferType::SignedInteger:		result = DXGI_FORMAT_R32G8X24_TYPELESS; break;
					}
					break;
				case TextureFormat::_D32_FLOAT_S8X24:
					switch(desc.type)
					{
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_D32_FLOAT_S8X24_UINT; break;
					}
					break;
				case TextureFormat::_R32_FLOAT_X8X24:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS; break;
					}
					break;
				case TextureFormat::_X32_TYPELESS_G8X24_UINT:
					switch(desc.type)
					{
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_X32_TYPELESS_G8X24_UINT; break;
					}
					break;
				case TextureFormat::_R10G10B10A2:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_R10G10B10A2_TYPELESS; break;
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_R10G10B10A2_UNORM; break;
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_R10G10B10A2_UINT; break;
					}
					break;
				case TextureFormat::_R11G11B10:
					switch(desc.type)
					{
						case BufferType::Float:				result = DXGI_FORMAT_R11G11B10_FLOAT; break;
					}
					break;
				case TextureFormat::_R8G8B8A8:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_R8G8B8A8_TYPELESS; break;
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_R8G8B8A8_UNORM; break;
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_R8G8B8A8_UINT; break;
						case BufferType::SignedNormalized:	result = DXGI_FORMAT_R8G8B8A8_SNORM; break;
						case BufferType::SignedInteger:		result = DXGI_FORMAT_R8G8B8A8_SINT; break;
					}
					break;
				case TextureFormat::_R16G16:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_R16G16_TYPELESS; break;
						case BufferType::Float:				result = DXGI_FORMAT_R16G16_FLOAT; break;
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_R16G16_UNORM; break;
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_R16G16_UINT; break;
						case BufferType::SignedNormalized:	result = DXGI_FORMAT_R16G16_SNORM; break;
						case BufferType::SignedInteger:		result = DXGI_FORMAT_R16G16_SINT; break;
					}
					break;
				case TextureFormat::_R32:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_R32_TYPELESS; break;
						case BufferType::Float:				result = DXGI_FORMAT_R32_FLOAT; break;
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_R32_UINT; break;
						case BufferType::SignedInteger:		result = DXGI_FORMAT_R32_SINT; break;
					}
					break;
				case TextureFormat::_D32:
					switch(desc.type)
					{
						case BufferType::Float:				result = DXGI_FORMAT_D32_FLOAT; break;
					}
					break;
				case TextureFormat::_R24G8:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_R24G8_TYPELESS; break;
					}
					break;
				case TextureFormat::_D24_S8:
					switch(desc.type)
					{
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_D24_UNORM_S8_UINT; break;
					}
					break;
				case TextureFormat::_R24_X8:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_R24_UNORM_X8_TYPELESS; break;
					}
					break;
				case TextureFormat::_X24_G8:
					switch(desc.type)
					{
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_X24_TYPELESS_G8_UINT; break;
					}
					break;
				case TextureFormat::_R8G8:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_R8G8_TYPELESS; break;
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_R8G8_UNORM; break;
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_R8G8_UINT; break;
						case BufferType::SignedNormalized:	result = DXGI_FORMAT_R8G8_SNORM; break;
						case BufferType::SignedInteger:		result = DXGI_FORMAT_R8G8_SINT; break;
					}
					break;
				case TextureFormat::_R16:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_R16_TYPELESS; break;
						case BufferType::Float:				result = DXGI_FORMAT_R16_FLOAT; break;
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_R16_UNORM; break;
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_R16_UINT; break;
						case BufferType::SignedNormalized:	result = DXGI_FORMAT_R16_SNORM; break;
						case BufferType::SignedInteger:		result = DXGI_FORMAT_R16_SINT; break;
					}
					break;
				case TextureFormat::_D16:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_D16_UNORM; break;
					}
					break;
				case TextureFormat::_R8:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_R8_TYPELESS; break;
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_R8_UNORM; break;
						case BufferType::UnsignedInteger:	result = DXGI_FORMAT_R8_UINT; break;
						case BufferType::SignedNormalized:	result = DXGI_FORMAT_R8_SNORM; break;
						case BufferType::SignedInteger:		result = DXGI_FORMAT_R8_SINT; break;
					}
					break;
				case TextureFormat::_A8:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_A8_UNORM; break;
					}
					break;
				case TextureFormat::_R1:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_R1_UNORM; break;
					}
					break;
				case TextureFormat::_R9G9B9E5:
					switch(desc.type)
					{
						case BufferType::Float:				result = DXGI_FORMAT_R9G9B9E5_SHAREDEXP; break;
					}
					break;
				case TextureFormat::_R8G8_B8G8:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_R8G8_B8G8_UNORM; break;
					}
					break;
				case TextureFormat::_G8R8_G8B8:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_G8R8_G8B8_UNORM; break;
					}
					break;
				case TextureFormat::_BC1:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_BC1_TYPELESS; break;
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_BC1_UNORM; break;
					}
					break;
				case TextureFormat::_BC2:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_BC2_TYPELESS; break;
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_BC2_UNORM; break;
					}
					break;
				case TextureFormat::_BC3:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_BC3_TYPELESS; break;
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_BC3_UNORM; break;
					}
					break;
				case TextureFormat::_BC4:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_BC4_TYPELESS; break;
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_BC4_UNORM; break;
						case BufferType::SignedNormalized:	result = DXGI_FORMAT_BC4_SNORM; break;
					}

					break;
				case TextureFormat::_BC5:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_BC5_TYPELESS; break;
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_BC5_UNORM; break;
						case BufferType::SignedNormalized:	result = DXGI_FORMAT_BC5_SNORM; break;

					}
					break;
				case TextureFormat::_B5G6R5:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_B5G6R5_UNORM; break;

					}
					break;
				case TextureFormat::_B5G5R5A1:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_B5G5R5A1_UNORM; break;

					}
					break;
				case TextureFormat::_B8G8R8A8:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_B8G8R8A8_UNORM; break;
						case BufferType::Undef:				result = DXGI_FORMAT_B8G8R8A8_TYPELESS; break;

					}
					break;
				case TextureFormat::_B8G8R8X8:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_B8G8R8X8_UNORM; break;
						case BufferType::Undef:				result = DXGI_FORMAT_B8G8R8X8_TYPELESS; break;


					}
					break;
				case TextureFormat::_R10G10B10_XR_A2:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM; break;

					}
					break;
				case TextureFormat::_BC6H:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_BC6H_TYPELESS; break;
						case BufferType::Float:				result = DXGI_FORMAT_BC6H_SF16; break;
					}
					break;
				case TextureFormat::_BC7:
					switch(desc.type)
					{
						case BufferType::Undef:				result = DXGI_FORMAT_BC7_TYPELESS; break;
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_BC7_UNORM; break;
					}
					break;
				case TextureFormat::_AYUV:
					result = DXGI_FORMAT_AYUV;
					break;
				case TextureFormat::_Y410:
					result = DXGI_FORMAT_Y410;
					break;
				case TextureFormat::_Y416:
					result = DXGI_FORMAT_Y416;
					break;
				case TextureFormat::_NV12:
					result = DXGI_FORMAT_NV12;
					break;
				case TextureFormat::_P010:
					result = DXGI_FORMAT_P010;
					break;
				case TextureFormat::_P016:
					result = DXGI_FORMAT_P016;
					break;
				case TextureFormat::_420_OPAQUE:
					result = DXGI_FORMAT_420_OPAQUE;
					break;
				case TextureFormat::_YUY2:
					result = DXGI_FORMAT_YUY2;
					break;
				case TextureFormat::_Y210:
					result = DXGI_FORMAT_Y210;
					break;
				case TextureFormat::_Y216:
					result = DXGI_FORMAT_Y216;
					break;
				case TextureFormat::_NV11:
					result = DXGI_FORMAT_NV11;
					break;
				case TextureFormat::_AI44:
					result = DXGI_FORMAT_AI44;
					break;
				case TextureFormat::_IA44:
					result = DXGI_FORMAT_IA44;
					break;
				case TextureFormat::_P8:
					result = DXGI_FORMAT_P8;
					break;
				case TextureFormat::_A8P8:
					result = DXGI_FORMAT_A8P8;
					break;
				case TextureFormat::_B4G4R4A4:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_B4G4R4A4_UNORM; break;
					}
					break;
				default:
					break;
			}
			if(!result)
			{
				throw UnsupportedFeature("Given RGB format is not supported");
			}
			return result.get();
		}


		DXGI_FORMAT BufferDescUtils::EncodeSRGBDesc(const BufferDesc &desc)
		{
			boost::optional<DXGI_FORMAT> result = DXGI_FORMAT_UNKNOWN;
			switch(desc.format)
			{
				case TextureFormat::_R32G32B32A32:
				case TextureFormat::_R32G32B32:
				case TextureFormat::_R16G16B16A16:
				case TextureFormat::_R32G32:
				case TextureFormat::_R32G8X24:
				case TextureFormat::_D32_FLOAT_S8X24:
				case TextureFormat::_R32_FLOAT_X8X24:
				case TextureFormat::_X32_TYPELESS_G8X24_UINT:
				case TextureFormat::_R10G10B10A2:
				case TextureFormat::_R11G11B10:
					break;
				case TextureFormat::_R8G8B8A8:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; break;
					}
					break;
				case TextureFormat::_R16G16:
				case TextureFormat::_R32:
				case TextureFormat::_D32:
				case TextureFormat::_R24G8:
				case TextureFormat::_D24_S8:
				case TextureFormat::_R24_X8:
				case TextureFormat::_X24_G8:
				case TextureFormat::_R8G8:
				case TextureFormat::_R16:
				case TextureFormat::_D16:
				case TextureFormat::_R8:
				case TextureFormat::_A8:
				case TextureFormat::_R1:
				case TextureFormat::_R9G9B9E5:
				case TextureFormat::_R8G8_B8G8:
				case TextureFormat::_G8R8_G8B8:
					break;
				case TextureFormat::_BC1:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_BC1_UNORM_SRGB; break;
					}
					break;
				case TextureFormat::_BC2:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_BC2_UNORM_SRGB; break;
					}
					break;
				case TextureFormat::_BC3:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_BC3_UNORM_SRGB; break;
					}
					break;
				case TextureFormat::_BC4:
				case TextureFormat::_BC5:
				case TextureFormat::_B5G6R5:
				case TextureFormat::_B5G5R5A1:
					break;
				case TextureFormat::_B8G8R8A8:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB; break;
					}
					break;
				case TextureFormat::_B8G8R8X8:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_B8G8R8X8_UNORM_SRGB; break;
					}
					break;
				case TextureFormat::_R10G10B10_XR_A2:
				case TextureFormat::_BC6H:
					break;
				case TextureFormat::_BC7:
					switch(desc.type)
					{
						case BufferType::UnsignedNormalized:result = DXGI_FORMAT_BC7_UNORM_SRGB; break;
					}
					break;
				case TextureFormat::_AYUV:
				case TextureFormat::_Y410:
				case TextureFormat::_Y416:
				case TextureFormat::_NV12:
				case TextureFormat::_P010:
				case TextureFormat::_P016:
				case TextureFormat::_420_OPAQUE:
				case TextureFormat::_YUY2:
				case TextureFormat::_Y210:
				case TextureFormat::_Y216:
				case TextureFormat::_NV11:
				case TextureFormat::_AI44:
				case TextureFormat::_IA44:
				case TextureFormat::_P8:
				case TextureFormat::_A8P8:
				case TextureFormat::_B4G4R4A4:
				default:
					break;
			}
			if(!result)
			{
				throw UnsupportedFeature("given SRGB format is not supported");
			}
			return result.get();
		}
	}
}

#endif