#pragma once
#include <glm/glm.hpp>

namespace engine
{
	using ScreenSpacePosition = glm::tvec2<int32_t>;
	using Color4 = glm::tvec4<int32_t>;

	enum class PrimitiveType
	{
		Triangle,
		Num
	};
}
