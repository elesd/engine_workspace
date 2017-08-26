#pragma once
#include <glm/glm.hpp>

namespace engine
{
	using glm::vec4;
	using glm::vec3;
	using glm::mat3;
	using glm::mat4;
	using glm::quat;

	using ScreenSpacePosition = glm::tvec2<int32_t>;
	using Color4 = glm::tvec4<int32_t>;


	enum class PrimitiveType
	{
		Triangle,
		Num
	};
}
