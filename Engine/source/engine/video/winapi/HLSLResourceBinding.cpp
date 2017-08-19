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
			uint32_t bufferId;
			std::vector<ShaderType> shaderTypes;
			HLSLResourceBindingPrivate(uint32_t bufferId, const std::vector<ShaderType>& shaderTypes)
				: bufferId(bufferId)
				, shaderTypes(shaderTypes)
			{ }
		};

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

		std::unique_ptr<ShaderResourceBinding> HLSLResourceBinding::cloneImpl() const
		{
			std::unique_ptr<ShaderResourceBinding> result(new HLSLResourceBinding(*this));
			return result;
		}

	}
}

#endif
