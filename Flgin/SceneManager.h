#pragma once
#include "Singleton.h"
#include <unordered_map>
#define FSceneManager flgin::SceneManager::GetInstance()

namespace flgin
{
	class FunctionHolderBase;
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* CreateScene(const std::string& name);
		~SceneManager();

		void ExecuteSwap();
		void SwapScene(FunctionHolderBase* pSwapAction);
		bool IsSceneSet() const { return m_pCurrScene; }
		void FixedUpdate();
		void Update();
		void Render() const;
		void ActivateSceneByName(std::string&& name);
		void RemoveSceneByName(std::string&& name);
		void RemoveCurrentScene();
		Scene* GetCurrentScene() const { return m_pCurrScene; }

	private:
		FunctionHolderBase* m_pSwapAction{ nullptr };
		Scene* m_pCurrScene{ nullptr };
		std::unordered_map<std::string, Scene*> m_pScenes{};
	};

}
