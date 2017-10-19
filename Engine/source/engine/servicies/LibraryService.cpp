#include <stdafx.h>
#include <engine/servicies/LibraryService.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/libraries/MaterialLibrary.h>
#include <engine/libraries/MaterialInstance.h>
#include <engine/libraries/GeometryLibrary.h>
#include <engine/libraries/GeometryInstance.h>
#include <engine/libraries/ShaderLibrary.h>
#include <engine/libraries/ShaderInstance.h>

#include <engine/servicies/SynchronizerService.h>

namespace engine
{
	struct LibraryServicePrivate
	{
		std::unique_ptr<ShaderLibrary> shaderLibrary;
		std::unique_ptr<GeometryLibrary> geometryLibrary;
		std::unique_ptr<MaterialLibrary> materialLibrary;

		std::mutex shaderLibraryMutex;
		std::mutex geometryLibraryMutex;
		std::mutex materialLibraryMutex;
		LibraryServicePrivate()
		{ }
	};

	LibraryService::LibraryService(RenderContext* renderContext)
		: _members(new LibraryServicePrivate())
	{
		_members->shaderLibrary.reset(new ShaderLibrary());
		_members->geometryLibrary.reset(new GeometryLibrary(renderContext));
		_members->materialLibrary.reset(new MaterialLibrary());
	}

	LibraryService::~LibraryService()
	{
		delete _members;
		_members = nullptr;
	}

	void LibraryService::setupSynchronizer(SynchronizerService* synchronizer)
	{
		synchronizer->setupMaterialLibrary(_members->materialLibrary.get());
	}

	std::unique_ptr<ShaderInstance> LibraryService::getShader(ShaderType type, const std::string& shaderName)
	{
		std::lock_guard<std::mutex> lock(_members->shaderLibraryMutex);
		return _members->shaderLibrary->getShader(type, shaderName);
	}

	void LibraryService::addShader(const ShaderLibraryLabel& label)
	{
		std::lock_guard<std::mutex> lock(_members->shaderLibraryMutex);
		_members->shaderLibrary->addShader(label);
	}

	bool LibraryService::hasShader(ShaderType type, const std::string& shaderName)
	{
		std::lock_guard<std::mutex> lock(_members->shaderLibraryMutex);
		return _members->shaderLibrary->hasShader(type, shaderName);
	}

	bool LibraryService::hasGeometry(const std::string& name)
	{
		std::lock_guard<std::mutex> lock(_members->geometryLibraryMutex);
		return _members->geometryLibrary->hasGeometry(name);
	}

	std::unique_ptr<GeometryInstance> LibraryService::getGeometry(const std::string& name)
	{
		std::lock_guard<std::mutex> lock(_members->geometryLibraryMutex);
		return _members->geometryLibrary->getGeometry(name);
	}

	void LibraryService::addMaterial(const std::string& materialName, const MaterialDescription& description)
	{
		std::lock_guard<std::mutex> lock(_members->materialLibraryMutex);
		_members->materialLibrary->addMaterial(materialName, description);
	}
	
	bool LibraryService::hasMaterial(const std::string& materialName)
	{
		std::lock_guard<std::mutex> lock(_members->materialLibraryMutex);
		return _members->materialLibrary->hasMaterial(materialName);
	}

	std::unique_ptr<MaterialInstance> LibraryService::getMaterial(const std::string& name)
	{
		std::lock_guard<std::mutex> lock(_members->materialLibraryMutex);
		return _members->materialLibrary->getMaterial(name);
	}
	
	GuardedObject<GeometryLibrary*> LibraryService::getGeometryLibrary()
	{
		GuardedObject<GeometryLibrary*> result(std::unique_lock<std::mutex>(_members->geometryLibraryMutex), _members->geometryLibrary.get());
		return result;
	}
}