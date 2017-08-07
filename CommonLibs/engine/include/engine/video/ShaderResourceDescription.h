#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class ShaderResourceBinding;
	enum class GPUMemberType;

	class ShaderResourceDescription
	{
	public:
		ShaderResourceDescription(const std::string &name, GPUMemberType type, std::unique_ptr<ShaderResourceBinding>&& bindingData);
		~ShaderResourceDescription();
		ShaderResourceDescription(const ShaderResourceDescription&);
		ShaderResourceDescription(ShaderResourceDescription&&);
		ShaderResourceDescription& operator=(const ShaderResourceDescription&);
		ShaderResourceDescription& operator=(ShaderResourceDescription&&);


		const ShaderResourceBinding* getResourceBinding() const;
		const std::string& getName() const;
		GPUMemberType getType() const;

	private:
		struct ShaderResourceDescriptionPrivate* _members = nullptr;
	};
}