#include <stdafx.h>
#include <engine/video/glew/IndexBufferObject.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_GLEW 

#include <engine/video/glew/DriverImpl.h>

namespace engine
{
	namespace glew
	{
		struct IndexBufferObjectPrivate
		{
			DriverImpl *driver = nullptr;
			GLuint bufferId = 0;
			bool bound = false;
			explicit IndexBufferObjectPrivate(DriverImpl *driver)
				: driver(driver)
			{
			}
		};

		IndexBufferObject::IndexBufferObject(size_t, Driver* driver)
			: _members(new IndexBufferObjectPrivate(static_cast<DriverImpl*>(driver)))
		{
			glGenBuffers(1, &_members->bufferId);
			_members->driver->checkErrors();

		}

		IndexBufferObject::~IndexBufferObject()
		{
			if(isBound())
			{
				unbind();
			}
			glDeleteBuffers(1, &_members->bufferId);
			_members->driver->checkErrors();

			delete _members;
		}

		void IndexBufferObject::bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _members->bufferId);
			_members->driver->checkErrors();
			_members->bound = true;
		}

		void IndexBufferObject::unbind()
		{
			ASSERT(isBound());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			_members->driver->checkErrors();
			_members->bound = false;
		}

		void IndexBufferObject::setData(const char* data, size_t size)
		{
			ASSERT(isBound());
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			_members->driver->checkErrors();
			// TODO handle buffer usage hint
		}

		bool IndexBufferObject::isBound() const
		{
#if ENGINE_OPENGL_PARANOID
			GLint currentId = 0;
			glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentId);
			_members->driver->checkErrors();
			ASSERT(_members->bound == (GLuint(currentId) == _members->bufferId));
			return GLuint(currentId) == _members->bufferId;
#else
			return _members->bound;
#endif
		}
	}
}
#endif