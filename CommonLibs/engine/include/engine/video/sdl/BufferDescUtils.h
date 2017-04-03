#pragma once


enum DXGI_FORMAT;

namespace engine
{
	struct BufferDesc;
	namespace sdl
	{
		
		/**Utility class for buffer conversion for glfw opengl*/
		struct BufferDescUtils
		{
			static uint32_t getSdlPixelFormat(const BufferDesc &desc);
		};
	}
}