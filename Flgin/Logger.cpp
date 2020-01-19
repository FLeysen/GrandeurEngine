#include "FlginPCH.h"
#include <ctime>
#include <time.h>
#include <chrono>

void flgin::Logger::Log(StatusCode&& sc)
{
#ifdef _DEBUG
	for (const StatusCode& logged : m_Logged)
	{
		if (logged.attachedObject == sc.attachedObject)
		{
			if (logged.message == sc.message)
				return;
		}
	}

	auto accurateTime{ std::chrono::system_clock::now() };
	std::time_t currentTime{ std::chrono::system_clock::to_time_t(accurateTime) };
	std::tm now{  };
	localtime_s(&now, &currentTime);

	m_Output << '[' << (now.tm_year + 1900) << '-'
		<< (now.tm_mon + 1) << '-' << now.tm_mday
		<< ' ' << now.tm_hour << ':' << now.tm_min
		<< ':' << now.tm_sec << ']';

	if (sc.status == StatusCode::Status::WARNING)
		m_Output << "[WARNING]: ";
	else if (sc.status == StatusCode::Status::FAIL)
		m_Output << "[ERROR]: ";
	else
		m_Output << "[SUCCESS]: ";

	m_Output << sc.message << '\n';

	if (sc.attachedObject != nullptr)
		m_Logged.push_back(sc);
#else
	(sc);
#endif
}

flgin::Logger::Logger()
	: m_Output{ }
{
#ifdef _DEBUG
	auto accurateTime{ std::chrono::system_clock::now() };
	std::time_t currentTime{ std::chrono::system_clock::to_time_t(accurateTime) };
	std::tm now{  };
	localtime_s(&now, &currentTime);
	std::stringstream outPath{};
	outPath << "Logger/Output_"
		<< (now.tm_year + 1900) << '-'
		<< (now.tm_mon + 1) << '-'
		<< now.tm_mday << '_' 
		<< now.tm_hour << '-' 
		<< now.tm_min << '-' 
		<< now.tm_sec << ".txt";
	m_Output.open(outPath.str());

	m_Output << "Engine version: 3.0\n";
#endif
}

flgin::Logger::~Logger()
{
	if (m_Output) m_Output.close();
}