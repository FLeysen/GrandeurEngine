#pragma once
#include "Observer.h"
#include <vector>
namespace flgin
{
	class Subject
	{
	public:
		Subject();
		virtual ~Subject() = default;
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		template <class T>
		T* GetObserver()
		{
			const type_info& typeInfo{ typeid(T) };
			for (Observer* const observer : m_pObservers)
			{
				if (typeid(*observer) == typeInfo)
					return static_cast<T*>(observer);
			}
			return nullptr;
		}

	protected:
		void Notify(Observer::Event event);

	private:
		std::vector<Observer*> m_pObservers;
	};
}