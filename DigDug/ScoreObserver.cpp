#include "pch.h"
#include "ScoreObserver.h"
#include "TextComponent.h"
#include "ObserverEvents.h"
#include "Player.h"

DigDug::ScoreObserver::ScoreObserver(flgin::TextComponent* pTextComp)
	: Observer()
	, m_pText{ pTextComp }
{
	m_pText->SetText("0");
}

void DigDug::ScoreObserver::Notify(Event event, const flgin::Subject* const pSubject)
{
	if (event != ObserverEvent::ScoreChanged) return;

	const Player* const player{ static_cast<const Player* const>(pSubject) };
	m_pText->SetText(std::to_string(player->GetScore()));
}