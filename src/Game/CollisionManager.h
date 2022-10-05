#pragma once
#include "Spaceship.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Pickup.h"

namespace Collisions {
	bool CircleCircleCollision(Vector2 aPos, float aRadius, Vector2 bPos, float bRadius);
	bool Vector2RectCollision(Vector2 v, Vector2 rectPos, Vector2 rectSize);

	bool CheckBulletShipCollision(Bullet bullet, Ship ship);
	bool CheckBulletAsteroidCollision(Bullet bullet, Asteroid asteroid);
	bool CheckShipAsteroidCollision(Asteroid asteroid);
	// Pickups
	void Update(Pickup& pickup);
	// Bullets
	void Update(Bullet& bullet);
	// Asteroids
	void Update(Asteroid& asteroid);
	// Ship
	void Update(Ship& ship);
}