#pragma once
#include "raylib.h"

#include <iostream>

enum class AsteroidType {
	BIG,
	MEDIUM,
	SMALL
};

struct Asteroid {
	Vector2 pos;
	AsteroidType type;
	float direction;
	float speed;
};

namespace Asteroids {
	std::string GetTypeString(AsteroidType type);
	float GetSpeed(AsteroidType type);
	float GetSize(AsteroidType type);

	void Draw(Asteroid asteroid);
	void Update(Asteroid& asteroid);
	Asteroid Create();
	void Init(Asteroid& asteroid); // Sobrecarga, crea un asteroide random, direccion y velocidad random.
	void Init(Asteroid& asteroid, AsteroidType type); // Sobrecarga, crea un asteroide de un tipo en una posicion, direccion y velocidad random.
	void Init(Asteroid& asteroid, Vector2 pos, AsteroidType type, float direction, float speed);
}
