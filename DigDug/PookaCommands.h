#pragma once
#include "Command.h"

namespace DigDug
{
	class GhostCommand final : public flgin::Command
	{
	public:
		GhostCommand() : Command() {}
		void Execute(flgin::GameObject& attachedObject, bool isInverseAction = false) override;
	};
}