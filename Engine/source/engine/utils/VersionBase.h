#pragma once

#include "engine/constraints/Singleton.h"

namespace engine
{
	namespace utils
	{
		template<class VersionClass>
		class VersionBase : public constraints::Singleton<VersionBase<VersionClass>>,
							public VersionClass
		{

			friend class constraints::Singleton<VersionBase<VersionClass>>;
		protected:
			VersionBase() = default;
		public:
			int32_t getMajor() const;
			int32_t getMinor() const;
			int32_t getCounter() const;
			int32_t getYear() const;
			int32_t getMonth() const;
			int32_t getDay() const;
			std::string getString() const;
			template<class OVersionClass>
			bool operator<(const VersionBase<OVersionClass> &o) const;

			template<class OVersionClass>
			bool operator==(const VersionBase<OVersionClass> &o) const;
			
			template<class OVersionClass>
			bool operator>(const VersionBase<OVersionClass> &o) const;

			template<class OVersionClass>
			bool operator>=(const VersionBase<OVersionClass> &o) const;

			template<class OVersionClass>
			bool operator<=(const VersionBase<OVersionClass> &o) const;

			template<class OVersionClass>
			bool operator!=(const VersionBase<OVersionClass> &o) const;
		};
	}
}

#include "engine/utils/VersionBase.hpp"