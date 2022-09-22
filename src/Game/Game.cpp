#include "Utils.h"
#include "Game.h"
#include "Spaceship.h"
#include "Game/Asteroid.h"

#include <iostream>

namespace Game {
	Ship ship;
	Vector2 positionToMove;

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
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			Spaceship::Accelerate(ship, GetMousePosition());

		// Shooting
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT));
	}

	void Draw() {
		BeginDrawing();
		ClearBackground(BLACK);

		Spaceship::Draw(ship);

		Asteroids::Draw(asteroid1);
		Asteroids::Draw(asteroid2);
		Asteroids::Draw(asteroid3);

		EndDrawing();
	}

	// Global

	void Update() {
		ManageInput();

		Spaceship::Update(ship);

		Asteroids::Update(asteroid1);
		Asteroids::Update(asteroid2);
		Asteroids::Update(asteroid3);

		Draw();
	}

	void Init() {
		ship = Spaceship::Create();
		Spaceship::Init(ship);

		asteroid1 = Asteroids::Create();
		Asteroids::Init(asteroid1);
		asteroid2 = Asteroids::Create();
		Asteroids::Init(asteroid2);
		asteroid3 = Asteroids::Create();
		Asteroids::Init(asteroid3);
	}
}