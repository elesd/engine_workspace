#include <stdafx.h>
#include <engine/video/ShaderResourceBindingData.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/Shader.h>

#include <boost/optional/optional.hpp>

namespace engine
{
	struct ShaderResourceBindingDataPrivate
	{
		boost::optional<uint32_t> layout;
		std::vector<ShaderType> shaderTypes;
		ShaderResourceBindingDataPrivate(const std::vector<ShaderType>& shaders)
			: shaderTypes(shaders)
		{}
		explicit ShaderResourceBindingDataPrivate(uint32_t layout, const std::vector<ShaderType>& shaders)
			: layout(layout)
			, shaderTypes(shaders)
		{}
	};

	ShaderResourceBindingData::ShaderResourceBindingData(const std::vector<ShaderType>& shaders)
		: _members(new ShaderResourceBindingDataPrivate(shaders))
	{

	}

	ShaderResourceBindingData::ShaderResourceBindingData(uint32_t layout, const std::vector<ShaderType>& shaders)
		: _members(new ShaderResourceBindingDataPrivate(layout, shaders))
	{

	}

	ShaderResourceBindingData::~ShaderResourceBindingData() 
	{
		delete _members;
	}

	ShaderResourceBindingData::ShaderResourceBindingData(const ShaderResourceBindingData& o)
		: _members(o._members ? new ShaderResourceBindingDataPrivate(*o._members) : nullptr)
	{

	}

	ShaderResourceBindingData::ShaderResourceBindingData(ShaderResourceBindingData&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	ShaderResourceBindingData& ShaderResourceBindingData::operator=(const ShaderResourceBindingData& o)
	{
		delete _members;
		_members = o._members ? new ShaderResourceBindingDataPrivate(*o._members) : nullptr;
		return *this;
	}

	ShaderResourceBindingData& ShaderResourceBindingData::operator=(ShaderResourceBindingData&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	bool ShaderResourceBindingData::hasLayout() const
	{
		return _members->layout.is_initialized();
	}

	uint32_t ShaderResourceBindingData::getLayout() const
	{
		return _members->layout.get();
	}

	const std::vector<ShaderType>& ShaderResourceBindingData::getShaderTypes() const
	{
		return _members->shaderTypes;
	}


}