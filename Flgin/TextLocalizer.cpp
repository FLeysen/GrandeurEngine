#include "FlginPCH.h"
#include "TextLocalizer.h"
#include "csv.h"

void flgin::Localizer::Load(std::string&& filename, std::string&& locale) 
{
	io::CSVReader<2, io::trim_chars<' '>, io::no_quote_escape <';'>> in{ filename };
	in.read_header(io::ignore_extra_column, "key", locale);
	std::string key{}, translation{};
	while (in.read_row(key, translation))
		m_Localizations[key] = translation;
}

const std::string& flgin::Localizer::Get(std::string&& key)
{
	return m_Localizations[key];
}
