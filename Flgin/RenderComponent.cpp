#include "FlginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "Scene.h"
#include "SDL.h"

flgin::RenderComponent::RenderComponent()
	: BaseComponent(nullptr)
	, m_pTexture{ nullptr }
	, m_XOffset{ 0.0f }
	, m_YOffset{ 0.0f }
	, m_Height{}
	, m_Width{}
{}

flgin::RenderComponent::RenderComponent(GameObject* const ownerObject)
	: BaseComponent(ownerObject)
	, m_pTexture{ nullptr }
	, m_XOffset{ 0.0f }
	, m_YOffset{ 0.0f }
	, m_Height{}
	, m_Width{}
{}

void flgin::RenderComponent::Render() const
{
	if (m_pOwnerObject->IsActive())
	{
		if (!m_pTexture)
		{
			FLogger.Log(StatusCode{ StatusCode::Status::WARNING, "RenderComponent does not have an attached texture!", (void*)this });
			return;
		}
		const glm::vec2& pos{ m_pOwnerObject->GetPosition() };
		FRenderer.RenderTexture(*m_pTexture, pos.x + m_XOffset, pos.y + m_YOffset, m_Width, m_Height);
	}
}

void flgin::RenderComponent::Update()
{}

void flgin::RenderComponent::SetTexture(flgin::Texture2D const* newTexture, bool maintainDimensions)
{
	m_pTexture = newTexture;
	if(!maintainDimensions) ResetDimensions();
}

void flgin::RenderComponent::SetPositionOffset(float x, float y)
{
	m_XOffset = x;
	m_YOffset = y;
}

void flgin::RenderComponent::ResetDimensions()
{
	if (!m_pTexture)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "Attempted to reset dimensions on nullpointer texture!" });
		return;
	}
	int width{};
	int height{};
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &width, &height);
	m_Width = float(width);
	m_Height = float(height);
}

void flgin::RenderComponent::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}