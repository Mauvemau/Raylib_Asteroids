#pragma once
#include "raylib.h"

struct Ship {
	Vector2 pos;
	Vector2 size;
	float rotation;
};

namespace Spaceship {
	void Rotate(Ship& ship, float ang);
	void Draw(Ship ship);
	Ship Create();
	void Init(Ship& ship);
}