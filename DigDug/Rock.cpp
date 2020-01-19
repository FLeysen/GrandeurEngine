#include "pch.h"
#include "Rock.h"
#include "MovementGrid.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "FreeMover.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "StateComponent.h"
#include "RockStates.h"

flgin::GameObject* DigDug::Rock::Create(flgin::Scene* pScene, flgin::GridNode* nearestNode, const std::string& texName)
{
	using namespace flgin;
	GameObject* go{ new GameObject{} };
	go->SetPosition(nearestNode->GetPosition().x, nearestNode->GetPosition().y);
	FreeMover* freeMoveComponent{ new FreeMover{go, 0.f} };
	ColliderComponent* rockColliderComponent{ new ColliderComponent{ go, "Rock", 30.f, 32.f } };
	RenderComponent* renderComponent{ pScene->CreateRenderComponent(go, 3) };
	renderComponent->SetPositionOffset(-15.f, -15.f);
	renderComponent->SetTexture(FResourceManager.LoadTexture(texName));
	renderComponent->SetDimensions(30.f, 30.f);

	StateComponent* stateComponent{ new StateComponent{ go } };
	StuckState* stuckState{ new StuckState{} };
	stuckState->SetAttachedCollider(rockColliderComponent);
	stuckState->SetAttachedMover(freeMoveComponent);
	stuckState->SetNode(nearestNode);
	stateComponent->SetCurrentState(stuckState);
	nearestNode->SetBlocked(true);

	go->SetTag("Rock");
	go->SetPosition(nearestNode->GetPosition().x, nearestNode->GetPosition().y);
	go->AddComponent(freeMoveComponent);
	go->AddComponent(renderComponent);
	go->AddComponent(rockColliderComponent);
	go->AddComponent(stateComponent);
	pScene->AddGameObject(go);
	return go;
}