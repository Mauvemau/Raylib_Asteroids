#include "Hud.h"
#include "Button.h" // Para el boton de pausa.
#include "Utils.h" // Para el texto centrado.
#include "Game/Game.h" // Para pausar el juego.

#include "Game/ObjectManager.h" // Debug

namespace Hud {
	Button pauseButton;

	void DrawText();
	void InitButtons();

	// --
	void DrawText() {
#ifdef _DEBUG
			DrawText(TextFormat("Active Bullets: %i", ObjManager::GetActiveBullets()), 
				GetScreenWidth() * .01, GetScreenHeight() * .9, GetScreenHeight() * .025, GREEN);
			DrawText(TextFormat("Active Asteroids: %i", ObjManager::GetActiveAsteroids()), 
				GetScreenWidth() * .01, GetScreenHeight() * .95, GetScreenHeight() * .025, GREEN);
#endif // _DEBUG
	}

	void InitButtons() {
		pauseButton = Buttons::Create(0,
			Vector2{ (float)(GetScreenHeight() * .08), (float)(GetScreenHeight() * .08) },
			Vector2{ (float)(GetScreenHeight() * .085), (float)(GetScreenHeight() * .085) },
			"| |");
	}

	// Global

	void Draw() {
		Buttons::Draw(pauseButton);
		DrawText();
	}

	void Update() {
		if (Buttons::Update(pauseButton))
			Game::SetPaused(true);
	}

	void Init() {
		InitButtons();
	}
}