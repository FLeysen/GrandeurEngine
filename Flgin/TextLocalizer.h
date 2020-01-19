#pragma once
#include <string>
#include <unordered_map>
#include "Singleton.h"
#define FLocalizer flgin::Localizer::GetInstance()

namespace flgin
{
	class Localizer final : public Singleton<Localizer>
	{
	public:
		void Load(std::string&& filename, std::string&& locale);
		const std::string& Get(std::string&& key);
		
		Localizer() = default;
		~Localizer() = default;
		Localizer(Localizer&&) = delete;
		Localizer(const Localizer&) = delete;
		Localizer& operator=(Localizer&&) = delete;
		Localizer& operator=(const Localizer&) = delete;

	private:
		std::unordered_map<std::string, std::string> m_Localizations;
	};
}
