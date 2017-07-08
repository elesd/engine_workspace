#include <stdafx.h>
#include <engine/video/MaterialContext.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	struct MaterialContextPrivate
	{
		const Material* material = nullptr;
		explicit MaterialContextPrivate(const Material* material)
			: material(material)
		{ }
	};

	MaterialContext::MaterialContext(const Material* material)
		: _members(new MaterialContextPrivate(material))
	{

	}

	MaterialContext::~MaterialContext()
	{
		delete _members;
		_members = nullptr;
	}

	const Material* MaterialContext::getMaterial() const
	{
		return _members->material;
	}
}