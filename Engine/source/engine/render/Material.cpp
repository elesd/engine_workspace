#include <stdafx.h>
#include <engine/render/Material.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/Shader.h>
#include <engine/video/ShaderCompilationData.h>
#include <engine/video/ShaderCompileOptions.h>

namespace engine
{
	
	struct MaterialPrivate
	{
		std::unique_ptr<Shader> vertexShader;
		std::string vertexTechniqueName;
		std::string fragmentTechniqueName;
		std::unique_ptr<Shader> fragmentShader;
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

	void Material::setVertexShader(std::unique_ptr<Shader>&& shader, const std::string& techniqueName)
	{
		_members->vertexShader = std::move(shader);
		_members->vertexTechniqueName = techniqueName;
	}

	void Material::setFragmentShader(std::unique_ptr<Shader>&& shader, const std::string& techniqueName)
	{
		_members->fragmentShader = std::move(shader);
		_members->fragmentTechniqueName = techniqueName;
	}

	const Shader* Material::getVertexShader() const
	{
		return _members->vertexShader.get();
	}

	const Shader* Material::getFragmentShader() const
	{
		return _members->fragmentShader.get();
	}

	Shader* Material::getVertexShader() 
	{
		return _members->vertexShader.get();
	}

	Shader* Material::getFragmentShader()
	{
		return _members->fragmentShader.get();
	}

	void Material::setVertexShaderTechniqueName(const std::string& techniqueName)
	{
		_members->vertexTechniqueName = techniqueName;
	}

	void Material::setFragmentShaderTechniqueName(const std::string& techniqueName)
	{
		_members->fragmentTechniqueName = techniqueName;
	}

	const std::string& Material::getVertexShaderTechniqueName() const
	{
		return _members->vertexTechniqueName;
	}

	const std::string& Material::getFragmentShaderTechniqueName() const
	{
		return _members->fragmentTechniqueName;
	}
	
}