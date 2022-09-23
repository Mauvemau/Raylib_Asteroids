#include "Utils.h"
#include "Game.h"
#include "Spaceship.h"
#include "Game/Asteroid.h"
#include "Menu/PauseMenu.h" // Extension, menu de pausa.
#include "Menu/Hud.h" // Hud del juego.

#include <iostream>

namespace Game {
	Ship ship;

	bool paused;

	// Placeholder
	Asteroid asteroid1;
	Asteroid asteroid2;
	Asteroid asteroid3;
	// Placeholder

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
		ClearBackground(BLACK);

		Spaceship::Draw(ship);

		Asteroids::Draw(asteroid1);
		Asteroids::Draw(asteroid2);
		Asteroids::Draw(asteroid3);

		if (!paused)
			Hud::Draw();
		else
			Pause::Draw();

		EndDrawing();
	}

	// Global

	void SetPaused(bool val) {
		paused = val;
	}

	void Update() {
		if (!paused) {
			ManageInput();

			Spaceship::Update(ship);

			Asteroids::Update(asteroid1);
			Asteroids::Update(asteroid2);
			Asteroids::Update(asteroid3);

			Hud::Update();
		}
		else {
			Pause::Update();
		}

		Draw();
	}

	void Init() {
		Hud::Init();
		Pause::Init();

		ship = Spaceship::Create();
		Spaceship::Init(ship);
		
		paused = false;

		asteroid1 = Asteroids::Create();
		Asteroids::Init(asteroid1, AsteroidType::BIG);
		asteroid2 = Asteroids::Create();
		Asteroids::Init(asteroid2, AsteroidType::MEDIUM);
		asteroid3 = Asteroids::Create();
		Asteroids::Init(asteroid3, AsteroidType::SMALL);
	}
}