#include <stdafx.h>
#include <engine/libraries/GeometryLibrary.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/libraries/GeometryInstance.h>

#include <engine/render/RenderContext.h>

#include <engine/video/Geometry.h>

namespace engine
{
	struct GeometryLibraryPrivate
	{
		RenderContext* renderContext;
		// TODO replace shared_ptr
		std::map<std::string, std::shared_ptr<Geometry>> geometries;
		explicit GeometryLibraryPrivate(RenderContext* renderContext)
			: renderContext(renderContext)
		{ }
	};

	GeometryLibrary::GeometryLibrary(RenderContext* renderContext)
		: _members(new GeometryLibraryPrivate(renderContext))
	{

	}

	GeometryLibrary::~GeometryLibrary()
	{
		delete _members;
		_members = nullptr;
	}

	bool GeometryLibrary::hasGeometry(const std::string& name) const
	{
		auto it = _members->geometries.find(name);
		return it != _members->geometries.end();
	}

	std::unique_ptr<GeometryInstance> GeometryLibrary::getGeometry(const std::string& name)
	{
		auto it = _members->geometries.find(name);
		ASSERT(it != _members->geometries.end());

		std::unique_ptr<GeometryInstance> result(new GeometryInstance(it->second));
		return result;
	}
}