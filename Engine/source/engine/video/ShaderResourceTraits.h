#pragma once

#include <engine/video/GPUTypes.h>

namespace engine
{
	
	template<GPUMemberType Type>
	struct ShaderResourceTraits;

	template<>
	struct ShaderResourceTraits<GPUMemberType::Float>
	{
		using ValueType = float;
	};

	template<>
	struct ShaderResourceTraits<GPUMemberType::Vec2>
	{
		using ValueType = glm::vec2;
	};

	template<>
	struct ShaderResourceTraits<GPUMemberType::Vec3>
	{
		using ValueType = glm::vec3;
	};

	template<>
	struct ShaderResourceTraits<GPUMemberType::Vec4>
	{
		using ValueType = glm::vec4;
	};

	template<>
	struct ShaderResourceTraits<GPUMemberType::Mat3>
	{
		using ValueType = glm::mat3;
	};

	template<>
	struct ShaderResourceTraits<GPUMemberType::Mat4>
	{
		using ValueType = glm::mat4;
	};
}