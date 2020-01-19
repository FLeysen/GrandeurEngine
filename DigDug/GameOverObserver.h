#pragma once
#include "Observer.h"

namespace flgin
{
	class SpriteComponent;
}

namespace DigDug
{
	class Game;
	class GameOverObserver : public flgin::Observer
	{
	public:
		GameOverObserver(const Game& game);
		void Notify(Event event, const flgin::Subject* const subject) override;
		~GameOverObserver() = default;

	private:
		const Game& m_Game;
	};
}
