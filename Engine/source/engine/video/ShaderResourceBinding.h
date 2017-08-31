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
		virtual bool isBound() const = 0;
	private:
	};
}