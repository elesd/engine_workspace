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

	enum class ShaderType;

	namespace winapi
	{
		class TextureImpl;
		class VertexBufferObject;
		class IndexBufferObject;
		class ConstantBufferObject;

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
			
			void bind(ConstantBufferObject* vertexBuffer);
			void bind(VertexBufferObject* vertexBuffer);
			void bind(IndexBufferObject* vertexBuffer);
			
			void unbind(ConstantBufferObject* vertexBuffer);
			void unbind(VertexBufferObject* vertexBuffer);
			void unbind(IndexBufferObject* vertexBuffer);
			ID3D11Buffer* createBuffer(const D3D11_BUFFER_DESC& description, D3D11_SUBRESOURCE_DATA* initData = nullptr);

			void setCurrentVertexBuffer(const VertexBuffer* verticies);
			void setCurrentIndexBuffer(const IndexBufferBase* indicies);
			void setConstantBufferObject(ShaderType type, uint32_t slot, const ConstantBufferObject * constantBuffer);
		private:
			void initDeviceImpl(const DeviceParameters& params) override;
			/**Initialize based on the given window*/
			void initImpl(const DriverInitParameters& params) override;
			void compileShaderImpl(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options, const AttributeFormat& attributeFormat) override;
			void compileEffectImpl(Effect* effect, Shader*, Shader*) override;
			void drawImpl(BufferContext*) override;
			void setViewPortImpl(int32_t x, int32_t y, int32_t width, int32_t height) override;
			void setRenderTargetImpl(RenderTarget* renderTarget) override;
			void setEffectImpl(Effect* effect) override;
			void setShaderImpl(Shader* shader, const std::string& techniqueName) override;
			std::unique_ptr<RenderTarget> createRenderTargetImpl(std::unique_ptr<Texture>&& texture) override;
			void swapBufferImpl() override;

			bool checkDeviceSetupImpl() override;
			std::unique_ptr<ShaderResourceHandler> createShaderResourceHandlerImpl() override;
			std::unique_ptr<ShaderResourceBinding> bindResourceImpl(const ShaderResourceDescription& desc, Effect* effect) override;


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