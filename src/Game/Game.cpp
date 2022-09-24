#include "Utils.h"
#include "Game.h"
#include "Spaceship.h"
#include "AsteroidManager.h"

#include "Menu/PauseMenu.h" // Extension, menu de pausa.
#include "Menu/Hud.h" // Hud del juego.

#include <iostream>

namespace Game {
	Ship ship;

	bool paused;

	void ManageInput();
	void Draw();

	// --

	void ManageInput() {
		// Rotation
		if (GetMouseX() < GetScreenWidth() && GetMouseX() > 0 &&
			GetMouseY() < GetScreenHeight() && GetMouseY > 0 &&
			Utils::GetDistance(ship.pos, GetMousePosition()) > (float)(ship.size.y * .25))
			Spaceship::Rotate(ship, Utils::CalculateRotationAngle(ship.pos, GetMousePosition()));

		// Acceleration
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) &&
			GetMouseX() < GetScreenWidth() && GetMouseX() > 0 &&
			GetMouseY() < GetScreenHeight() && GetMouseY > 0)
			Spaceship::Accelerate(ship, GetMousePosition());

		// Shooting
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT));

		// Pausing
		if (IsKeyPressed(KEY_ESCAPE))
			SetPaused(true);
	}

	void Draw() {
		BeginDrawing();
		// Background
		ClearBackground(BLACK);
		// Ship
		Spaceship::Draw(ship);
		// Asteroids
		AstManager::Draw();

		if (!paused)
			// Hud
			Hud::Draw();
		else
			// PauseMenu
			Pause::Draw();

		EndDrawing();
	}

	// Global

	void SetPaused(bool val) {
		paused = val;
	}

	void Update() {
		if (!paused) {
			// Input
			ManageInput();
			// Ship
			Spaceship::Update(ship);
			// Asteroids
			AstManager::Update();
			// Hud
			Hud::Update();
		}
		else
			// PauseMenu
			Pause::Update();

		Draw();
	}

	void Init() {
		// Hud
		Hud::Init();
		// PauseMenu
		Pause::Init();
		paused = false;
		// Ship
		ship = Spaceship::Create();
		Spaceship::Init(ship);
		// Asteroids
		AstManager::Init();

	}
}