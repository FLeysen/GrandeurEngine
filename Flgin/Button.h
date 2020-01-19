#pragma once
struct SDL_Color;

namespace flgin
{
	class GameObject;
	class FunctionHolderBase;
	class Scene;
	class MenuComponent;

	class Button final
	{
	public:
		static GameObject* Create(Scene* pScene, MenuComponent* pMenu, const std::string& text, const SDL_Color& colour, const std::string& fontName, const std::string& texName, const std::string& selectedTexName, FunctionHolderBase* action);
	private:
		Button() = delete;
	};
}

