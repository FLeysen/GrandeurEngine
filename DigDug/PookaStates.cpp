#include "pch.h"
#include "PookaStates.h"
#include "Pooka.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "TextLocalizer.h"
#include "GridMovementComponent.h"
#include "Timer.h"
#include "Player.h"
#include "FreeMover.h"

void DigDug::PookaState::SetPooka(Pooka * pPooka)
{
	m_pPooka = pPooka;
}

void DigDug::PookaState::SetSprite(flgin::SpriteComponent* pSprite)
{
	m_pSprite = pSprite;
}

void DigDug::PookaState::SetGridMover(flgin::GridMovementComponent * pMover)
{
	m_pGridMover = pMover;
}

void DigDug::PookaState::SetFreeMover(flgin::FreeMover * pMover)
{
	m_pFreeMover = pMover;
}

void DigDug::PookaIdleState::Enter()
{
	m_pSprite->SetTexture(FResourceManager.LoadTexture(FLocalizer.Get("texPooka")), true);
	m_pSprite->SetSpriteInfo(4, 1, 30.0f, 30.0f, 0.4f);
}

void DigDug::PookaIdleState::Exit()
{
}

bool DigDug::PookaIdleState::Update()
{
	switch (m_pGridMover->GetMovementDirection())
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

	if (!m_pPooka->IsBloating())
	{
		if (m_pPooka->IsGhosting())
		{
			PookaGhostingState* ghostingState{ new PookaGhostingState{} };
			ghostingState->SetPooka(m_pPooka);
			ghostingState->SetGridMover(m_pGridMover);
			ghostingState->SetSprite(m_pSprite);
			ghostingState->SetFreeMover(m_pFreeMover);
			m_pTargetState = ghostingState;
			return true;
		}
		return false;
	}
	PookaBloatingState* bloatingState{ new PookaBloatingState{} };
	bloatingState->SetPooka(m_pPooka);
	bloatingState->SetGridMover(m_pGridMover);
	bloatingState->SetSprite(m_pSprite);
	bloatingState->SetFreeMover(m_pFreeMover);
	m_pTargetState = bloatingState;
	return true;
}

void DigDug::PookaGhostingState::Enter()
{
	m_pSprite->SetTexture(FResourceManager.LoadTexture(FLocalizer.Get("texPookaGhost")), true);
	m_pSprite->SetSpriteInfo(4, 1, 30.f, 30.f, 0.4f, true);
	m_pSprite->SetRotation(0.f);
	m_pSprite->SetFlips(false, false);
	m_pGridMover->Disable();
	m_pFreeMover->SetMoving(true);
}

bool DigDug::PookaGhostingState::Update()
{
	if (!m_pPooka->IsBloating())
	{
		if (!m_pPooka->IsGhosting())
		{
			PookaIdleState* idleState{ new PookaIdleState{} };
			idleState->SetPooka(m_pPooka);
			idleState->SetGridMover(m_pGridMover);
			idleState->SetSprite(m_pSprite);
			idleState->SetFreeMover(m_pFreeMover);
			m_pTargetState = idleState;
			return true;
		}
		return false;
	}
	PookaBloatingState* bloatingState{ new PookaBloatingState{} };
	bloatingState->SetPooka(m_pPooka);
	bloatingState->SetGridMover(m_pGridMover);
	bloatingState->SetSprite(m_pSprite);
	bloatingState->SetFreeMover(m_pFreeMover);
	m_pTargetState = bloatingState;
	return true;
}

void DigDug::PookaGhostingState::Exit()
{
	m_pGridMover->Enable();
	m_pFreeMover->SetMoving(false);
}

void DigDug::PookaBloatingState::Enter()
{
	m_pGridMover->Disable();
}

bool DigDug::PookaBloatingState::Update()
{
	if (m_pPooka->IsBloating())
	{
		m_BloatTime += FTime.GetDeltaTime();
		float size{ 30.f * (1 + m_BloatTime / m_MaxBloatTime * m_MaxBloatScale) };
		m_pPooka->SetDeflating(false);
		m_pSprite->SetDimensions(size, size);
		m_pSprite->SetPositionOffset(size * -0.5f, size * -0.5f);
		if (m_BloatTime > m_MaxBloatTime)
		{
			m_pPooka->GetHitBy()->SetFiring(false);
			m_pPooka->GetHitBy()->ChangeScore(m_pPooka->GetScoreWorth());
			m_pPooka->Die();
		}
	}
	else
	{
		m_BloatTime -= FTime.GetDeltaTime();
		float size{ 30.f * (1 + m_BloatTime / m_MaxBloatTime * m_MaxBloatScale) };
		m_pPooka->SetDeflating(true);
		m_pSprite->SetPositionOffset(size * -0.5f, size * -0.5f);
		m_pSprite->SetDimensions(size, size);
		if (m_BloatTime < 0.f)
		{
			m_pSprite->SetPositionOffset(-15.f, -15.f);
			m_pSprite->SetDimensions(30.f, 30.f);
			PookaIdleState* idleState{ new PookaIdleState{} };
			idleState->SetPooka(m_pPooka);
			idleState->SetGridMover(m_pGridMover);
			idleState->SetSprite(m_pSprite);
			idleState->SetFreeMover(m_pFreeMover);
			m_pTargetState = idleState;
			return true;
		}
	}
	return false;
}

void DigDug::PookaBloatingState::Exit()
{
	m_pGridMover->Enable();
	m_pPooka->SetDeflating(false);
}