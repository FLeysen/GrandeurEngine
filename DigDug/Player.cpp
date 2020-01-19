#include "pch.h"
#include "Player.h"
#include "ObserverEvents.h"
#include "SpriteComponent.h"

DigDug::Player::Player(flgin::GameObject * pOwnerObject, flgin::GameObject * pPump)
	: Subject()
	, BaseComponent(pOwnerObject)
	, m_pPump{ pPump }
	, m_Lives{ 3 }
	, m_IsDying{ false }
	, m_IsFiring{ false }
{ m_pPump->SetActive(false); }

void DigDug::Player::ChangeLives(int amount, bool rawChange)
{
	if (!rawChange)
	{
		if (!m_IsDying)
		{
			m_Lives += amount;
			m_IsDying = true;
			Notify(ObserverEvent::LivesChanged);
		}
	}
	else
	{
		m_Lives = amount;
		Notify(ObserverEvent::LivesChanged);
	}
}

void DigDug::Player::ChangeScore(int amount)
{
	m_Score += amount;
	Notify(ObserverEvent::ScoreChanged);
}