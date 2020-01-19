#include "FlginPCH.h"
#include "InputManager.h"
#include "Command.h"
#include "SDL.h"
#include "SceneManager.h"

flgin::InputManager::InputManager()
	: m_pCommands{}
	, m_pPlayers{}
	, m_ShouldContinue{ true }
{}

flgin::InputManager::~InputManager()
{
	ClearCommands();
}

bool flgin::InputManager::ProcessInput()
{
	SDL_Event e{};
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) return false;
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			for (InputComponent& player : m_pPlayers)
				player.ProcessKeyboardKey(e.key.keysym.sym, e.type == SDL_KEYUP);
		}
		else if (e.type == SDL_CONTROLLERBUTTONDOWN || e.type == SDL_CONTROLLERBUTTONUP)
		{
			SDL_JoystickID playerID{ e.cbutton.which };
			if (playerID >= static_cast<SDL_JoystickID>(m_pPlayers.size())) 
				continue;
			m_pPlayers[playerID].ProcessControllerKey(e.cbutton.button, e.type == SDL_CONTROLLERBUTTONUP);
		}
		else if (e.type == SDL_CONTROLLERAXISMOTION)
		{
			SDL_JoystickID playerID{ e.caxis.which };
			if (playerID >= static_cast<SDL_JoystickID>(m_pPlayers.size())) 
				continue;
			m_pPlayers[playerID].ProcessAxisMotion(e.caxis.axis, e.caxis.value);
		}
	}
	return m_ShouldContinue;	
}

void flgin::InputManager::AddCommand(Command* const command)
{
	m_pCommands.push_back(command);
}

void flgin::InputManager::ClearCommands()
{
	Logger& logger{ FLogger };
	for (Command* command : m_pCommands)
		logger.SafeDelete(command);
	m_pCommands.clear();
}

void flgin::InputManager::AddPlayer()
{
	m_pPlayers.push_back(InputComponent{ nullptr });
}

void flgin::InputManager::RemovePlayer()
{
	m_pPlayers.pop_back();
}

flgin::InputComponent* flgin::InputManager::GetPlayer(unsigned int idx)
{
	if (idx >= m_pPlayers.size()) return nullptr;
	return &(m_pPlayers[idx]);
}

