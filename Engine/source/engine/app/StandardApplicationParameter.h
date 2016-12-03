#pragma once

#include "engine/app/IApplicationParameter.h"

namespace engine
{
	/**
	* Standard application parameter representation. For main(int argc, char **args) type main functions
	*/
	class StandardApplicationParameter : public IApplicationParameter
	{
	public:
		/**
		* Create a standard parameter representation
		* @param nParams: number of parameters
		* @param parameters: Parameters array with length nParams
		*/
		StandardApplicationParameter(uint32_t nParams, char *parameters[]);
	protected:
		/**
		* For child classes it is possible to empty initialization.
		*/
		StandardApplicationParameter();
	public:
		/**Destructor for PIMPL*/
		~StandardApplicationParameter()  override;
		/**@return Returns the parameters in a vector*/
		const std::vector<std::string> &getParameters() const;
		/**@return Returns the name of the binary*/
		const std::string &getBinaryName() const;
	protected:
		/**
		* Function for initialize the members
		*/
		void init(uint32_t nParams, const std::vector<std::string> &parameters);
	private:
		/**PIMPL*/
		struct StandardApplicationParameterPrivate *_members = nullptr;
	};
}
