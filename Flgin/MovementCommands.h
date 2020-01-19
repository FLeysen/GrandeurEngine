#pragma once
#include "Command.h"

namespace flgin
{
	class GridMovementComponent;
	class DirectionalGridMove : public Command
	{
	public:
		DirectionalGridMove(GridMovementComponent* attachedMover, bool isHorizontal = true, bool isPositiveDirection = true);
		void Execute(GameObject& attachedObject, bool isInverseAction);

	private:
		bool m_IsHeld;
		bool m_IsHorizontal;
		bool m_IsPositiveDirection;
		GridMovementComponent* m_pGridMover;
	};
}