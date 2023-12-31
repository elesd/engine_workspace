#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

#include <engine/libraries/GeometryLibraryData.h>

#include <engine/video/Geometry.h>
namespace engine
{
	class GeometryInstance;
	class RenderContext;

	class GeometryLibrary final
		: private NonCopyable
		, private NonMoveable
	{
	public:
		explicit GeometryLibrary(RenderContext* renderContext);
		~GeometryLibrary();

		template<typename T>
		void addGeometry(const std::string& name, const GeometryLibraryData<T>& data);
		bool hasGeometry(const std::string& name) const;
		std::unique_ptr<GeometryInstance> getGeometry(const std::string& name);
    private:
        RenderContext* getRenderContext();
        void storeGeometry(const std::string& name, std::unique_ptr<Geometry>&& geometry);
	private:
		struct GeometryLibraryPrivate* _members = nullptr;
	};

	template<typename T>
	void GeometryLibrary::addGeometry(const std::string& name, const GeometryLibraryData<T>& data)
	{
		std::unique_ptr<Geometry> geometry = getRenderContext()->createGeometry();
		geometry->setupVertexBuffer(data.getAttributeFormat(), data.getVerticies());
		geometry->setupIndexBuffer(data.getPrimitiveType(), data.getInicies());
        storeGeometry(name, std::move(geometry));
	}
}
