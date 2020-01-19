#include "FlginPCH.h"
#include "Button.h"
#include "FunctionHolder.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "TextLocalizer.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "ButtonComponent.h"
#include "MenuComponent.h"

flgin::GameObject* flgin::Button::Create(Scene* pScene, MenuComponent* pMenu, const std::string& text, const SDL_Colour& colour, const std::string& fontName, const std::string& texName, const std::string& selectedTexName, FunctionHolderBase* action)
{
	GameObject* go{ new GameObject{} };
	RenderComponent* renderComponent{ pScene->CreateRenderComponent(go, 3) };
	go->AddComponent(renderComponent);

	RenderComponent* otherRenderComponent{ pScene->CreateRenderComponent(go, 2) };
	otherRenderComponent->SetTexture(FResourceManager.LoadTexture(texName));

	unsigned int fontSize{ 60 };
	TextComponent* textComp{  };
	do
	{
		FLogger.SafeDelete(textComp, true);
		textComp = new TextComponent{ go, fontName, fontSize, colour, text };
		fontSize -= 2;
	} while (renderComponent->GetWidth() > (otherRenderComponent->GetWidth() - 20.f)
		|| renderComponent->GetHeight() > (otherRenderComponent->GetHeight() - 20.f));

	renderComponent->SetPositionOffset((otherRenderComponent->GetWidth() - renderComponent->GetWidth()) * .5f, (otherRenderComponent->GetHeight() - renderComponent->GetHeight()) * 0.5f);

	ButtonComponent* buttonComponent{ new ButtonComponent{ go, otherRenderComponent, action, FResourceManager.LoadTexture(texName), FResourceManager.LoadTexture(selectedTexName) } };
	go->AddComponent(otherRenderComponent);
	go->AddComponent(buttonComponent);
	go->AddComponent(textComp);
	
	pMenu->AddButton(buttonComponent);
	pScene->AddGameObject(go);

	return go;
}
