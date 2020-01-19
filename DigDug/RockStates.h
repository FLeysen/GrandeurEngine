#pragma once
#include "StateComponent.h"

namespace flgin
{
	class FreeMover;
	class ColliderComponent;
	class GridNode;
}

namespace DigDug
{
	class RockState : public flgin::State
	{
	public:
		RockState() : flgin::State(), m_pFreeMover{}, m_pCollider{}, m_pCollidedWith{}, m_pNode{} {}
		virtual ~RockState() = default;
		virtual void Enter() = 0;
		virtual void Exit() = 0;
		virtual bool Update() = 0;
		virtual void CheckPlayerHit() = 0;

		void SetAttachedMover(flgin::FreeMover* pMover) { m_pFreeMover = pMover; }
		void SetAttachedCollider(flgin::ColliderComponent* pCollider) { m_pCollider = pCollider; }
		void SetNode(flgin::GridNode* node) { m_pNode = node; }

	protected:
		flgin::FreeMover* m_pFreeMover;
		flgin::GridNode* m_pNode;
		flgin::ColliderComponent* m_pCollider;
		flgin::ColliderComponent* m_pCollidedWith;
	};

	class StuckState final : public RockState
	{
	public:
		StuckState() : RockState() {}
		~StuckState() = default;
		
		void Enter() override;
		void Exit() override;
		bool Update() override;
		void CheckPlayerHit() override;
	};

	class AwaitingFallState final : public RockState
	{
	public:
		AwaitingFallState(flgin::ColliderComponent* pOtherColl) : RockState(), m_StillColliding{ false } { m_pCollidedWith = pOtherColl; }
		~AwaitingFallState() = default;

		void Enter() override;
		void Exit() override;
		bool Update() override;
		void CheckPlayerHit() override;

	private:
		bool m_StillColliding;
	};

	class FallingState final : public RockState
	{
	public:
		FallingState(flgin::ColliderComponent* pOtherColl) : RockState() { m_pCollidedWith = pOtherColl; }
		~FallingState() = default;

		void Enter() override;
		void Exit() override;
		bool Update() override;
		void CheckPlayerHit() override;

	private:
		void GrantScore();

		UINT m_AmountCrushed;
	};
}