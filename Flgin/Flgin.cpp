#include "FlginPCH.h"
#include "Flgin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "Logger.h"
#include "Timer.h"
#include "Invoker.h"
#include "InputComponent.h"
#include "PlayerCommands.h"
#include "MovementGrid.h"
#include "GridRenderer.h"
#include "GridMovementComponent.h"
#include "MovementCommands.h"
#include "SpriteComponent.h"
#include "PathfinderComponent.h"
#include "TextLocalizer.h"
#include "StateComponent.h"
#include "FunctionHolder.h"
#include "CollisionManager.h"

void flgin::Flgin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0)
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, std::string("SDL_Init Error: ") + SDL_GetError(), this });
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	SDL_GameController* controller{ };

	for (int i{}, amt{ SDL_NumJoysticks() }; i < amt; ++i)
	{
		if (SDL_IsGameController(i))
			controller = SDL_GameControllerOpen(i);
	}

	m_pWindow = SDL_CreateWindow(
		"Flgin",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		630,
		460,
		SDL_WINDOW_OPENGL
	);
	if (m_pWindow == nullptr) 
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, std::string("SDL_CreateWindow Error: ") + SDL_GetError(), this });
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	FRenderer.Init(m_pWindow);
	FResourceManager.Init(FLocalizer.Get("dataPath"));
}

void flgin::Flgin::Cleanup()
{
	FRenderer.Destroy();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}

void flgin::Flgin::Run()
{
	float lag{ 1.0f };
	auto lastTime{ std::chrono::high_resolution_clock::now() };
	Renderer& renderer{ FRenderer };
	SceneManager& sceneManager{ FSceneManager };
	InputManager& input{ FInputManager };
	Invoker& invoker{ FInvoker };
	Time& time{ FTime };
	CollisionManager& collision{ FCollisionManager };
	bool doContinue{ true };
	float frameTime{ m_MsPerFrame / 1000.0f };
	time.SetFixedTime(frameTime);
	time.SetTimeScale(1.0f);

	if (!sceneManager.IsSceneSet())
	{
		FLogger.Log(StatusCode{ StatusCode::Status::FAIL, "Attempted to run engine, but no scene was set!" });
		return;
	}

	while (doContinue)
	{
		auto currTime{ std::chrono::high_resolution_clock::now() };
		float deltaTime{ std::chrono::duration<float>(currTime - lastTime).count() };
		lastTime = currTime;
		lag += deltaTime;
		time.SetDeltaTime(deltaTime);

		doContinue = input.ProcessInput();

		invoker.Update();
		sceneManager.Update();

		while (lag >= frameTime)
		{
			sceneManager.FixedUpdate();
			lag -= frameTime;
		}

		collision.HandleCollisions();

		renderer.Render();

		sceneManager.ExecuteSwap();
	}

	Cleanup();
}
