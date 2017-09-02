#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/video/IndexBuffer.h>
#include <engine/video/IndexBufferBase.h>

namespace engine
{
	class AttributeFormat;
	class Effect;
	class EffectCompiler;
	class MaterialDescription;
	class MaterialResourceHandler;
	class RenderContext;
	class Shader;
	class ShaderResourceStorage;
	class VertexBuffer;

	class Material
		: private NonCopyable
	{
		friend class MaterialResourceHandler;
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

		const AttributeFormat& getAttributeFormat() const;
		const MaterialDescription& getDescription() const;
		MaterialResourceHandler* getResourceHandler();
	private:
		const std::map<std::string, std::unique_ptr<Effect>>& getCompiledEffects();
	private:
		struct MaterialPrivate* _members = nullptr;
	};

}