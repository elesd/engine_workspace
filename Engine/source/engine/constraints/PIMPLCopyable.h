#pragma once

namespace engine
{
	template<class T>
	struct PIMPLCopyable
	{
		PIMPLCopyable() = default;
		PIMPLCopyable(const PIMPLCopyable &o)
		{
			static_cast<T*>(this)->_members = new std::remove_ptr(decltype(static_cast<T*>(this)->_members));
			*static_cast<T*>(this)->_members = static_cast<T&>(o)._members;
		}

		T& PIMPLCopyable::operator=(const PIMPLCopyable &o)
		{
			delete static_cast<T*>(this)->_members;
			static_cast<T*>(this)->_members = new std::remove_ptr(decltype(static_cast<T*>(this)->_members));
			*static_cast<T*>(this)->_members = static_cast<T&>(o)._members;
			return *static_cast<T*>(this);
		}
	};
}