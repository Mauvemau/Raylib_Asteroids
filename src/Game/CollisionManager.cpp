#include "CollisionManager.h"

#include "Game.h"

#include <iostream>

namespace Collisions {

	bool CheckAsteroidShipCollision(Asteroid asteroid);
	void CheckBounds(Vector2& pos); // Se ocupa de manejar el warping al chocar con los bordes de la pantalla.

	// --

	bool CheckAsteroidShipCollision(Asteroid asteroid) {
		Ship ship = Game::GetPlayer();
		return CircleCircleCollision(asteroid.pos, Asteroids::GetSize(asteroid.type), ship.pos, Spaceship::GetCollisionRadius(ship));
	}

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
	bool CircleCircleCollision(Vector2 aPos, float aRadius, Vector2 bPos, float bRadius) {
		float distX = aPos.x - bPos.x;
		float distY = aPos.y - bPos.y;
		float dist = sqrtf((distX * distX) + (distY * distY));

		return (dist <= (aRadius + bRadius));
	}

	bool Vector2RectCollision(Vector2 v, Vector2 rectPos, Vector2 rectSize) {
		return (v.x > rectPos.x && v.x < (rectPos.x + rectSize.x) && v.y > rectPos.y && v.y < (rectPos.y + rectSize.y));
	}

	bool CheckBulletAsteroidCollision(Bullet bullet, Asteroid asteroid) {
		return CircleCircleCollision(bullet.pos, bullet.size, asteroid.pos, Asteroids::GetSize(asteroid.type));
	}

	void Update(Bullet& bullet) {
		CheckBounds(bullet.pos);
	}

	void Update(Asteroid& asteroid, int id) {
		CheckBounds(asteroid.pos);
		if (CheckAsteroidShipCollision(asteroid))
			std::cout << "[COLLISION] Ship -> Asteroid [TYPE:" 
			<< Asteroids::GetTypeString(asteroid.type) << ", ID: " << id << "]\n";
	}

	void Update(Ship& ship) {
		CheckBounds(ship.pos);
	}
}