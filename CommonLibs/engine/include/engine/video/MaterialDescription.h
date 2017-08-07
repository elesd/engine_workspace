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
		explicit MaterialDescription(ShaderVersion);
		~MaterialDescription();
		MaterialDescription(const MaterialDescription&);
		MaterialDescription(MaterialDescription&&);

		MaterialDescription& operator=(const MaterialDescription&);
		MaterialDescription& operator=(MaterialDescription&&);

		EffectDescription createEffectDescription(const std::string& name) const;
		void addEffect(const EffectDescription& description);

		void setAttributeFormat(const AttributeFormat& attributeFormat);
		void setVertexShader(Shader* vertexShader);
		void setFragmentShader(Shader* fragmentShader);
		void addParameter(const ShaderResourceDescription &description);
		EffectDescription& getDefaultEffect();
		const EffectDescription& getDefaultEffect() const;

		const std::vector<ShaderResourceDescription>& getParameters() const;
		const AttributeFormat& getAttributeFormat() const;
		ShaderVersion getShaderVersion() const;
		Shader* getVertexShader() const;
		Shader* getFragmentShader() const;
		const EffectDescription& getEffectDescription(const std::string& techniqueName) const;
		EffectDescription& getEffectDescription(const std::string& techniqueName);
		const std::map<std::string, EffectDescription>& getEffectMap() const;
	private:
		void setDefaultEffect(const EffectDescription& description);
	private:
		struct MaterialDescriptionPrivate* _members = nullptr;
		
	};
}