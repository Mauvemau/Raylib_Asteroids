#pragma once
#include "Game/Spaceship.h"

namespace Collisions {
	bool Vector2RectCollision(Vector2 v, Vector2 rectPos, Vector2 rectSize);
	void Update(Ship& ship);
}