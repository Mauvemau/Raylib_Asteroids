#pragma once
#include "Spaceship.h"
#include "Asteroid.h"
#include "Bullet.h"

namespace Collisions {
	bool CircleCircleCollision(Vector2 aPos, float aRadius, Vector2 bPos, float bRadius);
	bool Vector2RectCollision(Vector2 v, Vector2 rectPos, Vector2 rectSize);

	bool CheckBulletAsteroidCollision(Bullet bullet, Asteroid asteroid);
	// Bullets
	void Update(Bullet& bullet);
	// Asteroids
	void Update(Asteroid& asteroid, int id);
	// Ship
	void Update(Ship& ship);
}