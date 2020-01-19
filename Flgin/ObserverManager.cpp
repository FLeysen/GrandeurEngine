#include "FlginPCH.h"
#include "ObserverManager.h"
#include "Observer.h"

flgin::ObserverManager::ObserverManager()
	: Singleton()
	, m_pObservers{}
{}

flgin::ObserverManager::~ObserverManager()
{
	Clear();
}

void flgin::ObserverManager::Clear()
{
	for (Observer* observer : m_pObservers)
		FLogger.SafeDelete(observer);
	m_pObservers.clear();
}