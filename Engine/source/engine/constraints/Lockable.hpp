// include For IDE
#include <engine/constraints/Lockable.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	template<class T>
	GuardedObject<T*> Lockable<T>::lock()
	{
		return GuardedObject<T*>(std::unique_lock<std::mutex>(_mutexForLock), static_cast<T*>(this));
	}

	template<class T>
	GuardedObject<const T*> Lockable<T>::lock() const
	{
		return GuardedObject<const T*>(std::unique_lock<std::mutex>(_mutexForLock), static_cast<const T*>(this));
	}
}