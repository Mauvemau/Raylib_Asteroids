#include "Hud.h"
#include "Button.h" // Para el boton de pausa.
#include "Utils.h" // Para el texto centrado.
#include "Game/Game.h" // Para pausar el juego.
#include "AssetLoader.h"

#include "Game/ObjectManager.h" // Debug

namespace Hud {
	Button pauseButton;
	Button playButton;

	void DrawTutorial();
	void DrawLives();
	void DrawText();
	void InitButtons();

	// --

	void DrawTutorial() {
		Utils::DrawCenteredText("Mission Objective:", 
			{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .1)},
			static_cast<int>(GetScreenHeight() * .07f),
			ORANGE);
		Utils::DrawCenteredText("- Collect the Gold -",
			{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .16) },
			static_cast<int>(GetScreenHeight() * .03f),
			RAYWHITE);
		Utils::DrawCenteredText("- Rescue the Stranded Astronauts -",
			{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .2) },
			static_cast<int>(GetScreenHeight() * .03f),
			RAYWHITE);
		Utils::DrawCenteredText("- Survive -",
			{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .24) },
			static_cast<int>(GetScreenHeight() * .03f),
			RED);
		Utils::DrawCenteredText("Important Notes:",
			{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .3) },
			static_cast<int>(GetScreenHeight() * .07f),
			ORANGE);
		Utils::DrawCenteredText("- [Right Click] to Accelerate towards the Cursor -",
			{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .36) },
			static_cast<int>(GetScreenHeight() * .03f),
			RAYWHITE);
		Utils::DrawCenteredText("- [Left Click] to Shoot -",
			{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .4) },
			static_cast<int>(GetScreenHeight() * .03f),
			RAYWHITE);
	}

	void DrawLives() {
		Vector2 size = { static_cast<float>(GetScreenHeight() * .03), static_cast<float>(GetScreenHeight() * .03) };
		float spacing = 0;
		for (int i = 0; i < Game::GetLives(); i++) {
			if (i > 0)
				spacing += size.x + GetScreenWidth() * .01f;
			Assets::DrawSprite(Sprite::SPACESHIP, 
				{ static_cast<float>((GetScreenWidth() * .01) + spacing), static_cast<float>(GetScreenHeight() * .08) }, size,
				{ 0, 0 }, 0, GREEN);
		}
	}

	void DrawText() {
		DrawText(TextFormat("Score: %i", Game::GetScore()),
			static_cast<int>(GetScreenWidth() * .01f), static_cast<int>(GetScreenHeight() * .01f), static_cast<int>(GetScreenHeight() * .06f), RAYWHITE);

#ifdef _DEBUG
			DrawText(TextFormat("Game Time: %f", Game::GetGameTime()),
				static_cast<int>(GetScreenWidth() * .01f), static_cast<int>(GetScreenHeight() * .85f), static_cast<int>(GetScreenHeight() * .025f), GREEN);
			DrawText(TextFormat("Active Bullets: %i", ObjManager::GetActiveBullets()), 
				static_cast<int>(GetScreenWidth() * .01f), static_cast<int>(GetScreenHeight() * .9f), static_cast<int>(GetScreenHeight() * .025f), GREEN);
			DrawText(TextFormat("Active Asteroids: %i", ObjManager::GetActiveAsteroids()), 
				static_cast<int>(GetScreenWidth() * .01f), static_cast<int>(GetScreenHeight() * .95f), static_cast<int>(GetScreenHeight() * .025f), GREEN);
#endif // _DEBUG
	}

	void InitButtons() {
		pauseButton = Buttons::Create(0,
			Vector2{ static_cast<float>(GetScreenWidth() * .935), static_cast<float>(GetScreenHeight() * .08) },
			Vector2{ static_cast<float>(GetScreenHeight() * .085), static_cast<float>(GetScreenHeight() * .085) },
			"| |");

		playButton = Buttons::Create(1,
			{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .75) },
			{ static_cast<float>(GetScreenWidth() * .3), static_cast<float>(GetScreenHeight() * .1) },
			"Start Mission");
	}

	// Global

	void Draw() {
		Buttons::Draw(pauseButton);
		if (Game::GetHasStarted()) {
			DrawText();
			DrawLives();
		}
		else {
			Buttons::Draw(playButton);
			DrawTutorial();
		}
	}

	void Update() {
		if (Buttons::Update(pauseButton))
			Game::SetPaused(true);
		if (!Game::GetHasStarted()) {
			if (Buttons::Update(playButton))
				Game::StartGame();
		}
	}

	void Init() {
		InitButtons();
	}
}