#include <stdafx.h>
#include <engine/video/winapi/RenderTargetImpl.h>
///////////////////////////////////////////////////////////////////////////////


namespace engine
{
	namespace winapi
	{
	

		RenderTargetImpl::RenderTargetImpl(std::unique_ptr<Texture>&& texture, ID3D11RenderTargetView* renderTarget)
			: RenderTarget(std::move(texture))
		{
			INACTIVE_MODULE_ERROR();
		}

		RenderTargetImpl::~RenderTargetImpl() 
		{
			INACTIVE_MODULE_ERROR();
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