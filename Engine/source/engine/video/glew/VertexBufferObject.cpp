#include <stdafx.h>
#include <engine/video/glew/VertexBufferObject.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/glew/DriverImpl.h>

namespace engine
{
	namespace glew
	{
		struct VertexBufferObjectPrivate
		{
			DriverImpl *driver = nullptr;
			GLuint vboId = 0;
			bool bind = false;
			explicit VertexBufferObjectPrivate(DriverImpl *driver)
				: driver(driver)
			{ }
		};

		VertexBufferObject::VertexBufferObject(size_t size, Driver* driver)
			: _members(new VertexBufferObjectPrivate(static_cast<DriverImpl*>(driver)))
		{
			_members->vboId = _members->driver->createBuffer();
		}

		VertexBufferObject::~VertexBufferObject()
		{
			if(isBind())
			{
				unbind();
			}
			delete _members;
		}

		void VertexBufferObject::bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, _members->vboId);
			_members->bind = true;
		}

		void VertexBufferObject::unbind()
		{
			ASSERT(isBind());
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			_members->bind = false;
		}
		
		void VertexBufferObject::setData(const char* data, size_t size)
		{
			ASSERT(isBind());
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			// TODO handle buffer usage hint
		}

		bool VertexBufferObject::isBind() const
		{
			return _members->bind;
		}
	}
}