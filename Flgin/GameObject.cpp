#include "FlginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "RenderComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "Texture2D.h"

unsigned int flgin::GameObject::m_Limit{ 0 };
std::unordered_map<std::string, unsigned int> flgin::GameObject::m_Tags{ {"Untagged", 0} };

flgin::GameObject::GameObject()
	: m_pComponents{}
	, m_Transform{}
	, m_IsActive{ true }
	, m_Tag{ 0 }
{}

flgin::GameObject::~GameObject()
{
	Logger& logger{ FLogger };
	for (BaseComponent* component : m_pComponents)
		 if(component->ShouldDelete()) logger.SafeDelete(component);
};

void flgin::GameObject::Update()
{
	if (m_IsActive)
	{
		for (BaseComponent* component : m_pComponents)
			component->Update();
	}
}

void flgin::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

glm::vec2 flgin::GameObject::GetPosition() const
{
	return glm::vec2{ m_Transform.GetPosition().x, m_Transform.GetPosition().y };
}

void flgin::GameObject::AddComponent(BaseComponent* const component)
{
	m_pComponents.push_back(component);
}

void flgin::GameObject::RemoveComponent(BaseComponent* const component)
{
	std::vector<BaseComponent*>::const_iterator cIt{ std::find(m_pComponents.cbegin(), m_pComponents.cend(), component) };
	if (cIt != m_pComponents.cend())
		m_pComponents.erase(cIt);
	else
		FLogger.Log(StatusCode{ StatusCode::Status::WARNING, "Attempted to remove component " + std::string(typeid(component).name()) + ", but it was not found.", component });
}

void flgin::GameObject::FixedUpdate()
{
	if (m_IsActive)
	{
		for (BaseComponent* component : m_pComponents)
			component->FixedUpdate();
	}
}

void flgin::GameObject::SetTag(std::string&& tag)
{
	if (m_Tags.find(tag) != m_Tags.cend())
	{
		m_Tag = m_Tags[tag];
		return;
	}
	m_Tag = m_Tags[tag] = ++m_Limit;
}

bool flgin::GameObject::CompareTag(std::string&& tag) const
{
	if (m_Tags.find(tag) != m_Tags.cend()) return m_Tag == m_Tags[tag];
	FLogger.Log(StatusCode{ StatusCode::Status::WARNING, "Attempted to compare tag with nonexistant tag: " + tag });
	return false;
}
