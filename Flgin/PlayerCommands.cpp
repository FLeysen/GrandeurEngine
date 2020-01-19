#include "FlginPCH.h"
#include "PlayerCommands.h"
#include "GameObject.h"
#include <Xinput.h>
#include "InputManager.h"

void flgin::QuitCommand::Execute(GameObject&, bool)
{
	FInputManager.Quit();
}

void flgin::RumbleCommand::Execute(GameObject&, bool isInverseAction)
{
	if (!isInverseAction)
	{
		_XINPUT_VIBRATION vib{};
		WORD rumbleValue{ 0 };
		m_IsRumbling = !m_IsRumbling;
		if (m_IsRumbling)
		{
			rumbleValue = 65535;
			rumbleValue = 65535;
		}
		vib.wLeftMotorSpeed = rumbleValue;
		vib.wRightMotorSpeed = rumbleValue;
		XInputSetState(m_UserID, &vib);
	}
}
