#include <stdafx.h>
#include <engine/video/glew/BufferContextImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_GLEW 

#include <engine/utils/ScopeExit.h>

#include <engine/video/GPUTypes.h>
#include <engine/video/glew/DriverImpl.h>
#include <engine/video/glew/IndexBufferObject.h>
#include <engine/video/glew/VertexBufferObject.h>

namespace
{

	size_t getAttirbuteMemberCount(engine::GPUMemberType type)
	{
		switch(type)
		{
			case engine::GPUMemberType::Float: return 1; break;
			case engine::GPUMemberType::Vec2: return 2; break;
			case engine::GPUMemberType::Vec3: return 3; break;
			case engine::GPUMemberType::Vec4: return 4; break;
			case engine::GPUMemberType::Mat3: return 9; break;
			case engine::GPUMemberType::Mat4: return 16; break;
			case engine::GPUMemberType::Undef:
			default: FAIL("Unknown gpu member type"); return 0;
				break;
		}
	}

	size_t getTypeSize(engine::GPUMemberType type)
	{
		return getAttirbuteMemberCount(type) * sizeof(GLfloat);
	}
}

namespace engine
{
	namespace glew
	{
		struct BufferContextImplPrivate
		{
			bool bound = false;
			GLuint vao = 0;
		};

		BufferContextImpl::BufferContextImpl(RenderContext *renderContext, Driver* driver)
			: BufferContext(renderContext, driver)
			, _members(new BufferContextImplPrivate())
		{
			glGenVertexArrays(1, &_members->vao);
			static_cast<DriverImpl*>(getDriver())->checkErrors();
		}

		BufferContextImpl::~BufferContextImpl()
		{
			if(isBound())
			{
				unbind();
			}
			glDeleteVertexArrays(1, &_members->vao);
			static_cast<DriverImpl*>(getDriver())->checkErrors();
			delete _members;
			_members = nullptr;
		}

		void BufferContextImpl::bindBuffersImpl()
		{
			bind();
		}

		void BufferContextImpl::unbindBuffersImpl()
		{
			unbind();
		}

		void BufferContextImpl::setupLayout()
		{
			bind();
			ScopeExit unbindOnExit([=]() { unbind(); });
			if(getVertexBuffer()->isMapped() == false)
			{
				accessVertexBuffer()->map(getRenderContext());
			}

			accessVertexBuffer()->getBufferObject()->bind();

			size_t layoutSize = 0;
			const std::vector<GPUMemberType> attributeTypes = getVertexBuffer()->getAttributeTypes();
			for(GPUMemberType type : attributeTypes)
			{
				layoutSize += getTypeSize(type);
			}

			size_t offset = 0;
			for(size_t i = 0; i < attributeTypes.size(); ++i)
			{
				glEnableVertexAttribArray(i);
				static_cast<DriverImpl*>(getDriver())->checkErrors();
				glVertexAttribPointer(
					i,
					getAttirbuteMemberCount(attributeTypes[i]),
					GL_FLOAT, // TODO
					false, // TODO
					layoutSize,
					(void*)offset
				);
				static_cast<DriverImpl*>(getDriver())->checkErrors();
				offset += getTypeSize(attributeTypes[i]);
			}
			accessVertexBuffer()->getBufferObject()->unbind();
		}

		void BufferContextImpl::bind()
		{
			glBindVertexArray(_members->vao);
			_members->bound = true;
			static_cast<DriverImpl*>(getDriver())->checkErrors();
		}

		void BufferContextImpl::unbind()
		{
			glBindVertexArray(0);
			_members->bound = false;
			static_cast<DriverImpl*>(getDriver())->checkErrors();
		}

		void BufferContextImpl::finalizeImpl()
		{
			ScopeExit unbindOnExit([=]() { unbind(); });
			bind();
			ASSERT(getVertexBuffer()->isMapped() && "If it is not mapped layouts are not setup.");
			if(accessIndexBuffer()->isMapped() == false)
			{
				accessIndexBuffer()->map(getRenderContext());
			}
			accessIndexBuffer()->getBufferObject()->bind();
			accessVertexBuffer()->getBufferObject()->bind();
		}

		bool BufferContextImpl::isBound() const
		{
#if ENGINE_OPENGL_PARANOID
			GLint currentVao = 0;
			glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVao);
			static_cast<DriverImpl*>(getDriver())->checkErrors();
			ASSERT(_members->bound == (currentVao == _members->vao));
			return currentVao == _members->vao;
#else
			return _members->bound;
#endif
		}
	}
}
#else

#include <engine/video/glew/empty/BufferContextImpl.cpp>

#endif