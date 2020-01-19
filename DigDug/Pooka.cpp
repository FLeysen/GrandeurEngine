#include "pch.h"
#include "Pooka.h"
#include "ObserverEvents.h"
#include "MovementGrid.h"

flgin::MovementGrid* DigDug::Pooka::m_pGrid{ nullptr };

DigDug::Pooka::Pooka(flgin::GameObject* pOwnerObject)
	: BaseComponent(pOwnerObject)
	, m_IsBloating{ false }
	, m_IsDeflating{ false }
	, m_pHitBy{}
	, m_IsGhosting{ false }  
{}

void DigDug::Pooka::Die()
{
	m_pOwnerObject->SetActive(false);
	Notify(ObserverEvent::EnemyEliminated);
}

UINT DigDug::Pooka::GetScoreWorth()
{
	float yPos{ m_pOwnerObject->GetPosition().y - m_pGrid->GetGameObject()->GetPosition().y };
	float row{ yPos / m_pGrid->GetNodeSize() };
	if (row < 1.f) return 200;

	int tier{ int(row - 1.f) / 3 };
	switch (tier)
	{
	case 0:
		return 200;
		break;
	case 1:
		return 300;
		break;
	case 2:
		return 400;
		break;
	case 3:
		return 500;
		break;
	}
	return 0;
}
