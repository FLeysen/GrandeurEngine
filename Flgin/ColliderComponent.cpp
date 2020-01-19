#include "FlginPCH.h"
#include "ColliderComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "FunctionHolder.h"
#include "CollisionManager.h"

flgin::ColliderComponent::ColliderComponent(GameObject* pOwnerObject, std::string&& layer, float width, float height)
	: ColliderComponent(pOwnerObject, std::move(layer), 0, 0, width, height)
{}

flgin::ColliderComponent::ColliderComponent(GameObject* pOwnerObject, std::string&& layer, float xOffset, float yOffset, float width, float height)
	: BaseComponent(pOwnerObject)
	, m_XOffset{ xOffset }
	, m_YOffset{ yOffset }
	, m_Width{ width }
	, m_Height{ height }
	, m_pCollisionHit{ nullptr }
{
	FCollisionManager.AddCollider(this, std::move(layer));
}

flgin::ColliderComponent::~ColliderComponent()
{
	FLogger.SafeDelete(m_pOnCollisionFunction);
}

void flgin::ColliderComponent::SetOnCollisionFunction(FunctionHolderBase* pFunc)
{
	FLogger.SafeDelete(m_pOnCollisionFunction, true);
	m_pOnCollisionFunction = pFunc;
}

void flgin::ColliderComponent::CheckAndExecuteCollision(ColliderComponent& other)
{
	if (m_pOwnerObject->IsActive() && other.m_pOwnerObject->IsActive())
	{
		if (!IsColliding(other)) return;

		m_pCollisionHit = &other;
		other.m_pCollisionHit = this;

		m_pOnCollisionFunction->Call();
		other.m_pOnCollisionFunction->Call();

		m_pCollisionHit = nullptr;
		other.m_pCollisionHit = nullptr;
	}
}

bool flgin::ColliderComponent::IsColliding(const ColliderComponent& other)
{
	glm::vec2 pos{ m_pOwnerObject->GetPosition() };
	glm::vec2 otherPos{ other.m_pOwnerObject->GetPosition() };
	pos.x += m_XOffset;
	pos.y += m_YOffset;
	otherPos.x += other.m_XOffset;
	otherPos.y += other.m_YOffset;

	return (pos.x < otherPos.x + other.m_Width  && pos.x + m_Width > otherPos.x
		 && pos.y < otherPos.y + other.m_Height && pos.y + m_Height > otherPos.y);
}