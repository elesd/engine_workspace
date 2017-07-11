#include <stdafx.h>
#include <engine/video/EffectComperator.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/Effect.h>

#include <engine/video/ShaderCompilationData.h>
#include <engine/video/ShaderCompileOptions.h>

#include <engine/functional/functions.h>

namespace engine
{
	struct EffectComperatorPrivate
	{
		std::array<bool, size_t(EffectComperator::DifferenceType::Num)> changes;
	};

	EffectComperator::EffectComperator()
		: _members(new EffectComperatorPrivate())
	{}
	EffectComperator::~EffectComperator()
	{
		delete _members;
		_members = nullptr;
	}

	void EffectComperator::compare(const Effect* a, const Effect* b)
	{
		_members->changes.fill(false);
		if(a == b)
		{
			return;
		}
		if(a == nullptr || b == nullptr)
		{
			_members->changes.fill(true);
			return;
		}

		_members->changes[size_t(DifferenceType::VertexShader)] = a->getVertexShaderData()->getOptions() == b->getVertexShaderData()->getOptions();
		_members->changes[size_t(DifferenceType::FragmentShader)] = a->getFragmentShaderData()->getOptions() == b->getFragmentShaderData()->getOptions();
	}

	bool EffectComperator::isChanged(EffectComperator::DifferenceType type) const
	{
		return _members->changes[size_t(type)];
	}

	bool EffectComperator::hasAnyChange() const
	{
		return std::any_of(_members->changes.begin(), _members->changes.end(), EqualTo<bool>(true));
	}
}