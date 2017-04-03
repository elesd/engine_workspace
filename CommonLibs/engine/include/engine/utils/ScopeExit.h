#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class ScopeExit : private NonCopyable
	{
	public:
		ScopeExit(std::function<void()> &&f)
			:_f(std::move(f))
		{	}

		ScopeExit(ScopeExit &&o)
			:_f(std::move(o._f))
		{	}

		~ScopeExit()
		{
			_f();
		}

		ScopeExit &operator=(ScopeExit &&o)
		{
			_f = std::move(o._f);
		}

	private:
		std::function<void()> _f;
	};

	template<class T>
	struct ScopeExit_DeleteContainer : ScopeExit
	{
		static void deleteContainer(T &container);
	public:
		ScopeExit_DeleteContainer(T &container)
			:ScopeExit(std::bind(&deleteContainer, container))
		{}
	};
}

#include <ScopeExit.hpp> 