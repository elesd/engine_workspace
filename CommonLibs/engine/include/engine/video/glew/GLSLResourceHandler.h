#pragma once

#include <engine/video/ShaderResourceHandler.h>

namespace engine
{
	namespace glew
	{
		class GLSLResourceHandler
			: public ShaderResourceHandler
		{
		public:
			GLSLResourceHandler(Driver* driver);
			~GLSLResourceHandler() override;

		private:
			void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, float) override;
			void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec2&) override;
			void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec3&) override;
			void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec4&) override;
			void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::mat3&) override;
			void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::mat4&) override;
		};
	}
}