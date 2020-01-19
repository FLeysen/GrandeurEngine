#pragma once
namespace flgin
{
	class Subject;
	class Observer
	{
	public:
		typedef unsigned int Event;
		Observer();
		virtual ~Observer() {}
		virtual void Notify(Event event, const Subject* const subject) = 0;
	};
}