#pragma once
#include "raylib.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Pickup.h"

/*
Pseudo Pool, se ocupa de instanciar, activar y desactivar objetos dentro de arrays.
*/

namespace ObjManager {
	int GetMaxBullets();
	int GetActiveBullets();
	int GetMaxAsteroids();
	int GetActiveAsteroids();

	// Pickups
	void DeActivatePickup(int id);
	void ActivatePickup();
	void ActivatePickup(PickupType type);

	// Bullets
	void DeActivateBullet(int id);
	void ActivateBullet(Vector2 pos, float size, float direction, float speed, float lifeTime, bool hurtsPlayer);

	// Asteroids
	void DeActivateAsteroid(int id);
	void ActivateAsteroid(AsteroidType type); // Sobrecarga, crea un asteroide de caracteristicas random.
	void ActivateAsteroid(Vector2 pos, AsteroidType type, float direction, float speed);

	// General
	void Draw();
	void Update();
	void Init();
}