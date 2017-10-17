#include <stdafx.h>
#include <engine/video/EffectComperator.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/libraries/ShaderInstance.h>

#include <engine/libraries/EffectInstance.h>

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

	void EffectComperator::compare(const EffectInstance* a, const EffectInstance* b)
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
		
		_members->changes[size_t(DifferenceType::VertexShader)] = a->getVertexShader()->isSame(a->getName(), *b->getVertexShader());
		_members->changes[size_t(DifferenceType::FragmentShader)] = a->getFragmentShader()->isSame(a->getName(), *b->getFragmentShader());
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