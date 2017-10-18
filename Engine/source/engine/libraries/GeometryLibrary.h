#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

#include <engine/libraries/GeometryLibraryData.h>

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

		void addGeometry(const std::string& name, const GeometryLibraryData<int32_t>& data);
		std::unique_ptr<GeometryInstance> findGeometry(const std::string& name);
	private:
		struct GeometryLibraryPrivate* _members = nullptr;
	};
}