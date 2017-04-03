#pragma once

namespace engine
{
	/**
	* Supported buffer fomrats
	*/
	enum class TextureFormat
	{
		_Unknown,
		_R32G32B32A32,
		_R32G32B32,
		_R16G16B16A16,
		_R32G32,
		_R32G8X24,
		_D32_FLOAT_S8X24,
		_R32_FLOAT_X8X24,
		_X32_TYPELESS_G8X24_UINT,
		_R10G10B10A2,
		_R11G11B10,
		_R8G8B8A8,
		_R16G16,
		_R32,
		_D32,
		_R24G8,
		_D24_S8,
		_R24_X8,
		_X24_G8,
		_R8G8,
		_R16,
		_D16,
		_R8,
		_A8,
		_R1,
		_R9G9B9E5,
		_R8G8_B8G8,
		_G8R8_G8B8,
		_BC1,
		_BC2,
		_BC3,
		_BC4,
		_BC5,
		_B5G6R5,
		_B5G5R5A1,
		_B8G8R8A8,
		_B8G8R8X8,
		_R10G10B10_XR_A2,
		_BC6H,
		_BC7,
		_AYUV,
		_Y410,
		_Y416,
		_NV12,
		_P010,
		_P016,
		_420_OPAQUE,
		_YUY2,
		_Y210,
		_Y216,
		_NV11,
		_AI44,
		_IA44,
		_P8,
		_A8P8,
		_B4G4R4A4,
		Num
	};

	/**Supported buffer types*/
	enum class BufferType
	{
		SignedInteger,
		UnsignedInteger,
		SignedNormalized,
		UnsignedNormalized,
		Float,
		Undef,
		Num
	};

	/** Buffer descriptor*/
	struct BufferDesc
	{
		/**Format of the buffer*/
		TextureFormat format = TextureFormat::_Unknown;
		/**Elements type in the buffer*/
		BufferType type = BufferType::Undef;
		/**True if it is an SRGB buffer*/
		bool isSRGB = false;
	};
}