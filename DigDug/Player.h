#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace DigDug
{
	class Player final : public flgin::Subject, public flgin::BaseComponent
	{
	public:
		Player(flgin::GameObject* pOwnerObject, flgin::GameObject* pPump);
		~Player() = default;
		void Update() {}

		glm::vec2 GetInitPos() const { return m_InitPos; }
		void SetInitPos(float x, float y) { m_InitPos.x = x; m_InitPos.y = y; }

		void ChangeLives(int amount, bool rawChange = false);
		UINT GetLives() const { return m_Lives; }

		void SetDying(bool dying) { m_IsDying = dying; }
		bool IsDying() const { return m_IsDying; }

		void ChangeScore(int amount);
		UINT GetScore() const { return m_Score; }

		void SetFiring(bool firing) { m_IsFiring = firing; }
		bool IsFiring() const { return m_IsFiring; }

		flgin::GameObject* GetPump() const { return m_pPump; }

	private:
		bool m_IsDying;
		bool m_IsFiring;
		UINT m_Lives;
		UINT m_Score;
		glm::vec2 m_InitPos;
		flgin::GameObject* m_pPump;
	};
}

