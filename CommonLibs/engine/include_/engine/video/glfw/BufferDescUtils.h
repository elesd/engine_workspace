#pragma once

enum DXGI_FORMAT;

namespace engine
{
	struct BufferDesc;
	namespace glfw
	{
		
		/**Utility class for buffer conversion for glfw opengl*/
		struct BufferDescUtils
		{
			struct GlfwDesc
			{
				int32_t redBits = 0;
				int32_t blueBits = 0;
				int32_t greenBits = 0;
				int32_t alphaBits = 0;
				int32_t stencilBits = 0;
				int32_t depthBits = 0;
				bool useSrgb = false;
			};

			static GlfwDesc getGlfwDesc(const BufferDesc &desc);

		private:
			static int32_t getRedBits(const BufferDesc &desc);
			static int32_t getBlueBits(const BufferDesc &desc);
			static int32_t getGreenBits(const BufferDesc &desc);
			static int32_t getAlphaBits(const BufferDesc &desc);
			static int32_t getStencilBits(const BufferDesc &desc);
			static int32_t getDepthBits(const BufferDesc &desc);
		};
	}
}