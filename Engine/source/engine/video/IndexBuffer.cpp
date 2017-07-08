#include <stdafx.h>
#include <engine/video/IndexBuffer.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	namespace IndexBufferPrivate
	{
		///////////////////////////////////////////////////////////////////////

		template<>
		size_t getByteSize<int32_t>()
		{
			return 4;
		}

		template<>
		bool isSupportedSizeType<int32_t>()
		{
			return true;
		}

		///////////////////////////////////////////////////////////////////////

		template<>
		size_t getByteSize<int16_t>()
		{
			return 2;
		}

		template<>
		bool isSupportedSizeType<int16_t>()
		{
			return true;
		}
	}
}