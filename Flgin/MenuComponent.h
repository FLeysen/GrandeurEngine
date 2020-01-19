#pragma once
#include "BaseComponent.h"

namespace flgin
{
	class ButtonComponent;

	class MenuComponent final : public BaseComponent
	{
	public:
		MenuComponent(GameObject* pOwnerObject) : BaseComponent(pOwnerObject), m_pButtons{}, m_CurrentButton{}, m_IsActive{} {}
		~MenuComponent() = default;

		void Update() override {}
		void AddButton(ButtonComponent* pButtonToAdd) { m_pButtons.push_back(pButtonToAdd); }
		void SelectDefault();
		void SelectNext();
		void SelectPrevious();
		void PressCurrentButton();
		bool IsActive() const { return m_IsActive; }
		void SetActive(bool active) { m_IsActive = active; }

	private:
		bool m_IsActive;
		size_t m_CurrentButton;
		std::vector<ButtonComponent*> m_pButtons;
	};
}