#pragma once

namespace engine
{
	enum class ShaderMemberType
	{
		Undef,
		Float,
		Vec2,
		Vec3,
		Vec4,
		Mat3,
		Mat4
	};

	class ShaderLayout
	{
	public:
		ShaderLayout();
		ShaderLayout(const ShaderLayout&);
		ShaderLayout(ShaderLayout&&);
		~ShaderLayout();

		ShaderLayout& operator=(const ShaderLayout&);
		ShaderLayout& operator=(ShaderLayout&&);

		bool operator==(const ShaderLayout&) const;
		void insertAttribute(ShaderMemberType type, uint32_t layout);
		void removeAttirbute(uint32_t layout);
		ShaderMemberType getAttribute(uint32_t layout) const;
	private:
		struct ShaderLayoutPrivate* _members = nullptr;
	};
}