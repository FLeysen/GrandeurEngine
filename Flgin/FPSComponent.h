#pragma once
#include "BaseComponent.h"
namespace flgin
{
	class TextComponent;
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(GameObject* const ownerObject, const float timeBetweenUpdates);
		~FPSComponent() = default;
		void Update() override;

	private:
		int m_ElapsedFrames;
		float m_TimeBetweenUpdates;
		float m_ElapsedTime;
		TextComponent* m_Text;
	};
}