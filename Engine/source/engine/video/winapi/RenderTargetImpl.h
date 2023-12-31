#pragma once

#include <engine/video/RenderTarget.h>
#include <engine/constraints/NonCopyable.h>

struct ID3D11RenderTargetView;

namespace engine
{
	
	namespace winapi
	{
		class TextureImpl;
		class DriverImpl;
		class RenderTargetImpl 
			: public RenderTarget
		{
		public:
			RenderTargetImpl(std::unique_ptr<Texture>&& texture, ID3D11RenderTargetView* renderTarget);
			~RenderTargetImpl() override;

			ID3D11RenderTargetView* getRenderTargetView() const;
		private:
			void destroy();
		private:
			struct RenderTargetImplPrivate* _members = nullptr;
		};
	}
}