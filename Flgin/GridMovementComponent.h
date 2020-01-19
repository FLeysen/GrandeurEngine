#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace flgin
{
	enum class MovementDirection : UINT8
	{
		Up, Down, Left, Right
	};

	class MovementGrid;
	class GridMovementComponent : public BaseComponent
	{
	public:
		GridMovementComponent(GameObject* const ownerObject, float maxVelocity, MovementGrid* pAttachedGrid, float acceptableTurnDist = 60.0f, bool canDig = false);
		void Update() override;
		void SetMoving(bool isHorizontal, bool isPositiveDirection);
		void StopMoving();
		glm::vec2 GetVelocity();
		MovementDirection GetMovementDirection() const { return m_LastMovedDir; }
		void Enable() { m_Enabled = true; }
		void Disable() { m_Enabled = false; }

	protected:
		void MoveLeft();
		void MoveRight();
		void MoveDown();
		void MoveUp();
		void ClampVelocity();

		bool m_Enabled;
		bool m_AllowedToDig;
		bool m_WasStopped;
		MovementDirection m_LastMovedDir;
		float m_MaxVelocity;
		float m_MaxTurnDistance; //Uses deltatime, raw distance can be much shorter on higher fps
		glm::vec2 m_CurrentVelocity;
		glm::vec2 m_TargetPos;
		MovementGrid* m_pMovementGrid;
	};
}