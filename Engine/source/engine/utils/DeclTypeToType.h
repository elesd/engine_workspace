#pragma once

namespace engine
{
	namespace utils
	{
		/**Small hack for identity*/
		template<class T>
		struct DeclTypeToType
		{
			using Value = T;

		};
	}
}