#include <stdafx.h>
#include <engine/video/GPUTypes.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	bool GPUMemberTypeInfo::isAttributeType(GPUMemberType type)
	{
		switch(type)
		{
			case GPUMemberType::Float: return GPUMemberTypeTraits<GPUMemberType::Float>::isAttributeType;
			case GPUMemberType::Vec2:  return GPUMemberTypeTraits<GPUMemberType::Vec2>::isAttributeType;
			case GPUMemberType::Vec3:  return GPUMemberTypeTraits<GPUMemberType::Vec3>::isAttributeType;
			case GPUMemberType::Vec4:  return GPUMemberTypeTraits<GPUMemberType::Vec4>::isAttributeType;
			case GPUMemberType::Mat3:  return GPUMemberTypeTraits<GPUMemberType::Mat3>::isAttributeType;
			case GPUMemberType::Mat4:  return GPUMemberTypeTraits<GPUMemberType::Mat4>::isAttributeType;
			case GPUMemberType::Undef:
			default:
				FAIL("Undefined GPU member type");
				return false;
				break;
		}
	}

	size_t GPUMemberTypeInfo::getSize(GPUMemberType type)
	{
		switch(type)
		{
			case GPUMemberType::Float: return GPUMemberTypeTraits<GPUMemberType::Float>::size;
			case GPUMemberType::Vec2:  return GPUMemberTypeTraits<GPUMemberType::Vec2>::size;
			case GPUMemberType::Vec3:  return GPUMemberTypeTraits<GPUMemberType::Vec3>::size;
			case GPUMemberType::Vec4:  return GPUMemberTypeTraits<GPUMemberType::Vec4>::size;
			case GPUMemberType::Mat3:  return GPUMemberTypeTraits<GPUMemberType::Mat3>::size;
			case GPUMemberType::Mat4:  return GPUMemberTypeTraits<GPUMemberType::Mat4>::size;
			case engine::GPUMemberType::Undef:
			default:
				FAIL("Undefined GPU member type");
				return 0;
				break;
		}
	}
}