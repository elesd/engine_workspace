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

		RenderTargetImpl::RenderTargetImpl(ID3D11RenderTargetView* renderTarget)
			: _members(new RenderTargetImplPrivate(renderTarget))
		{

		}

		RenderTargetImpl::~RenderTargetImpl() 
		{
			destroy();
		}

		RenderTargetImpl::RenderTargetImpl(RenderTargetImpl&& o)
			: RenderTarget(std::move(o))
			, _members(o._members)
		{
			o._members = nullptr;
		}

		RenderTargetImpl& RenderTargetImpl::operator=(RenderTargetImpl&& o)
		{
			RenderTarget::operator=(std::move(o));
			destroy();
			_members = o._members;
			o._members = nullptr;
			return *this;
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

#else

#include <engine/video/winapi/empty/RenderTargetImpl.cpp>

#endif