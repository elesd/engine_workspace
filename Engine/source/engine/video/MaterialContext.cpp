#include <stdafx.h>
#include <engine/video/MaterialContext.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/Driver.h>

namespace engine
{
	struct MaterialContextPrivate
	{
		const Material* material = nullptr;
		Driver* driver = nullptr;
		explicit MaterialContextPrivate(const Material* material, Driver* driver)
			: material(material)
			, driver(driver)
		{ }
	};

	MaterialContext::MaterialContext(const Material* material, Driver* driver)
		: _members(new MaterialContextPrivate(material, driver))
	{

	}

	MaterialContext::~MaterialContext()
	{
		delete _members;
		_members = nullptr;
	}

	void MaterialContext::bind() const
	{
		_members->driver->setMaterialContext(this);
	}

	void MaterialContext::unbind() const
	{
		_members->driver->resetMaterialContext();
	}

	const Material* MaterialContext::getMaterial() const
	{
		return _members->material;
	}
}