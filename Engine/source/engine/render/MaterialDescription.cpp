#include <stdafx.h>
#include <engine/render/MaterialDescription.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/Material.h>

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
		explicit MaterialDescriptionPrivate(ShaderVersion version)
			: version(version)
		{ }
	};

	MaterialDescription::MaterialDescription(ShaderVersion version)
		: _members(new MaterialDescriptionPrivate(version))
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

	void MaterialDescription::addTechnique(const std::string& name, const ShaderCompileOptions& compileOptions)
	{
		ASSERT(_members->techniqueMap.find(name) == _members->techniqueMap.end());
		_members->techniqueMap.insert(std::make_pair(name, compileOptions));
	}

	void MaterialDescription::setDefaultTechnique(const ShaderCompileOptions& compileOptions)
	{
		_members->techniqueMap.insert(std::make_pair(Material::defaultEffectName, compileOptions));
	}

	void MaterialDescription::setVertexShader(Shader* vertexShader)
	{
		_members->vertexShader = vertexShader;
	}

	void MaterialDescription::setFragmentShader(Shader* fragmentShader)
	{
		_members->fragmentShader = fragmentShader;
	}

	ShaderCompileOptions MaterialDescription::createEmptyOptions() const
	{
		return ShaderCompileOptions(_members->version);
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

	const ShaderCompileOptions&  MaterialDescription::getOptions(const std::string& techniqueName) const
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