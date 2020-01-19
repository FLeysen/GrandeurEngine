#include "FlginPCH.h"
#include "Timer.h"
#include "Invoker.h"

flgin::InvokeHolderBase::InvokeHolderBase(float invocationTime, void* origin)
	: m_ElapsedTime{ 0.0f }
	, m_InvocationTime{ invocationTime }
	, m_IsRepeating{ false }
	, m_pOrigin{ origin }
{}

bool flgin::InvokeHolderBase::Update()
{
	m_ElapsedTime += FTime.GetDeltaTime();
	if (m_ElapsedTime > m_InvocationTime)
	{
		Invoke();
		if (m_IsRepeating)
		{
			m_ElapsedTime -= m_InvocationTime;
			return false;
		}
		return true;
	}
	return false;
}

bool flgin::InvokeHolderBase::DoesOriginateFrom(void* owner)
{
	return owner == m_pOrigin;
}

void flgin::InvokeHolderBase::SetRepeating(bool repeating)
{
	m_IsRepeating = repeating;
}

flgin::Invoker::~Invoker()
{
	Logger& logger{ FLogger };
	for (int i{}; i < m_FunctionsHeld; ++i)
		logger.SafeDelete(m_pFunctionHolders[i]);
}

void flgin::Invoker::Update()
{
	for (int i{}; i < m_FunctionsHeld; ++i)
	{
		if (m_pFunctionHolders[i]->Update())
		{
			--m_FunctionsHeld;
			FLogger.SafeDelete(m_pFunctionHolders[i]);
			m_pFunctionHolders[i] = m_pFunctionHolders[m_FunctionsHeld];
			--i;
		}
	}
}

void flgin::Invoker::AddInvoke(InvokeHolderBase * pInvokeToAdd)
{
	if (m_FunctionsHeld == MAX_INVOCATIONS)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "Invoker is full, could not add invoke." });
		FLogger.SafeDelete(pInvokeToAdd);
		return;
	}
	m_pFunctionHolders[m_FunctionsHeld] = pInvokeToAdd;
	++m_FunctionsHeld;
}

void flgin::Invoker::CancelOwnedInvokes(void* owner)
{
	for (int i{}; i < m_FunctionsHeld; ++i)
	{
		if (m_pFunctionHolders[i]->DoesOriginateFrom(owner))
		{
			--m_FunctionsHeld;
			FLogger.SafeDelete(m_pFunctionHolders[i]);
			m_pFunctionHolders[i] = m_pFunctionHolders[m_FunctionsHeld];
			--i;
		}
	}
}

void flgin::Invoker::CancelAllInvokes()
{
	for (int i{}; i < m_FunctionsHeld; ++i)
			FLogger.SafeDelete(m_pFunctionHolders[i]);
	m_FunctionsHeld = 0;
}