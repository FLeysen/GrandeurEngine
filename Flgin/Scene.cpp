#include "FlginPCH.h"
#include "Scene.h"
#include "GameObject.h"

flgin::Scene::Scene(const std::string& name) 
	: m_Name{ name }
	, m_pGameObjects{}
	, m_RenderComponents{}
	, m_SpriteComponents{}
	, m_RenderCompCount{}
	, m_SpriteCompCount{}
{}

flgin::Scene::~Scene()
{
	Logger& logger{ FLogger };
	for (GameObject* gameObject : m_pGameObjects)
		logger.SafeDelete(gameObject);
};

void flgin::Scene::AddGameObject(GameObject* const object)
{
	m_pGameObjects.push_back(object);
}

flgin::RenderComponent* flgin::Scene::CreateRenderComponent(GameObject* const ownerObject, unsigned int layer)
{
	if (layer > MAX_RENDERLAYERS)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "Attempted to add render component to nonexistant layer: " + layer });
		return nullptr;
	}
	if (m_RenderCompCount[layer] == MAX_RENDERERS_PER_LAYER)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "Attempted to add render component to full layer: " + layer });
		return nullptr;
	}
	
	return &(m_RenderComponents[layer * MAX_RENDERERS_PER_LAYER + m_RenderCompCount[layer]++] = RenderComponent{ ownerObject });
}

flgin::SpriteComponent* flgin::Scene::CreateSpriteComponent(GameObject* const ownerObject, unsigned int layer)
{
	if (layer > MAX_RENDERLAYERS)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "Attempted to add sprite component to nonexistant layer: " + layer });
		return nullptr;
	}
	if (m_SpriteCompCount[layer] == MAX_SPRITES_PER_LAYER)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "Attempted to add sprite component to full layer: " + layer });
		return nullptr;
	}

	return &(m_SpriteComponents[layer * MAX_SPRITES_PER_LAYER + m_SpriteCompCount[layer]++] = SpriteComponent{ ownerObject });
}

void flgin::Scene::Update()
{
	for (GameObject* const gameObject : m_pGameObjects)
		gameObject->Update();
}

void flgin::Scene::FixedUpdate()
{
	for (GameObject* const gameObject : m_pGameObjects)
		gameObject->FixedUpdate();
}

void flgin::Scene::Render() const
{
	for (unsigned int i{}; i < MAX_RENDERLAYERS; ++i)
	{
		for (unsigned int j{}; j < m_RenderCompCount[i]; ++j)
			m_RenderComponents[i * MAX_RENDERERS_PER_LAYER + j].Render();
		for (unsigned int j{}; j < m_SpriteCompCount[i]; ++j)
			m_SpriteComponents[i * MAX_SPRITES_PER_LAYER + j].Render();
	}
}
