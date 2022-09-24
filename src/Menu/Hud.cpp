#include "Hud.h"
#include "Button.h" // Para el boton de pausa.
#include "Game/Game.h"

namespace Hud {
	Button pauseButton;

	void InitButtons();

	// --

	void InitButtons() {
		pauseButton = Buttons::Create(0,
			Vector2{ (float)(GetScreenHeight() * .08), (float)(GetScreenHeight() * .08) },
			Vector2{ (float)(GetScreenHeight() * .085), (float)(GetScreenHeight() * .085) },
			"| |");
	}

	// Global

	void Draw() {
		Buttons::Draw(pauseButton);
	}

	void Update() {
		if (Buttons::Update(pauseButton))
			Game::SetPaused(true);
	}

	void Init() {
		InitButtons();
	}
}