#include <stdafx.h>
#include <engine/libraries/MaterialLibrary.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/Material.h>
#include <engine/video/MaterialDescription.h>

namespace engine
{
	struct MaterialLibraryEntry
	{
		engine::MaterialDescription description;
		std::unique_ptr<Material> material;
		MaterialLibraryEntry() = default;
		MaterialLibraryEntry(MaterialLibraryEntry&& o)
			: material(std::move(o.material))
			, description(std::move(o.description))
		{ }

		MaterialLibraryEntry& operator=(MaterialLibraryEntry&& o)
		{
			material = std::move(o.material);
			description = std::move(o.description);
			return *this;
		}
	};

	struct MaterialLibraryPrivate
	{
		std::string windowName = "";
		RenderContext* renderContext = nullptr;
		std::map<std::string, MaterialLibraryEntry> materials;
	};

	MaterialLibrary::MaterialLibrary()
		: _members(new MaterialLibraryPrivate())
	{

	}

	MaterialLibrary::~MaterialLibrary()
	{
		delete _members;
		_members = nullptr;
	}

	void MaterialLibrary::init(const std::string& windowName, RenderContext* renderContext)
	{
		_members->renderContext = renderContext;
		_members->windowName = windowName;
	}

	void MaterialLibrary::addMateria(const std::string& materialName, const MaterialDescription& description)
	{
		ASSERT(isInitialized());
		MaterialLibraryEntry entry;
		entry.description = description;
		entry.material.reset(new Material(materialName, description, _members->renderContext));
		// BUG: MSVC2014 insert doesn't work 
		_members->materials[materialName] = std::move(entry);
	}

	MaterialInstance* MaterialLibrary::findMaterial(const std::string& name)
	{
		return nullptr;
	}

	bool  MaterialLibrary::isInitialized() const
	{
		return _members->renderContext != nullptr;
	}
}