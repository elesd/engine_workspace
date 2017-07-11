#include <stdafx.h>
#include <engine/video/EffectCompiler.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/MaterialDescription.h>

#include <engine/video/Effect.h>
#include <engine/video/EffectCompilationData.h>
#include <engine/video/Driver.h>
#include <engine/video/Material.h>
#include <engine/video/ShaderCompiler.h>
#include <engine/video/ShaderCompileOptions.h>

namespace engine
{
	struct EffectCompilerPrivate
	{
		std::unique_ptr<ShaderCompiler> compiler;
		const Material* material = nullptr;
		Driver* driver = nullptr;
		EffectCompilerPrivate(const Material* material, Driver* driver, std::unique_ptr<ShaderCompiler>&& compiler)
			: compiler(std::move(compiler))
			, material(material)
			, driver(driver)
		{ }
	};

	EffectCompiler::EffectCompiler(const Material* material, Driver* driver, std::unique_ptr<ShaderCompiler>&& compiler)
		: _members(new EffectCompilerPrivate(material, driver, std::move(compiler)))
	{
		_members->compiler->init(_members->material->getDescription().getTechniqueMap());
	}

	EffectCompiler::~EffectCompiler()
	{
		delete _members;
		_members = nullptr;
	}


	std::unique_ptr<Effect> EffectCompiler::compileEffect(const std::string& techniqueName)
	{
		_members->compiler->compileShader(_members->material->getDescription().getVertexShader(), techniqueName);
		_members->compiler->compileShader(_members->material->getDescription().getFragmentShader(), techniqueName);
		std::unique_ptr<Effect> effect = std::make_unique<Effect>(_members->material, 
																  techniqueName, 
																  _members->material->getDescription().getVertexShader(), 
																  _members->material->getDescription().getFragmentShader());
		_members->driver->compileEffect(effect.get());
		return effect;
	}

}