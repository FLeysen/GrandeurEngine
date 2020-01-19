#include "FlginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "RenderComponent.h"
#include "ResourceManager.h"

flgin::TextComponent::TextComponent(GameObject* const ownerObject, const std::string& fontPath, const unsigned int fontSize, const SDL_Color& color, const std::string& text)
	: BaseComponent(ownerObject)
	, m_pFont{ FResourceManager.LoadFont(fontPath, fontSize) }
	, m_TextColor{ color }
	, m_Text{ text }
	, m_WasTextChanged{ true }
{
	CreateTexture();
}

flgin::TextComponent::~TextComponent()
{
	FLogger.SafeDelete(m_pTexture);
}

void flgin::TextComponent::Update()
{
	if (m_WasTextChanged)
		CreateTexture();
}

void flgin::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_WasTextChanged = true;
}

void flgin::TextComponent::CreateTexture()
{
	RenderComponent* const renderComponent{ m_pOwnerObject->GetComponent<RenderComponent>() };
	if (renderComponent == nullptr)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::WARNING, "TextComponent could not find attached RenderComponent.", this });
		return;
	}

	SDL_Surface* const surface{ TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_TextColor) };
	if (surface == nullptr)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, std::string("Render text failed: ") + SDL_GetError(), this });
		return;
	}
	SDL_Texture* const texture{ SDL_CreateTextureFromSurface(FRenderer.GetSDLRenderer(), surface) };
	if (texture == nullptr)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, std::string("Create text texture from surface failed: ") + SDL_GetError(), this });
		return;
	}
	SDL_FreeSurface(surface);

	FLogger.SafeDelete(m_pTexture, true);
	renderComponent->SetTexture(m_pTexture = new Texture2D{ texture });
	m_WasTextChanged = false;
}
