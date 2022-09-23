#pragma once
#include "raylib.h"
#include "Asteroid.h"

/*
Pseudo Pool, se ocupa de instanciar, activar y desactivar asteroides dentro de un array.
*/

namespace AstManager {
	void DeActivateAsteroid(AsteroidType type, int id);
	void ActivateAsteroid(AsteroidType type); // Sobrecarga, crea un asteroide de caracteristicas random.
	void ActivateAsteroid(Asteroid& asteroid, Vector2 pos, AsteroidType type, float direction, float speed);

	void Update();
	void Init();
}