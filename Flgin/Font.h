#pragma once
#include <SDL_ttf.h>

namespace flgin
{
	class Font
	{
	public:
		TTF_Font* GetFont() const;
		unsigned int GetSize() const;
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();
		Font(Font&& other);

		Font(const Font &) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;

	private:
		unsigned int m_Size;
		std::string m_Path;
		TTF_Font* m_pFont;
	};
}
