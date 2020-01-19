#include "FlginPCH.h"
#include "MovementGrid.h"
#include "GameObject.h"

flgin::MovementGrid::MovementGrid(GameObject* pOwnerObject, unsigned int rows, unsigned int cols, float distBetween)
	: BaseComponent(pOwnerObject)
	, m_pNodes{ new GridNode[rows * cols]{} }
	, m_Rows{ rows }
	, m_Cols{ cols }
	, m_DistBetween{ distBetween }
{
	unsigned int nodeId{ 0 };
	glm::vec2 position{ pOwnerObject->GetPosition() };
	GridNode* leftNode{ nullptr };
	GridNode* rightNode{ nullptr };
	GridNode* upNode{ nullptr };
	GridNode* downNode{ nullptr };

	for (unsigned int row{}; row < rows; ++row)
	{
		for (unsigned int col{}; col < cols; ++col)
		{
			nodeId = row * cols + col;

			if (col > 0) leftNode = &m_pNodes[nodeId - 1];
			else leftNode = nullptr;

			if (col < cols - 1) rightNode = &m_pNodes[nodeId + 1];
			else rightNode = nullptr;

			if (row > 0) upNode = &m_pNodes[nodeId - cols];
			else upNode = nullptr;

			if (row < rows - 1) downNode = &m_pNodes[nodeId + cols];
			else downNode = nullptr;

			m_pNodes[nodeId] = GridNode{ position, leftNode, rightNode, upNode, downNode };

			position.x += distBetween;
		}
		position.x = pOwnerObject->GetPosition().x;
		position.y += distBetween;
	}
}

flgin::GridNode* flgin::MovementGrid::GetNodeNearestTo(float x, float y)
{
	if (!m_pNodes) return nullptr;

	glm::vec2 ownerPosition{ m_pOwnerObject->GetPosition() };
	x -= ownerPosition.x;
	y -= ownerPosition.y;

	float xSteps{ x / m_DistBetween };
	float ySteps{ y / m_DistBetween };
	int col{ static_cast<int>(round(xSteps)) };
	int row{ static_cast<int>(round(ySteps)) };

	if (col < 0) col = 0;
	else if (col >= static_cast<int>(m_Cols)) col = m_Cols - 1;
	if (row < 0) row = 0;
	else if (row >= static_cast<int>(m_Rows)) row = m_Rows - 1;

	return &m_pNodes[col + row * m_Cols];
}

flgin::GridNode* flgin::MovementGrid::GetGrid()
{
	return m_pNodes;
}

flgin::MovementGrid::~MovementGrid()
{
	FLogger.SafeDeleteArray(m_pNodes);
}

void flgin::MovementGrid::Update()
{}

flgin::GridNode::GridNode()
	: m_pLeftNode{}
	, m_pRightNode{}
	, m_pDownNode{}
	, m_pUpNode{}
	, m_Position{}
	, m_IsBlocked{}
	, m_Connections{}
{}

flgin::GridNode::GridNode(glm::vec2 pos, GridNode* leftNode, GridNode* rightNode, GridNode* upNode, GridNode* downNode)
	: m_pLeftNode{ leftNode }
	, m_pRightNode{ rightNode }
	, m_pUpNode{ upNode }
	, m_pDownNode{ downNode }
	, m_Position{ pos }
	, m_IsBlocked{ false }
	, m_Connections{}
{
	if (m_pLeftNode) m_Connections.push_back(GridConnection{ this, m_pLeftNode });
	if (m_pRightNode) m_Connections.push_back(GridConnection{ this, m_pRightNode });
	if (m_pUpNode) m_Connections.push_back(GridConnection{ this, m_pUpNode });
	if (m_pDownNode) m_Connections.push_back(GridConnection{ this, m_pDownNode });
}

glm::vec2 flgin::GridNode::GetPosition() const
{
	return m_Position;
}

flgin::GridConnection::GridConnection(GridNode* pStartNode, GridNode* pEndNode)
	: m_pEndNode{ pEndNode }
	, m_pStartNode{ pStartNode }
	, m_Weight{ }
{}

bool flgin::GridConnection::operator==(const GridConnection& other) const
{
	return (m_pStartNode == other.m_pStartNode && m_pEndNode == other.m_pEndNode)
		|| (m_pStartNode == other.m_pEndNode && m_pEndNode == other.m_pStartNode);
}

int flgin::GridConnection::GetWeight()
{
	return m_Weight = static_cast<int>(abs(m_pStartNode->GetPosition().x - m_pEndNode->GetPosition().x) + abs(m_pStartNode->GetPosition().y - m_pEndNode->GetPosition().y));
}
