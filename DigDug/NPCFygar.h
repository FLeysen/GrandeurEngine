#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace flgin
{
	class GameObject;
	class Scene;
}

namespace DigDug
{
	class NPCFygar
	{
	public:
		static flgin::GameObject* Create(flgin::Scene* pScene, const glm::vec2& pos);

	private:
		NPCFygar() = delete;
	};
}