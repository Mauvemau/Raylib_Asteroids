#include "Game.h"

#include "raylib.h"

#include <iostream>

namespace Game {
	Vector2 positionToMove;

	void ManageInput();
	void Draw();

	void ManageInput() {
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			positionToMove = GetMousePosition();
			std::cout << "Moving towards (" << positionToMove.x << ";" << positionToMove.y << ")\n";
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			std::cout << "Shooting!\n";
	}

	void Draw() {
		BeginDrawing();
		ClearBackground(BLACK);

		EndDrawing();
	}

	void Update() {
		ManageInput();
		Draw();
	}

	void Init() {

	}
}