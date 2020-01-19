#pragma once
#include "Singleton.h"
#define FObserverManager flgin::ObserverManager::GetInstance()

namespace flgin
{
	class Observer;
	class ObserverManager final : public Singleton<ObserverManager>
	{
	public:
		ObserverManager();
		~ObserverManager();
		void Add(Observer* observer) { m_pObservers.push_back(observer); }
		template <class T>
		T* Get()
		{
			const type_info& typeInfo{ typeid(T) };
			for (Observer* const observer : m_pObservers)
			{
				if (typeid(*observer) == typeInfo)
					return static_cast<T*>(observer);
			}
			return nullptr;
		}
		void Clear();

	private:
		std::vector<Observer*> m_pObservers;
	};
}
