#pragma once

#include <engine/video/ShaderResourceBinding.h>

namespace engine
{
	enum class GPUMemberType;
	enum class ShaderType;
	namespace winapi
	{
		class DriverImpl;


		class HLSLResourceBinding 
			: public ShaderResourceBinding
		{
		public:
			HLSLResourceBinding(uint32_t bufferId, const std::vector<ShaderType>& shaderTypes);
			HLSLResourceBinding(const HLSLResourceBinding&);
			HLSLResourceBinding(HLSLResourceBinding&&);
			~HLSLResourceBinding() override;

			HLSLResourceBinding& operator=(const HLSLResourceBinding&);
			HLSLResourceBinding& operator=(HLSLResourceBinding&&);

			uint32_t getBufferId() const;
			std::vector<ShaderType> getShaderTypes() const;
			bool isBound() const override;

		private:
			struct HLSLResourceBindingPrivate* _members = nullptr;
		};
	}
}