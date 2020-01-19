#pragma once
#include "BaseComponent.h"

namespace flgin
{
	class GameObject;
	class State
	{
	public:
		State() : m_pTargetState{ nullptr } {}
		virtual ~State() = default;
		virtual void Enter() = 0;
		virtual void Exit() = 0;
		virtual bool Update() = 0;
		State* GetTargetState() const { return m_pTargetState; }

	protected:
		State* m_pTargetState;
	};

	class StateComponent final : public BaseComponent
	{
	public:
		StateComponent(GameObject* pOwnerObject);
		~StateComponent();
		void Update();
		void SetCurrentState(State* pNewState);
		State* GetCurrentState() const { return m_pCurrentState; }

		StateComponent(StateComponent&&) = delete;
		StateComponent(const StateComponent&) = delete;
		StateComponent& operator=(StateComponent&&) = delete;
		StateComponent& operator=(const StateComponent&) = delete;

	private:
		void RawSetCurrentState(State* pNewState);

		State* m_pCurrentState;
	};
}

