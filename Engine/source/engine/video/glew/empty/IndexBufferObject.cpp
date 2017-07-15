#include <stdafx.h>
#include <engine/video/glew/IndexBufferObject.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_GLEW



namespace engine
{
	namespace glew
	{

		IndexBufferObject::IndexBufferObject(size_t size, Driver* driver)
		{
			INACTIVE_MODULE_ERROR();
		}

		IndexBufferObject::~IndexBufferObject()
		{
			INACTIVE_MODULE_ERROR();
		}

		void IndexBufferObject::bind()
		{
			INACTIVE_MODULE_ERROR();
		}

		void IndexBufferObject::unbind()
		{
			INACTIVE_MODULE_ERROR();
		}

		void IndexBufferObject::setData(const char* data, size_t size)
		{
			INACTIVE_MODULE_ERROR();
		}

		bool IndexBufferObject::isBound() const
		{
			INACTIVE_MODULE_ERROR();
			return false;
		}
	}
}
#else
#include <engine/video/glew/empty/IndexBufferObject.cpp>
#endif