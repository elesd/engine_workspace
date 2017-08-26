#pragma once

namespace engine
{
	namespace common
	{
		template<typename T, typename U>
		typename std::unique_ptr<T> static_unique_ptr_cast(typename std::unique_ptr<U>&& ptr)
		{
			static_assert(std::is_convertible<T, U>::value);
			return std::unique_ptr<T>(ptr.release());
		}
	}
}