#pragma once

namespace engine
{
	class AttributeFormat;
	class Shader;
	class ShaderCompileOptions;

	class ShaderResourceDescription;
	class EffectDescription;
	enum class ShaderVersion;

	class MaterialDescription
	{
	public:
		MaterialDescription() = default;
		explicit MaterialDescription(ShaderVersion);
		~MaterialDescription();
		MaterialDescription(const MaterialDescription&);
		MaterialDescription(MaterialDescription&&);

		MaterialDescription& operator=(const MaterialDescription&);
		MaterialDescription& operator=(MaterialDescription&&);

		EffectDescription createEffectDescription(const std::string& name) const;
		void addEffect(const EffectDescription& description);

		void setAttributeFormat(const AttributeFormat& attributeFormat);
		void setVertexShaderName(const std::string& shaderName);
		void setFragmentShaderName(const std::string& shaderName);
		EffectDescription& getDefaultEffect();
		const EffectDescription& getDefaultEffect() const;

		const AttributeFormat& getAttributeFormat() const;
		ShaderVersion getShaderVersion() const;
		const std::string& getVertexShaderName() const;
		const std::string& getFragmentShaderName() const;
		const EffectDescription& getEffectDescription(const std::string& techniqueName) const;
		EffectDescription& getEffectDescription(const std::string& techniqueName);
		const std::map<std::string, EffectDescription>& getEffectMap() const;
	private:
		void setDefaultEffect(const EffectDescription& description);
	private:
		struct MaterialDescriptionPrivate* _members = nullptr;
		
	};
}