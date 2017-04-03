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
			/**Returns the corresponding sdl pixel format*/
			static uint32_t getSdlPixelFormat(const BufferDesc &desc);
		};
	}
}