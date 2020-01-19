#include "FlginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "FunctionHolder.h"

void flgin::SceneManager::Update()
{
	m_pCurrScene->Update();
}

void flgin::SceneManager::FixedUpdate()
{
	m_pCurrScene->FixedUpdate();
}

void flgin::SceneManager::Render() const
{
	m_pCurrScene->Render();
}

void flgin::SceneManager::ActivateSceneByName(std::string&& name)
{
	if (m_pScenes.find(name) == m_pScenes.cend())
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "Attempted to activate nonexistant scene!" });
		return;
	}
	m_pCurrScene = m_pScenes[name];
}

flgin::Scene* flgin::SceneManager::CreateScene(const std::string& name)
{
	if (m_pScenes.find(name) != m_pScenes.cend())
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "Attempted to create scene " + name + ", but a scene with the same name is already present!" });
		return nullptr;
	}
	m_pScenes[name] = new Scene{ name };
	return m_pScenes[name];
}

flgin::SceneManager::~SceneManager()
{
	FLogger.SafeDelete(m_pSwapAction, true);
	for (std::pair<std::string, Scene*> scene : m_pScenes)
		FLogger.SafeDelete(scene.second);
}

void flgin::SceneManager::ExecuteSwap()
{
	if (!m_pSwapAction) return;
	m_pSwapAction->Call();
	delete m_pSwapAction;
	m_pSwapAction = nullptr;
}

void flgin::SceneManager::SwapScene(FunctionHolderBase* pSwapAction)
{
	m_pSwapAction = pSwapAction;
}

void flgin::SceneManager::RemoveSceneByName(std::string&& name)
{
	auto it{ m_pScenes.find(name) };
	if (it == m_pScenes.end())
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "Attempted to remove scene " + name + ", but a scene with no such name exists!" });
		return;
	}
	FLogger.SafeDelete(it->second);
	m_pScenes.erase(it);
}

void flgin::SceneManager::RemoveCurrentScene()
{
	if (m_pCurrScene)
	{
		auto it{ std::find_if(m_pScenes.begin(), m_pScenes.end(), [this](const std::pair<std::string, Scene*>& scene) { return scene.second == m_pCurrScene; }) };
		m_pScenes.erase(it);
		FLogger.SafeDelete(m_pCurrScene);
	}
	else
	{
		FLogger.Log(StatusCode{ StatusCode::Status::WARNING, "Attempted to remove current scene, but no scene was set!" });
	}
}
