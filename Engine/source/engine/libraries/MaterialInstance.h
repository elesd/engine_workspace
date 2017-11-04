#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class AttributeFormat;
	class Material;
	class EffectInstance;
	class MaterialResourceHandler;
	class MaterialDescription;


	class MaterialInstance
		: private NonCopyable
		, private NonMoveable
	{
	public:
		explicit MaterialInstance(std::shared_ptr<Material> source);
		~MaterialInstance();

		const std::string& getMaterialName() const;

		void setCurrentEffect(const std::string& name);
		EffectInstance* getCurrentEffect() const;

		const AttributeFormat& getAttributeFormat() const;
		const MaterialDescription& getDescription() const;
		MaterialResourceHandler* getResourceHandler();
		std::map<std::string, EffectInstance*> collectAllEffects();
		std::map<std::string, const EffectInstance*> collectAllEffects() const;

		std::unique_ptr<MaterialInstance> clone() const;
	private:
		struct MaterialInstancePrivate* _members = nullptr;
	};
}