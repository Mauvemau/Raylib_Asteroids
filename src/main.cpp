#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;

int main() {
	InitWindow(screenWidth, screenHeight, "Raylib Asteroids!");

	while (!WindowShouldClose()) {

		BeginDrawing();
			ClearBackground(BLACK);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}