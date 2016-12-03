#pragma once

namespace engine
{
	/**
	* Supported buffer fomrats
	*/
	enum class BufferFormat
	{
		Format_Unknown,
		Format_R32G32B32A32,
		Format_R32G32B32,
		Format_R16G16B16A16,
		Format_R32G32,
		Format_R32G8X24,
		Format_D32_FLOAT_X8X24,
		Format_R32_FLOAT_X8X24,
		Format_X32_TYPELESS_G8X24_UINT,
		Format_R10G10B10A2,
		Format_R11G11B10,
		Format_R8G8B8A8,
		Format_R16G16,
		Format_R32,
		Format_D32,
		Format_R24G8,
		Format_D24_S8,
		Format_R24_X8,
		Format_X24_G8,
		Format_R8G8,
		Format_R16,
		Format_D16,
		Format_R8,
		Format_A8,
		Format_R1,
		Format_R9G9B9E5,
		Format_R8G8_B8G8,
		Format_G8R8_G8B8,
		Format_BC1,
		Format_BC2,
		Format_BC3,
		Format_BC4,
		Format_BC5,
		Format_B5G6R5,
		Format_B5G5R5A1,
		Format_B8G8R8A8,
		Format_B8G8R8X8,
		Format_R10G10B10_XR_A2,
		Format_BC6H,
		Format_BC7,
		Format_AYUV,
		Format_Y410,
		Format_Y416,
		Format_NV12,
		Format_P010,
		Format_P016,
		Format_420_OPAQUE,
		Format_YUY2,
		Format_Y210,
		Format_Y216,
		Format_NV11,
		Format_AI44,
		Format_IA44,
		Format_P8,
		Format_A8P8,
		Format_B4G4R4A4,
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
		BufferFormat format = BufferFormat::Format_Unknown;
		/**Elements type in the buffer*/
		BufferType type = BufferType::Undef;
		/**True if it is an SRGB buffer*/
		bool isSRGB = false;
	};
}