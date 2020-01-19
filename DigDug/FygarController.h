#pragma once
#include "BaseComponent.h"

namespace flgin
{
	class GridMovementComponent;
	class GridNode;
	class DirectionalGridMove;
	class MovementGrid;
}

namespace DigDug
{
	class Fygar;

	class FygarController final : public flgin::BaseComponent
	{
	public:
		FygarController(flgin::GameObject* ownerObject, Fygar* fygar, flgin::GridMovementComponent* mover, flgin::MovementGrid* grid);
		~FygarController() = default;
		void Update() override;

	private:
		bool IsNearTarget();
		flgin::GridNode* DetermineNextNode();

		float m_AccuTime;
		float m_FireInterval;
		UINT m_FireChance;

		Fygar* m_pFygar;
		flgin::GridNode* m_pLastNode;
		flgin::GridNode* m_pTargetNode;
		flgin::GridMovementComponent* m_pMover;
		flgin::DirectionalGridMove* m_pLastCommand;
		flgin::DirectionalGridMove* m_pUpMove;
		flgin::DirectionalGridMove* m_pDownMove;
		flgin::DirectionalGridMove* m_pLeftMove;
		flgin::DirectionalGridMove* m_pRightMove;
	};
}

