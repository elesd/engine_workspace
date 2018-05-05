#pragma once

#include <engine/utils/CustomPlaceholder.h>
#include <engine/utils/GenSequence.h>


namespace engine
{
	/**
	* This class is responsible for calling a signal's slot on a given object with the stored paramters.
	*/
	template <typename... Ts>
	class SignalCaller
	{
	public:
		/**
		* Bind the callback to the given t object.
		* It creates a function which is bind the callback to the t object.
		* @param t: object which will be assigned to the callback.
		* @param callback: This member function will be called on the t object.
		* @return Returns a function which will call the member function on the given object.
		*/
		template <typename T>
		static std::function<void(Ts...)> createCallable(T *t, void (T::*callback)(Ts...))
		{
			return bindCallable(t, callback, engine::GenSequence < sizeof...(Ts) > {});
		}
	private:

		/**
		* This function does the real binding.
		* This function is necessery becuase the std::placeholders are not prepared for template sequences.
		* @tparam T: Object's type
		* @tparam Is: seqences to generate the placeholders.
		* @param t: object which will be assigned to the callback.
		* @param callback: This member function will be called on the t object.
		* @return Returns a function which will call the member function on the given object.
		*/
		template <typename T, int... Is>
		static std::function<void(Ts...)> bindCallable(T *t, void (T::*callback)(Ts...), engine::Index<Is...>)
		{
			return std::bind(callback, t, engine::CustomPlaceholder < Is > {}...);
		}


	public:
		/**
		* Store the callback function and call it when it is necessery.
		* The function paramter can be produced via static functions @see SignalCaller::createCallable
		* @param func: Function which will be called with the given parameters
		*/
		explicit SignalCaller(const std::function<void(Ts...)> &func)
			: f(func)
		{}

		/**
		* Calls the stored function with the given parameters.
		* @param args: Arguments for the stored function.
		*/
		void operator()(const std::tuple<Ts...> &args)
		{
			call(args, engine::GenSequence < sizeof...(Ts) > {});
		}

	private:
		/**
		* This function does the real function calling with the given arguments.
		* @tparam Args: Arguments' types
		* @tparam Is: integer constants which represent the number of arguments.
		* @param tup: Arguments of the function call.
		* @param indeces: For template argument auto deduction
		*/
		template <typename... Args, int... Is>
		void call(const std::tuple<Args...>& tup, engine::Index<Is...> /*indeces*/)
		{
			f(std::get<Is>(tup)...);
		}

	private:
		/**
		* The stored function which will be called
		*/
		std::function<void(Ts...)> f;
	};
}
