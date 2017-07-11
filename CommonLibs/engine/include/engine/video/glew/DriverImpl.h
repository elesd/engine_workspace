#pragma once

#include <engine/video/Driver.h>

namespace engine
{
	namespace glew
	{

		class DriverImpl :
			public Driver
		{
		public:
			GLuint createBuffer();
		private:
			void compileShaderImpl(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options) override;
			void compileEffectImpl(Effect* effect) override;
			void drawImpl(const VertexBuffer* verticies, const IndexBufferBase* indicies) override;
			void setRenderTargetImpl(RenderTarget* renderTarget) override;
			void resetRenderTargetImpl() override;
			void setMaterialContextImpl(const MaterialContext* material) override;
			void setEffectImpl(Effect* effect) override;
			void setShaderImpl(Shader* shader, const std::string& techniqueName) override;

			std::unique_ptr<RenderTarget> createRenderTargetImpl(std::unique_ptr<Texture>&& texture) override;
			std::unique_ptr<MaterialContext> createMaterialContextImpl(const Material* material) override;

		};
	}
}
