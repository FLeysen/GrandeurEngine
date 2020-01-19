#include "pch.h"
#include "NextLevelObserver.h"
#include "ObserverEvents.h"
#include "FunctionHolder.h"

DigDug::NextLevelObserver::~NextLevelObserver()
{
	FLogger.SafeDelete(m_pNextInitFunc);
}

void DigDug::NextLevelObserver::Notify(Event event, const flgin::Subject* const)
{
	if (event == ObserverEvent::EnemyEliminated)
	{
		if (--m_EnemyCount == 0)
			m_pNextInitFunc->Call();
	}
}

void DigDug::NextLevelObserver::SetNextLevelInit(flgin::FunctionHolderBase * func)
{
	FLogger.SafeDelete(m_pNextInitFunc, true);
	m_pNextInitFunc = func;
}
