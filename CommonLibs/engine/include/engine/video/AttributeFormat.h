#pragma once

namespace engine
{
	enum class GPUMemberType;

	struct ShaderLayout
	{
		GPUMemberType type;
		std::string name;
		bool operator==(const ShaderLayout& o) const;
	};

	class AttributeFormat
	{
	public:
		AttributeFormat();
		AttributeFormat(const AttributeFormat&);
		AttributeFormat(AttributeFormat&&);
		~AttributeFormat();

		AttributeFormat& operator=(const AttributeFormat&);
		AttributeFormat& operator=(AttributeFormat&&);

		bool operator==(const AttributeFormat&) const;
		void insertAttribute(GPUMemberType type, uint32_t layout, const std::string& name);
		size_t getNumOfAttributes() const;
		void removeAttirbute(uint32_t layout);
		const ShaderLayout& getAttribute(uint32_t layout) const;
	private:
		struct AttributeFormatPrivate* _members = nullptr;
	};
}