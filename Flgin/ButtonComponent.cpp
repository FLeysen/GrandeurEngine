#include "FlginPCH.h"
#include "ButtonComponent.h"
#include "FunctionHolder.h"
#include "RenderComponent.h"

flgin::ButtonComponent::ButtonComponent(GameObject* pOwnerObject, RenderComponent* pRenderer, FunctionHolderBase* pFunc, Texture2D* pDefaultTex, Texture2D* pSelectedTex)
	: BaseComponent(pOwnerObject)
	, m_pFunc{ pFunc }
	, m_pDefaultTex{ pDefaultTex }
	, m_pSelectedTex{ pSelectedTex }
	, m_pRenderComp{ pRenderer }
{}

flgin::ButtonComponent::~ButtonComponent()
{
	FLogger.SafeDelete(m_pFunc);
}

void flgin::ButtonComponent::Select()
{
#ifdef _DEBUG
	if (!m_pSelectedTex)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "Attempted to select a button without select texture!\n", this });
		return;
	}
#endif
	m_pRenderComp->SetTexture(m_pSelectedTex);
}

void flgin::ButtonComponent::Deselect()
{
#ifdef _DEBUG
	if (!m_pSelectedTex)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "Attempted to deselect a button without deselect texture!\n", this });
		return;
	}
#endif
	m_pRenderComp->SetTexture(m_pDefaultTex);
}

void flgin::ButtonComponent::Press()
{
#ifdef _DEBUG
	if (!m_pFunc)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "Attempted to press a button without linked function!\n", this });
		return;
	}
#endif
	m_pFunc->Call();
}
