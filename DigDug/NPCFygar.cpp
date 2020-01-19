#include "pch.h"
#include "NPCFygar.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "Scene.h"
#include "TextLocalizer.h"
#include "ResourceManager.h"
#include "FunctionHolder.h"
#include "Player.h"
#include "Fygar.h"
#include "StateComponent.h"
#include "FygarStates.h"
#include "GridMovementComponent.h"
#include "MovementGrid.h"
#include "ObserverManager.h"
#include "NextLevelObserver.h"
#include "FygarController.h"

flgin::GameObject * DigDug::NPCFygar::Create(flgin::Scene* scene, const glm::vec2& pos)
{
	using namespace flgin;
	GameObject* flame{ new GameObject{} };
	flame->SetTag("Flame");
	SpriteComponent* flameSprite{ scene->CreateSpriteComponent(flame) };
	flameSprite->SetTexture(FResourceManager.LoadTexture(FLocalizer.Get("texFire")));
	flameSprite->SetDimensions(30.f, 24.f);
	flameSprite->SetPositionOffset(-15.f, -12.f);
	flameSprite->SetSpriteInfo(6, 1, 30.f, 24.f, 0.3f, true);
	ColliderComponent* flameCollider{ new ColliderComponent{flame, "Flame", 20.f, 17.f} };
	flameCollider->SetOnCollisionFunction(new FunctionHolder<void>{
	[flameCollider]() {
	if (flameCollider->GetCollisionHit()->GetGameObject()->CompareTag("Player"))
		flameCollider->GetCollisionHit()->GetGameObject()->GetComponent<Player>()->ChangeLives(-1); } });
	FCollisionManager.AddIgnore("Pump", "Flame");

	flame->AddComponent(flameCollider);
	flame->AddComponent(flameSprite);
	scene->AddGameObject(flame);

	GameObject* fygar{ new GameObject{} };
	MovementGrid* grid{ scene->FindComponentOfType<MovementGrid>() };
	fygar->SetPosition(pos.x, pos.y);
	GridMovementComponent* gridMover{ new GridMovementComponent{ fygar, 90.0f, grid, 90.0f, false } };
	fygar->AddComponent(gridMover);

	SpriteComponent* spriteComponent{ scene->CreateSpriteComponent(fygar, 4) };
	spriteComponent->SetTexture(FResourceManager.LoadTexture(FLocalizer.Get("texFygar")));
	spriteComponent->SetPositionOffset(-15.f, -15.f);
	spriteComponent->SetSpriteInfo(4, 1, 30.0f, 30.0f, 0.4f);
	spriteComponent->SetDimensions(30.0f, 30.0f);
	spriteComponent->SetRotationalOffset(0.f, 0.f);
	spriteComponent->SetRotation(180.f);
	spriteComponent->SetFlips(false, true);

	Fygar* fygarComponent{ new Fygar{ fygar, flame } };
	StateComponent* stateComponent{ new StateComponent{ fygar } };
	FygarIdleState* idleState{ new FygarIdleState{} };
	idleState->SetSprite(spriteComponent);
	idleState->SetFygar(fygarComponent);
	idleState->SetMover(gridMover);
	stateComponent->SetCurrentState(idleState);

	ColliderComponent* colliderComponent{ new ColliderComponent{ fygar, "Fygar", 30.f, 30.f } };
	colliderComponent->SetOnCollisionFunction(new FunctionHolder<void>{
		[colliderComponent, fygarComponent]() {
		if (colliderComponent->GetCollisionHit()->GetGameObject()->CompareTag("Player") && !fygarComponent->IsDeflating())
			colliderComponent->GetCollisionHit()->GetGameObject()->GetComponent<Player>()->ChangeLives(-1); } });

	FygarController* fygarController{ new FygarController{fygar, fygarComponent, gridMover, grid} };

	fygar->SetTag("Fygar");
	fygar->AddComponent(colliderComponent);
	fygar->AddComponent(spriteComponent);
	fygar->AddComponent(fygarComponent);
	fygar->AddComponent(stateComponent);
	fygar->AddComponent(fygarController);
	scene->AddGameObject(fygar);

	NextLevelObserver* ob{ FObserverManager.Get<NextLevelObserver>() };
	ob->AddEnemy();
	fygarComponent->AddObserver(ob);

	return fygar;
}