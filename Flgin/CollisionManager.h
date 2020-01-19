#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <unordered_set>
#define FCollisionManager flgin::CollisionManager::GetInstance()

namespace flgin
{
	class ColliderComponent;

	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		~CollisionManager() = default;
		void AddCollider(ColliderComponent* pCollider, std::string&& layer);
		void AddIgnore(std::string&& layer, std::string&& ignoredLayer); //ignoredLayer should always have value higher than or equal to layer
		void HandleCollisions();
		void ClearColliders();

	private:
		UINT m_Limit{ 0 };
		std::unordered_map<std::string, UINT> m_LayerNames{};
		std::unordered_map<UINT, std::vector<ColliderComponent*>> m_pColliders{}; //Colliders of layer n
		std::unordered_map<UINT, std::unordered_set<UINT>> m_IgnoredLayers{};	  //Layers that layer n ignores, should only contain values higher than n!
	};
}
