#include "pch.h"
#include "FygarStates.h"
#include "Fygar.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "TextLocalizer.h"
#include "GridMovementComponent.h"
#include "Timer.h"
#include "Player.h"

void DigDug::FygarState::SetFygar(Fygar * pFygar)
{
	m_pFygar = pFygar;
}

void DigDug::FygarState::SetSprite(flgin::SpriteComponent* pSprite)
{
	m_pSprite = pSprite;
}

void DigDug::FygarState::SetMover(flgin::GridMovementComponent * pMover)
{
	m_pMover = pMover;
}

void DigDug::FygarIdleState::Enter()
{
	m_pSprite->SetTexture(FResourceManager.LoadTexture(FLocalizer.Get("texFygar")), true);
	m_pSprite->SetSpriteInfo(4, 1, 30.0f, 30.0f, 0.4f);
}

void DigDug::FygarIdleState::Exit()
{
}

bool DigDug::FygarIdleState::Update()
{
	switch (m_pMover->GetMovementDirection())
	{
	case flgin::MovementDirection::Up:
		m_pSprite->SetFlips(false, false);
		m_pSprite->SetRotation(270.f);
		break;
	case flgin::MovementDirection::Down:
		m_pSprite->SetFlips(false, false);
		m_pSprite->SetRotation(90.f);
		break;
	case flgin::MovementDirection::Left:
		m_pSprite->SetFlips(true, false);
		m_pSprite->SetRotation(0.f);
		break;
	case flgin::MovementDirection::Right:
		m_pSprite->SetFlips(false, false);
		m_pSprite->SetRotation(0.f);
		break;
	}

	if (!m_pFygar->IsBloating())
	{
		if (m_pFygar->IsFiring())
		{
			FygarFiringState* fireState{ new FygarFiringState{} };
			fireState->SetFygar(m_pFygar);
			fireState->SetMover(m_pMover);
			fireState->SetSprite(m_pSprite);
			m_pTargetState = fireState;
			return true;
		}
		return false;
	}
	FygarBloatingState* dyingState{ new FygarBloatingState{} };
	dyingState->SetFygar(m_pFygar);
	dyingState->SetMover(m_pMover);
	dyingState->SetSprite(m_pSprite);
	m_pTargetState = dyingState;
	return true;
}

void DigDug::FygarFiringState::Enter()
{
	flgin::GameObject* fire{ m_pFygar->GetFire() };
	fire->SetActive(true);

	m_pSprite->SetTexture(FResourceManager.LoadTexture(FLocalizer.Get("texFygarBreathe")), true);
	m_pSprite->SetSpriteInfo(6, 1, 30.f, 30.f, 0.2f, true);

	flgin::SpriteComponent* fireSprite{ fire->GetComponent<flgin::SpriteComponent>() };
	fireSprite->SetSpriteInfo(6, 1, 30.f, 24.f, 0.2f, true);
	fireSprite->SetRotationalOffset(0.f, 0.f);

	float xPos{ m_pFygar->GetGameObject()->GetPosition().x };
	float yPos{ m_pFygar->GetGameObject()->GetPosition().y };
	m_pMover->Disable();

	switch (m_pMover->GetMovementDirection())
	{
	case flgin::MovementDirection::Up:
		fireSprite->SetFlips(false, false);
		fireSprite->SetRotation(270.f);
		yPos -= 30.f;
		break;
	case flgin::MovementDirection::Down:
		fireSprite->SetFlips(false, false);
		fireSprite->SetRotation(90.f);
		yPos += 30.f;
		break;
	case flgin::MovementDirection::Left:
		fireSprite->SetFlips(true, false);
		fireSprite->SetRotation(0.f);
		xPos -= 30.f;
		break;
	case flgin::MovementDirection::Right:
		fireSprite->SetFlips(false, false);
		fireSprite->SetRotation(0.f);
		xPos += 30.f;
		break;
	}
	fire->SetPosition(xPos, yPos);
}

bool DigDug::FygarFiringState::Update()
{
	if (!m_pFygar->IsBloating())
	{
		if (!m_pFygar->IsFiring())
		{
			FygarIdleState* idleState{ new FygarIdleState{} };
			idleState->SetFygar(m_pFygar);
			idleState->SetMover(m_pMover);
			idleState->SetSprite(m_pSprite);
			m_pTargetState = idleState;
			return true;
		}
		return false;
	}
	FygarBloatingState* dyingState{ new FygarBloatingState{} };
	dyingState->SetFygar(m_pFygar);
	dyingState->SetMover(m_pMover);
	dyingState->SetSprite(m_pSprite);
	m_pTargetState = dyingState;
	return true;
}

void DigDug::FygarFiringState::Exit()
{
	m_pFygar->GetFire()->SetActive(false);
	m_pMover->Enable();
}

void DigDug::FygarBloatingState::Enter()
{
	m_pMover->Disable();
}

bool DigDug::FygarBloatingState::Update()
{
	if (m_pFygar->IsBloating())
	{
		m_BloatTime += FTime.GetDeltaTime();
		float size{ 30.f * (1 + m_BloatTime / m_MaxBloatTime * m_MaxBloatScale) };
		m_pFygar->SetDeflating(false);
		m_pSprite->SetDimensions(size, size);
		m_pSprite->SetPositionOffset(size * -0.5f, size * -0.5f);
		if (m_BloatTime > m_MaxBloatTime)
		{
			m_pFygar->GetHitBy()->SetFiring(false);
			m_pFygar->GetHitBy()->ChangeScore(m_pFygar->GetScoreWorth());
			m_pFygar->Die();
		}
	}
	else
	{
		m_BloatTime -= FTime.GetDeltaTime();
		float size{ 30.f * (1 + m_BloatTime / m_MaxBloatTime * m_MaxBloatScale) };
		m_pFygar->SetDeflating(true);
		m_pSprite->SetPositionOffset(size * -0.5f, size * -0.5f);
		m_pSprite->SetDimensions(size, size);
		if (m_BloatTime < 0.f)
		{
			m_pSprite->SetPositionOffset(-15.f, -15.f);
			m_pSprite->SetDimensions(30.f, 30.f);
			FygarIdleState* idleState{ new FygarIdleState{} };
			idleState->SetFygar(m_pFygar);
			idleState->SetMover(m_pMover);
			idleState->SetSprite(m_pSprite);
			m_pTargetState = idleState;
			return true;
		}
	}
	return false;
}

void DigDug::FygarBloatingState::Exit()
{
	m_pMover->Enable();
	m_pFygar->SetDeflating(false);
}