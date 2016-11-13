
#pragma once

namespace engine
{
	namespace utils
	{
		template<int>
		struct CustomPlaceholder
		{};
	}
}


namespace std
{
	template<int N>
	struct is_placeholder<engine::utils::CustomPlaceholder<N> >
		: integral_constant < int, N + 1 >
	{};
}