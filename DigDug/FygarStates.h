#pragma once
#include "StateComponent.h"

namespace flgin
{
	class SpriteComponent;
	class GridMovementComponent;
}

namespace DigDug
{
	class Fygar;
	class Player;

	class FygarState : public flgin::State
	{
	public:
		FygarState() : flgin::State(), m_pFygar{}, m_pSprite{} {}
		virtual ~FygarState() = default;
		virtual void Enter() = 0;
		virtual void Exit() = 0;
		virtual bool Update() = 0;

		void SetFygar(Fygar* pFygar);
		void SetSprite(flgin::SpriteComponent* pSprite);
		void SetMover(flgin::GridMovementComponent* pMover);

	protected:
		Fygar* m_pFygar;
		flgin::SpriteComponent* m_pSprite;
		flgin::GridMovementComponent* m_pMover;
	};

	class FygarIdleState final : public FygarState
	{
	public:
		FygarIdleState() : FygarState() {}
		~FygarIdleState() = default;
		void Enter() override;
		void Exit() override;
		bool Update() override;
	};

	class FygarFiringState final : public FygarState
	{
	public:
		FygarFiringState() : FygarState() {}
		~FygarFiringState() = default;
		void Enter() override;
		bool Update() override;
		void Exit() override;
	};

	class FygarBloatingState final : public FygarState
	{
	public:
		FygarBloatingState() : FygarState(), m_BloatTime{ 0.f }, m_MaxBloatTime{ 3.f }, m_MaxBloatScale{ 1.f } {}
		~FygarBloatingState() = default;
		void Enter() override;
		bool Update() override;
		void Exit() override;

	private:
		float m_BloatTime;
		float m_MaxBloatTime;
		float m_MaxBloatScale;
	};
};