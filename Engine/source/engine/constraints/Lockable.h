#pragma once

#include <engine/utils/GuardedObject.h>

namespace engine
{
	template<class T>
	class Lockable
	{
	protected:
		Lockable() = default;
		~Lockable() = default;
	public:
		GuardedObject<T*> lock();
		GuardedObject<const T*> lock() const;
	private:
		mutable std::mutex _mutexForLock;
	};
}
#include <engine/constraints/Lockable.hpp>