#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/video/IndexBuffer.h>
#include <engine/video/IndexBufferBase.h>

namespace engine
{
	class AttributeFormat;
	class Effect;
	class EffectCmpiler;
	class EffectInstance;
	class MaterialInstance;
	class MaterialDescription;
	class MaterialResourceHandler;
	class RenderContext;
	class Shader;
	class ShaderResourceStorage;
	class VertexBuffer;

	class Material
		: private NonCopyable
	{
	public:
		static const std::string defaultEffectName;
	public:
		Material(const std::string& name, const MaterialDescription& description, RenderContext* renderContext);
		~Material();
		Material(Material&&);
		Material& operator=(Material&&);

		const std::string& getMaterialName() const;

		std::unique_ptr<EffectInstance> getEffect(const std::string& name) const;

		const AttributeFormat& getAttributeFormat() const;
		const MaterialDescription& getDescription() const;

		void sync(MaterialInstance* instance);
	private:
		void syncEffects(MaterialInstance* instance);
		Effect* compileEffect(const std::string& name);
	private:
		struct MaterialPrivate* _members = nullptr;
	};

}