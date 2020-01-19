#pragma once
#include "Command.h"

namespace flgin
{
	class QuitCommand final : public Command
	{
	public:
		void Execute(GameObject& attachedObject, bool isInverseAction = false) override;
	};

	class RumbleCommand final : public Command
	{
	public:
		RumbleCommand(DWORD userId) : Command(), m_UserID{ userId }, m_IsRumbling{ false }{}
		void Execute(GameObject& attachedObject, bool isInverseAction = false) override;

	private:
		DWORD m_UserID;
		bool m_IsRumbling;
	};
}