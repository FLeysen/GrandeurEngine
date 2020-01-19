#include "FlginPCH.h"
#include "CollisionManager.h"
#include "FunctionHolder.h"
#include "ColliderComponent.h"

void flgin::CollisionManager::AddCollider(ColliderComponent* pCollider, std::string&& layer)
{
	if (m_LayerNames.find(layer) == m_LayerNames.cend())
	{
		m_LayerNames[layer] = m_Limit;
		m_pColliders[m_Limit] = {};
		m_IgnoredLayers[m_Limit] = {};
		++m_Limit;
	}
	m_pColliders[m_LayerNames[layer]].push_back(pCollider);
}

void flgin::CollisionManager::AddIgnore(std::string&& layer, std::string&& ignoredLayer)
{
	if (m_LayerNames.find(ignoredLayer) != m_LayerNames.cend() && m_LayerNames.find(layer) != m_LayerNames.cend())
	{
		if (m_LayerNames[layer] <= m_LayerNames[ignoredLayer])
		{
			m_IgnoredLayers[m_LayerNames[layer]].emplace(m_LayerNames[ignoredLayer]);
		}
		else
			FLogger.Log(StatusCode{ StatusCode::Status::WARNING, "Cannot add ignore layer " + ignoredLayer + " to layer " + layer + " (should be higher or equal index)" });
	}
	else
		FLogger.Log(StatusCode{ StatusCode::Status::WARNING, "Cannot add ignore layer " + ignoredLayer + " to layer " + layer + " (at least one of the layers does not exist)" });
}

void flgin::CollisionManager::HandleCollisions()
{
	for (UINT i{}; i < m_Limit; ++i)
	{
		for (UINT j{ i }; j < m_Limit; ++j)
		{
			if (m_IgnoredLayers[i].find(j) == m_IgnoredLayers[i].cend())
			{
				for (ColliderComponent* pCollider : m_pColliders[i])
				{
					for (ColliderComponent* pOther : m_pColliders[j])
					{
						if (pCollider != pOther)
							pCollider->CheckAndExecuteCollision(*pOther);
					}
				}
			}
		}
	}
}

void flgin::CollisionManager::ClearColliders()
{
	m_Limit = 0;
	m_pColliders.clear();
	m_IgnoredLayers.clear();
	m_LayerNames.clear();
}
