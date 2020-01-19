#pragma once
#include "Observer.h"

namespace flgin
{
	class TextComponent;
}

namespace DigDug
{
	class ScoreObserver : public flgin::Observer
	{
	public:
		ScoreObserver(flgin::TextComponent* pTextComp);
		~ScoreObserver() = default;
		void Notify(Event event, const flgin::Subject* const subject) override;
		
	private:
		flgin::TextComponent* m_pText;
	};
}