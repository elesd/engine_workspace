#include <stdafx.h>
#include <engine/video/glew/BufferContextImpl.h>
///////////////////////////////////////////////////////////////////////////////

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

		}

		void BufferContextImpl::bind()
		{
			glBindVertexArray(_members->vao);
			static_cast<DriverImpl*>(getDriver())->checkErrors();
		}

		void BufferContextImpl::unbind()
		{
			glBindVertexArray(0);
			static_cast<DriverImpl*>(getDriver())->checkErrors();
		}

		bool BufferContextImpl::isBound() const
		{
			GLint currentVao = 0;
			glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVao);
			static_cast<DriverImpl*>(getDriver())->checkErrors();
			return currentVao == _members->vao;
		}
	}
}