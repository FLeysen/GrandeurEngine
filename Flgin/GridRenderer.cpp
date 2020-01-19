#include "FlginPCH.h"
#include "GridRenderer.h"
#include "MovementGrid.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "TextLocalizer.h"
#include "Scene.h"

flgin::GridRenderer::GridRenderer(GameObject* pOwnerObject, Scene* pScene, MovementGrid* pGrid)
	: BaseComponent(pOwnerObject)
{
	m_pRenderers.resize(pGrid->GetGridSize());
	GridNode* pGridNodes{ pGrid->GetGrid() };
	Texture2D* pTex{ FResourceManager.LoadTexture(FLocalizer.Get("texGameBg")) };
	glm::vec2 negativeOffset{ pGrid->GetGameObject()->GetPosition() };
	negativeOffset += pGrid->GetNodeSize() * 0.5f;
	for (size_t i{}, size{ m_pRenderers.size() }; i < size; ++i)
	{
		m_pRenderers[i] = pScene->CreateRenderComponent(pOwnerObject, 1);
		m_pRenderers[i]->SetTexture(pTex);
		m_pRenderers[i]->SetPositionOffset(pGridNodes[i].GetPosition().x - negativeOffset.x, pGridNodes[i].GetPosition().y - negativeOffset.y);
	}
}

void flgin::GridRenderer::Update()
{}
