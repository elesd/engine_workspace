#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class ShaderResourceBindingData;
	enum class GPUMemberType;

	class ShaderResourceDescription
	{
	public:
		ShaderResourceDescription(const std::string &name, GPUMemberType type, const ShaderResourceBindingData& bindingData);
		~ShaderResourceDescription();
		ShaderResourceDescription(const ShaderResourceDescription&);
		ShaderResourceDescription(ShaderResourceDescription&&);
		ShaderResourceDescription& operator=(const ShaderResourceDescription&);
		ShaderResourceDescription& operator=(ShaderResourceDescription&&);

		const ShaderResourceBindingData& getResourceBindingData() const;
		const std::string& getName() const;
		GPUMemberType getType() const;

	private:
		struct ShaderResourceDescriptionPrivate* _members = nullptr;
	};
}