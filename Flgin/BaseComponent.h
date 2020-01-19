#pragma once
#include "GameObject.h"
namespace flgin
{
	class BaseComponent
	{
	public:
		BaseComponent(GameObject* ownerObject) : m_pOwnerObject{ ownerObject } {};
		virtual ~BaseComponent() = default;

		virtual void Update() = 0;
		virtual void FixedUpdate() {}
		virtual bool ShouldDelete() { return true; }
		GameObject* GetGameObject() { return m_pOwnerObject; };

		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) = delete;
		BaseComponent& operator=(const BaseComponent&) = delete;
		BaseComponent& operator=(BaseComponent&&) = delete;

	protected:
		GameObject* m_pOwnerObject;
	};
}