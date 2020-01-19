#pragma once
#include "Singleton.h"
#include <unordered_map>
#include "Font.h"
#include "Texture2D.h"
#define FResourceManager flgin::ResourceManager::GetInstance()

namespace flgin
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		ResourceManager() = default;
		~ResourceManager() = default;

		void Init(const std::string& data);

		Texture2D* LoadTexture(const std::string& file);
		Font* LoadFont(const std::string& file, unsigned int size);

	private:
		std::string m_DataPath;
		std::unordered_map<std::string, Texture2D> m_Textures;
		std::unordered_multimap<std::string, Font> m_Fonts;
	};
}
