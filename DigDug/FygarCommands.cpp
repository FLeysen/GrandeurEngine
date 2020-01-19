#include "pch.h"
#include "FygarCommands.h"
#include "Fygar.h"

void DigDug::BreatheFireCommand::Execute(flgin::GameObject& commander, bool isInverse)
{
	commander.GetComponent<Fygar>()->SetFiring(!isInverse);
}
