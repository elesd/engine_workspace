#pragma once

#include <glm/glm.hpp>

namespace engine
{
	enum class GPUMemberType
	{
		Undef,
		Float,
		Vec2,
		Vec3,
		Vec4,
		Mat3,
		Mat4
	};

	struct GPUMemberTypeInfo
	{
		static bool isAttributeType(GPUMemberType type);
		static size_t getSize(GPUMemberType type);
	};

	template<GPUMemberType type>
	struct GPUMemberTypeTraits;
	
	template<>
	struct GPUMemberTypeTraits<GPUMemberType::Float>
	{
		using ValueType = float;
		static const bool isAttributeType = true;
		static const size_t size = sizeof(ValueType);
	};

	template<>
	struct GPUMemberTypeTraits<GPUMemberType::Vec2>
	{
		using ValueType = glm::vec2;
		static const bool isAttributeType = true;
		static const size_t size = sizeof(ValueType);
	};

	template<>
	struct GPUMemberTypeTraits<GPUMemberType::Vec3>
	{
		using ValueType = glm::vec3;
		static const bool isAttributeType = true;
		static const size_t size = sizeof(ValueType);
	};

	template<>
	struct GPUMemberTypeTraits<GPUMemberType::Vec4>
	{
		using ValueType = glm::vec4;
		static const bool isAttributeType = true;
		static const size_t size = sizeof(ValueType);
	};

	template<>
	struct GPUMemberTypeTraits<GPUMemberType::Mat3>
	{
		using ValueType = glm::mat3;
		static const bool isAttributeType = false;
		static const size_t size = sizeof(ValueType);
	};

	template<>
	struct GPUMemberTypeTraits<GPUMemberType::Mat4>
	{
		using ValueType = glm::mat4;
		static const bool isAttributeType = false;
		static const size_t size = sizeof(ValueType);
	};

}