#include "FlginPCH.h"
#include "InputComponent.h"
#include "InputManager.h"
#include "Command.h"

flgin::InputComponent::InputComponent(GameObject* const ownerObject)
	: BaseComponent(ownerObject)
	, m_ControllerMappings{}
	, m_KeyboardMappings{}
{}

void flgin::InputComponent::AddControllerMapping(UINT8 key, Command* command)
{
	m_ControllerMappings.emplace(key, command);
}

void flgin::InputComponent::AddKeyboardMapping(int key, Command* command)
{
	m_KeyboardMappings.emplace(key, command);
}

void flgin::InputComponent::AddAxisMapping(UINT8 axis, const AxisRange& range, Command* command)
{
	m_AxisMappings.emplace(axis, std::make_pair(range, command));
}

void flgin::InputComponent::Update()
{}

void flgin::InputComponent::ProcessKeyboardKey(int key, bool isKeyUp)
{
	for (const std::pair<int, Command*>& mapping : m_KeyboardMappings)
	{
		if (key == mapping.first)
			mapping.second->Execute(*m_pOwnerObject, isKeyUp);
	}
}

void flgin::InputComponent::ProcessControllerKey(UINT8 key, bool isKeyUp)
{
	for (const std::pair<UINT8, Command*>& mapping : m_ControllerMappings)
	{
		if (key == mapping.first)
			mapping.second->Execute(*m_pOwnerObject, isKeyUp);
	}
}

void flgin::InputComponent::ProcessAxisMotion(UINT8 axis, short int value)
{
	for (std::pair<const UINT8, std::pair<AxisRange, Command*>>& mapping : m_AxisMappings)
	{
		if (axis == mapping.first)
		{
			if (value <= mapping.second.first.max && value >= mapping.second.first.min)
			{
				mapping.second.first.wasReached = true;
				mapping.second.second->Execute(*m_pOwnerObject, false);
			}
			else if (mapping.second.first.wasReached)
			{
				mapping.second.first.wasReached = false;
				mapping.second.second->Execute(*m_pOwnerObject, true);
			}
		}
	}
}

void flgin::InputComponent::Clear()
{
	m_ControllerMappings.clear();
	m_KeyboardMappings.clear();
	m_AxisMappings.clear();
}