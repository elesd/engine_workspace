#pragma once
#include <glm/glm.hpp>

namespace engine
{
	using glm::vec4;
	using glm::vec3;
	using glm::vec2;
	using glm::mat3;
	using glm::mat4;
	using glm::quat;

	using ScreenSpacePosition = glm::tvec2<int32_t>;
	using Color4 = glm::tvec4<int32_t>;
	
	struct TNBFrame
	{
		vec3 tangent;
		vec3 normal;
		vec3 binormal;
		TNBFrame() = default;
		TNBFrame(const vec3& tangent, const vec3& normal, const vec3& binormal)
			: tangent(tangent)
			, normal(normal)
			, binormal(binormal)
		{ }
	};

	enum class PrimitiveType
	{
		Triangle,
		Num
	};
}
