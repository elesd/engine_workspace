#include <stdafx.h>
#include <engine/video/glew/DriverImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_GLEW

#include <engine/video/RenderTarget.h>

namespace engine
{
	namespace glew
	{
		DriverImpl::DriverImpl()
		{
			INACTIVE_MODULE_ERROR();

		}

		void DriverImpl::checkErrors()
		{
			INACTIVE_MODULE_ERROR();

		}

		void DriverImpl::printBindings()
		{
			INACTIVE_MODULE_ERROR();

		}

		void DriverImpl::drawImpl(BufferContext* bufferContext)
		{
			INACTIVE_MODULE_ERROR();

		}

		void DriverImpl::setViewPortImpl(int32_t x, int32_t y, int32_t width, int32_t height) 
		{
			INACTIVE_MODULE_ERROR();

		}

		void DriverImpl::setRenderTargetImpl(RenderTarget* renderTarget)
		{
			INACTIVE_MODULE_ERROR();

		}

		void DriverImpl::compileShaderImpl(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options, const AttributeFormat&)
		{
			INACTIVE_MODULE_ERROR();

		}

		void DriverImpl::compileEffectImpl(Effect* effect) 
		{
			INACTIVE_MODULE_ERROR();

		}

		void DriverImpl::setEffectImpl(Effect* effect)
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

			return nullptr;
		}
	}
}

#endif