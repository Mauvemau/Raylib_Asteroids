#include "Game.h"
#include "raylib.h"

namespace Game {
	void Draw();

	void Draw() {
		BeginDrawing();
		ClearBackground(BLACK);

		EndDrawing();
	}

	void Update() {
		Draw();
	}

	void Init() {

	}
}