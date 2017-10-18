#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

#include <engine/libraries/GeometryLibrary.h>
#include <engine/libraries/GeometryLibraryData.h>

#include <engine/utils/GuardedObject.h>
namespace engine
{
	class ShaderInstance;
	class GeometryInstance;
	class MeshInstance;
	struct ShaderLibraryLabel;

	enum class ShaderType;

	class LibraryService final
		: private NonCopyable
		, private NonMoveable
	{
		friend class Application;
	private:
		explicit LibraryService(RenderContext* renderContext);
	public:
		~LibraryService();

		std::unique_ptr<ShaderInstance> getShader(ShaderType type, const std::string& shaderName);
		void addShader(const ShaderLibraryLabel& label);
		bool hasShader(ShaderType type, const std::string& shaderName);

		template<typename T>
		void addGeometry(const std::string& name, const GeometryLibraryData<T>& data);
		bool hasGeometry(const std::string& name);
		std::unique_ptr<GeometryInstance> getGeometry(const std::string& name);

		void addMaterial(const std::string& materialName, const MaterialDescription& description);
		bool hasMaterial(const std::string& materialName);
		std::unique_ptr<MaterialInstance> getMaterial(const std::string& name);
	protected:
		GuardedObject<GeometryLibrary*> getGeometryLibrary();
	private:
		struct LibraryServicePrivate* _members = nullptr;
	};

	template<typename T>
	void LibraryService::addGeometry(const std::string& name, const GeometryLibraryData<T>& data)
	{
		getGeometryLibrary()->addGeometry(name, data);
	}

}