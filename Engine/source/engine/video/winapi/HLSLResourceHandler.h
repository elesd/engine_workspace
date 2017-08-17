#pragma once

#include <engine/video/ShaderResourceHandler.h>

namespace engine
{
	namespace winapi
	{
		class DriverImpl;
		class ConstantBufferObject;

		class HLSLResourceHandler
			: public ShaderResourceHandler
		{
		public:
			explicit HLSLResourceHandler(DriverImpl* driver);
			~HLSLResourceHandler() override {}
			
		private:
			void commitValue(const ShaderResourceBinding* binding, const ConstantBufferObject& buffer);

			void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, float) override;
			void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec2&) override;
			void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec3&) override;
			void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec4&) override;
			void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::mat3&) override;
			void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::mat4&) override;
			std::unique_ptr<ShaderResourceHandler> cloneImpl() const override;
		};
	}
}