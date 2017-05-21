#pragma once

#include <engine/video/Driver.h>

namespace engine
{
	namespace winapi
	{
		/**
		* Video driver implementation for winapi
		*/
		class DriverImpl 
			: public Driver
		{
		public:
			/**Simple constructor*/
			DriverImpl();
			/**For PIMPL*/
			~DriverImpl() override;

		private:
			/**Initialize based on the given window*/
			void initImpl(const DriverInitParameters& params, Window *window) override;
			void drawImpl(const VertexBuffer* verticies, const IndexBuffer* indicies) override;
			void setViewPortImpl(int32_t topX, int32_t topY, int32_t width, int32_t height) override;
			void setRenderTargetImpl(RenderTarget* renderTarget) override;
			void setMaterialImpl(Material* material) override;

			void createDevice();
			void createSwapChain(const DriverInitParameters& params, Window *window);
			void initRenderTarget();
			void createBackBufferRenderTarget();
			void initViewPort(Window *window);

		private:
			/**PIMPL*/
			struct DriverImplPrivate *_members = nullptr;
		};
	}
}