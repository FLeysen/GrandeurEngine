#include "FlginPCH.h"
#include "MovementCommands.h"
#include "GridMovementComponent.h"

flgin::DirectionalGridMove::DirectionalGridMove(GridMovementComponent* attachedMover, bool isHorizontal, bool isPositiveDirection)
	: m_IsHorizontal{ isHorizontal }
	, m_IsPositiveDirection{ isPositiveDirection }
	, m_pGridMover{ attachedMover }
{}

void flgin::DirectionalGridMove::Execute(GameObject&, bool isInverseAction)
{
	if (!m_IsHeld)
	{
		m_IsHeld = true;
		m_pGridMover->SetMoving(m_IsHorizontal, m_IsPositiveDirection);
	}
	else if (isInverseAction)
	{
		m_IsHeld = false;
		m_pGridMover->SetMoving(m_IsHorizontal, !m_IsPositiveDirection);
	}
}