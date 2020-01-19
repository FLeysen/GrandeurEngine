#include "pch.h"
#include "FygarController.h"
#include "Fygar.h"
#include "GridMovementComponent.h"
#include "MovementGrid.h"
#include "MovementCommands.h"
#include "Timer.h"
#include "Invoker.h"

DigDug::FygarController::FygarController(flgin::GameObject* ownerObject, Fygar* fygar, flgin::GridMovementComponent* mover, flgin::MovementGrid* grid)
	: BaseComponent(ownerObject)
	, m_pFygar{ fygar }
	, m_pMover{ mover }
	, m_pLastNode{}
	, m_pTargetNode{}
	, m_pUpMove{}
	, m_pDownMove{}
	, m_pLeftMove{}
	, m_pRightMove{}
	, m_AccuTime{}
	, m_FireChance{ 5 }
	, m_FireInterval{ 1.f }
	, m_pLastCommand{}
{
	m_pRightMove = new flgin::DirectionalGridMove{ mover, true, true };
	m_pLeftMove = new flgin::DirectionalGridMove{ mover, true, false };
	m_pDownMove = new flgin::DirectionalGridMove{ mover, false, true };
	m_pUpMove = new flgin::DirectionalGridMove{ mover, false, false };
	m_pLastNode = grid->GetNodeNearestTo(m_pOwnerObject->GetPosition().x, m_pOwnerObject->GetPosition().y);
	m_pTargetNode = m_pLastNode;
}

void DigDug::FygarController::Update()
{
	if (IsNearTarget())
	{
		m_pOwnerObject->SetPosition(m_pTargetNode->GetPosition().x, m_pTargetNode->GetPosition().y);
		if (m_pLastCommand)
		{
			m_pLastCommand->Execute(*m_pOwnerObject, true);
			m_pLastCommand = nullptr;
		}
		flgin::GridNode* nextNode{ DetermineNextNode() };
		m_pLastNode = m_pTargetNode;
		m_pTargetNode = nextNode;
	}
	if (m_pMover->GetMovementDirection() == flgin::MovementDirection::Left || m_pMover->GetMovementDirection() == flgin::MovementDirection::Right)
	{
		m_AccuTime += FTime.GetDeltaTime();
		if (m_AccuTime > m_FireInterval)
		{
			m_AccuTime -= m_FireInterval;
			if (rand() % m_FireChance == 0)
			{
				m_pFygar->SetFiring(true);
				FInvoker.AddInvoke(new flgin::InvokeHolder<void>{ this, 1.2f,  [this]() { m_pFygar->SetFiring(false); } });
			}
		}
	}
}

bool DigDug::FygarController::IsNearTarget()
{
	return (abs(m_pOwnerObject->GetPosition().x - m_pTargetNode->GetPosition().x) + abs(m_pOwnerObject->GetPosition().y - m_pTargetNode->GetPosition().y)) < 1.f;
}

flgin::GridNode* DigDug::FygarController::DetermineNextNode()
{
	flgin::GridNode* nextNode{};
	int initial{ rand() % 4 };
	int curr{ initial + 1 };
	if (curr == 4) curr = 0;

	while (curr != initial)
	{
		switch (curr)
		{
		case 0:
			if ((nextNode = m_pTargetNode->GetLeftNode()) != nullptr)
			{
				if (!nextNode->IsBlocked() && nextNode != m_pLastNode)
				{
					m_pLeftMove->Execute(*m_pOwnerObject, false);
					m_pLastCommand = m_pLeftMove;
					return m_pTargetNode->GetLeftNode();
				}
			}
			break;
		case 1:
			if ((nextNode = m_pTargetNode->GetRightNode()) != nullptr)
			{
				if (!nextNode->IsBlocked() && nextNode != m_pLastNode)
				{
					m_pRightMove->Execute(*m_pOwnerObject, false);
					m_pLastCommand = m_pRightMove;
					return m_pTargetNode->GetRightNode();
				}
			}
			break;
		case 2:
			if ((nextNode = m_pTargetNode->GetUpNode()) != nullptr)
			{
				if (!nextNode->IsBlocked() && nextNode != m_pLastNode)
				{
					m_pUpMove->Execute(*m_pOwnerObject, false);
					m_pLastCommand = m_pUpMove;
					return m_pTargetNode->GetUpNode();
				}
			}
			break;
		case 3:
			if ((nextNode = m_pTargetNode->GetDownNode()) != nullptr)
			{
				if (!nextNode->IsBlocked() && nextNode != m_pLastNode)
				{
					m_pDownMove->Execute(*m_pOwnerObject, false);
					m_pLastCommand = m_pDownMove;
					return m_pTargetNode->GetDownNode();
				}
			}
			break;
		}
		++curr;
		if (curr == 4) curr = 0;
	}
	return m_pTargetNode;
}
