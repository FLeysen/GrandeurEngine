// This invoker was inspired by Matthieu Delaere's Elite engine Multicast functionality and the Invoke function in Unity engine
#pragma once
#include "Singleton.h"
#include <functional>

#ifndef MAX_INVOCATIONS
#define MAX_INVOCATIONS 50
#endif
#define FInvoker flgin::Invoker::GetInstance()

namespace flgin
{
	class InvokeHolderBase
	{
	public:
		InvokeHolderBase(float invocationTime, void* origin);
		virtual ~InvokeHolderBase() = default;
		bool Update();
		bool DoesOriginateFrom(void* owner);
		void SetRepeating(bool repeating);

	protected:
		virtual void Invoke() = 0;

		bool m_IsRepeating;
		float m_ElapsedTime;
		float m_InvocationTime;
		void* m_pOrigin;
	};

	template<typename returnType, typename... argList>
	class InvokeHolder : public InvokeHolderBase
	{
	public:
		//Origin is used to cancel invokes on a specific object, set this to nullptr if you only want it canceled by CancelAll
		explicit InvokeHolder(void* origin, float invocationTime, std::function<returnType(argList...)> function, argList... arguments)
			: InvokeHolderBase(invocationTime, origin), m_Function{ function }, m_Arguments{ arguments... } {}

	private:
		returnType Invoke() 
		{
			return CallFunction(m_Function, m_Arguments, std::index_sequence_for<argList...>());
		}
		template<std::size_t... Is>
		returnType CallFunction(std::function<returnType(argList...)>& func, const std::tuple<argList...>& tuple, std::index_sequence<Is...>)
		{
			return func(std::get<Is>(tuple)...);
		}

		std::function<returnType(argList...)> m_Function;
		std::tuple<argList...> m_Arguments;
	};

	class Invoker final : public Singleton<Invoker>
	{
	public:
		~Invoker();
		Invoker() = default;
		Invoker(const Invoker& other) = delete;
		Invoker(Invoker&& other) = delete;
		Invoker& operator=(const Invoker& other) = delete;
		Invoker& operator=(Invoker&& other) = delete;

		void Update();
		void AddInvoke(InvokeHolderBase* pInvokeToAdd);
		void CancelOwnedInvokes(void* owner);
		void CancelAllInvokes();

	private:
		InvokeHolderBase* m_pFunctionHolders[MAX_INVOCATIONS];
		int m_FunctionsHeld;
	};
}