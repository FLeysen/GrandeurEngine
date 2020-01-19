#include "FlginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

flgin::Texture2D::~Texture2D()
{
	if (m_pTexture) SDL_DestroyTexture(m_pTexture);
}

SDL_Texture* flgin::Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}

flgin::Texture2D::Texture2D(SDL_Texture* texture)
	: m_pTexture{ texture }
{}

flgin::Texture2D& flgin::Texture2D::operator=(Texture2D&& other)
{
	m_pTexture = other.m_pTexture;
	other.m_pTexture = nullptr;
	return *this;
}
