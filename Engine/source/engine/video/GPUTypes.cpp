#include <stdafx.h>
#include <engine/video/GPUTypes.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	bool GPUMemberTypeTraits::isAttributeType(GPUMemberType type)
	{
		switch(type)
		{
			case engine::GPUMemberType::Float:
			case engine::GPUMemberType::Vec2:
			case engine::GPUMemberType::Vec3:
			case engine::GPUMemberType::Vec4:
				return true;
			case engine::GPUMemberType::Mat3:
			case engine::GPUMemberType::Mat4:
				return false;
				break;
			case engine::GPUMemberType::Undef:
			default:
				FAIL("Undefined GPU member type");
				return false;
				break;
		}
	}

	size_t GPUMemberTypeTraits::getSize(GPUMemberType type)
	{
		switch(type)
		{
			case engine::GPUMemberType::Float:
				return 4;
				break;
			case engine::GPUMemberType::Vec2:
				return 4 * 2;
				break;
			case engine::GPUMemberType::Vec3:
				return 4 * 3;
				break;
			case engine::GPUMemberType::Vec4:
				return 4 * 4;
				break;
			case engine::GPUMemberType::Mat3:
				return 4 * 3 * 3;
				break;
			case engine::GPUMemberType::Mat4:
				return 4 * 4 * 4;
				break;
			case engine::GPUMemberType::Undef:
			default:
				FAIL("Undefined GPU member type");
				return 0;
				break;
		}
	}
}