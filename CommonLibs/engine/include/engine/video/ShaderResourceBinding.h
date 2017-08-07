#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class ShaderResourceBinding
		: private NonCopyable
	{
	public:
		ShaderResourceBinding() {};
		virtual ~ShaderResourceBinding() {};
		std::unique_ptr<ShaderResourceBinding> clone() const;
	private:
		virtual std::unique_ptr<ShaderResourceBinding> cloneImpl() const = 0;
	};
}