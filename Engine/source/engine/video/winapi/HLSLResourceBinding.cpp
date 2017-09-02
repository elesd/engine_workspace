#include <stdafx.h>
#include <engine/video/winapi/HLSLResourceBinding.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/GPUTypes.h>
#include <engine/video/winapi/ConstantBufferObject.h>
#include <engine/video/winapi/DriverImpl.h>

#include <engine/video/Shader.h>

#if ENGINE_USE_WINAPI

namespace engine
{
	namespace winapi
	{
		struct HLSLResourceBindingPrivate
		{
			int32_t bufferId;
			std::vector<ShaderType> shaderTypes;
			HLSLResourceBindingPrivate(uint32_t bufferId, const std::vector<ShaderType>& shaderTypes)
				: bufferId(bufferId)
				, shaderTypes(shaderTypes)
			{ }
		};

		HLSLResourceBinding::HLSLResourceBinding(const std::vector<ShaderType>& shaderTypes)
			: ShaderResourceBinding()
			, _members(new HLSLResourceBindingPrivate(-1, shaderTypes))
		{

		}

		HLSLResourceBinding::HLSLResourceBinding(uint32_t bufferId, const std::vector<ShaderType>& shaderTypes)
			: ShaderResourceBinding()
			, _members(new HLSLResourceBindingPrivate(bufferId, shaderTypes))
		{
		}

		HLSLResourceBinding::HLSLResourceBinding(const HLSLResourceBinding& o)
			: ShaderResourceBinding()
			, _members(o._members ? new HLSLResourceBindingPrivate(*o._members) : nullptr)
		{
		}

		HLSLResourceBinding::HLSLResourceBinding(HLSLResourceBinding&& o)
			: ShaderResourceBinding()
			, _members(o._members)
		{
			o._members = nullptr;
		}

		HLSLResourceBinding::~HLSLResourceBinding() 
		{
			delete _members;
			_members = nullptr;
		}

		HLSLResourceBinding& HLSLResourceBinding::operator=(const HLSLResourceBinding& o)
		{
			delete _members;
			if(o._members)
			{
				_members = new HLSLResourceBindingPrivate(*o._members);
			}
			else
			{
				_members = nullptr;
			}
			return *this;
		}

		HLSLResourceBinding& HLSLResourceBinding::operator=(HLSLResourceBinding&& o)
		{
			delete _members;
			_members = o._members;
			o._members = nullptr;
			return *this;
		}

		uint32_t HLSLResourceBinding::getBufferId() const
		{
			return _members->bufferId;
		}

		std::vector<ShaderType> HLSLResourceBinding::getShaderTypes() const
		{
			return _members->shaderTypes;
		}

		bool HLSLResourceBinding::isBound() const
		{
			return _members->bufferId >= 0;
		}

	}
}

#endif
