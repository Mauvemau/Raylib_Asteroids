#include "Game.h"
#include "Spaceship.h"

#include "raylib.h"

#include <iostream>

#define M_PI 3.14159265358979323846

namespace Game {
	Ship ship;
	Vector2 positionToMove;

	float GetDistance(Vector2 v1, Vector2 v2);
	float CalculateRotationAngle();
	void ManageInput();
	void Draw();

	float GetDistance(Vector2 v1, Vector2 v2)
	{
		float distX = v1.x - v2.x;
		float distY = v1.y - v2.y;
		return sqrt((distX * distX) + (distY * distY));
	}

	float CalculateRotationAngle() {
		if (GetMouseX() > GetScreenWidth() || GetMouseX() < 0 ||
			GetMouseY() > GetScreenHeight() || GetMouseY < 0 ||
			GetDistance(ship.pos, GetMousePosition()) < (float)(ship.size.y * .25))
			return ship.rotation;

		Vector2 targetVector = {
			(GetMouseX() - ship.pos.x),
			(GetMouseY() - ship.pos.y)
		};
		float targetAng = atan2(targetVector.x, -targetVector.y);
		targetAng = targetAng * (180.0 / M_PI);
		return targetAng;
	}

	void ManageInput() {
		Spaceship::Rotate(ship, CalculateRotationAngle());
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