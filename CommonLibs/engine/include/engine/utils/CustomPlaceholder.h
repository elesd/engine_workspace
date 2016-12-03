
#pragma once

namespace engine
{
	/** Custom amount of placeholder for funciton binding*/
	template<int>
	struct CustomPlaceholder
	{};
}


namespace std
{
	/** Template specialization*/
	template<int N>
	struct is_placeholder<engine::CustomPlaceholder<N> >
		: integral_constant < int, N + 1 >
	{};
}