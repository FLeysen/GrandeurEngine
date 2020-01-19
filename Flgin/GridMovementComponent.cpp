#include "FlginPCH.h"
#include "GridMovementComponent.h"
#include "MovementGrid.h"
#include "Timer.h"

flgin::GridMovementComponent::GridMovementComponent(GameObject* const ownerObject, float maxVelocity, MovementGrid* pAttachedGrid, float acceptableTurnDist, bool canDig)
	: BaseComponent(ownerObject)
	, m_WasStopped{ false }
	, m_CurrentVelocity{ 0,0 }
	, m_MaxVelocity{ maxVelocity }
	, m_pMovementGrid{ pAttachedGrid }
	, m_MaxTurnDistance{ acceptableTurnDist }
	, m_TargetPos{ ownerObject->GetPosition() }
	, m_AllowedToDig{ canDig }
	, m_LastMovedDir{ MovementDirection::Right }
	, m_Enabled{ true }
{
	if (m_pMovementGrid)
	{
		GridNode* nearestNode{ m_pMovementGrid->GetNodeNearestTo(m_TargetPos.x, m_TargetPos.y) };
		m_pOwnerObject->SetPosition(nearestNode->GetPosition().x, nearestNode->GetPosition().y);
		m_TargetPos = nearestNode->GetPosition();
	}
	else
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "GridMovementComponent has no attached Movement Grid!" });
}

void flgin::GridMovementComponent::Update()
{
	m_WasStopped = false;
	
	if (m_Enabled)
	{
		m_TargetPos = m_pOwnerObject->GetPosition();
		if (m_CurrentVelocity.x < 0.0f)
			MoveLeft();
		else if (m_CurrentVelocity.x > 0.0f)
			MoveRight();

		if (m_CurrentVelocity.y > 0.0f)
			MoveDown();
		else if (m_CurrentVelocity.y < 0.0f)
			MoveUp();

		m_pOwnerObject->SetPosition(m_TargetPos.x, m_TargetPos.y);
	}
}

void flgin::GridMovementComponent::SetMoving(bool isHorizontal, bool isPositiveDirection)
{
	(isHorizontal ? m_CurrentVelocity.x : m_CurrentVelocity.y)
		+= m_MaxVelocity * (isPositiveDirection ? 1 : -1);
}

void flgin::GridMovementComponent::StopMoving()
{
	if (!m_WasStopped) m_CurrentVelocity = { 0.0f, 0.0f };
	m_WasStopped = true;
}

glm::vec2 flgin::GridMovementComponent::GetVelocity()
{
	return m_CurrentVelocity;
}

void flgin::GridMovementComponent::MoveLeft()
{
	glm::vec2 pos{ m_TargetPos };
	GridNode* nearestNode{ m_pMovementGrid->GetNodeNearestTo(pos.x, pos.y) };
	if (!nearestNode)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "GridMovementComponent Update could not find a nearest node in movement grid.", this });
		return;
	}

	glm::vec2 nodePos{ nearestNode->GetPosition() };
	if (abs(pos.y - nodePos.y) < m_MaxTurnDistance * FTime.GetDeltaTime())
	{
		m_TargetPos.y = nodePos.y;
		m_TargetPos.x += m_CurrentVelocity.x * FTime.GetDeltaTime();
		m_LastMovedDir = MovementDirection::Left;
		if (m_TargetPos.x < nodePos.x)
		{
			GridNode* leftNode{ nearestNode->GetLeftNode() };
			if (!leftNode)
				m_TargetPos.x = nodePos.x;
			else if (leftNode->IsBlocked() && !m_AllowedToDig)
				m_TargetPos.x = nodePos.x;

			else if (pos.x < leftNode->GetPosition().x && !leftNode->GetLeftNode())
				m_TargetPos.x = leftNode->GetPosition().x;
		}
	}
}

void flgin::GridMovementComponent::MoveRight()
{
	glm::vec2 pos{ m_TargetPos };
	GridNode* nearestNode{ m_pMovementGrid->GetNodeNearestTo(pos.x, pos.y) };
	if (!nearestNode)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "GridMovementComponent Update could not find a nearest node in movement grid.", this });
		return;
	}

	glm::vec2 nodePos{ nearestNode->GetPosition() };
	if (abs(pos.y - nodePos.y) < m_MaxTurnDistance * FTime.GetDeltaTime())
	{
		m_TargetPos.y = nodePos.y;
		m_TargetPos.x += m_CurrentVelocity.x * FTime.GetDeltaTime();
		m_LastMovedDir = MovementDirection::Right;
		if (m_TargetPos.x > nodePos.x)
		{
			GridNode* rightNode{ nearestNode->GetRightNode() };
			if (!rightNode)
				m_TargetPos.x = nodePos.x;
			else if (rightNode->IsBlocked() && !m_AllowedToDig)
				m_TargetPos.x = nodePos.x;

			else if (pos.x > rightNode->GetPosition().x && !rightNode->GetRightNode())
				m_TargetPos.x = rightNode->GetPosition().x;
		}
	}
}

void flgin::GridMovementComponent::MoveDown()
{
	glm::vec2 pos{ m_TargetPos };
	GridNode* nearestNode{ m_pMovementGrid->GetNodeNearestTo(pos.x, pos.y) };
	if (!nearestNode)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "GridMovementComponent Update could not find a nearest node in movement grid.", this });
		return;
	}

	glm::vec2 nodePos{ nearestNode->GetPosition() };
	if (abs(pos.x - nodePos.x) < m_MaxTurnDistance * FTime.GetDeltaTime())
	{
		m_TargetPos.x = nodePos.x;
		m_TargetPos.y += m_CurrentVelocity.y * FTime.GetDeltaTime();
		m_LastMovedDir = MovementDirection::Down;
		if (m_TargetPos.y > nodePos.y)
		{
			GridNode* downNode{ nearestNode->GetDownNode() };
			if (!downNode)
				m_TargetPos.y = nodePos.y;
			else if (downNode->IsBlocked() && !m_AllowedToDig)
				m_TargetPos.y = nodePos.y;

			else if (pos.y > downNode->GetPosition().y && !downNode->GetDownNode())
				m_TargetPos.y = downNode->GetPosition().y;
		}
	}
}

void flgin::GridMovementComponent::MoveUp()
{
	glm::vec2 pos{ m_TargetPos };
	GridNode* nearestNode{ m_pMovementGrid->GetNodeNearestTo(pos.x, pos.y) };
	if (!nearestNode)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "GridMovementComponent Update could not find a nearest node in movement grid.", this });
		return;
	}

	glm::vec2 nodePos{ nearestNode->GetPosition() };
	if (abs(pos.x - nodePos.x) < m_MaxTurnDistance * FTime.GetDeltaTime())
	{
		m_TargetPos.x = nodePos.x;
		m_TargetPos.y += m_CurrentVelocity.y * FTime.GetDeltaTime();
		m_LastMovedDir = MovementDirection::Up;
		if (m_TargetPos.y < nodePos.y)
		{
			GridNode* upNode{ nearestNode->GetUpNode() };
			if (!upNode)
				m_TargetPos.y = nodePos.y;
			else if (upNode->IsBlocked() && !m_AllowedToDig)
				m_TargetPos.y = nodePos.y;

			else if (pos.y < upNode->GetPosition().y && !upNode->GetUpNode())
				m_TargetPos.y = upNode->GetPosition().y;
		}
	}
}

void flgin::GridMovementComponent::ClampVelocity()
{
	if (m_CurrentVelocity.x > m_MaxVelocity) m_CurrentVelocity.x = m_MaxVelocity;
	else if (m_CurrentVelocity.x < -m_MaxVelocity) m_CurrentVelocity.x = -m_MaxVelocity;
	if (m_CurrentVelocity.y > m_MaxVelocity) m_CurrentVelocity.y = m_MaxVelocity;
	else if (m_CurrentVelocity.y < -m_MaxVelocity) m_CurrentVelocity.y = -m_MaxVelocity;
}