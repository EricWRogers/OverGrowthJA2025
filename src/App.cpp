#include "App.hpp"

#include <Canis/Canis.hpp>
#include <Canis/Debug.hpp>

#include <Canis/ECS/Decode.hpp>

#include "ECS/ScriptableEntities/DebugCamera2D.hpp"
#include "ECS/ScriptableEntities/SplashLoader.hpp"
//#include "ECS/ScriptableEntities/MainMenuButtons.hpp"

#include <Canis/ECS/Systems/ButtonSystem.hpp>

#include <Canis/ECS/Systems/RenderHUDSystem.hpp>
#include <Canis/ECS/Systems/RenderTextSystem.hpp>
#include <Canis/ECS/Systems/SpriteRenderer2DSystem.hpp>

App::App()
{
	//LoadConfigs();

	{ // decode system
		sceneManager.decodeSystem.push_back(Canis::DecodeButtonSystem);
	}

	{ // decode render system
		sceneManager.decodeRenderSystem.push_back(Canis::DecodeRenderHUDSystem);
		sceneManager.decodeRenderSystem.push_back(Canis::DecodeRenderTextSystem);
		sceneManager.decodeRenderSystem.push_back(Canis::DecodeSpriteRenderer2DSystem);
	}

	{ // decode scriptable entities
		sceneManager.decodeScriptableEntity.push_back(DecodeDebugCamera2D);
		sceneManager.decodeScriptableEntity.push_back(DecodeSplashLoader);
		//sceneManager.decodeScriptableEntity.push_back(DecodeMainMenuButtons);
	}

	{ // decode component
		sceneManager.decodeEntity.push_back(Canis::DecodeTagComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeCamera2DComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeRectTransformComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeColorComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeTextComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeSprite2DComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeUIImageComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeUISliderComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeSpriteAnimationComponent);
	}
}
App::~App()
{
	
}

void App::Run()
{
	if (appState == AppState::ON)
		Canis::FatalError("App already running.");

	Canis::Init();

	unsigned int windowFlags = 0;

	// windowFlags |= Canis::WindowFlags::FULLSCREEN;

	// windowFlags |= Canis::WindowFlags::BORDERLESS;

	if (false)//gameConfig.fullscreen)
		window.CreateFullScreen("Canis : Template Project");
	else
		window.Create("Canis : Template Project", 1280, 800, windowFlags);//gameConfig.width, gameConfig.heigth, windowFlags);

	time.init(10000);

	camera.override_camera = false;

	seed = std::time(NULL);
	srand(seed);
	Canis::Log("seed : " + std::to_string(seed));

	sceneManager.Add(new Canis::Scene("engine_splash", "assets/scenes/engine_splash.scene"));
	sceneManager.Add(new Canis::Scene("main_menu", "assets/scenes/main_menu.scene"));

	sceneManager.PreLoad(
		&window,
		&inputManager,
		&time,
		&camera,
		&assetManager,
		seed
	);

	Canis::Log("Q App 0");

	Load();

	appState = AppState::ON;

	Loop();
}
void App::Load()
{
	sceneManager.ForceLoad("engine_splash");
	//sceneManager.ForceLoad("MainMenuScene");
	//sceneManager.ForceLoad("MainScene");

	// start timer
	previousTime = high_resolution_clock::now();
}
void App::Loop()
{
	while (appState == AppState::ON)
	{
		deltaTime = time.startFrame();
		sceneManager.SetDeltaTime(deltaTime);

		Update();
		Draw();
		// Get SDL to swap our buffer
		window.SwapBuffer();
		LateUpdate();
		InputUpdate();

		window.fps = time.endFrame(); 
	}
}
void App::Update()
{
	sceneManager.Update();
}
void App::Draw()
{
	sceneManager.Draw();
}
void App::LateUpdate()
{
	sceneManager.LateUpdate();
}
void App::InputUpdate()
{
	if (!inputManager.Update(window.GetScreenWidth(), window.GetScreenHeight()))
		appState = AppState::OFF;
	
	sceneManager.InputUpdate();
}