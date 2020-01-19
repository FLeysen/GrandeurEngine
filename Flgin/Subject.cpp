#include "FlginPCH.h"
#include "Subject.h"
#include <algorithm>

flgin::Subject::Subject()
	: m_pObservers{}
{}

void flgin::Subject::AddObserver(flgin::Observer* observer)
{
	m_pObservers.push_back(observer);
}

void flgin::Subject::RemoveObserver(flgin::Observer* observer)
{
	auto it{ std::find(m_pObservers.begin(), m_pObservers.end(), observer) };
	m_pObservers.erase(it);
}

void flgin::Subject::Notify(flgin::Observer::Event event)
{
	for (Observer* const observer : m_pObservers)
		observer->Notify(event, this);
}