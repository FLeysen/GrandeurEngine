#include "pch.h"
#include "PookaCommands.h"
#include "Pooka.h"
#include "GameObject.h"

void DigDug::GhostCommand::Execute(flgin::GameObject& commander, bool isInverse)
{
	commander.GetComponent<Pooka>()->SetGhosting(!isInverse);
}
