#include "Asteroid.h"
#include "CollisionManager.h" // Para manejar las colisiones.

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

	void Move(Asteroid& asteroid) {
		asteroid.pos.x += asteroid.speed * cosf(asteroid.direction) * GetFrameTime();
		asteroid.pos.y += asteroid.speed * sinf(asteroid.direction) * GetFrameTime();
	}

	// Global
	std::string GetTypeString(AsteroidType type) {
		std::string name;
		switch (type)
		{
		case AsteroidType::BIG:
			name = "Big";
			break;
		case AsteroidType::MEDIUM:
			name = "Medium";
			break;
		case AsteroidType::SMALL:
			name = "Small";
			break;
		default:
			std::cout << "Invalid type! [Asteroid.cpp - GetSize()]\n";
			name = "Wtf";
			break;
		}
		return name;
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

	void Draw(Asteroid asteroid) {
		DrawCircle(asteroid.pos.x, asteroid.pos.y, GetSize(asteroid.type), ORANGE);
	}

	void Update(Asteroid& asteroid, int id) {
		Move(asteroid);
		Collisions::Update(asteroid, id);
	}

	Asteroid Create() {
		Asteroid asteroid;
		asteroid.pos = { 0, 0 };
		asteroid.type = AsteroidType::BIG;
		asteroid.direction = 0;
		asteroid.speed = 0;
		return asteroid;
	}

	void Init(Asteroid& asteroid) {
		asteroid.type = (AsteroidType)GetRandomValue((int)AsteroidType::BIG, (int)AsteroidType::SMALL);
		asteroid.pos = GetRandomSpawnPosition();
		asteroid.direction = (float)GetRandomValue(0, 360);
		asteroid.speed = GetSpeed(asteroid.type);
	}

	void Init(Asteroid& asteroid, AsteroidType type) {
		asteroid.type = type;
		asteroid.pos = GetRandomSpawnPosition();
		asteroid.direction = (float)GetRandomValue(0, 360);
		asteroid.speed = GetSpeed(asteroid.type);
	}

	void Init(Asteroid& asteroid, Vector2 pos, AsteroidType type, float direction, float speed) {
		asteroid.type = type;
		asteroid.pos = pos;
		asteroid.direction = direction;
		asteroid.speed = speed;
	}
}