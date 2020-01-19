#pragma once
#include "Observer.h"

namespace flgin
{
	class FunctionHolderBase;
}

namespace DigDug
{
	class NextLevelObserver : public flgin::Observer
	{
	public:
		NextLevelObserver() : Observer(), m_pNextInitFunc{}, m_EnemyCount{ 0 } {}
		~NextLevelObserver();
		void Notify(Event event, const flgin::Subject* const subject) override;
		void AddEnemy() { ++m_EnemyCount; }
		void SetNextLevelInit(flgin::FunctionHolderBase* func);

	private:
		UINT m_EnemyCount;
		flgin::FunctionHolderBase* m_pNextInitFunc;
	};
}
