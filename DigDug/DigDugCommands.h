#pragma once
#include "Command.h"

namespace flgin
{
	class MenuComponent;
}

namespace DigDug
{
	class Player;
	class Game;

	class DieCommand final : public flgin::Command
	{
	public:
		DieCommand(Player* pPlayer) : Command(), m_pPlayer{ pPlayer } {}
		void Execute(flgin::GameObject& attachedObject, bool isInverseAction = false) override;

	private:
		Player* m_pPlayer;
	};

	class MenuNextCommand final : public flgin::Command 
	{
	public:
		MenuNextCommand(flgin::MenuComponent* pMenu) : Command(), m_pMenu{ pMenu }{}
		void Execute(flgin::GameObject& attachedObject, bool isInverseAction = false) override;

	private:
		flgin::MenuComponent* m_pMenu;
	};

	class MenuPreviousCommand final : public flgin::Command
	{
	public:
		MenuPreviousCommand(flgin::MenuComponent* pMenu) : Command(), m_pMenu{ pMenu }{}
		void Execute(flgin::GameObject& attachedObject, bool isInverseAction = false) override;

	private:
		flgin::MenuComponent* m_pMenu;
	};

	class MenuConfirmCommand final : public flgin::Command
	{
	public:
		MenuConfirmCommand(flgin::MenuComponent* pMenu) : Command(), m_pMenu{ pMenu }{}
		void Execute(flgin::GameObject& attachedObject, bool isInverseAction = false) override;

	private:
		flgin::MenuComponent* m_pMenu;
	};

	class ReturnToMenuCommand final : public flgin::Command
	{
	public:
		ReturnToMenuCommand(Game& game) : Command(), m_Game{ game } {}
		void Execute(flgin::GameObject&, bool = false) override;

	private:
		Game& m_Game;
	};

	class FireCommand final : public flgin::Command
	{
	public:
		FireCommand() : Command() {}
		void Execute(flgin::GameObject& commander, bool isInverse = false) override;
	};
}