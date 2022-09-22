#include "Asteroid.h"
#include "CollisionManager.h" // Para manejar las colisiones.

#include <iostream>

namespace Asteroids {
	
	float GetSize(AsteroidType type);
	void Move(Asteroid& asteroid);

	// --

	float GetSize(AsteroidType type) {
		float size;
		switch (type)
		{
		case AsteroidType::BIG:
			size = .05f;
			break;
		case AsteroidType::MEDIUM:
			size = .025f;
			break;
		case AsteroidType::SMALL:
			size = .05f;
			break;
		default:
			std::cout << "Invalid type! [Asteroid.cpp - GetSize()]\n";
			size = .2f;
			break;
		}
		return (float)(GetScreenWidth() * size);
	}

	void Move(Asteroid& asteroid) {
		asteroid.pos.x += asteroid.speed * cosf(asteroid.direction) * GetFrameTime();
		asteroid.pos.y += asteroid.speed * sinf(asteroid.direction) * GetFrameTime();
	}

	// Global

	void Draw(Asteroid asteroid) {
		DrawCircle(asteroid.pos.x, asteroid.pos.y, asteroid.radius, ORANGE);
	}

	void Update(Asteroid& asteroid) {
		Move(asteroid);
		Collisions::Update(asteroid);
	}

	Asteroid Create() {
		Asteroid asteroid;
		asteroid.pos = { 0, 0 };
		asteroid.radius = 0;
		asteroid.direction = 0;
		asteroid.speed = 0;
		return asteroid;
	}

	void Init(Asteroid& asteroid) {
		asteroid.radius = GetSize(AsteroidType::BIG);
		asteroid.direction = (float)GetRandomValue(0, 360);
		asteroid.speed = (float)GetRandomValue(25, 125);
	}

	void Init(Asteroid& asteroid, Vector2 pos, AsteroidType type, float direction, float speed) {
		asteroid.pos = pos;
		asteroid.radius = GetSize(type);
		asteroid.direction = direction;
		asteroid.speed = speed;
	}
}