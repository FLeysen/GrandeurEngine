#pragma once
#include "BaseComponent.h"
#include <unordered_map>
namespace flgin
{
	struct AxisRange
	{
		short int min, max;
		bool wasReached;
	};

	class Command;
	class InputComponent : public BaseComponent
	{
	public:
		InputComponent(GameObject* const ownerObject);
		~InputComponent() = default;
		InputComponent(InputComponent&& other) : BaseComponent(other.m_pOwnerObject), m_KeyboardMappings{ other.m_KeyboardMappings }, m_ControllerMappings{ other.m_ControllerMappings } { }

		bool ShouldDelete() override { return false; }
		void AddControllerMapping(UINT8 key, Command* command);
		void AddKeyboardMapping(int key, Command* command);
		void AddAxisMapping(UINT8 axis, const AxisRange& range, Command* command);
		void Update() override;
		void ProcessKeyboardKey(int key, bool isKeyUp = false);
		void ProcessControllerKey(UINT8 key, bool isKeyUp = false);
		void ProcessAxisMotion(UINT8 axis, short int value);
		void AttachToGameObject(GameObject* const newOwner) { m_pOwnerObject = newOwner; }
		void Clear();

	private:
		std::unordered_multimap<int, Command*> m_KeyboardMappings;
		std::unordered_multimap<UINT8, Command*> m_ControllerMappings;
		std::unordered_multimap<UINT8, std::pair<AxisRange, Command*>> m_AxisMappings;
	};
}