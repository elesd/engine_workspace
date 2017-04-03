#pragma once

namespace engine
{
	template<class T>
	struct PIMPLMoveable
	{
		PIMPLMoveable() = default;
		PIMPLMoveable(PIMPLMoveable &&o)
		{
			static_cast<T*>(this)->_members = static_cast<T&&>(o)._members;
			static_cast<T&&>(o)._members = nullptr;
		}

		T& PIMPLMoveable::operator=(PIMPLMoveable &&o)
		{
			static_cast<T*>(this)->_members = static_cast<T&&>(o)._members;
			static_cast<T&&>(o)._members = nullptr;
			return *static_cast<T*>(this);
		}
	};
}