#include "pch.h"
#include "LivesObserver.h"
#include "ObserverEvents.h"
#include "SpriteComponent.h"
#include "Player.h"

DigDug::LivesObserver::LivesObserver(unsigned int lives, flgin::SpriteComponent* pSprite)
	: Observer()
	, m_InitLives{ lives }
	, m_SizePerLife{}
	, m_pLivesSprite{ pSprite }
{
	m_pLivesSprite->SetDimensions(m_pLivesSprite->GetWidth() * 0.75f, m_pLivesSprite->GetHeight());
	m_pLivesSprite->SetSpriteInfo(m_InitLives, 1, m_pLivesSprite->GetWidth(), m_pLivesSprite->GetHeight(), 0.f, false);
	m_SizePerLife = m_pLivesSprite->GetWidth() / 3.f;
}

void DigDug::LivesObserver::Notify(Event event, const flgin::Subject* const pSubject)
{
	if (event != ObserverEvent::LivesChanged) return;

	const Player* const player{ static_cast<const Player* const>(pSubject) };
	m_pLivesSprite->SetSpriteInfo(m_InitLives, 1, m_SizePerLife * player->GetLives(), m_pLivesSprite->GetHeight(), 0.f, false);
	m_pLivesSprite->SetDimensions(m_SizePerLife * player->GetLives(), m_pLivesSprite->GetHeight());
}
