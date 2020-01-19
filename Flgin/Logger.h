#pragma once
#include "Singleton.h"
#include <fstream>
#define FLogger flgin::Logger::GetInstance()

namespace flgin
{
	struct StatusCode
	{
		enum class Status : unsigned int { FAIL = 0, SUCCESS = 1, WARNING = 2 };
		Status status;
		std::string message;
		void* attachedObject;
		explicit StatusCode(Status status = Status::SUCCESS, const std::string& message = "", void* attachedObject = nullptr)
			: status{ status }, message{ message }, attachedObject{ attachedObject }{}
	};

	class Logger : public Singleton<Logger>
	{
	public:
		void Log(StatusCode&& sc);
		template<class T>
		void SafeDelete(T& pObjectToDelete, bool ignoreWarning = false)
		{
			if (pObjectToDelete != nullptr)
			{
				delete pObjectToDelete;
				pObjectToDelete = nullptr;
			}
			else if (!ignoreWarning)
			{
				Log(StatusCode{ StatusCode::Status::WARNING, "Attempted to delete a nullpointer of type " + std::string(typeid(T).name()) });
			}
		}

		template<class T>
		void SafeDeleteArray(T& pArrayToDelete, bool ignoreWarning = false)
		{
			if (pArrayToDelete != nullptr)
			{
				delete[] pArrayToDelete;
				pArrayToDelete = nullptr;
			}
			else if (!ignoreWarning)
			{
				Log(StatusCode{ StatusCode::Status::WARNING, "Attempted to delete a nullpointer to array of type " + std::string(typeid(T).name()) });
			}
		}

		Logger();
		~Logger();

		Logger(const Logger& other) = delete;
		Logger(Logger&& other) = delete;
		Logger& operator=(const Logger& other) = delete;
		Logger& operator=(Logger&& other) = delete;

	private:
		std::ofstream m_Output;
		std::vector<StatusCode> m_Logged;
	};
}