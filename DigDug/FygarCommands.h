#pragma once
#include "Command.h"

namespace DigDug
{
	class BreatheFireCommand final : public flgin::Command
	{
	public:
		BreatheFireCommand() : Command(){}
		void Execute(flgin::GameObject& attachedObject, bool isInverseAction = false) override;
	};
}