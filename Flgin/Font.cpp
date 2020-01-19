#include "FlginPCH.h"
#include "Font.h"

flgin::Font::Font(const std::string& fullPath, unsigned int size)
	: m_pFont{ nullptr }
	, m_Size{ size }
	, m_Path{ fullPath }
{
	m_pFont = TTF_OpenFont(fullPath.c_str(), size);
	if (m_pFont == nullptr)
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, std::string("Failed to load font: ") + SDL_GetError(), this });
}

flgin::Font::~Font()
{
	if (m_pFont) TTF_CloseFont(m_pFont);
}

flgin::Font::Font(Font&& other)
{
	m_Size = other.m_Size;
	m_Path = other.m_Path;
	m_pFont = other.m_pFont;
	other.m_pFont = nullptr;
}

TTF_Font* flgin::Font::GetFont() const
{
	return m_pFont;
}

unsigned int flgin::Font::GetSize() const
{
	return m_Size;
}
