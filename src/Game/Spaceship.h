#pragma once
#include "raylib.h"

struct Cannon {
	bool isEvil; // Si las balas de este cañon lastiman al jugador.
	float fireRate; // La cantidad de disparos por segundo.
	float power; // La velocidad a la que salen disparadas las balas.
	float range; // Cuantos segundos las balas permanecen vivas.
	float caliber; // El tamaño de las balas.
	float lastShot; // La ultima vez que se disparo.
};

struct Ship {
	Vector2 pos; // La posicion actual en pantalla.
	Vector2 size; // Que tan ancho y alto.
	Vector2 acceleration; // Aceleracion en cada direccion.
	float rotation; // Rotacion de la nave.
	float speed;
	float maxAccel; // Aceleracion maxima.
	Cannon cannon;
};

namespace Spaceship {
	float GetCollisionRadius(Ship ship);

	void Shoot(Ship& ship);
	void ResetAcceleration(Ship& ship);
	void Accelerate(Ship& ship, Vector2 target);
	void Rotate(Ship& ship, float ang);

	void Draw(Ship ship);
	void AdjustToRes(Ship& ship);
	void Update(Ship& ship);
	Ship Create();
	void Init(Ship& ship); // Sobrecarga, asigna a valores default.
	void Init(Ship& ship, Vector2 pos, float speed, float maxAccel);
}
