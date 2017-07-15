#include <stdafx.h>
#include <engine/video/glew/VertexBufferObject.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_GLEW



namespace engine
{
	namespace glew
	{
		VertexBufferObject::VertexBufferObject(size_t size, Driver* driver)
		{
			INACTIVE_MODULE_ERROR();
		}

		VertexBufferObject::~VertexBufferObject()
		{
			INACTIVE_MODULE_ERROR();
		}

		void VertexBufferObject::bind()
		{
			INACTIVE_MODULE_ERROR();
		}

		void VertexBufferObject::unbind()
		{
			INACTIVE_MODULE_ERROR();
		}

		void VertexBufferObject::setData(const char* data, size_t size)
		{
			INACTIVE_MODULE_ERROR();
		}

		bool VertexBufferObject::isBound() const
		{
			INACTIVE_MODULE_ERROR();
			return false;
		}
	}
}

#endif