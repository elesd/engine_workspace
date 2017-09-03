#include <stdafx.h>
#include <engine/servicies/LibraryService.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/libraries/ShaderLibrary.h>
#include <engine/libraries/ShaderInstance.h>

namespace engine
{
	struct LibraryServicePrivate
	{
		ShaderLibrary* shaderLibrary = nullptr;
		std::mutex shaderLibraryMutex;
		explicit LibraryServicePrivate(ShaderLibrary* shaderLibrary)
			: shaderLibrary(shaderLibrary)
		{ }
	};

	LibraryService::LibraryService(ShaderLibrary* shaderLibrary)
		: _members(new LibraryServicePrivate(shaderLibrary))
	{

	}

	LibraryService::~LibraryService()
	{
		delete _members;
		_members = nullptr;
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
}