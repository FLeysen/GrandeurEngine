#pragma once
#include "BaseComponent.h"

namespace flgin
{
	class Scene;
	class RenderComponent;
	class MovementGrid;
	class GridRenderer final : public BaseComponent
	{
	public:
		GridRenderer(GameObject* pOwnerObject, Scene* pScene, MovementGrid* pGrid);
		~GridRenderer() = default;
		void Update() override;

	private:
		std::vector<RenderComponent*> m_pRenderers;
	};
}