#pragma once
#include "Singleton.h"
#define FRenderer flgin::Renderer::GetInstance()

struct SDL_Window;
struct SDL_Renderer;

namespace flgin
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }

	private:
		SDL_Renderer* m_pRenderer{ nullptr };
	};
}

