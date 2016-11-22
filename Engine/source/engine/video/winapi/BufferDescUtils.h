#pragma once

enum DXGI_FORMAT;

namespace engine
{
	namespace video
	{
		struct BufferDesc;
		namespace winapi
		{
			struct BufferDescUtils
			{
				static DXGI_FORMAT EncodeDesc(const BufferDesc &desc);
			private:
				static DXGI_FORMAT EncodeSRGBDesc(const BufferDesc &desc);
				static DXGI_FORMAT EncodeRGBDesc(const BufferDesc &desc);

			};
		}
	}
}