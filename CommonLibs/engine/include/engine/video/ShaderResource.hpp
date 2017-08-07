
namespace engine
{

	template<GPUMemberType Type>
	ShaderResource<Type>::ShaderResource(ShaderResourceHandler *resourceHandler, const ShaderResourceDescription& description)
		: _resourceHandler(resourceHandler)
		, _description(description)
	{

	}

	template<GPUMemberType Type>
	ShaderResource<Type>::ShaderResource(ShaderResource&& o)
		: _resourceHandler(o._resourceHandler)
		, _changed(o._changed)
		, _value(std::move(o._value))
		, _description(std::move(o._description))
	{
		o._resourceHandler = nullptr;
	}

	template<GPUMemberType Type>
	ShaderResource<Type>& ShaderResource<Type>::operator=(ShaderResource<Type>&& o)
	{
		_resourceHandler = o._resourceHandler;
		o._resourceHandler = nullptr;
		_changed = o._changed;
		_value = std::move(o._value);
		_description = std::move(o._description);
		return *this;
	}

	template<GPUMemberType Type>
	ShaderResource<Type>::~ShaderResource()
	{

	}

	template<GPUMemberType Type>
	const typename ShaderResourceTraits<Type>::ValueType& ShaderResource<Type>::getValue() const
	{
		return _value;
	}

	template<GPUMemberType Type>
	void ShaderResource<Type>::setValue(const typename ShaderResourceTraits<Type>::ValueType& value)
	{
		_value = value;
		_changed = true;
	}

	template<GPUMemberType Type>
	void ShaderResource<Type>::commitChanges()
	{
		ASSERT(_resourceHandler != nullptr);
		if(_changed)
		{
			_resourceHandler->commitValue(_description, _value);
			_changed = false;
		}
	}
}