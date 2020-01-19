#pragma once
#include "BaseComponent.h"

namespace flgin
{
	class FunctionHolderBase;

	class ColliderComponent final : public BaseComponent
	{
	public:
		ColliderComponent(GameObject* pOwnerObject, std::string&& layer, float width, float height);
		ColliderComponent(GameObject* pOwnerObject, std::string&& layer, float xOffset, float yOffset, float width, float height);
		~ColliderComponent();

		void Update() override {}
		void SetWidth(float width) { m_Width = width; }
		void SetHeight(float height) { m_Height = height; }
		void SetXOffset(float value) { m_XOffset = value; }
		void SetYOffset(float value) { m_YOffset = value; }
		void SetOnCollisionFunction(FunctionHolderBase* pFunc);
		void CheckAndExecuteCollision(ColliderComponent& other);
		ColliderComponent* GetCollisionHit() const { return m_pCollisionHit; }

	private:
		bool IsColliding(const ColliderComponent& other);

		float m_XOffset;
		float m_YOffset;
		float m_Width;
		float m_Height;
		ColliderComponent* m_pCollisionHit;
		FunctionHolderBase* m_pOnCollisionFunction;
	};
}