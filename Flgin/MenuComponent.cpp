#include "FlginPCH.h"
#include "MenuComponent.h"
#include "ButtonComponent.h"

void flgin::MenuComponent::SelectDefault()
{
	m_pButtons[m_CurrentButton]->Deselect();
	m_pButtons[0]->Select();
}

void flgin::MenuComponent::SelectNext()
{
	if (m_CurrentButton == m_pButtons.size() - 1)
		return;
	m_pButtons[m_CurrentButton]->Deselect();
	m_pButtons[++m_CurrentButton]->Select();
}

void flgin::MenuComponent::SelectPrevious()
{
	if (m_CurrentButton == 0)
		return;
	m_pButtons[m_CurrentButton]->Deselect();
	m_pButtons[--m_CurrentButton]->Select();
}

void flgin::MenuComponent::PressCurrentButton()
{
	m_pButtons[m_CurrentButton]->Press();
}
