#include <stdafx.h>
#include <engine/video/Material.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/libraries/EffectInstance.h>
#include <engine/libraries/MaterialInstance.h>

#include <engine/video/EffectCompiler.h>
#include <engine/video/Effect.h>
#include <engine/video/MaterialDescription.h>
#include <engine/render/RenderContext.h>

#include <engine/video/AttributeFormat.h>
#include <engine/video/GlobalShaderResourceStorage.h>
#include <engine/video/Shader.h>
#include <engine/video/ShaderCompilationData.h>
#include <engine/video/ShaderCompileOptions.h>
#include <engine/video/VertexBuffer.h>

namespace engine
{
	
	struct MaterialPrivate
	{
		std::unique_ptr<EffectCompiler> effectCompiler;
		// TODO Replace shared_ptr
		std::map<std::string, std::shared_ptr<Effect>> effectCache;
		std::string name;
		MaterialDescription description;
		RenderContext* renderContext;

		MaterialPrivate(const std::string& name, const MaterialDescription& description, RenderContext* renderContext)
			: name(name) 
			, description(description)
			, renderContext(renderContext)
		{}
	};

	const std::string Material::defaultEffectName = "Default";

	Material::Material(const std::string& name, const MaterialDescription& description, RenderContext* renderContext)
		: _members(new MaterialPrivate(name, description, renderContext))
	{
		_members->effectCompiler = renderContext->createEffectCompiler(this);
		compileEffect(defaultEffectName);
	}

	Material::Material(Material&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	Material& Material::operator=(Material&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	Material::~Material()
	{
		delete _members;
		_members = nullptr;
	}

	Effect* Material::compileEffect(const std::string& name)
	{
		std::unique_ptr<Effect> effect = _members->effectCompiler->compileEffect(name, _members->renderContext->getGlobalResources());
		Effect* result = effect.get();
		_members->effectCache.insert(std::make_pair(name, std::move(effect)));
		return result;
	}

	std::unique_ptr<EffectInstance> Material::getEffect(const std::string& name) const
	{
		auto it = _members->effectCache.find(name);
		ASSERT(it != _members->effectCache.end());
		std::unique_ptr<EffectInstance> result(new EffectInstance(it->second));
		return result;
	}

	const AttributeFormat& Material::getAttributeFormat() const
	{
		return _members->description.getAttributeFormat();
	}

	const MaterialDescription& Material::getDescription() const
	{
		return _members->description;
	}

	void Material::sync(MaterialInstance* instance)
	{
		syncEffects(instance);
	}

	void Material::syncEffects(MaterialInstance* instance)
	{
		for(const std::pair<std::string, EffectInstance*>& pair : instance->collectAllEffects())
		{
			auto it = _members->effectCache.find(pair.first);
			ASSERT(it != _members->effectCache.end());
			std::shared_ptr<Effect>& effect = it->second;
			effect->sync(pair.second);
		}
	}

	const std::string& Material::getMaterialName() const
	{
		return _members->name;
	}
	
}
