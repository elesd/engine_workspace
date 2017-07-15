#include <stdafx.h>
#include <engine/video/glew/BufferContextImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_GLEW

namespace engine
{
	namespace glew
	{

		BufferContextImpl::BufferContextImpl(RenderContext *renderContext, Driver* driver)
			: BufferContext(renderContext, driver)
		{
			INACTIVE_MODULE_ERROR();
		}

		BufferContextImpl::~BufferContextImpl()
		{
			INACTIVE_MODULE_ERROR();
		}

		void BufferContextImpl::bindBuffersImpl()
		{
			INACTIVE_MODULE_ERROR();
		}

		void BufferContextImpl::unbindBuffersImpl()
		{
			INACTIVE_MODULE_ERROR();
		}

		void BufferContextImpl::setupLayout()
		{
			INACTIVE_MODULE_ERROR();
		}

		void BufferContextImpl::bind()
		{
			INACTIVE_MODULE_ERROR();

		}

		void BufferContextImpl::unbind()
		{
			INACTIVE_MODULE_ERROR();

		}

		void BufferContextImpl::finalizeImpl()
		{
			INACTIVE_MODULE_ERROR();

		}

		bool BufferContextImpl::isBound() const
		{
			INACTIVE_MODULE_ERROR();
			return false;
		}
	}
}	
#endif