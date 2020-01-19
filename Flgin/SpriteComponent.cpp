#include "FlginPCH.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "Invoker.h"

void flgin::SpriteComponent::Update()
{}

void flgin::SpriteComponent::Render() const
{
	if (m_pOwnerObject->IsActive())
	{
		if (!m_pTexture)
		{
			FLogger.Log(StatusCode{ StatusCode::Status::WARNING, "SpriteComponent does not have an attached texture!", (void*)this });
			return;
		}

		const glm::vec2& pos{ m_pOwnerObject->GetPosition() };
		SDL_Rect destRect{ };
		destRect.x = static_cast<int>(pos.x + m_XOffset);
		destRect.y = static_cast<int>(pos.y + m_YOffset);
		destRect.w = static_cast<int>(m_Width);
		destRect.h = static_cast<int>(m_Height);

		int result{ SDL_RenderCopyEx(
				FRenderer.GetSDLRenderer(),
				m_pTexture->GetSDLTexture(),
				&m_SourceRect,
				&destRect,
				m_Rotation,
				&m_RotationalCenter,
				m_Flips) };

		if (result != 0)
			FLogger.Log(StatusCode{ StatusCode::Status::FAIL, std::string("SpriteComponent failed to render: ") + SDL_GetError(), (void*)this });
	}
}

void flgin::SpriteComponent::SetSpriteInfo(unsigned int columns, unsigned int rows, float spriteWidth, float spriteHeight, float frameTime, bool shouldAnimate)
{
	m_CurrentFrame = 0;
	m_Columns = columns;
	m_Rows = rows;
	m_SourceRect.x = 0;
	m_SourceRect.y = 0;
	m_SourceRect.w = static_cast<int>(spriteWidth);
	m_SourceRect.h = static_cast<int>(spriteHeight);
	Invoker& invoker{ FInvoker };
	invoker.CancelOwnedInvokes(this);

	if (shouldAnimate)
	{
		std::function<void()> calculateFrame{ std::bind(&flgin::SpriteComponent::IncrementCurrentFrame, this) };
		InvokeHolderBase* fnHolder{ new InvokeHolder<void>{this, frameTime, calculateFrame} };
		fnHolder->SetRepeating(true);
		invoker.AddInvoke(fnHolder);
	}
}

void flgin::SpriteComponent::SetFlips(bool horizontal, bool vertical)
{
	m_Flips = SDL_FLIP_NONE;

	if (horizontal)
		m_Flips = SDL_FLIP_HORIZONTAL;
	if (vertical)
		m_Flips = static_cast<SDL_RendererFlip>(m_Flips | SDL_FLIP_VERTICAL);
}

void flgin::SpriteComponent::SetRotation(float angleInDegrees)
{
	m_Rotation = angleInDegrees;
}

void flgin::SpriteComponent::SetRotationalOffset(float xOffsetFromCenter, float yOffsetFromCenter)
{
	m_RotationalCenter.x = static_cast<int>(m_SourceRect.w / 2.f + xOffsetFromCenter);
	m_RotationalCenter.y = static_cast<int>(m_SourceRect.h / 2.f + yOffsetFromCenter);
}

void flgin::SpriteComponent::IncrementCurrentFrame()
{
	++m_CurrentFrame;
	if (m_CurrentFrame == m_Columns * m_Rows)
		m_CurrentFrame = 0;

	m_SourceRect.x = static_cast<int>(m_CurrentFrame % m_Columns * m_SourceRect.w);
	m_SourceRect.y = static_cast<int>(m_CurrentFrame / m_Columns * m_SourceRect.h);
}

void flgin::SpriteComponent::StopAnimating()
{
	FInvoker.CancelOwnedInvokes(this);
}
