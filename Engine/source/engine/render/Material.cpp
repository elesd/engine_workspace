#include <stdafx.h>
#include <engine/render/Material.h>

#include <engine/video/Shader.h>

namespace engine
{
	struct MaterialPrivate
	{
		Shader vertexShader;
		Shader fragmentShader;
		std::string name;
		MaterialPrivate(const std::string& name) : name(name) {}
	};

	Material::Material(const std::string& name)
		: _members(new MaterialPrivate(name))
	{

	}

	Material::Material(Material&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	Material& Material::operator=(Material&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	Material::~Material()
	{
		delete _members;
		_members = nullptr;
	}

	void Material::SetVertexShader(const Shader& shader)
	{
		_members->vertexShader = shader;
	}

	void Material::SetFragmentShader(const Shader& shader)
	{
		_members->fragmentShader = shader;
	}

	const Shader& Material::getVertexShader()
	{
		return _members->vertexShader;
	}

	const Shader& Material::getFragmentShader()
	{
		return _members->fragmentShader;
	}
}