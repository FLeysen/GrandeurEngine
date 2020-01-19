#pragma once
#include "RenderComponent.h"
#include "SDL.h"

namespace flgin
{
	class Scene;
	class SpriteComponent final : public RenderComponent
	{
	public:
		~SpriteComponent() = default;
		void Update() override;
		void Render() const override;

		void SetSpriteInfo(unsigned int columns, unsigned int rows, float spriteWidth, float spriteHeight, float frameTime, bool shouldAnimate = true);
		void SetFlips(bool horizontal, bool vertical);
		void SetRotation(float angleInDegrees);
		void SetRotationalOffset(float xOffsetFromCenter, float yOffsetFromCenter);
		void IncrementCurrentFrame();
		bool GetFlippedHorizontal() const { return m_Flips & SDL_FLIP_HORIZONTAL; }
		bool GetFlippedVertical() const { return m_Flips & SDL_FLIP_VERTICAL; }
		void StopAnimating();

#pragma region ro5
		SpriteComponent()
			: RenderComponent(nullptr)
			, m_CurrentFrame{}
			, m_Columns{}
			, m_Rows{}
			, m_Rotation{}
			, m_Flips{}
			, m_RotationalCenter{}
			, m_SourceRect{}
		{}
		SpriteComponent(GameObject* const pOwnerObject)
			: RenderComponent(pOwnerObject)
			, m_CurrentFrame{}
			, m_Columns{}
			, m_Rows{}
			, m_Rotation{}
			, m_Flips{}
			, m_RotationalCenter{}
			, m_SourceRect{}
		{}
		SpriteComponent(SpriteComponent&& other) 
			: RenderComponent(other.m_pOwnerObject)
			, m_CurrentFrame{ other.m_CurrentFrame }
			, m_Columns{ other.m_Columns }
			, m_Rows{ other.m_Rows }
			, m_Rotation{ other.m_Rotation }
			, m_Flips{ other.m_Flips }
			, m_RotationalCenter{ other.m_RotationalCenter }
			, m_SourceRect{ other.m_SourceRect }
		{
			m_pTexture = other.m_pTexture;
			m_XOffset = other.m_XOffset;
			m_Width = other.m_Width;
			m_Height = other.m_Height;
			m_YOffset = other.m_YOffset;
		}
		SpriteComponent& operator=(SpriteComponent&& other)
		{
			m_pOwnerObject = other.m_pOwnerObject;
			m_CurrentFrame = other.m_CurrentFrame;
			m_Columns = other.m_Columns;
			m_Rows = other.m_Rows;
			m_Rotation = other.m_Rotation;
			m_Flips = other.m_Flips;
			m_RotationalCenter = other.m_RotationalCenter;
			m_SourceRect = other.m_SourceRect;
			m_pTexture = other.m_pTexture;
			m_XOffset = other.m_XOffset;
			m_Width = other.m_Width;
			m_Height = other.m_Height;
			m_YOffset = other.m_YOffset;
			return *this;
		};
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(const SpriteComponent&) = delete;
#pragma endregion

	private:
		unsigned int m_CurrentFrame;
		unsigned int m_Columns;
		unsigned int m_Rows;
		float m_Rotation;
		SDL_RendererFlip m_Flips;
		SDL_Point m_RotationalCenter;
		SDL_Rect m_SourceRect;
	};
}