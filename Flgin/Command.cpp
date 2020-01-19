#include "FlginPCH.h"
#include "Command.h"
#include "InputManager.h"

flgin::Command::Command()
{
	FInputManager.AddCommand(this);
}
