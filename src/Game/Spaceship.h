#pragma once
#include "raylib.h"

struct Ship {
	Vector2 pos; // The current position on the screen.
	Vector2 size; // The width and height.
	Vector2 acceleration; // Direction in which to move the spaceship.
	float rotation; // The current rotation of the sprite.
	float maxAccel; // The maximum acceleration.
};

namespace Spaceship {
	void Accelerate(Ship& ship, Vector2 target);
	void Rotate(Ship& ship, float ang);
	void Draw(Ship ship);
	void Update(Ship& ship);
	Ship Create();
	void Init(Ship& ship); // Sobrecarga, asigna a valores default.
	void Init(Ship& ship, Vector2 pos, float maxAccel);
}