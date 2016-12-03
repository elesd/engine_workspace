#pragma once

namespace engine
{
	/**Small hack for identity*/
	template<class T>
	struct DeclTypeToType
	{
		using Value = T;

	};
}