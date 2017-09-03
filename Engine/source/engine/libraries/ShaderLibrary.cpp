#include <stdafx.h>
#include <engine/libraries/ShaderLibrary.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/libraries/ShaderInstance.h>

#include <engine/video/Shader.h>

namespace engine
{
	struct ShaderLibraryEntry
	{
		ShaderLibraryEntry() = default;
		ShaderLibraryEntry(ShaderLibraryEntry&& o)
			: label(o.label)
			, shader(std::move(o.shader))
		{ }

		ShaderLibraryEntry& operator=(ShaderLibraryEntry&& o)
		{
			label = o.label;
			shader = std::move(o.shader);
			return *this;
		}
		ShaderLibraryLabel label;
		std::shared_ptr<Shader> shader;
	};

	struct ShaderLibraryPrivate
	{
		std::map<ShaderType, std::vector<ShaderLibraryEntry>> entries;
	};

	ShaderLibrary::ShaderLibrary()
		: _members(new ShaderLibraryPrivate())
	{

	}

	ShaderLibrary::~ShaderLibrary()
	{
		delete _members;
		_members = nullptr;
	}

	void ShaderLibrary::addShader(const ShaderLibraryLabel& label)
	{
		std::shared_ptr<Shader> foundShader = findShader(label.type, label.name);
		if(foundShader == nullptr)
		{
			loadShader(label);
		}
	}

	std::unique_ptr<ShaderInstance> ShaderLibrary::getShader(ShaderType type, const std::string& name) const
	{
		std::shared_ptr<Shader> foundShader = findShader(type, name);
		ASSERT(foundShader);
		return std::unique_ptr<ShaderInstance>(new ShaderInstance(foundShader));
	}


	void ShaderLibrary::removeShader(Shader* shader)
	{
		auto it = _members->entries.find(shader->getShaderType());
		if(it != _members->entries.end())
		{
			std::vector<ShaderLibraryEntry>& entries = it->second;
			auto entryIt = std::remove_if(entries.begin(), entries.end(),
											  [shader](const ShaderLibraryEntry& entry)->bool { return entry.shader.get() == shader; });
			entries.erase(entryIt, entries.end());
		}
	}

	std::shared_ptr<Shader> ShaderLibrary::findShader(ShaderType type, const std::string& name) const
	{
		auto it = _members->entries.find(type);
		if(it == _members->entries.end())
		{
			return nullptr;
		}

		auto entryIt = std::find_if(it->second.begin(), it->second.end(),
									[name](const ShaderLibraryEntry& entry)->bool { return entry.shader->isInitialized() && entry.label.name == name; });
		return entryIt != it->second.end() ? entryIt->shader : nullptr;
	}

	bool ShaderLibrary::hasShader(ShaderType type, const std::string& name) const
	{
		return findShader(type, name) != nullptr;
	}

	void ShaderLibrary::update()
	{
		// TODO use borrow pointer to avoid check in every frame
	/*	for(auto& pair : _members->entries)
		{
			auto it = std::remove_if(pair.second.begin(), pair.second.end(), 
									 [](const ShaderLibraryEntry& e)->bool { return e.shader.unique(); });
			pair.second.erase(it, pair.second.end());
		}*/
	}

	void ShaderLibrary::loadShader(const ShaderLibraryLabel& label)
	{
		ShaderLibraryEntry entry;
		entry.label = label;
		entry.shader.reset(new Shader(label.type));
		bool success = entry.shader->init(label.path, label.mainFunction);
		ASSERT(success);
		_members->entries[label.type].push_back(std::move(entry));
	}


}