#pragma once
#include "StateComponent.h"

namespace flgin
{
	class SpriteComponent;
	class GridMovementComponent;
	class FreeMover;
}

namespace DigDug
{
	class Pooka;
	class Player;

	class PookaState : public flgin::State
	{
	public:
		PookaState() : flgin::State(), m_pPooka{}, m_pSprite{}, m_pFreeMover{} {}
		virtual ~PookaState() = default;
		virtual void Enter() = 0;
		virtual void Exit() = 0;
		virtual bool Update() = 0;

		void SetPooka(Pooka* pPooka);
		void SetSprite(flgin::SpriteComponent* pSprite);
		void SetGridMover(flgin::GridMovementComponent* pMover);
		void SetFreeMover(flgin::FreeMover* pMover);

	protected:
		Pooka* m_pPooka;
		flgin::SpriteComponent* m_pSprite;
		flgin::GridMovementComponent* m_pGridMover;
		flgin::FreeMover* m_pFreeMover;
	};

	class PookaIdleState final : public PookaState
	{
	public:
		PookaIdleState() : PookaState() {}
		~PookaIdleState() = default;
		void Enter() override;
		void Exit() override;
		bool Update() override;
	};

	class PookaGhostingState final : public PookaState
	{
	public:
		PookaGhostingState() : PookaState() {}
		~PookaGhostingState() = default;
		void Enter() override;
		bool Update() override;
		void Exit() override;
	};

	class PookaBloatingState final : public PookaState
	{
	public:
		PookaBloatingState() : PookaState(), m_BloatTime{ 0.f }, m_MaxBloatTime{ 3.f }, m_MaxBloatScale{ 1.f } {}
		~PookaBloatingState() = default;
		void Enter() override;
		bool Update() override;
		void Exit() override;

	private:
		float m_BloatTime;
		float m_MaxBloatTime;
		float m_MaxBloatScale;
	};
};