#pragma once
#include <vector>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "BaseComponent.h"

namespace flgin
{
	class GridNode;
	class GridConnection
	{
	public:
		GridConnection() : m_pEndNode{ nullptr }, m_pStartNode{ nullptr }, m_Weight{ -1 }{}
		GridConnection(GridNode* pStartNode, GridNode* pEndNode);
		bool operator==(const GridConnection& other) const;

		int GetWeight();
		GridNode* GetStartNode() const { return m_pStartNode; }
		GridNode* GetEndNode() const { return m_pEndNode; }
		void SetHeadConnection(GridConnection* newHead) { m_pHeadConnection = newHead; }
		GridConnection* GetHeadConnection() { return m_pHeadConnection; }

	private:
		int m_Weight;
		GridNode* m_pStartNode;
		GridNode* m_pEndNode;
		GridConnection* m_pHeadConnection;
	};

	class GridNode
	{
	public:
		GridNode();
		GridNode(glm::vec2 pos, GridNode* leftNode = nullptr, GridNode* rightNode = nullptr, GridNode* upNode = nullptr, GridNode* downNode = nullptr);
		glm::vec2 GetPosition() const;
		std::vector<GridConnection>& GetConnections() { return m_Connections; }
		GridNode* GetLeftNode() { return m_pLeftNode; }
		GridNode* GetRightNode() { return m_pRightNode; }
		GridNode* GetUpNode() { return m_pUpNode; }
		GridNode* GetDownNode() { return m_pDownNode; }
		void SetBlocked(bool isBlocked) { m_IsBlocked = isBlocked; }
		bool IsBlocked() const { return m_IsBlocked; }

	private:
		bool m_IsBlocked;
		glm::vec2 m_Position;
		GridNode* m_pLeftNode;
		GridNode* m_pRightNode;
		GridNode* m_pUpNode;
		GridNode* m_pDownNode;
		std::vector<GridConnection> m_Connections;
	};

	class MovementGrid : public BaseComponent
	{
	public:
		MovementGrid(GameObject* pOwnerObject, unsigned int rows, unsigned int cols, float distBetween);
		~MovementGrid();
		void Update() override;
		GridNode* GetNodeNearestTo(float x, float y);
		GridNode* GetGrid();
		unsigned int GetGridSize() const { return m_Rows * m_Cols; }
		float GetNodeSize() const { return m_DistBetween; }

	private:
		unsigned int m_Rows;
		unsigned int m_Cols;
		float m_DistBetween;
		GridNode* m_pNodes;
	};
}