#include "FlginPCH.h"
#include "FreeMover.h"
#include "Timer.h"

flgin::FreeMover::FreeMover(GameObject* pOwnerObject, float maxVelocity)
	: FreeMover(pOwnerObject, maxVelocity, maxVelocity, 0.f, 0.f)
{}

flgin::FreeMover::FreeMover(GameObject* pOwnerObject, float maxVelocity, float accel)
	: FreeMover(pOwnerObject, maxVelocity, maxVelocity, accel, accel)
{}

flgin::FreeMover::FreeMover(GameObject * pOwnerObject, float maxXVelocity, float maxYVelocity, float xAccel, float yAccel)
	: BaseComponent(pOwnerObject)
	, m_CurrVelocity{}
	, m_MaxVelocity{ maxXVelocity, maxYVelocity }
	, m_Acceleration{ xAccel, yAccel }
	, m_UseAccel{ xAccel != 0.0f && yAccel != 0.0f }
	, m_IsMoving{ false }
{}

void flgin::FreeMover::Update()
{
	if (m_IsMoving)
	{
		if (m_UseAccel)
		{
			m_CurrVelocity += m_Acceleration * FTime.GetDeltaTime();
			ClampVelocity();
		}
		else
			m_CurrVelocity = m_MaxVelocity;

		glm::vec2 target{ m_pOwnerObject->GetPosition() };
		target += m_CurrVelocity * FTime.GetDeltaTime();
		m_pOwnerObject->SetPosition(target.x, target.y);
	}
	else
		m_CurrVelocity = { 0.f, 0.f };
}

void flgin::FreeMover::ClampVelocity()
{
	if (signbit(m_CurrVelocity.x))
	{
		if (m_CurrVelocity.x < m_MaxVelocity.x)
			m_CurrVelocity.x = m_MaxVelocity.x;
	}
	else if (m_CurrVelocity.x > m_MaxVelocity.x)
			 m_CurrVelocity.x = m_MaxVelocity.x;

	if (signbit(m_CurrVelocity.y))
	{
		if (m_CurrVelocity.y < m_MaxVelocity.y)
			m_CurrVelocity.y = m_MaxVelocity.y;
	}
	else if (m_CurrVelocity.y > m_MaxVelocity.y)
			 m_CurrVelocity.y = m_MaxVelocity.y;
}
