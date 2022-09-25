#include "Utils.h"
#include "Game.h"
#include "ObjectManager.h"

#include "Menu/PauseMenu.h" // Extension, menu de pausa.
#include "Menu/Hud.h" // Hud del juego.

#include <iostream>

Ship ship;

namespace Game {

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
		ObjManager::Draw();

		if (!paused)
			// Hud
			Hud::Draw();
		else
			// PauseMenu
			Pause::Draw();

		EndDrawing();
	}

	// Global

	Ship GetPlayer() {
		return ship;
	}

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
			ObjManager::Update();
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
		ObjManager::Init();
		for (int i = 0; i < 20; i++) {
			ObjManager::ActivateAsteroid((AsteroidType)
				GetRandomValue((int)AsteroidType::BIG, (int)AsteroidType::SMALL));
		}
		ObjManager::ActivateBullet(Vector2{ 0, 0 }, (GetScreenWidth() * .005), 64.0f, 300.0f);
	}
}