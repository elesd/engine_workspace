#include <stdafx.h>
#include <engine/render/MaterialDescription.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/ShaderCompileOptions.h>
#include <engine/video/Shader.h>

namespace engine
{
	struct MaterialDescriptionPrivate
	{
		std::map<std::string, ShaderCompileOptions> techniqueMap;
		ShaderVersion version;
		Shader* vertexShader = nullptr;
		Shader* fragmentShader = nullptr;
	};

	MaterialDescription::MaterialDescription()
		: _members(new MaterialDescriptionPrivate())
	{

	}

	MaterialDescription::~MaterialDescription()
	{
		delete _members;
		_members = nullptr;
	}

	MaterialDescription::MaterialDescription(const MaterialDescription& o)
		: _members(o._members ? new MaterialDescriptionPrivate(*o._members) : nullptr)
	{

	}

	MaterialDescription::MaterialDescription(MaterialDescription&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	MaterialDescription& MaterialDescription::operator=(const MaterialDescription& o)
	{
		delete _members;
		_members = o._members ? new MaterialDescriptionPrivate(*o._members) : nullptr;
		return *this;
	}

	MaterialDescription& MaterialDescription::operator=(MaterialDescription&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}


	void MaterialDescription::setShaderVersion(ShaderVersion version)
	{
		_members->version = version;
	}

	void MaterialDescription::addTechnique(const std::string& name, const ShaderCompileOptions& compileOptions)
	{
		ASSERT(_members->techniqueMap.find(name) == _members->techniqueMap.end());
		_members->techniqueMap.insert(std::make_pair(name, compileOptions));
	}

	void MaterialDescription::setVertexShader(Shader* vertexShader)
	{
		_members->vertexShader = vertexShader;
	}

	void MaterialDescription::setFragmentShader(Shader* fragmentShader)
	{
		_members->fragmentShader = fragmentShader;
	}

	ShaderVersion MaterialDescription::getShaderVersion() const
	{
		return _members->version;
	}

	Shader* MaterialDescription::getVertexShader() const
	{
		return _members->vertexShader;
	}

	Shader* MaterialDescription::getFragmentShader() const
	{
		return _members->fragmentShader;
	}

	ShaderCompileOptions MaterialDescription::getOption(const std::string& techniqueName) const
	{
		auto it = _members->techniqueMap.find(techniqueName);
		ASSERT(it != _members->techniqueMap.end());
		return it->second;
	}

	const std::map<std::string, ShaderCompileOptions>& MaterialDescription::getTechniqueMap() const
	{
		return _members->techniqueMap;
	}
}