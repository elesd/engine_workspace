#include <stdafx.h>
#include <engine/video/MaterialDescription.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/Material.h>

#include <engine/video/AttributeFormat.h>
#include <engine/video/EffectDescription.h>
#include <engine/video/ShaderCompileOptions.h>
#include <engine/video/Shader.h>
#include <engine/video/ShaderResourceDescription.h>

namespace engine
{
	struct MaterialDescriptionPrivate
	{
		std::map<std::string, EffectDescription> effectMap;
		std::vector<ShaderResourceDescription> resourceDescriptions;
		ShaderVersion version;
		AttributeFormat attributeFormat;
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

	void MaterialDescription::addEffect(const EffectDescription& description)
	{
		ASSERT(_members->effectMap.find(description.getName()) == _members->effectMap.end());
		_members->effectMap.insert(std::make_pair(description.getName(), description));
	}

	void MaterialDescription::setAttributeFormat(const AttributeFormat& attributeFormat)
	{
		_members->attributeFormat = attributeFormat;
	}

	void MaterialDescription::setDefaultEffect(const EffectDescription& description)
	{
		_members->effectMap.insert(std::make_pair(Material::defaultEffectName, description));
	}

	void MaterialDescription::setVertexShader(Shader* vertexShader)
	{
		_members->vertexShader = vertexShader;
	}

	void MaterialDescription::setFragmentShader(Shader* fragmentShader)
	{
		_members->fragmentShader = fragmentShader;
	}

	void MaterialDescription::addParameter(const ShaderResourceDescription &description)
	{
		_members->resourceDescriptions.push_back(description);
	}

	const std::vector<ShaderResourceDescription>& MaterialDescription::getParameters() const
	{
		return _members->resourceDescriptions;
	}

	EffectDescription MaterialDescription::createEffectDescription(const std::string& name) const
	{
		ShaderCompileOptions options = ShaderCompileOptions(_members->version);
		EffectDescription result(name, options);
		return result;
	}

	const AttributeFormat& MaterialDescription::getAttributeFormat() const
	{
		return _members->attributeFormat;
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

	const EffectDescription&  MaterialDescription::getEffectDescription(const std::string& techniqueName) const
	{
		auto it = _members->effectMap.find(techniqueName);
		ASSERT(it != _members->effectMap.end());
		return it->second;
	}

	const std::map<std::string, EffectDescription>& MaterialDescription::getEffectMap() const
	{
		return _members->effectMap;
	}
}