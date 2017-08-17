#pragma once

namespace engine
{
	enum class ShaderType;
	class ShaderResourceBindingData
	{
	public:
		explicit ShaderResourceBindingData(const std::vector<ShaderType>& shaders);
		ShaderResourceBindingData(uint32_t layout, const std::vector<ShaderType>& shaders);
		~ShaderResourceBindingData();
		ShaderResourceBindingData(const ShaderResourceBindingData&);
		ShaderResourceBindingData(ShaderResourceBindingData&&);

		ShaderResourceBindingData& operator=(const ShaderResourceBindingData&);
		ShaderResourceBindingData& operator=(ShaderResourceBindingData&&);

		bool hasLayout() const;
		uint32_t getLayout() const;
		const std::vector<ShaderType>& getShaderTypes() const;

	private:
		struct ShaderResourceBindingDataPrivate* _members = nullptr;
	};
}