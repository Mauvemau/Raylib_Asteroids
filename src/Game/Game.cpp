#include "Utils.h"
#include "Game.h"
#include "Spaceship.h"

#include <iostream>

namespace Game {
	Ship ship;
	Vector2 positionToMove;

	void ManageInput();
	void Draw();

	void ManageInput() {
		// Rotation.
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

		EndDrawing();
	}

	void Update() {
		ManageInput();

		Spaceship::Update(ship);

		Draw();
	}

	void Init() {
		ship = Spaceship::Create();
		Spaceship::Init(ship);
	}
}