#include "pch.h"
#include "NPCPooka.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "Scene.h"
#include "TextLocalizer.h"
#include "ResourceManager.h"
#include "FunctionHolder.h"
#include "Player.h"
#include "Pooka.h"
#include "StateComponent.h"
#include "PookaStates.h"
#include "GridMovementComponent.h"
#include "MovementGrid.h"
#include "ObserverManager.h"
#include "NextLevelObserver.h"
#include "PookaController.h"
#include "FreeMover.h"

flgin::GameObject* DigDug::NPCPooka::Create(flgin::Scene* scene, const glm::vec2& pos)
{
	using namespace flgin;
	GameObject* pooka{ new GameObject{} };
	MovementGrid* grid{ scene->FindComponentOfType<MovementGrid>() };
	pooka->SetPosition(pos.x, pos.y);
	GridMovementComponent* gridMover{ new GridMovementComponent{ pooka, 110.0f, grid, 90.0f, false } };
	pooka->AddComponent(gridMover);
	FreeMover* freeMover{ new FreeMover{pooka, 0.f} };
	freeMover->SetMoving(false);
	pooka->AddComponent(freeMover);

	SpriteComponent* spriteComponent{ scene->CreateSpriteComponent(pooka, 4) };
	spriteComponent->SetTexture(FResourceManager.LoadTexture(FLocalizer.Get("texPooka")));
	spriteComponent->SetPositionOffset(-15.f, -15.f);
	spriteComponent->SetSpriteInfo(4, 1, 30.0f, 30.0f, 0.4f);
	spriteComponent->SetDimensions(30.0f, 30.0f);
	spriteComponent->SetRotationalOffset(0.f, 0.f);
	spriteComponent->SetRotation(180.f);
	spriteComponent->SetFlips(false, true);

	Pooka* pookaComponent{ new Pooka{ pooka } };
	StateComponent* stateComponent{ new StateComponent{ pooka } };
	PookaIdleState* idleState{ new PookaIdleState{} };
	idleState->SetSprite(spriteComponent);
	idleState->SetPooka(pookaComponent);
	idleState->SetGridMover(gridMover);
	idleState->SetFreeMover(freeMover);
	stateComponent->SetCurrentState(idleState);

	ColliderComponent* colliderComponent{ new ColliderComponent{ pooka, "Pooka", 30.f, 30.f } };
	colliderComponent->SetOnCollisionFunction(new FunctionHolder<void>{
		[colliderComponent, pookaComponent]() {
		if (colliderComponent->GetCollisionHit()->GetGameObject()->CompareTag("Player") && !pookaComponent->IsDeflating())
			colliderComponent->GetCollisionHit()->GetGameObject()->GetComponent<Player>()->ChangeLives(-1); } });

	PookaController* pookaController{ new PookaController{pooka, pookaComponent} };

	pooka->SetTag("Pooka");
	pooka->AddComponent(colliderComponent);
	pooka->AddComponent(spriteComponent);
	pooka->AddComponent(pookaComponent);
	pooka->AddComponent(stateComponent);
	pooka->AddComponent(pookaController);
	scene->AddGameObject(pooka);

	NextLevelObserver* ob{ FObserverManager.Get<NextLevelObserver>() };
	ob->AddEnemy();
	pookaComponent->AddObserver(ob);

	return pooka;
}