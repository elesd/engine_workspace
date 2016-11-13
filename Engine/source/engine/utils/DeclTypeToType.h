#pragma once

namespace engine
{
	namespace utils
	{
		template<class T>
		struct DeclTypeToType
		{
			using Value = T;

		};
	}
}