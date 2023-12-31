
#include <algorithm>

#include <engine/utils/Math.h>

namespace engine
{

	template<GPUMemberType Type>
	GlobalShaderResource<Type>::GlobalShaderResource(const ShaderResourceDescription& desc)
		: _description(desc)
	{

	}

	template<GPUMemberType Type>
	void GlobalShaderResource<Type>::attachResource(ShaderResource<Type> *resource)
	{
		ASSERT(std::find(_attachedResources.begin(), _attachedResources.end(), resource) == _attachedResources.end());
		_attachedResources.push_back(resource);
		resource->setValue(_value);
	}

	template<GPUMemberType Type>
	void GlobalShaderResource<Type>::detachResource(ShaderResource<Type> *resource)
	{
		ASSERT(!_attachedResources.empty());
		auto it = std::remove(_attachedResources.begin(), _attachedResources.end(), resource);
		ASSERT(it != _attachedResources.end());
		_attachedResources.erase(it, _attachedResources.end());
	}

	template<GPUMemberType Type>
	bool GlobalShaderResource<Type>::hasAttachement() const
	{
		return _attachedResources.empty() == false;
	}

	template<GPUMemberType Type>
	void GlobalShaderResource<Type>::setValue(const typename GPUMemberTypeTraits<Type>::ValueType& v)
	{
		if(math::notEquals(_value, v, glm::epsilon<float>()))
		{
			_dirty = true;
			_value = v;
			for(ShaderResource<Type>* resource : _attachedResources)
			{
				resource->setValue(_value);
			}
		}
	}

	template<GPUMemberType Type>
	const typename GPUMemberTypeTraits<Type>::ValueType& GlobalShaderResource<Type>::getValue() const
	{
		return _value;
	}

	template<GPUMemberType Type>
	const std::string& GlobalShaderResource<Type>::getName() const
	{
		return _description.getName();
	}

	template<GPUMemberType Type>
	const ShaderResourceDescription& GlobalShaderResource<Type>::getDescription() const
	{
		return _description;
	}

	template<GPUMemberType Type>
	void GlobalShaderResource<Type>::cleanUpDirtyFlag() const
	{
		_dirty = false;
	}

	template<GPUMemberType Type>
	bool GlobalShaderResource<Type>::isDirty() const
	{
		return _dirty;
	}

}