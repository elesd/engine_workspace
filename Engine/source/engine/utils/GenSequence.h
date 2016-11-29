#pragma once

namespace engine
{
	namespace utils
	{
		/**Base class for meta sequence*/
		template <int... Is>
		struct Index {};

		/**
		* Generate compile time sequence, like Index<5, 4, 3, 2, 1>.
		* It is really usefull for generate placeholders in compile time
		*/
		template <int N, int... Is>
		struct GenSequence: GenSequence < N - 1, N - 1, Is... > {};

		/**Final element*/
		template <int... Is>
		struct GenSequence<0, Is...>: Index < Is... >{};
	}
}