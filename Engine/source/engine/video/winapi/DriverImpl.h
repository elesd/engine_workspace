#pragma once

#include <engine/video/Driver.h>

struct ID3D11PixelShader;
struct ID3D11VertexShader;

namespace engine
{
	class ShaderCompilationData;
	namespace winapi
	{
		class TextureImpl;

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
			void compileShaderImpl(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options) override;
			void drawImpl(const VertexBuffer* verticies, const IndexBuffer* indicies) override;
			void setViewPortImpl(int32_t topX, int32_t topY, int32_t width, int32_t height) override;
			void setRenderTargetImpl(RenderTarget* renderTarget) override;
			void setShaderImpl(Shader* shader, const std::string& techniqueName) override;
			std::unique_ptr<RenderTarget> createRenderTargetImpl(Texture* texture) override;

			void createDevice();
			void createSwapChain(const DriverInitParameters& params, Window *window);
			void initRenderTarget();
			void createBackBufferRenderTarget();
			std::unique_ptr<TextureImpl> createBackBufferTexture();
			void initViewPort(Window *window);

			ID3D11PixelShader* createD3DFragmentShaderInto(ID3DBlob* compiledCode, ShaderCompilationData* resultData) const;
			ID3D11VertexShader* createD3DVertexShaderInto(ID3DBlob* compiledCode, ShaderCompilationData* resultData) const;

		private:
			/**PIMPL*/
			struct DriverImplPrivate *_members = nullptr;
		};
	}
}