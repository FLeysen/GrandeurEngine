#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace flgin
{
	class FreeMover : public BaseComponent
	{
	public:
		FreeMover(GameObject* pOwnerObject, float maxVelocity);
		FreeMover(GameObject* pOwnerObject, float maxXVelocity, float maxYVelocity);
		FreeMover(GameObject* pOwnerObject, float maxXVelocity, float maxYVelocity, float xAccel, float yAccel);

		void SetMaxXVelocity(float xVal) { m_MaxVelocity.x = xVal; }
		void SetMaxYVelocity(float yVal) { m_MaxVelocity.y = yVal; }
		void SetXAccel(float xVal) { m_Acceleration.x = xVal; }
		void SetYAccel(float yVal) { m_Acceleration.y = yVal; }
		void SetMoving(bool isMoving) { m_IsMoving = isMoving; }

		void Update() override;

	private:
		void ClampVelocity();

		bool m_UseAccel;
		bool m_IsMoving;
		glm::vec2 m_CurrVelocity;
		glm::vec2 m_MaxVelocity;
		glm::vec2 m_Acceleration;
	};
}