#pragma once
namespace flgin
{
	class GameObject;
	class Command
	{
	public:
		Command();
		virtual ~Command() = default;
		virtual void Execute(GameObject& attachedObject, bool isInverseAction = false) = 0;
	};
}