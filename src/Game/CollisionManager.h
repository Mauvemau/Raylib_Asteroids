#pragma once
#include "Spaceship.h"
#include "Asteroid.h"

namespace Collisions {
	bool CircleCircleCollision(Vector2 aPos, float aRadius, Vector2 bPos, float bRadius);
	bool Vector2RectCollision(Vector2 v, Vector2 rectPos, Vector2 rectSize);
	void Update(Asteroid& asteroid, int id);
	void Update(Ship& ship);
}