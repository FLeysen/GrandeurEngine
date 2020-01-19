#include "FlginPCH.h"
#include "Observer.h"
#include "ObserverManager.h"

flgin::Observer::Observer()
{
	FObserverManager.Add(this);
}