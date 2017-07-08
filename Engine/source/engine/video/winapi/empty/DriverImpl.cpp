#include <stdafx.h>

#include <engine/video/winapi/DriverImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_WINAPI == 0
#include <engine/video/RenderTarget.h>

#include <engine/video/winapi/TextureImpl.h>

namespace engine
{
	namespace winapi
	{

		
		void DriverImpl::bind(IndexBufferObject* vertexBuffer)
		{
			INACTIVE_MODULE_ERROR();
		}

		void DriverImpl::unbind(IndexBufferObject* vertexBuffer)
		{
			INACTIVE_MODULE_ERROR();

		}

		void DriverImpl::bind(VertexBufferObject* vertexBuffer)
		{
			INACTIVE_MODULE_ERROR();

		}

		void DriverImpl::unbind(VertexBufferObject* vertexBuffer)
		{
			INACTIVE_MODULE_ERROR();

		}

		ID3D11Buffer* DriverImpl::createBuffer(const D3D11_BUFFER_DESC& description)
		{
			INACTIVE_MODULE_ERROR();
			return nullptr;
		}

		void DriverImpl::initImpl(const DriverInitParameters& params, Window *window)
		{
			INACTIVE_MODULE_ERROR();
		}

		void DriverImpl::setViewPortImpl(int32_t topX, int32_t topY, int32_t width, int32_t height)
		{
			INACTIVE_MODULE_ERROR();
		}

		void DriverImpl::createDevice()
		{
			INACTIVE_MODULE_ERROR();
		}

		void DriverImpl::createSwapChain(const DriverInitParameters& params, Window *window)
		{
			INACTIVE_MODULE_ERROR();
		}

		void DriverImpl::initRenderTarget()
		{
			INACTIVE_MODULE_ERROR();
		}

		std::unique_ptr<TextureImpl> DriverImpl::createBackBufferTexture()
		{
			INACTIVE_MODULE_ERROR();
			return std::unique_ptr<TextureImpl>();
		}

		void DriverImpl::createBackBufferRenderTarget()
		{
			INACTIVE_MODULE_ERROR();
		}

		void DriverImpl::initViewPort(Window *window)
		{
			INACTIVE_MODULE_ERROR();
		}

		void DriverImpl::drawImpl(const VertexBuffer* verticies, const IndexBufferBase* indicies)
		{
			INACTIVE_MODULE_ERROR();
		}

		void DriverImpl::setVertexBuffer(const VertexBuffer* verticies)
		{
			INACTIVE_MODULE_ERROR();
		}

		void DriverImpl::setIndexBuffer(const IndexBufferBase* indicies)
		{

			INACTIVE_MODULE_ERROR();
		}

		void DriverImpl::setRenderTargetImpl(RenderTarget* renderTarget)
		{
			INACTIVE_MODULE_ERROR();
		}

		void DriverImpl::setShaderImpl(Shader* shader, const std::string& techniqueName)
		{
			INACTIVE_MODULE_ERROR();
		}

		std::unique_ptr<RenderTarget> DriverImpl::createRenderTargetImpl(std::unique_ptr<Texture>&& texture)
		{
			INACTIVE_MODULE_ERROR();
			return std::unique_ptr<RenderTarget>();
		}

		void DriverImpl::compileShaderImpl(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options)
		{
			INACTIVE_MODULE_ERROR();
		}

		ID3D11PixelShader* DriverImpl::createD3DFragmentShaderInto(ID3DBlob* compiledCode, ShaderCompilationData* resultData) const
		{
			INACTIVE_MODULE_ERROR();
			return nullptr;
		}

		ID3D11VertexShader* DriverImpl::createD3DVertexShaderInto(ID3DBlob* compiledCode, ShaderCompilationData* resultData) const
		{
			INACTIVE_MODULE_ERROR();
			return nullptr;
		}

		void DriverImpl::swapBufferImpl() 
		{
			INACTIVE_MODULE_ERROR();
		}
	}
}
#endif