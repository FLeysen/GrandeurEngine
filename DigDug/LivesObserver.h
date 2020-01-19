#pragma once
#include "Observer.h"

namespace flgin
{
	class SpriteComponent;
}

namespace DigDug
{
	class LivesObserver : public flgin::Observer
	{
	public:
		LivesObserver(unsigned int lives, flgin::SpriteComponent* pSprite);
		void Notify(Event event, const flgin::Subject* const subject) override;

		~LivesObserver() = default;

	private:
		UINT m_InitLives;
		float m_SizePerLife;
		flgin::SpriteComponent* m_pLivesSprite;
	};
}
