#include <stdafx.h>
#include <engine/video/Material.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/EffectCompiler.h>
#include <engine/video/Effect.h>
#include <engine/video/MaterialDescription.h>
#include <engine/render/RenderContext.h>

#include <engine/video/AttributeFormat.h>
#include <engine/video/MaterialContext.h>
#include <engine/video/Shader.h>
#include <engine/video/ShaderCompilationData.h>
#include <engine/video/ShaderCompileOptions.h>
#include <engine/video/VertexBuffer.h>

namespace engine
{
	
	struct MaterialPrivate
	{
		std::unique_ptr<EffectCompiler> effectCompiler;
		std::map<std::string, std::unique_ptr<Effect>> effectCache;
		MaterialDescription description;
		std::unique_ptr<MaterialContext> materialContext;
		std::string name;
		std::string currentEffect;
		MaterialPrivate(const std::string& name, const MaterialDescription& description)
			: name(name) 
			, description(description)
			, currentEffect(Material::defaultEffectName)
		{}
	};

	const std::string Material::defaultEffectName = "Default";

	Material::Material(const std::string& name, const MaterialDescription& description, RenderContext* renderContext)
		: _members(new MaterialPrivate(name, description))
	{
		_members->materialContext = renderContext->createMaterialContext(this);
		_members->effectCompiler = renderContext->createEffectCompiler(this);
		setCurrentEffect(_members->currentEffect);
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

	void Material::setCurrentEffect(const std::string& name)
	{
		_members->currentEffect = name;
		if(_members->effectCache.find(name) == _members->effectCache.end())
		{
			std::unique_ptr<Effect> effect = _members->effectCompiler->compileEffect(name);
			_members->effectCache.insert(std::make_pair(name, std::move(effect)));
		}
	}

	const std::string& Material::getCurrentEffectName() const
	{
		return _members->currentEffect;
	}

	Effect* Material::getEffect() const
	{
		auto it = _members->effectCache.find(_members->currentEffect);
		ASSERT(it != _members->effectCache.end());
		return it->second.get();
	}

	std::unique_ptr<VertexBuffer> Material::createVertexBufferFor(const std::string& techniqueName) const
	{
		_members->materialContext->bind();
		const AttributeFormat& layout = getAttributeFormat();
		std::vector<GPUMemberType> format;
		format.reserve(layout.getNumOfAttributes());
		for(uint32_t i = 0; i < layout.getNumOfAttributes(); ++i)
		{
			format.push_back(layout.getAttribute(i).type);
		}
		std::unique_ptr<engine::VertexBuffer> buffer(new engine::VertexBuffer(format));
		_members->materialContext->unbind();
		return buffer;
	}

	const MaterialContext* Material::getMaterialContext() const
	{
		return _members->materialContext.get();
	}

	const AttributeFormat& Material::getAttributeFormat() const
	{
		return _members->description.getAttributeFormat();
	}

	const MaterialDescription& Material::getDescription() const
	{
		return _members->description;
	}

	const std::string& Material::getMaterialName() const
	{
		return _members->name;
	}



	
}