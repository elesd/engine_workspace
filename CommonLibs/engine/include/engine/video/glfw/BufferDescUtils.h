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
			/**Buffer description for glfw module*/
			struct GlfwDesc
			{
				int32_t redBits = 0; /**< Red bits in the buffer*/
				int32_t blueBits = 0; /**< Blue bits in the buffer*/
				int32_t greenBits = 0; /**< Green bits in the buffer*/
				int32_t alphaBits = 0; /**< alpha bits in the buffer*/
				int32_t stencilBits = 0; /**< stencil bits in the buffer*/
				int32_t depthBits = 0; /**< depth bits in the buffer*/
				bool useSrgb = false; /**< Whether use srgb format or not*/
			};

			/**Convert a buffer description into GlfwDesc class*/
			static GlfwDesc getGlfwDesc(const BufferDesc &desc);

		private:
			/**@return Returns the red bits in the given buffer*/
			static int32_t getRedBits(const BufferDesc &desc);
			/**@return Returns the Blue bits in the given buffer*/
			static int32_t getBlueBits(const BufferDesc &desc);
			/**@return Returns the Green bits in the given buffer*/
			static int32_t getGreenBits(const BufferDesc &desc);
			/**@return Returns the alpha bits in the given buffer*/
			static int32_t getAlphaBits(const BufferDesc &desc);
			/**@return Returns the stencil bits in the given buffer*/
			static int32_t getStencilBits(const BufferDesc &desc);
			/**@return Returns the depth bits in the given buffer*/
			static int32_t getDepthBits(const BufferDesc &desc);
		};
	}
}