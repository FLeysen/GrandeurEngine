#include "pch.h"
#include "DigDugStates.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TextLocalizer.h"
#include "GridMovementComponent.h"
#include "Timer.h"
#include "FreeMover.h"
#include "Invoker.h"
#include "ColliderComponent.h"
#include "Fygar.h"
#include "Pooka.h"

void DigDug::DigDugState::SetAttachedSprite(flgin::SpriteComponent* pSprite)
{
	m_pSpriteComponent = pSprite;
}

void DigDug::DigDugState::SetPlayer(Player* pPlayer)
{
	m_pPlayer = pPlayer;
}

DigDug::IdleState::IdleState()
	: DigDugState()
{}

void DigDug::IdleState::Enter()
{
	m_pSpriteComponent->SetTexture(FResourceManager.LoadTexture(FLocalizer.Get("texPlayer")), true);
	m_pSpriteComponent->SetSpriteInfo(6, 1, 30.f, 30.f, 0.4f, true);
	m_pGridMover = m_pPlayer->GetGameObject()->GetComponent<flgin::GridMovementComponent>();
}

bool DigDug::IdleState::Update()
{
	if (!m_pPlayer->IsDying())
	{
		if (!m_pPlayer->IsFiring())
		{
			if (m_pGridMover->GetVelocity().x != 0.f || m_pGridMover->GetVelocity().y != 0.f)
			{
				MovingState* movingState{ new MovingState{} };
				movingState->SetAttachedSprite(m_pSpriteComponent);
				movingState->SetPlayer(m_pPlayer);
				m_pTargetState = movingState;
				return true;
			}
			return false;
		}
		FiringState* fire{ new FiringState{} };
		fire->SetAttachedSprite(m_pSpriteComponent);
		fire->SetPlayer(m_pPlayer);
		m_pTargetState = fire;
		return true;
	}
	DeathState* deathState{ new DeathState{} };
	deathState->SetAttachedSprite(m_pSpriteComponent);
	deathState->SetPlayer(m_pPlayer);
	m_pTargetState = deathState;
	return true;
}

void DigDug::MovingState::Enter()
{
	m_pGridMover = m_pPlayer->GetGameObject()->GetComponent<flgin::GridMovementComponent>();
	m_pSpriteComponent->SetRotationalOffset(0.f, 0.f);
	m_PreviousDirection = m_pGridMover->GetMovementDirection();
	m_pSpriteComponent->SetTexture(FResourceManager.LoadTexture(FLocalizer.Get("texPlayerMoving")), true);
	m_pSpriteComponent->SetSpriteInfo(4, 1, 30.f, 30.f, 0.25f, true);
}

bool DigDug::MovingState::Update()
{
	if (!m_pPlayer->IsDying())
	{
		if (!m_pPlayer->IsFiring())
		{
			if (m_pGridMover->GetVelocity().x != 0.f || m_pGridMover->GetVelocity().y != 0.f)
			{
				switch (m_pGridMover->GetMovementDirection())
				{
				case flgin::MovementDirection::Up:
					m_pSpriteComponent->SetRotation(270.f);
					if (m_PreviousDirection == flgin::MovementDirection::Right) m_pSpriteComponent->SetFlips(false, false);
					else if (m_PreviousDirection == flgin::MovementDirection::Down) m_pSpriteComponent->SetFlips(false, !m_pSpriteComponent->GetFlippedVertical());
					break;
				case flgin::MovementDirection::Down:
					m_pSpriteComponent->SetRotation(90.f);
					if (m_PreviousDirection == flgin::MovementDirection::Left) m_pSpriteComponent->SetFlips(false, true);
					else if (m_PreviousDirection == flgin::MovementDirection::Up) m_pSpriteComponent->SetFlips(false, !m_pSpriteComponent->GetFlippedVertical());
					break;
				case flgin::MovementDirection::Left:
					m_pSpriteComponent->SetRotation(180.f);
					m_pSpriteComponent->SetFlips(false, true);
					break;
				case flgin::MovementDirection::Right:
					m_pSpriteComponent->SetRotation(0.f);
					m_pSpriteComponent->SetFlips(false, false);
					break;
				}
				m_PreviousDirection = m_pGridMover->GetMovementDirection();
				return false;
			}
			IdleState* idle{ new IdleState{} };
			idle->SetAttachedSprite(m_pSpriteComponent);
			idle->SetPlayer(m_pPlayer);
			m_pTargetState = idle;
			return true;
		}
		FiringState* fire{ new FiringState{} };
		fire->SetAttachedSprite(m_pSpriteComponent);
		fire->SetPlayer(m_pPlayer);
		m_pTargetState = fire;
		return true;
	}
	DeathState* deathState{ new DeathState{} };
	deathState->SetAttachedSprite(m_pSpriteComponent);
	deathState->SetPlayer(m_pPlayer);
	m_pTargetState = deathState;
	return true;
}

void DigDug::DeathState::Enter()
{
	m_pSpriteComponent->SetTexture(FResourceManager.LoadTexture(FLocalizer.Get("texPlayerDeath")), true);
	m_pSpriteComponent->SetSpriteInfo(6, 1, 30.f, 30.f, .35f, true);
	m_pGridMover = m_pPlayer->GetGameObject()->GetComponent<flgin::GridMovementComponent>();
	m_pGridMover->Disable();
	m_Duration = 2.1f;
}

bool DigDug::DeathState::Update()
{
	m_Elapsed += FTime.GetDeltaTime();
	if (m_Elapsed > m_Duration)
	{
		IdleState* idle{ new IdleState{} };
		idle->SetAttachedSprite(m_pSpriteComponent);
		idle->SetPlayer(m_pPlayer);
		m_pTargetState = idle;
		return true;
	}
	return false;
}

void DigDug::DeathState::Exit()
{
	m_pPlayer->GetGameObject()->SetPosition(m_pPlayer->GetInitPos().x, m_pPlayer->GetInitPos().y);
	m_pPlayer->SetDying(false);
	m_pGridMover->Enable();
	m_pSpriteComponent->SetTexture(FResourceManager.LoadTexture(FLocalizer.Get("texPlayer")), true);
	m_pSpriteComponent->SetPositionOffset(-15.f, -15.f);
	m_pSpriteComponent->SetSpriteInfo(6, 1, 30.0f, 30.0f, 0.4f);
	m_pSpriteComponent->SetFlips(false, false);
	m_pSpriteComponent->SetRotation(0.f);
}

void DigDug::FiringState::Enter()
{
	float pumpVelocity{ 288.f };
	m_pPumpMover = m_pPlayer->GetPump()->GetComponent<flgin::FreeMover>();
	m_pPumpMover->SetMoving(true);
	m_pPlayer->GetPump()->SetActive(true);

	flgin::SpriteComponent* pumpSprite{ m_pPlayer->GetPump()->GetComponent<flgin::SpriteComponent>() };
	pumpSprite->SetSpriteInfo(1, 10, 180.f, 18.f, 18.f / pumpVelocity, true);
	pumpSprite->SetRotationalOffset(85.5f, 0.f);

	m_pPlayer->GetPump()->SetPosition(m_pPlayer->GetGameObject()->GetPosition().x, m_pPlayer->GetGameObject()->GetPosition().y);
	m_pPlayer->GetGameObject()->GetComponent<flgin::GridMovementComponent>()->Disable();
	FInvoker.AddInvoke(new flgin::InvokeHolder<void>{ this, 180.f / pumpVelocity, [this]() { m_pPlayer->SetFiring(false); } });

	switch (m_pPlayer->GetGameObject()->GetComponent<flgin::GridMovementComponent>()->GetMovementDirection())
	{
	case flgin::MovementDirection::Up:
		m_pPumpMover->SetMaxYVelocity(-pumpVelocity);
		pumpSprite->SetFlips(false, false);
		pumpSprite->SetPositionOffset(-173.f, -14.f);
		pumpSprite->SetRotation(270.f);
		break;
	case flgin::MovementDirection::Down:
		m_pPumpMover->SetMaxYVelocity(pumpVelocity);
		pumpSprite->SetFlips(false, false);
		pumpSprite->SetPositionOffset(-173.f, 0.f);
		pumpSprite->SetRotation(90.f);
		break;
	case flgin::MovementDirection::Left:
		m_pPumpMover->SetMaxXVelocity(-pumpVelocity);
		pumpSprite->SetPositionOffset(-9.f, -7.f);
		pumpSprite->SetFlips(true, false);
		pumpSprite->SetRotation(0.f);
		break;
	case flgin::MovementDirection::Right:
		m_pPumpMover->SetMaxXVelocity(pumpVelocity);
		pumpSprite->SetPositionOffset(-171.f, -7.f);
		pumpSprite->SetFlips(false, false);
		pumpSprite->SetRotation(0.f);
		break;
	}
}

bool DigDug::FiringState::Update()
{
	if (!m_pPlayer->IsDying())
	{
		if (m_pPlayer->IsFiring())
			return false;

		if (m_pHit) m_pHit->SetBloating(false);
		if (m_pPookaHit) m_pPookaHit->SetBloating(false);

		IdleState* idleState{ new IdleState{} };
		idleState->SetAttachedSprite(m_pSpriteComponent);
		idleState->SetPlayer(m_pPlayer);
		m_pTargetState = idleState;
		return true;
	}
	DeathState* deathState{ new DeathState{} };
	deathState->SetAttachedSprite(m_pSpriteComponent);
	deathState->SetPlayer(m_pPlayer);
	m_pTargetState = deathState;
	return true;
}

void DigDug::FiringState::Exit()
{
	m_pPlayer->GetPump()->SetActive(false);
	m_pPumpMover->SetMaxYVelocity(0.f);
	m_pPumpMover->SetMaxXVelocity(0.f);
	m_pPumpMover->SetMoving(false);
	m_pPlayer->GetGameObject()->GetComponent<flgin::GridMovementComponent>()->Enable();
	FInvoker.CancelOwnedInvokes(this);
}
