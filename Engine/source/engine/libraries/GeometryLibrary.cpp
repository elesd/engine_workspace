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

	}

	void GeometryLibrary::addGeometry(const std::string& name, const GeometryLibraryData<int32_t>& data)
	{
		std::unique_ptr<Geometry> geometry = _members->renderContext->createGeometry();
		geometry->setupVertexBuffer(data.getAttributeFormat(), data.getVerticies());
		geometry->setupIndexBuffer(data.getPrimitiveType(), data.getInicies());
		_members->geometries[name].reset(geometry.get());
		geometry.release();
	}

	std::unique_ptr<GeometryInstance> GeometryLibrary::findGeometry(const std::string& name)
	{
		auto it = _members->geometries.find(name);
		ASSERT(it != _members->geometries.end());

		std::unique_ptr<GeometryInstance> result(new GeometryInstance(it->second));
		return result;
	}
}