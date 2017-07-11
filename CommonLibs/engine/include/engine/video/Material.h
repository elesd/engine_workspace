#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class AttributeFormat;
	class Effect;
	class EffectCompiler;
	class MaterialContext;
	class MaterialDescription;
	class RenderContext;
	class Shader;
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

		void setCurrentEffect(const std::string& name);
		const std::string& getCurrentEffectName() const;
		Effect* getEffect() const;

		std::unique_ptr<VertexBuffer> createVertexBufferFor(const std::string& techniqueName) const;

		const MaterialContext* getMaterialContext() const;
		const AttributeFormat& getAttributeFormat() const;
		const MaterialDescription& getDescription() const;
	private:
		struct MaterialPrivate* _members = nullptr;
	};
}