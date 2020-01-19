#pragma once
#include <memory>
#include <algorithm>
#include <unordered_map>

#include "Transform.h"
#include "Texture2D.h"
namespace flgin
{
	class BaseComponent;
	class GameObject final
	{
	public:
		GameObject();

		void SetActive(bool active) { m_IsActive = active; }
		bool IsActive() const { return m_IsActive; }
		void Update();
		void FixedUpdate();

		void SetTag(std::string&& tag);
		bool CompareTag(std::string&& tag) const;

		void SetPosition(float x, float y);
		glm::vec2 GetPosition() const;
		void AddComponent(BaseComponent* const component);
		void RemoveComponent(BaseComponent* const component);

		template <class T>
		void RemoveComponentsOfType()
		{
			const type_info& typeInfo{ typeid(T) };
			auto it{ std::remove_if(m_pComponents.begin(), m_pComponents.end(), 
					[&typeInfo](BaseComponent* component)
					{
						if (typeid(*component) == typeInfo)
						{
							FLogger.SafeDelete(component);
							return true;
						}
						return false;
					}) };
			m_pComponents.erase(it, m_pComponents.end());
		}
		template <class T> 
		T* GetComponent()
		{
			const type_info& typeInfo{ typeid(T) };
			for (BaseComponent* const component : m_pComponents)
			{
				if (typeid(*component) == typeInfo)					
					return static_cast<T*>(component);
			}
			return nullptr;
		}

		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		bool m_IsActive;
		UINT m_Tag;
	    Transform m_Transform;
		std::vector<BaseComponent*> m_pComponents;

		static UINT m_Limit;
		static std::unordered_map<std::string, UINT> m_Tags;
	};
}