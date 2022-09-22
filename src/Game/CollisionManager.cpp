#include "CollisionManager.h"

namespace Collisions {
	void CheckBounds(Vector2& pos); // Se ocupa de manejar el warping al chocar con los bordes de la pantalla.

	// --

	void CheckBounds(Vector2& pos) {
		if (pos.x < 0)
			pos.x = GetScreenWidth();
		if (pos.x > GetScreenWidth())
			pos.x = 0;
		if (pos.y < 0)
			pos.y = GetScreenHeight();
		if (pos.y > GetScreenHeight())
			pos.y = 0;
	}

	// Global

	bool Vector2RectCollision(Vector2 v, Vector2 rectPos, Vector2 rectSize) {
		return (v.x > rectPos.x && v.x < (rectPos.x + rectSize.x) && v.y > rectPos.y && v.y < (rectPos.y + rectSize.y));
	}

	void Update(Asteroid& asteroid) {
		CheckBounds(asteroid.pos);
	}

	void Update(Ship& ship) {
		CheckBounds(ship.pos);
	}
}