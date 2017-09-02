#include <stdafx.h>
#include <engine/video/EffectCompiler.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/MaterialDescription.h>

#include <engine/video/Effect.h>
#include <engine/video/EffectDescription.h>
#include <engine/video/EffectCompilationData.h>
#include <engine/video/Driver.h>
#include <engine/video/Material.h>
#include <engine/video/Shader.h>
#include <engine/video/ShaderCompiler.h>
#include <engine/video/ShaderCompileOptions.h>
#include <engine/video/ShaderResourceBinding.h>
#include <engine/video/ShaderResourceBindingData.h>
#include <engine/video/ShaderResourceDescription.h>
#include <engine/video/ShaderResourceStorage.h>

namespace engine
{
	struct EffectCompilerPrivate
	{
		std::unique_ptr<ShaderCompiler> compiler;
		Material* material = nullptr;
		Driver* driver = nullptr;
		EffectCompilerPrivate(Material* material, Driver* driver, std::unique_ptr<ShaderCompiler>&& compiler)
			: compiler(std::move(compiler))
			, material(material)
			, driver(driver)
		{ }
	};

	EffectCompiler::EffectCompiler(Material* material, Driver* driver, std::unique_ptr<ShaderCompiler>&& compiler)
		: _members(new EffectCompilerPrivate(material, driver, std::move(compiler)))
	{
		std::map<std::string, ShaderCompileOptions> techniques;
		for(const auto& pair : _members->material->getDescription().getEffectMap())
		{
			techniques.insert(std::make_pair(pair.first, pair.second.getOptions()));
		}
		_members->compiler->init(techniques);
	}

	EffectCompiler::~EffectCompiler()
	{
		delete _members;
		_members = nullptr;
	}


	std::unique_ptr<Effect> EffectCompiler::compileEffect(const std::string& techniqueName, GlobalShaderResourceStorage* globalResourceStorage)
	{
		_members->compiler->compileShader(_members->material->getDescription().getVertexShader(), techniqueName);
		_members->compiler->compileShader(_members->material->getDescription().getFragmentShader(), techniqueName);
		const std::vector<ShaderResourceDescription>& effectParameters = _members->material->getDescription().getEffectDescription(techniqueName).getParameters();
		std::unique_ptr<ShaderResourceStorage> resourceStorage = _members->driver->createResourceStorage(effectParameters, globalResourceStorage);
		std::unique_ptr<Effect> effect = std::make_unique<Effect>(_members->material, 
																  techniqueName, 
																  _members->material->getDescription().getVertexShader(), 
																  _members->material->getDescription().getFragmentShader(),
																  std::move(resourceStorage));
		_members->driver->compileEffect(effect.get());
		if(effect->isCompiled())
		{
			bindResources(effect.get());
		}
		else
		{
			
			FAIL("Effect compilation failed!");
		}
		return effect;
	}

	void EffectCompiler::bindResources(Effect* effect) const
	{
		ShaderResourceStorage* resources = effect->getResources();
		const std::vector<ShaderResourceDescription>& descriptions = resources->collectDescriptions();
		std::vector<std::pair<ShaderResourceDescription, std::unique_ptr<ShaderResourceBinding>>> bindings;
		for(const ShaderResourceDescription& desc : descriptions)
		{
			std::unique_ptr<ShaderResourceBinding> binding = _members->driver->bindResource(desc, effect);
			if(binding->isBound())
			{
				bindings.emplace_back(desc, std::move(binding));
			}
		}
		resources->setResourceBinding(std::move(bindings));
	}

}
