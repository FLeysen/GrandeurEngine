#pragma once
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "RenderComponent.h"
#ifndef MAX_RENDERLAYERS
#define MAX_RENDERLAYERS 5
#endif
#ifndef MAX_RENDERERS_PER_LAYER
#define MAX_RENDERERS_PER_LAYER 300
#endif
#ifndef MAX_SPRITES_PER_LAYER
#define MAX_SPRITES_PER_LAYER 10
#endif

namespace flgin
{
	class RenderComponent;
	class GameObject;
	class SpriteComponent;

	class Scene
	{
	public:
		void AddGameObject(GameObject* const object);
		RenderComponent* CreateRenderComponent(GameObject* const ownerObject, unsigned int layer = 2);
		SpriteComponent* CreateSpriteComponent(GameObject* const ownerObject, unsigned int layer = 2);

		void FixedUpdate();
		void Update();
		void Render() const;

		template <class T>
		T* FindComponentOfType()
		{
			for (GameObject* const go : m_pGameObjects)
			{
				T* component{ go->GetComponent<T>() };
				if (component) return component;
			}
			return nullptr;
		}

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		friend Scene* SceneManager::CreateScene(const std::string& name);
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector<GameObject*> m_pGameObjects;
		RenderComponent m_RenderComponents[MAX_RENDERLAYERS * MAX_RENDERERS_PER_LAYER];
		SpriteComponent m_SpriteComponents[MAX_RENDERLAYERS * MAX_SPRITES_PER_LAYER];
		unsigned int m_RenderCompCount[MAX_RENDERLAYERS];
		unsigned int m_SpriteCompCount[MAX_RENDERLAYERS];
	};

}
