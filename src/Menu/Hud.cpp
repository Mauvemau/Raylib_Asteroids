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
			{(float)(GetScreenWidth() * .5),(float)(GetScreenHeight() * .1)},
			GetScreenHeight() * .07,
			ORANGE);
		Utils::DrawCenteredText("- Collect the Gold -",
			{ (float)(GetScreenWidth() * .5),(float)(GetScreenHeight() * .16) },
			GetScreenHeight() * .03,
			RAYWHITE);
		Utils::DrawCenteredText("- Rescue the Stranded Astronauts -",
			{ (float)(GetScreenWidth() * .5),(float)(GetScreenHeight() * .2) },
			GetScreenHeight() * .03,
			RAYWHITE);
		Utils::DrawCenteredText("- Survive -",
			{ (float)(GetScreenWidth() * .5),(float)(GetScreenHeight() * .24) },
			GetScreenHeight() * .03,
			RED);
		Utils::DrawCenteredText("Important Notes:",
			{ (float)(GetScreenWidth() * .5),(float)(GetScreenHeight() * .3) },
			GetScreenHeight() * .07,
			ORANGE);
		Utils::DrawCenteredText("- [Right Click] to Accelerate towards the Cursor -",
			{ (float)(GetScreenWidth() * .5),(float)(GetScreenHeight() * .36) },
			GetScreenHeight() * .03,
			RAYWHITE);
		Utils::DrawCenteredText("- [Left Click] to Shoot -",
			{ (float)(GetScreenWidth() * .5),(float)(GetScreenHeight() * .4) },
			GetScreenHeight() * .03,
			RAYWHITE);
	}

	void DrawLives() {
		Vector2 size = { (float)(GetScreenHeight() * .03), (float)(GetScreenHeight() * .03) };
		float spacing = 0;
		for (int i = 0; i < Game::GetLives(); i++) {
			if (i > 0)
				spacing += size.x + GetScreenWidth() * .01;
			Assets::DrawSprite(Sprite::SPACESHIP, 
				{ (float)((GetScreenWidth() * .01) + spacing), (float)(GetScreenHeight() * .08) }, size,
				{ 0, 0 }, 0, GREEN);
		}
	}

	void DrawText() {
		DrawText(TextFormat("Score: %i", Game::GetScore()),
			GetScreenWidth() * .01, GetScreenHeight() * .01, GetScreenHeight() * .06, RAYWHITE);

#ifdef _DEBUG
			DrawText(TextFormat("Game Time: %f", Game::GetGameTime()),
				GetScreenWidth() * .01, GetScreenHeight() * .85, GetScreenHeight() * .025, GREEN);
			DrawText(TextFormat("Active Bullets: %i", ObjManager::GetActiveBullets()), 
				GetScreenWidth() * .01, GetScreenHeight() * .9, GetScreenHeight() * .025, GREEN);
			DrawText(TextFormat("Active Asteroids: %i", ObjManager::GetActiveAsteroids()), 
				GetScreenWidth() * .01, GetScreenHeight() * .95, GetScreenHeight() * .025, GREEN);
#endif // _DEBUG
	}

	void InitButtons() {
		pauseButton = Buttons::Create(0,
			Vector2{ (float)(GetScreenWidth() * .935), (float)(GetScreenHeight() * .08) },
			Vector2{ (float)(GetScreenHeight() * .085), (float)(GetScreenHeight() * .085) },
			"| |");

		playButton = Buttons::Create(1,
			{ (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .75) },
			{ (float)(GetScreenWidth() * .3), (float)(GetScreenHeight() * .1) },
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