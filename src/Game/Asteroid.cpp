#include "Asteroid.h"
#include "CollisionManager.h" // Para manejar las colisiones.
#include "AssetLoader.h" // Para el sprite
#include "Utils.h"

namespace Asteroids {
	void Move(Asteroid& asteroid);

	// --

	float GetSpeed(AsteroidType type) {
		float speed;
		switch (type)
		{
		case AsteroidType::BIG:
			speed = static_cast<float>(GetRandomValue(50, 200));
			break;
		case AsteroidType::MEDIUM:
			speed = static_cast<float>(GetRandomValue(150, 250));
			break;
		case AsteroidType::SMALL:
			speed = static_cast<float>(GetRandomValue(200, 300));
			break;
		default:
			std::cout << "Invalid type! [Asteroid.cpp - GetSpeed()]\n";
			speed = static_cast<float>(GetRandomValue(25, 125));
			break;
		}
		return speed * (static_cast<float>(GetScreenHeight()) / 1080);
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
		return static_cast<float>(GetScreenWidth() * size);
	}

	void Draw(Asteroid asteroid) {
#ifdef _DEBUG
		DrawCircle(static_cast<int>(asteroid.pos.x), static_cast<int>(asteroid.pos.y), GetSize(asteroid.type), Fade(GREEN, .25));
#endif
		
		Assets::DrawSprite(Assets::GetAsteroidSprite(asteroid.type),
			asteroid.pos,
			{ static_cast<float>(GetSize(asteroid.type) * 2), static_cast<float>(GetSize(asteroid.type) * 2) },
			{ static_cast<float>(GetSize(asteroid.type)), static_cast<float>(GetSize(asteroid.type)) },
			0, WHITE);
	}

	void Update(Asteroid& asteroid) {
		Move(asteroid);
		Collisions::Update(asteroid);
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
		asteroid.type = (AsteroidType)GetRandomValue(static_cast<int>(AsteroidType::BIG), static_cast<int>(AsteroidType::SMALL));
		asteroid.pos = Utils::GetRandomSpawnPosition();
		asteroid.direction = static_cast<float>(GetRandomValue(0, 360));
		asteroid.speed = GetSpeed(asteroid.type);
	}

	void Init(Asteroid& asteroid, AsteroidType type) {
		asteroid.type = type;
		asteroid.pos = Utils::GetRandomSpawnPosition();
		asteroid.direction = static_cast<float>(GetRandomValue(0, 360));
		asteroid.speed = GetSpeed(asteroid.type);
	}

	void Init(Asteroid& asteroid, Vector2 pos, AsteroidType type, float direction, float speed) {
		asteroid.type = type;
		asteroid.pos = pos;
		asteroid.direction = direction;
		asteroid.speed = speed;
	}
}