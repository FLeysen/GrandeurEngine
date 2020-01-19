#pragma once
#include "BaseComponent.h"

namespace flgin
{
	class Texture2D;
	class Scene;

	class RenderComponent : public BaseComponent
	{
	public:
		virtual ~RenderComponent() = default;
		virtual void Render() const;
		virtual void Update() override;

		bool ShouldDelete() override { return false; }
		void SetTexture(Texture2D const* newTexture, bool maintainDimensions = false);
		void SetPositionOffset(float x, float y);
		void SetDimensions(float width, float height);
		void ResetDimensions();
		float GetWidth() const { return m_Width; }
		float GetHeight() const { return m_Height; }

		RenderComponent();
		RenderComponent(GameObject* const ownerObject);
		RenderComponent(RenderComponent&& other) 
			: BaseComponent(other.m_pOwnerObject)
			, m_pTexture{ other.m_pTexture }
			, m_XOffset{ other.m_XOffset }
			, m_YOffset{ other.m_YOffset }
			, m_Width{ other.m_Width }
			, m_Height{ other.m_Height}
		{}
		RenderComponent& operator=(RenderComponent&& other)
		{
			m_pOwnerObject = other.m_pOwnerObject;
			m_pTexture = other.m_pTexture;
			m_XOffset = other.m_XOffset;
			m_Width = other.m_Width;
			m_Height = other.m_Height;
			m_YOffset = other.m_YOffset;
			return *this;
		};
		RenderComponent(const RenderComponent&) = delete;
		RenderComponent& operator=(const RenderComponent&) = delete;

	protected:
		float m_XOffset;
		float m_YOffset;
		float m_Width;
		float m_Height;
		Texture2D const* m_pTexture;
	};
}
