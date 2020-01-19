#pragma once
#define FTime flgin::Time::GetInstance()

#include "Singleton.h"
namespace flgin
{
	class Time final : public Singleton<Time>
	{
	public:
		Time() : m_DeltaTime{ 0.0f }, m_FixedTime{ 0.02f }, m_TimeScale{ 1.0f }, m_TotalTime{ 0.0f }, m_SceneTime{ 0.0f }{};

		float GetDeltaTime() { return m_DeltaTime * m_TimeScale; }
		float GetRawDeltaTime() { return m_DeltaTime; }
		float GetFixedTime() { return m_FixedTime; }
		float GetSceneTime() { return m_SceneTime; }
		float GetTotalTime() { return m_TotalTime; }
		void SetDeltaTime(float deltaTime) { m_DeltaTime = deltaTime; m_TotalTime += m_DeltaTime; }
		void SetFixedTime(float fixedTime) { m_FixedTime = fixedTime; }
		void SetTimeScale(float timeScale) { m_TimeScale = timeScale; }
		void ResetSceneTime() { m_SceneTime = 0.0f; }

		~Time() = default;
		Time(const Time& other) = delete;
		Time(Time&& other) = delete;
		Time& operator=(const Time& other) = delete;
		Time& operator=(Time&& other) = delete;

	private:
		float m_DeltaTime;
		float m_TimeScale;
		float m_FixedTime;
		float m_SceneTime;
		float m_TotalTime;
	};
}