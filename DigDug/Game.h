#pragma once
#include "Flgin.h"
namespace DigDug
{
	enum class GameState : UINT8
	{
		Single, Coop, Versus
	};

	class Game
	{
	public:
		Game();
		~Game();
		void Run();
		void InitGameScene();
		void InitMenuScene();
		void InitSinglePlayer();
		void InitTwoPlayer();
		void InitVersus();
		void InitEndScene();
		void InitNextLevel();

		void SetSwappingToSingle();
		void SetSwappingToTwoPlayer();
		void SetSwappingToVerus();
		void SetSwappingToNextLevel();
		void SetSwappingToEndScene();

	private:
		flgin::Flgin m_Engine;
		GameState m_GameState;
	};
}

