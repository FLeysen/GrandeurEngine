#pragma once
#include <Xinput.h>
#include <vector>
#include "Singleton.h"
#include "InputComponent.h"
#define FInputManager flgin::InputManager::GetInstance()

namespace flgin
{
	class Command;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		bool ProcessInput();
		void AddCommand(Command* const command);
		void ClearCommands();
		void AddPlayer();
		void RemovePlayer();
		void Quit() { m_ShouldContinue = false; }
		InputComponent* GetPlayer(unsigned int idx);
		
		template <class T>
		void RemoveCommand()
		{
			const type_info& typeInfo{ typeid(T) };
			for (size_t i{}, commandAmount{ m_pCommands.size() }; i < commandAmount; ++i)
			{
				if (m_pCommands[i])
				{
					if (typeid(*m_pCommands[i]) == typeInfo)
					{
						delete m_pCommands[i];
						m_pCommands[i] = nullptr;
					}
				}
			}
		}

		template <class T>
		T* GetCommand()
		{
			const type_info& typeInfo{ typeid(T) };
			for (size_t i{}, commandAmount{ m_pCommands.size() }; i < commandAmount; ++i)
			{
				if (m_pCommands[i])
				{
					if (typeid(*m_pCommands[i]) == typeInfo)
						return static_cast<T*>(m_pCommands[i]);
				}
			}
			return nullptr;
		}

	private:
		std::vector<Command*> m_pCommands;
		std::vector<InputComponent> m_pPlayers;
		bool m_ShouldContinue;
	};
}