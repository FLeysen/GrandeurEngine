#pragma once
#include "BaseComponent.h"

namespace flgin
{
	class GridMovementComponent;
	class GridNode;
	class DirectionalGridMove;
	class MovementGrid;
	class FreeMover;
	class Command;
}

namespace DigDug
{
	class Pooka;

	class PookaController final : public flgin::BaseComponent
	{
	public:
		PookaController(flgin::GameObject* ownerObject, Pooka* pooka);
		~PookaController() = default;
		void Update() override;

	private:
		bool IsNearTarget();
		flgin::GridNode* DetermineNextNode();

		float m_AccuTime;
		float m_GhostInterval;
		float m_MaxVelocity;
		float m_AcceptableNearDist;

		Pooka* m_pPooka;
		flgin::GridNode* m_pLastNode;
		flgin::GridNode* m_pTargetNode;
		flgin::FreeMover* m_pFreeMover;
		flgin::GridMovementComponent* m_pGridMover;
		flgin::Command* m_pLastCommand;
		flgin::DirectionalGridMove* m_pUpMove;
		flgin::DirectionalGridMove* m_pDownMove;
		flgin::DirectionalGridMove* m_pLeftMove;
		flgin::DirectionalGridMove* m_pRightMove;
	};
}
