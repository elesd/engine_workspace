#include <stdafx.h>
#include <engine/video/glew/IndexBufferObject.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/glew/DriverImpl.h>

namespace engine
{
	namespace glew
	{
		struct IndexBufferObjectPrivate
		{
			DriverImpl *driver = nullptr;
			GLuint bufferId = 0;
			bool bind = false;
			explicit IndexBufferObjectPrivate(DriverImpl *driver)
				: driver(driver)
			{
			}
		};

		IndexBufferObject::IndexBufferObject(size_t size, Driver* driver)
			: _members(new IndexBufferObjectPrivate(static_cast<DriverImpl*>(driver)))
		{
			_members->bufferId = _members->driver->createBuffer();
		}

		IndexBufferObject::~IndexBufferObject()
		{
			if(isBind())
			{
				unbind();
			}
			delete _members;
		}

		void IndexBufferObject::bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _members->bufferId);
			{
				std::cout << "IndexBufferObject::bind()" << std::endl;
				GLint param;
				glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &param);
				std::cout << "current vao: " << param << std::endl;
				glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &param);
				std::cout << "Index buffer: " << param << std::endl;
				glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &param);
				std::cout << "Vertex buffer: " << param << std::endl;
				glGetIntegerv(GL_CURRENT_PROGRAM, &param);
				std::cout << "program: " << param << std::endl;
			}
			_members->bind = true;
		}

		void IndexBufferObject::unbind()
		{
			ASSERT(isBind());
		//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			_members->bind = false;
		}

		void IndexBufferObject::setData(const char* data, size_t size)
		{
			{
				std::cout << "IndexBufferObject::setData()" << std::endl;
				GLint param;
				glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &param);
				std::cout << "current vao: " << param << std::endl;
				glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &param);
				std::cout << "Index buffer: " << param << std::endl;
				glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &param);
				std::cout << "Vertex buffer: " << param << std::endl;
				glGetIntegerv(GL_CURRENT_PROGRAM, &param);
				std::cout << "program: " << param << std::endl;
			}
			ASSERT(isBind());
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			// TODO handle buffer usage hint
		}

		bool IndexBufferObject::isBind() const
		{
			return _members->bind;
		}
	}
}