
#define DECL_TEMPLATE template<class VersionClass>
#define T_VERSION_BASE VersionBase<VersionClass>

namespace engine
{
	DECL_TEMPLATE
		int32_t T_VERSION_BASE::getMajor() const
	{
		return VersionClass::major;
	}

	DECL_TEMPLATE
		int32_t T_VERSION_BASE::getMinor() const
	{
		return VersionClass::minor;
	}

	DECL_TEMPLATE
		int32_t T_VERSION_BASE::getCounter() const
	{
		return VersionClass::counter;
	}

	DECL_TEMPLATE
		int32_t T_VERSION_BASE::getYear() const
	{
		return std::atoi(VersionClass::year.c_str());
	}

	DECL_TEMPLATE
		int32_t T_VERSION_BASE::getMonth() const
	{
		return std::atoi(VersionClass::month.c_str());
	}

	DECL_TEMPLATE
		int32_t T_VERSION_BASE::getDay() const
	{
		return std::atoi(VersionClass::day.c_str());
	}

	DECL_TEMPLATE
		std::string T_VERSION_BASE::getString() const
	{
		std::stringstream os;
		os << VersionClass::major << "." << VersionClass::minor << ":" << VersionClass::counter
			<< " " << VersionClass::year << "-" << VersionClass::month << "-" << VersionClass::day;
		return os.str();
	}

	DECL_TEMPLATE
		template<class OVersionClass>
	bool T_VERSION_BASE::operator<(const VersionBase<OVersionClass> &o) const
	{
		std::vector<int32_t> versionProperties =
		{
			getMajor(),
			getMinor(),
			getCounter(),
			getYear(),
			getMonth(),
			getDay()
		};

		std::vector<int32_t> oVersionProperties =
		{
			o.getMajor(),
			o.getMinor(),
			o.getCounter(),
			o.getYear(),
			o.getMonth(),
			o.getDay()
		};
		bool go = true;
		bool less = false;

		for(uint32_t i = 0; go && i < versionProperties.size(); ++i)
		{
			int32_t comp = versionProperties[i] - oVersionProperties[i];
			if(comp > 0)
			{
				go = false;
				less = false;
			}
			else if(comp < 0)
			{
				go = false;
				less = true;
			}
		}
		return less;
	}

	DECL_TEMPLATE
		template<class OVersionClass>
	bool T_VERSION_BASE::operator==(const VersionBase<OVersionClass> &o) const
	{
		std::vector<int32_t> versionProperties =
		{
			getMajor(),
			getMinor(),
			getCounter(),
			getYear(),
			getMonth(),
			getDay()
		};

		std::vector<int32_t> oVersionProperties =
		{
			o.getMajor(),
			o.getMinor(),
			o.getCounter(),
			o.getYear(),
			o.getMonth(),
			o.getDay()
		};
		bool go = true;
		bool eq = true;

		for(uint32_t i = 0; go && i < versionProperties.size(); ++i)
		{
			int32_t comp = versionProperties[i] - oVersionProperties[i];
			if(comp != 0)
			{
				go = false;
				eq = false;
			}
		}
		return eq;
	}

	DECL_TEMPLATE
		template<class OVersionClass>
	bool T_VERSION_BASE::operator>(const VersionBase<OVersionClass> &o) const
	{
		return !operator<=(o);
	}

	DECL_TEMPLATE
		template<class OVersionClass>
	bool T_VERSION_BASE::operator>=(const VersionBase<OVersionClass> &o) const
	{
		return !operator<(o);
	}

	DECL_TEMPLATE
		template<class OVersionClass>
	bool T_VERSION_BASE::operator<=(const VersionBase<OVersionClass> &o) const
	{
		return operator<(o) || operator==(o);
	}

	DECL_TEMPLATE
		template<class OVersionClass>
	bool T_VERSION_BASE::operator!=(const VersionBase<OVersionClass> &o) const
	{
		return !operator==(o);
	}
}

#undef DECL_TEMPLATE
#undef DECL_CLASS
