#pragma once
#include "Spaceship.h"
#include "Asteroid.h"

namespace Collisions {
	bool Vector2RectCollision(Vector2 v, Vector2 rectPos, Vector2 rectSize);
	void Update(Asteroid& asteroid);
	void Update(Ship& ship);
}