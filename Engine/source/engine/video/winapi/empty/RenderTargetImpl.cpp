#include <stdafx.h>
#include <engine/video/winapi/RenderTargetImpl.h>
///////////////////////////////////////////////////////////////////////////////


namespace engine
{
	namespace winapi
	{
	

		RenderTargetImpl::RenderTargetImpl(ID3D11RenderTargetView* renderTarget)
		{
			INACTIVE_MODULE_ERROR();
		}

		RenderTargetImpl::~RenderTargetImpl() 
		{
			INACTIVE_MODULE_ERROR();
		}

		RenderTargetImpl::RenderTargetImpl(RenderTargetImpl&& o)
		{
			INACTIVE_MODULE_ERROR();
		}

		RenderTargetImpl& RenderTargetImpl::operator=(RenderTargetImpl&& o)
		{
			INACTIVE_MODULE_ERROR();
			return *this;
		}

		ID3D11RenderTargetView* RenderTargetImpl::getRenderTargetView() const
		{
			INACTIVE_MODULE_ERROR();
			return nullptr;
		}

		void RenderTargetImpl::destroy()
		{
			INACTIVE_MODULE_ERROR();
		}
	}
}