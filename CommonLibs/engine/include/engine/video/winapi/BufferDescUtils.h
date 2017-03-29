#pragma once

enum DXGI_FORMAT;

namespace engine
{
	struct BufferDesc;
	namespace winapi
	{

		/**Utility class for buffer conversion for DirectX*/
		struct BufferDescUtils
		{
			/**
			* @param desc: Engine description format
			* @return Returns the corresponding directx format if it exists
			*/
			static DXGI_FORMAT EncodeDesc(const BufferDesc &desc);

		private:
			/**
			* When the description is a kind of SRGB buffer
			* @param desc: Engine description format
			* @return Returns the corresponding directx format if it exists
			*/
			static DXGI_FORMAT EncodeSRGBDesc(const BufferDesc &desc);
			/**
			* When the description is a kind of RGB buffer
			* @param desc: Engine description format
			* @return Returns the corresponding directx format if it exists
			*/
			static DXGI_FORMAT EncodeRGBDesc(const BufferDesc &desc);

		};
	}
}