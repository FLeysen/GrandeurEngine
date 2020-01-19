#pragma once
#include "BaseComponent.h"

namespace flgin
{
	class FunctionHolderBase;
	class RenderComponent;
	class Texture2D;

	class ButtonComponent final : public BaseComponent
	{
	public:
		ButtonComponent(GameObject* pOwnerObject, RenderComponent* pRenderer, FunctionHolderBase* pFunc, Texture2D* pDefaultTex, Texture2D* pSelectedTex);
		~ButtonComponent();
		void Update() override {};
		void Select();
		void Deselect();
		void Press();
		void SetFunction(FunctionHolderBase* func) { m_pFunc = func; }

	private:
		FunctionHolderBase* m_pFunc;
		RenderComponent* m_pRenderComp;
		Texture2D* m_pDefaultTex;
		Texture2D* m_pSelectedTex;
	};
}
