#include <stdafx.h>
#include <engine/video/ShaderCompileOptions.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/AttributeFormat.h>

namespace engine
{
	struct ShaderCompileOptionsPrivate
	{
		ShaderVersion version;
		std::vector<std::string> defines;
		std::vector<ShaderCompileFlag> flags;

		ShaderCompileOptionsPrivate(ShaderVersion version)
			: version(version)
		{ }
	};

	ShaderCompileOptions::ShaderCompileOptions()
		: _members(nullptr)
	{

	}


	ShaderCompileOptions::ShaderCompileOptions(ShaderVersion version)
		: _members(new ShaderCompileOptionsPrivate(version))
	{

	}

	ShaderCompileOptions::~ShaderCompileOptions()
	{
		delete _members;
		_members = nullptr;
	}

	ShaderCompileOptions::ShaderCompileOptions(const ShaderCompileOptions& o)
		: _members(o._members ? new ShaderCompileOptionsPrivate(*o._members) : nullptr)
	{

	}

	ShaderCompileOptions::ShaderCompileOptions(ShaderCompileOptions&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	ShaderCompileOptions& ShaderCompileOptions::operator=(const ShaderCompileOptions& o)
	{
		delete _members;
		_members = o._members ? new ShaderCompileOptionsPrivate(*o._members) : nullptr;
		return *this;
	}

	ShaderCompileOptions& ShaderCompileOptions::operator=(ShaderCompileOptions&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	bool ShaderCompileOptions::operator==(const ShaderCompileOptions& o) const
	{
		return _members->defines == o._members->defines
			&& _members->flags == o._members->flags
			&& _members->version == o._members->version;
	}

	void ShaderCompileOptions::addDefine(const std::string& define)
	{
		if(!hasDefine(define))
		{
			_members->defines.push_back(define);
		}
	}

	bool ShaderCompileOptions::hasDefine(const std::string& define) const
	{
		auto it = std::find(_members->defines.begin(), _members->defines.end(), define);
		return it != _members->defines.end();
	}

	void ShaderCompileOptions::removeDefine(const std::string& definition)
	{
		auto it = std::remove(_members->defines.begin(), _members->defines.end(), definition);
		_members->defines.erase(it, _members->defines.end());
	}

	const std::vector<std::string>& ShaderCompileOptions::getDefines() const
	{
		return _members->defines;
	}

	void ShaderCompileOptions::addFlag(ShaderCompileFlag flag)
	{
		if(!hasFlag(flag))
		{
			_members->flags.push_back(flag);
		}
	}
	bool ShaderCompileOptions::hasFlag(ShaderCompileFlag flag) const
	{
		auto it = std::find(_members->flags.begin(), _members->flags.end(), flag);
		return it != _members->flags.end();
	}

	void ShaderCompileOptions::removeFlag(ShaderCompileFlag flag)
	{
		auto it = std::remove(_members->flags.begin(), _members->flags.end(), flag);
		_members->flags.erase(it, _members->flags.end());
	}

	const std::vector<ShaderCompileFlag>& ShaderCompileOptions::getFlags() const
	{
		return _members->flags;
	}

	ShaderVersion ShaderCompileOptions::getVersion() const
	{
		return _members->version;
	}

}