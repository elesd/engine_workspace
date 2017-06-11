#pragma once

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

	struct GPUMemberTypeTraits
	{
		static bool isAttributeType(GPUMemberType type);
		static size_t getSize(GPUMemberType type);
	};
}