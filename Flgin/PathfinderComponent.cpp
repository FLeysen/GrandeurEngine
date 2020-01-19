#include "FlginPCH.h"
#include "PathfinderComponent.h"
#include <algorithm>
#include "Timer.h"

flgin::PathfinderComponent::PathfinderComponent(GameObject* const pOwnerObject, float maxVelocity, MovementGrid* pAttachedGrid, float acceptableTurnDist)
	: GridMovementComponent(pOwnerObject, maxVelocity, pAttachedGrid, acceptableTurnDist)
	, m_Target{}
	, m_TargetChanged{}
	, m_IsActive{ true }
	, m_pPath{}
{}

void flgin::PathfinderComponent::Update()
{
	if (m_IsActive)
	{
		if (m_TargetChanged) FindPath();
		m_TargetChanged = false;
		m_WasStopped = false;
		m_CurrentVelocity.x = m_MaxVelocity * FTime.GetDeltaTime();

		if (m_pPath.size() > 0)
			Move(m_pPath[0]);
	}
}

void flgin::PathfinderComponent::SetTarget(float x, float y)
{
	m_TargetChanged = true;
	m_Target.x = x;
	m_Target.y = y;
}

void flgin::PathfinderComponent::SetActive(bool isActive)
{
	m_IsActive = isActive;
}

void flgin::PathfinderComponent::FindPath()
{
	m_pPath.clear();
	std::vector<GridConnection*> openList{};
	std::vector<GridConnection*> closedList{};
	GridConnection* currentConnection{};

	glm::vec2 pos{ m_pOwnerObject->GetPosition() };
	GridNode* pNearestNode{ m_pMovementGrid->GetNodeNearestTo(pos.x, pos.y) };
	GridNode* pNodeNearestToEnd{ m_pMovementGrid->GetNodeNearestTo(m_Target.x, m_Target.y) };
	GridNode* pNearestOtherNode{ nullptr };
	glm::vec2 nearestPos{ pNearestNode->GetPosition() };

	if (nearestPos.x > pos.x)
		pNearestOtherNode = pNearestNode->GetLeftNode();
	
	else if (nearestPos.x < pos.x)
		pNearestOtherNode = pNearestNode->GetRightNode();

	else if (nearestPos.y > pos.y)
		pNearestOtherNode = pNearestNode->GetDownNode();

	else
		pNearestOtherNode = pNearestNode->GetUpNode();

	///if (pNearestOtherNode)
	///{
	///	if (!pNearestOtherNode->IsBlocked())
	///	{
	///		for (GridConnection& conn : pNearestOtherNode->GetConnections())
	///			openList.push_back(&conn);
	///	}
	///}

	for (GridConnection& conn : pNearestNode->GetConnections())
		openList.push_back(&conn);

	while (!openList.empty())
	{
		currentConnection = openList[0];
		for (size_t i{ 1 }, listSize{ openList.size() }; i < listSize; ++i)
		{
			if (openList[i]->GetWeight() < currentConnection->GetWeight())
				currentConnection = openList[i];
		}

		openList.erase(std::remove(openList.begin(), openList.end(), currentConnection), openList.end());
		closedList.push_back(currentConnection);

		std::vector<GridConnection>& currConnections{ currentConnection->GetEndNode()->GetConnections() };
		std::vector<GridConnection>::iterator result{ std::find_if(currConnections.begin(), currConnections.end(),
			[pNodeNearestToEnd](GridConnection& connection) { return connection.GetEndNode() == pNodeNearestToEnd; }) };

		if (result != currConnections.end())
		{
			result->SetHeadConnection(currentConnection);
			currentConnection = &*result;
			openList.clear();
			break;
		}

		for (GridConnection& connection : currConnections)
		{
			if (std::find(closedList.cbegin(), closedList.cend(), &connection) != closedList.cend()) continue;
			else if (std::find(openList.cbegin(), openList.cend(), &connection) != openList.cend()) continue;

			connection.SetHeadConnection(currentConnection);
			openList.push_back(&connection);
		}
	}

	while (currentConnection->GetStartNode() != pNearestNode)
	{
		m_pPath.push_back(currentConnection->GetEndNode());
		currentConnection = currentConnection->GetHeadConnection();
	}
	m_pPath.push_back(currentConnection->GetEndNode());
	std::reverse(m_pPath.begin(), m_pPath.end());
}

void flgin::PathfinderComponent::Move(GridNode const* moveTo)
{
	glm::vec2 pos{ m_pOwnerObject->GetPosition() };
	glm::vec2 nodePos{ moveTo->GetPosition() };

	if (pos.x < nodePos.x)
	{
		pos.x += m_CurrentVelocity.x;

		if (pos.x > nodePos.x && m_pPath.size() > 1)
		{
			m_CurrentVelocity.x -= pos.x - nodePos.x;
			pos.x = nodePos.x;
			Move(m_pPath[1]);
		}
	}

	else if (pos.x > nodePos.x)
	{
		pos.x -= m_CurrentVelocity.x;

		if (pos.x < nodePos.x && m_pPath.size() > 1)
		{
			m_CurrentVelocity.x -= nodePos.x - pos.x;
			pos.x = nodePos.x;
			Move(m_pPath[1]);
		}
	}

	else if (pos.y < nodePos.y)
	{
		pos.y += m_CurrentVelocity.x;

		if (pos.y > nodePos.y && m_pPath.size() > 1)
		{
			m_CurrentVelocity.x -= pos.y - nodePos.y;
			pos.y = nodePos.y;
			Move(m_pPath[1]);
		}
	}

	else if (pos.y > nodePos.y)
	{
		pos.y += m_CurrentVelocity.x;

		if (pos.y < nodePos.y && m_pPath.size() > 1)
		{
			m_CurrentVelocity.x -= nodePos.y - pos.y;
			pos.y = nodePos.y;
			Move(m_pPath[1]);
		}
	}
}