#pragma once
struct SDL_Texture;

namespace flgin
{
	class Texture2D
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		Texture2D() {}
		explicit Texture2D(SDL_Texture* texture);
		Texture2D & operator=(Texture2D&& other);
		~Texture2D();

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D&& other) = delete;
		Texture2D & operator= (const Texture2D &) = delete;

	private:
		SDL_Texture* m_pTexture;
	};
}
