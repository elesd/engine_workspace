#pragma once

namespace engine
{
	namespace utils
	{
		template <int... Is>
		struct Index {};

		template <int N, int... Is>
		struct GenSequence: GenSequence < N - 1, N - 1, Is... > {};

		template <int... Is>
		struct GenSequence<0, Is...>: Index < Is... >{};
	}
}