#pragma once
#include <functional>

namespace flgin
{
	class FunctionHolderBase
	{
	public:
		FunctionHolderBase() = default;
		virtual ~FunctionHolderBase() = default;
		virtual void Call() = 0;
	};

	template<typename returnType, typename... argList>
	class FunctionHolder : public FunctionHolderBase
	{
	public:
		explicit FunctionHolder(std::function<returnType(argList...)> function, argList... arguments)
			: FunctionHolderBase(), m_Function{ function }, m_Arguments{ arguments... } {}
		void Call() override
		{
			CallFunction(m_Function, m_Arguments, std::index_sequence_for<argList...>());
		}

	private:
		template<std::size_t... Is>
		returnType CallFunction(std::function<returnType(argList...)>& func, const std::tuple<argList...>& tuple, std::index_sequence<Is...>)
		{
			return func(std::get<Is>(tuple)...);
		}

		std::function<returnType(argList...)> m_Function;
		std::tuple<argList...> m_Arguments;
	};

	class ConditionalFunctionHolderBase
	{
	public:
		ConditionalFunctionHolderBase() = default;
		virtual ~ConditionalFunctionHolderBase() = default;
		virtual bool Call() = 0;
	};

	template<typename... argList>
	class ConditionalFunctionHolder : public ConditionalFunctionHolderBase
	{
	public:
		explicit ConditionalFunctionHolder(std::function<bool(argList...)> function, argList... arguments)
			: ConditionalFunctionHolderBase(), m_Function{ function }, m_Arguments{ arguments... } {}
		bool Call() override
		{
			return CallFunction(m_Function, m_Arguments, std::index_sequence_for<argList...>());
		}

	private:
		template<std::size_t... Is>
		bool CallFunction(std::function<bool(argList...)>& func, const std::tuple<argList...>& tuple, std::index_sequence<Is...>)
		{
			return func(std::get<Is>(tuple)...);
		}

		std::function<bool(argList...)> m_Function;
		std::tuple<argList...> m_Arguments;
	};
}