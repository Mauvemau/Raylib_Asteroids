#include "CollisionManager.h"

namespace Collisions {
	void CheckBounds(Vector2& pos); // Se ocupa de manejar el warping al chocar con los bordes de la pantalla.

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

	void Update(Ship& ship) {
		CheckBounds(ship.pos);
	}
}