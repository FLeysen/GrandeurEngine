#pragma once
#include "MovementGrid.h"
#include "GridMovementComponent.h"
#include <deque>

namespace flgin
{
	class PathfinderComponent final : public GridMovementComponent
	{
	public:
		PathfinderComponent(GameObject* const pOwnerObject, float maxVelocity, MovementGrid* pAttachedGrid, float acceptableTurnDist = 1.0f);
		void Update() override;
		void SetTarget(float x, float y);
		void SetActive(bool isActive);

	private:
		void FindPath();
		void Move(GridNode const* moveTo);

		bool m_TargetChanged;
		bool m_IsActive;
		glm::vec2 m_Target;
		std::deque<GridNode const*> m_pPath;
	};
}