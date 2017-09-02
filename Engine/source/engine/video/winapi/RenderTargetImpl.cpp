#include <stdafx.h>
#include <engine/video/winapi/RenderTargetImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_WINAPI

#include <d3d11.h>

namespace engine
{
	namespace winapi
	{
		struct RenderTargetImplPrivate
		{
			ID3D11RenderTargetView* renderTarget;
			RenderTargetImplPrivate(ID3D11RenderTargetView* renderTarget)
				: renderTarget(renderTarget)
			{ }
		};

		RenderTargetImpl::RenderTargetImpl(std::unique_ptr<Texture>&& texture, ID3D11RenderTargetView* renderTarget)
			: RenderTarget(std::move(texture))
			, _members(new RenderTargetImplPrivate(renderTarget))
		{

		}

		RenderTargetImpl::~RenderTargetImpl() 
		{
			destroy();
		}

		ID3D11RenderTargetView* RenderTargetImpl::getRenderTargetView() const
		{
			return _members->renderTarget;
		}

		void RenderTargetImpl::destroy()
		{
			if(_members && _members->renderTarget)
			{
				_members->renderTarget->Release();
			}
			delete _members;
			_members = nullptr;
		}
	}
}

#endif