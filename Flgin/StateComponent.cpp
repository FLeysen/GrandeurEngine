#include "FlginPCH.h"
#include "StateComponent.h"
#include "GameObject.h"

flgin::StateComponent::StateComponent(GameObject* pOwnerObject)
	: BaseComponent(pOwnerObject)
	, m_pCurrentState{ nullptr }
{}

flgin::StateComponent::~StateComponent()
{
	FLogger.SafeDelete(m_pCurrentState);
}

void flgin::StateComponent::Update()
{
#ifdef _DEBUG
	if (!m_pCurrentState) FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "Attempted to update simple state component with no current state!", this });
#endif
	if (m_pCurrentState->Update())
		RawSetCurrentState(m_pCurrentState->GetTargetState());
}

void flgin::StateComponent::SetCurrentState(State* pNewState)
{
	if (m_pCurrentState)
	{
		m_pCurrentState->Exit();
		delete m_pCurrentState;
	}
	m_pCurrentState = pNewState;
	m_pCurrentState->Enter();
}

void flgin::StateComponent::RawSetCurrentState(State * pNewState)
{
	m_pCurrentState->Exit();
	delete m_pCurrentState;
	m_pCurrentState = pNewState;
	m_pCurrentState->Enter();
}