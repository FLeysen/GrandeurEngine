#pragma once
namespace flgin
{
	class GameObject;
	class Scene;
	class GridNode;
}

namespace DigDug
{
	class Rock final
	{
	public:
		static flgin::GameObject* Create(flgin::Scene* pScene, flgin::GridNode* nearestNode, const std::string& texName);
	private:
		Rock() = delete;
	};
}
