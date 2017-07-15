#include <stdafx.h>
#include <engine/video/winapi/BufferContextImpl.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/winapi/DriverImpl.h>

namespace engine
{
	namespace winapi
	{
		struct BufferContextImplPrivate
		{
			bool bound = false;
		};


		BufferContextImpl::BufferContextImpl(RenderContext* renderContext, Driver* driver)
			: BufferContext(renderContext, driver)
			, _members(new BufferContextImplPrivate())
		{

		}

		BufferContextImpl::~BufferContextImpl() 
		{
			delete _members;
			_members = nullptr;
		}

		void BufferContextImpl::bindBuffersImpl()
		{
			DriverImpl* driver = static_cast<DriverImpl*>(getDriver());
			driver->setCurrentVertexBuffer(getVertexBuffer());
			driver->setCurrentIndexBuffer(getIndexBuffer());
		}

		void BufferContextImpl::unbindBuffersImpl()
		{

		}

		void BufferContextImpl::setupLayout()
		{

		}
		
		void BufferContextImpl::finalizeImpl()
		{
			if(getIndexBuffer()->isMapped() == false)
			{
				accessIndexBuffer()->map(getRenderContext());
			}
			if(getVertexBuffer()->isMapped() == false)
			{
				accessVertexBuffer()->map(getRenderContext());
			}
		}

		void BufferContextImpl::bind()
		{
			_members->bound = true;
		}

		void BufferContextImpl::unbind()
		{
			_members->bound = false;
		}

		bool BufferContextImpl::isBound() const
		{
			return _members->bound;
		}
	}
}