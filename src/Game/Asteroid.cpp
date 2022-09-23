#include "Asteroid.h"
#include "CollisionManager.h" // Para manejar las colisiones.

#include <iostream>

namespace Asteroids {
	
	Vector2 GetRandomSpawnPosition();
	float GetSpeed(AsteroidType type);
	float GetSize(AsteroidType type);
	void Move(Asteroid& asteroid);

	// --

	Vector2 GetRandomSpawnPosition() {
		return { 0, 0 };
	}

	float GetSpeed(AsteroidType type) {
		float speed;
		switch (type)
		{
		case AsteroidType::BIG:
			speed = (float)GetRandomValue(25, 125);
			break;
		case AsteroidType::MEDIUM:
			speed = (float)GetRandomValue(50, 150);
			break;
		case AsteroidType::SMALL:
			speed = (float)GetRandomValue(75, 175);
			break;
		default:
			std::cout << "Invalid type! [Asteroid.cpp - GetSpeed()]\n";
			speed = (float)GetRandomValue(25, 125);
			break;
		}
		return speed;
	}

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
			size = .01f;
			break;
		default:
			std::cout << "Invalid type! [Asteroid.cpp - GetSize()]\n";
			size = .05f;
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
		AsteroidType type = (AsteroidType)GetRandomValue((int)AsteroidType::BIG, (int)AsteroidType::SMALL);
		asteroid.pos = GetRandomSpawnPosition();
		asteroid.direction = (float)GetRandomValue(0, 360);
		asteroid.radius = GetSize(type);
		asteroid.speed = GetSpeed(type);
	}

	void Init(Asteroid& asteroid, AsteroidType type) {
		asteroid.pos = GetRandomSpawnPosition();
		asteroid.direction = (float)GetRandomValue(0, 360);
		asteroid.radius = GetSize(type);
		asteroid.speed = GetSpeed(type);
	}

	void Init(Asteroid& asteroid, Vector2 pos, AsteroidType type, float direction, float speed) {
		asteroid.pos = pos;
		asteroid.radius = GetSize(type);
		asteroid.direction = direction;
		asteroid.speed = speed;
	}
}