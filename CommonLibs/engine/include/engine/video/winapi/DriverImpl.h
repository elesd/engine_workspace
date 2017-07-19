#pragma once

#include <engine/video/Driver.h>

struct ID3D11PixelShader;
struct ID3D11VertexShader;
struct ID3D11Buffer;
struct D3D11_BUFFER_DESC;
namespace engine
{
	class Effect;
	class IndexBufferBase;
	class RenderTarget;
	class ShaderCompilationData;
	class ShaderCompileOptions;
	class Shader;
	class VertexBuffer;
	class Window;
	namespace winapi
	{
		class TextureImpl;
		class VertexBufferObject;
		class IndexBufferObject;

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
			
			void bind(VertexBufferObject* vertexBuffer);
			void bind(IndexBufferObject* vertexBuffer);
			void unbind(VertexBufferObject* vertexBuffer);
			void unbind(IndexBufferObject* vertexBuffer);
			ID3D11Buffer* createBuffer(const D3D11_BUFFER_DESC& description);

			void setCurrentVertexBuffer(const VertexBuffer* verticies);
			void setCurrentIndexBuffer(const IndexBufferBase* indicies);
		private:
			void initDeviceImpl(const DeviceParameters& params) override;
			/**Initialize based on the given window*/
			void initImpl(const DriverInitParameters& params) override;
			void compileShaderImpl(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options, const AttributeFormat& attributeFormat) override;
			void compileEffectImpl(Effect* effect) override;
			void drawImpl(BufferContext*) override;
			void setViewPortImpl(int32_t x, int32_t y, int32_t width, int32_t height) override;
			void setRenderTargetImpl(RenderTarget* renderTarget) override;
			void setEffectImpl(Effect* effect);
			void setShaderImpl(Shader* shader, const std::string& techniqueName) override;
			std::unique_ptr<RenderTarget> createRenderTargetImpl(std::unique_ptr<Texture>&& texture) override;
			void swapBufferImpl() override;

			bool checkDeviceSetupImpl() override;

			void createDevice();
			void createSwapChain(const DriverInitParameters& params, Window *window);
			void initRenderTarget();
			void createBackBufferRenderTarget();
			std::unique_ptr<TextureImpl> createBackBufferTexture();
			void initViewPort(Window *window);

			ID3D11PixelShader* createD3DFragmentShaderInto(ID3DBlob* compiledCode, ShaderCompilationData* resultData) const;
			ID3D11VertexShader* createD3DVertexShaderInto(ID3DBlob* compiledCode, ShaderCompilationData* resultData, const AttributeFormat& attributeFormat) const;

		private:
			/**PIMPL*/
			struct DriverImplPrivate *_members = nullptr;
		};
	}
}