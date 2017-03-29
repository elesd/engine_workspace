#pragma once

#include <engine/constraints/Singleton.h>

namespace engine
{
	/**
	* Template base class to extend version classes.
	* @tparam VersionClass: The class to extend functionalities.
	*/
	template<class VersionClass>
	class VersionBase : public Singleton<VersionBase<VersionClass>>,
		public VersionClass
	{

		friend class Singleton < VersionBase<VersionClass> > ;
	protected:
		/**Defualt constructable*/
		VersionBase() = default;
	public:
		/**@return Returns the major number*/
		int32_t getMajor() const;
		/**@return Returns the minor number*/
		int32_t getMinor() const;
		/**@return Returns the counter part*/
		int32_t getCounter() const;
		/**@return Returns the build year*/
		int32_t getYear() const;
		/**@return Returns the build month */
		int32_t getMonth() const;
		/**@return Returns the build day*/
		int32_t getDay() const;
		/**@return Returns the string format*/
		std::string getString() const;

		/**
		* Comparson operator.
		* @param o: other object
		*/
		template<class OVersionClass>
		bool operator<(const VersionBase<OVersionClass> &o) const;

		/**
		* Comparson operator.
		* @param o: other object
		*/
		template<class OVersionClass>
		bool operator==(const VersionBase<OVersionClass> &o) const;

		/**
		* Comparson operator.
		* @param o: other object
		*/
		template<class OVersionClass>
		bool operator>(const VersionBase<OVersionClass> &o) const;

		/**
		* Comparson operator.
		* @param o: other object
		*/
		template<class OVersionClass>
		bool operator>=(const VersionBase<OVersionClass> &o) const;

		/**
		* Comparson operator.
		* @param o: other object
		*/
		template<class OVersionClass>
		bool operator<=(const VersionBase<OVersionClass> &o) const;

		/**
		* Comparson operator.
		* @param o: other object
		*/
		template<class OVersionClass>
		bool operator!=(const VersionBase<OVersionClass> &o) const;
	};
}

#include <engine/utils/VersionBase.hpp>