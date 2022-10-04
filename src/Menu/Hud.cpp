#include "Hud.h"
#include "Button.h" // Para el boton de pausa.
#include "Utils.h" // Para el texto centrado.
#include "Game/Game.h" // Para pausar el juego.
#include "AssetLoader.h"

#include "Game/ObjectManager.h" // Debug

namespace Hud {
	Button pauseButton;

	void DrawLives();
	void DrawText();
	void InitButtons();

	// --

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
		DrawText(TextFormat("Score: %i", 00000),
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
	}

	// Global

	void Draw() {
		Buttons::Draw(pauseButton);
		DrawText();
		DrawLives();
	}

	void Update() {
		if (Buttons::Update(pauseButton))
			Game::SetPaused(true);
	}

	void Init() {
		InitButtons();
	}
}