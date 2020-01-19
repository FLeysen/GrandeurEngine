#pragma once
#include "BaseComponent.h"
#include "Font.h"
namespace flgin
{
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(GameObject* const ownerObject, const std::string& fontPath, const unsigned int fontSize, const SDL_Color& color = { 255,255,255 }, const std::string& text = " ");
		~TextComponent();
		void Update() override;
		void SetText(const std::string& text);

		TextComponent(const TextComponent&) = delete;
		TextComponent(TextComponent&&) = delete;
		TextComponent& operator=(const TextComponent&) = delete;
		TextComponent& operator=(TextComponent&&) = delete;

	private:
		void CreateTexture();

		bool m_WasTextChanged;
		std::string m_Text;
		Font* m_pFont;
		Texture2D* m_pTexture;
		SDL_Color m_TextColor;
	};
}