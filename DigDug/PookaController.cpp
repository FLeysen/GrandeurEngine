#include "pch.h"
#include "PookaController.h"
#include "Pooka.h"
#include "GridMovementComponent.h"
#include "MovementGrid.h"
#include "MovementCommands.h"
#include "Timer.h"
#include "Invoker.h"
#include "InputManager.h"
#include "FreeMover.h"

DigDug::PookaController::PookaController(flgin::GameObject* ownerObject, Pooka* pooka)
	: BaseComponent(ownerObject)
	, m_pPooka{ pooka }
	, m_pGridMover{ ownerObject->GetComponent<flgin::GridMovementComponent>() }
	, m_pFreeMover{ ownerObject->GetComponent<flgin::FreeMover>() }
	, m_pLastNode{}
	, m_pTargetNode{}
	, m_pUpMove{}
	, m_pDownMove{}
	, m_pLeftMove{}
	, m_pRightMove{}
	, m_AccuTime{}
	, m_pLastCommand{}
	, m_GhostInterval{ (rand() % 10000 + 10000) / 1000.f }
	, m_MaxVelocity{ 200.f }
	, m_AcceptableNearDist{ 60.f }
{
	m_pRightMove = new flgin::DirectionalGridMove{ m_pGridMover, true, true };
	m_pLeftMove = new flgin::DirectionalGridMove{ m_pGridMover, true, false };
	m_pDownMove = new flgin::DirectionalGridMove{ m_pGridMover, false, true };
	m_pUpMove = new flgin::DirectionalGridMove{ m_pGridMover, false, false };
	m_pLastNode = pooka->GetGrid()->GetNodeNearestTo(m_pOwnerObject->GetPosition().x, m_pOwnerObject->GetPosition().y);
	m_pTargetNode = m_pLastNode;
}

void DigDug::PookaController::Update()
{
	if (IsNearTarget())
	{
		m_AcceptableNearDist = 60.f;
		m_pPooka->SetGhosting(false);
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

	if (!m_pPooka->IsGhosting())
	{
		m_AcceptableNearDist = 240.f;
		m_AccuTime += FTime.GetDeltaTime();
		if (m_AccuTime > m_GhostInterval)
		{
			m_AccuTime -= m_GhostInterval;
			m_pTargetNode = m_pPooka->GetGrid()->GetNodeNearestTo(FInputManager.GetPlayer(0)->GetGameObject()->GetPosition().x, FInputManager.GetPlayer(0)->GetGameObject()->GetPosition().y);

			float xVel{ 0.f };
			float yVel{ 0.f };
			float yDist{ m_pOwnerObject->GetPosition().y - m_pTargetNode->GetPosition().y };
			float xDist{ m_pOwnerObject->GetPosition().x - m_pTargetNode->GetPosition().x };
			if (abs(yDist) < 0.1f)
			{
				xVel = Sign(xDist) * -m_MaxVelocity;
				yVel = 0.f;
			}
			else if (abs(xDist) < 0.1f)
			{
				xVel = 0.f;
				yVel = Sign(yDist) * -m_MaxVelocity;
			}
			else
			{
				float total{ abs(xDist) + abs(yDist) };
				xVel = -m_MaxVelocity * xDist / total;
				yVel = -m_MaxVelocity * yDist / total;
			}
			m_pFreeMover->SetMaxXVelocity(xVel);
			m_pFreeMover->SetMaxYVelocity(yVel);

			m_pLastNode = m_pTargetNode;
			m_pLastCommand = nullptr;
			m_pPooka->SetGhosting(true);

			if (m_pLastCommand)
			{
				m_pLastCommand->Execute(*m_pOwnerObject, true);
				m_pLastCommand = nullptr;
			}
			flgin::GridNode* nextNode{ DetermineNextNode() };
			m_pLastNode = m_pTargetNode;
			m_pTargetNode = nextNode;
		}
	}
}

bool DigDug::PookaController::IsNearTarget()
{
	if (m_pPooka->IsGhosting()) return (abs(m_pOwnerObject->GetPosition().x - m_pLastNode->GetPosition().x) + abs(m_pOwnerObject->GetPosition().y - m_pLastNode->GetPosition().y)) < (m_AcceptableNearDist * FTime.GetDeltaTime());
	return (abs(m_pOwnerObject->GetPosition().x - m_pTargetNode->GetPosition().x) + abs(m_pOwnerObject->GetPosition().y - m_pTargetNode->GetPosition().y)) < (m_AcceptableNearDist * FTime.GetDeltaTime());
}

flgin::GridNode* DigDug::PookaController::DetermineNextNode()
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
