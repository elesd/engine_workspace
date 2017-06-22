#include <stdafx.h>
#include <engine/render/EffectCompiler.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/Effect.h>
#include <engine/render/MaterialDescription.h>

#include <engine/video/ShaderCompiler.h>
#include <engine/video/ShaderCompileOptions.h>

namespace engine
{
	struct EffectCompilerPrivate
	{
		std::unique_ptr<ShaderCompiler> compiler;
		MaterialDescription description;
		Driver* driver = nullptr;
		EffectCompilerPrivate(Driver* driver, std::unique_ptr<ShaderCompiler>&& compiler, const MaterialDescription& descriptor)
			: compiler(std::move(compiler))
			, description(descriptor)
			, driver(driver)
		{ }
	};

	EffectCompiler::EffectCompiler(Driver* driver, std::unique_ptr<ShaderCompiler>&& compiler, const MaterialDescription& descriptor)
		: _members(new EffectCompilerPrivate(driver, std::move(compiler), descriptor))
	{
		_members->compiler->init(_members->description.getTechniqueMap());
	}

	EffectCompiler::~EffectCompiler()
	{
		delete _members;
		_members = nullptr;
	}


	std::unique_ptr<Effect> EffectCompiler::compileEffect(const std::string& techniqueName)
	{
		_members->compiler->compileShader(_members->description.getVertexShader(), techniqueName);
		_members->compiler->compileShader(_members->description.getFragmentShader(), techniqueName);
		std::unique_ptr<Effect> effect = std::make_unique<Effect>(techniqueName, _members->description.getVertexShader(), _members->description.getFragmentShader());
		return effect;
	}

}