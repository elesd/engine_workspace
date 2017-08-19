#pragma once

#include <engine/video/Driver.h>

namespace engine
{
	enum class DriverVersion;
	namespace glew
	{

		class DriverImpl :
			public Driver
		{
		public:
			DriverImpl();

			void checkErrors();
			void printBindings();
			void printInfo();
		protected:
			std::pair<int32_t, int32_t> getOpenglMajorMinorVersion(DriverVersion version) const; 
		private:
			void compileShaderImpl(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options, const AttributeFormat&) override;
			void compileEffectImpl(Effect* effect) override;
			void drawImpl(BufferContext* bufferContext) override;
			void setRenderTargetImpl(RenderTarget* renderTarget) override;
			void setEffectImpl(Effect* effect) override;
			void setShaderImpl(Shader* shader, const std::string& techniqueName) override;
			void setViewPortImpl(int32_t x, int32_t y, int32_t width, int32_t height) override;

			std::unique_ptr<RenderTarget> createRenderTargetImpl(std::unique_ptr<Texture>&& texture) override;

			bool checkShaderOptions(const ShaderCompileOptions& options) const;
			bool checkDeviceSetupImpl() override;

			std::unique_ptr<ShaderResourceHandler> createShaderResourceHandlerImpl() override;
			std::unique_ptr<ShaderResourceBinding> bindResourceImpl(const ShaderResourceDescription& desc, Effect* effect) override;

			std::unique_ptr<ShaderResourceBinding> bindResourceImplDebug(const ShaderResourceDescription& desc, Effect* effect);
			std::unique_ptr<ShaderResourceBinding> bindResourceImplRelease(const ShaderResourceDescription& desc, Effect* effect);

		};
	}
}

