#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace flgin
{
	class MovementGrid;
}

namespace DigDug
{
	class Player;

	class Pooka final : public flgin::Subject, public flgin::BaseComponent
	{
	public:
		Pooka(flgin::GameObject* pOwnerObject);
		~Pooka() = default;
		void Update() override {}

		void Die();

		UINT GetScoreWorth();

		void SetBloating(bool bloating) { m_IsBloating = bloating; }
		bool IsBloating() const { return m_IsBloating; }

		void SetDeflating(bool deflating) { m_IsDeflating = deflating; }
		bool IsDeflating() const { return m_IsDeflating; }

		void SetGhosting(bool ghosting) { m_IsGhosting = ghosting; }
		bool IsGhosting() const { return m_IsGhosting; }

		void SetHitBy(Player* player) { m_pHitBy = player; }
		Player* GetHitBy() const { return m_pHitBy; }

		flgin::MovementGrid* GetGrid() { return m_pGrid; }
		static void SetGrid(flgin::MovementGrid* grid) { m_pGrid = grid; }

	private:
		bool m_IsBloating;
		bool m_IsDeflating;
		bool m_IsGhosting;
		Player* m_pHitBy;
		static flgin::MovementGrid* m_pGrid;
	};
}