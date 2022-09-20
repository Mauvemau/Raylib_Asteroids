#include "Utils.h"
#include "Game.h"
#include "Spaceship.h"

#include "raylib.h"

#include <iostream>

#define M_PI 3.14159265358979323846

namespace Game {
	Ship ship;
	Vector2 positionToMove;
	void ManageInput();
	void Draw();

	void ManageInput() {
		if (GetMouseX() < GetScreenWidth() && GetMouseX() > 0 &&
			GetMouseY() < GetScreenHeight() && GetMouseY > 0 &&
			Utils::GetDistance(ship.pos, GetMousePosition()) > (float)(ship.size.y * .25))
			Spaceship::Rotate(ship, Utils::CalculateRotationAngle(ship.pos, GetMousePosition()));
	}

	void Draw() {
		BeginDrawing();
		ClearBackground(BLACK);

		Spaceship::Draw(ship);

		EndDrawing();
	}

	void Update() {
		ManageInput();
		Draw();
	}

	void Init() {
		ship = Spaceship::Create();
		Spaceship::Init(ship);
	}
}