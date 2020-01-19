#include "pch.h"
#include "Fygar.h"
#include "MovementGrid.h"
#include "ObserverEvents.h"

flgin::MovementGrid* DigDug::Fygar::m_pGrid{ nullptr };

DigDug::Fygar::Fygar(flgin::GameObject* pOwnerObject, flgin::GameObject* pFire)
	: BaseComponent(pOwnerObject)
	, m_pFire{ pFire }
	, m_IsFiring{ false }
	, m_IsBloating{ false }
	, m_IsDeflating{ false }
	, m_pHitBy{}
{
	m_pFire->SetActive(false);
}

void DigDug::Fygar::Die()
{
	m_pOwnerObject->SetActive(false);
	Notify(ObserverEvent::EnemyEliminated);
}

UINT DigDug::Fygar::GetScoreWorth()
{
	float yPos{ m_pOwnerObject->GetPosition().y - m_pGrid->GetGameObject()->GetPosition().y };
	float row{ yPos / m_pGrid->GetNodeSize() };
	if (row < 1.f) return 400;

	int tier{ int(row - 1.f) / 3 };
	switch (tier)
	{
	case 0:
		return 400;
		break;
	case 1:
		return 600;
		break;
	case 2:
		return 800;
		break;
	case 3:
		return 1000;
		break;
	}
	return 0;
}
