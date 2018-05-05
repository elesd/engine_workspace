#include <stdafx.h>
#include <engine/video/glew/VertexBufferObject.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_GLEW 

#include <engine/video/glew/DriverImpl.h>

namespace engine
{
	namespace glew
	{
		struct VertexBufferObjectPrivate
		{
			DriverImpl *driver = nullptr;
			bool bound = false;
			GLuint vboId = 0;
			explicit VertexBufferObjectPrivate(DriverImpl *driver)
				: driver(driver)
			{ }
		};

		VertexBufferObject::VertexBufferObject(size_t, Driver* driver)
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
			_members->bound = true;
		}

		void VertexBufferObject::unbind()
		{
			ASSERT(isBound());
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			_members->driver->checkErrors();
			_members->bound = false;
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
#if ENGINE_OPENGL_PARANOID
			GLint currentId = 0;
			glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentId);
			_members->driver->checkErrors();
			ASSERT(_members->bound == (GLuint(currentId) == _members->vboId));
			return GLuint(currentId) == _members->vboId;
#else
			return _members->bound;
#endif
		}
	}
}

#endif