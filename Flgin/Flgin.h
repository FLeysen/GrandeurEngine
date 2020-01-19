#pragma once

struct SDL_Window;

namespace flgin
{
	class Flgin
	{
	public:
		void Initialize();
		void Cleanup();
		void Run();

	private:
		SDL_Window* m_pWindow{};
		const int m_MsPerFrame{ 16 }; //16 for 60 fps, 33 for 30 fps
	};
}