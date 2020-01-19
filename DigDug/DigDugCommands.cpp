#include "pch.h"
#include "DigDugCommands.h"
#include "Player.h"
#include "MenuComponent.h"
#include "InputManager.h"
#include "Game.h"
#include "SceneManager.h"
#include "FunctionHolder.h"

void DigDug::DieCommand::Execute(flgin::GameObject&, bool isInverseAction)
{
	if (!isInverseAction) m_pPlayer->ChangeLives(-1);
}

void DigDug::MenuPreviousCommand::Execute(flgin::GameObject&, bool isInverseAction)
{
	if (!isInverseAction) m_pMenu->SelectPrevious();
}

void DigDug::MenuNextCommand::Execute(flgin::GameObject&, bool isInverseAction)
{
	if (!isInverseAction) m_pMenu->SelectNext();
}

void DigDug::MenuConfirmCommand::Execute(flgin::GameObject&, bool isInverseAction)
{
	if (!isInverseAction) m_pMenu->PressCurrentButton();
}

void DigDug::ReturnToMenuCommand::Execute(flgin::GameObject &, bool)
{
	flgin::FunctionHolder<void>* pFunc{ new flgin::FunctionHolder<void>{ std::bind(&DigDug::Game::InitMenuScene, m_Game) } };
	FSceneManager.SwapScene(pFunc);
}

void DigDug::FireCommand::Execute(flgin::GameObject& commander, bool isInverse)
{
	commander.GetComponent<Player>()->SetFiring(!isInverse);
}