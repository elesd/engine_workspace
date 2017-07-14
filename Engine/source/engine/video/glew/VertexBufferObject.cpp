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
			explicit VertexBufferObjectPrivate(DriverImpl *driver)
				: driver(driver)
			{ }
		};

		VertexBufferObject::VertexBufferObject(size_t size, Driver* driver)
			: _members(new VertexBufferObjectPrivate(static_cast<DriverImpl*>(driver)))
		{
			glGenBuffers(1, &_members->vboId);
			_members->driver->checkErrors();
		}

		VertexBufferObject::~VertexBufferObject()
		{
			if(isBound())
			{
				unbind();
			}
			glDeleteBuffers(1, &_members->vboId);
			_members->driver->checkErrors();
			delete _members;
		}

		void VertexBufferObject::bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, _members->vboId);
			_members->driver->checkErrors();
		}

		void VertexBufferObject::unbind()
		{
			ASSERT(isBound());
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			_members->driver->checkErrors();
		}
		
		void VertexBufferObject::setData(const char* data, size_t size)
		{
			ASSERT(isBound());
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			_members->driver->checkErrors();
			// TODO handle buffer usage hint
		}

		bool VertexBufferObject::isBound() const
		{
			GLint currentId = 0;
			glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentId);

			return currentId == _members->vboId;
		}
	}
}