#include "ObjectManager.h"
#include "CollisionManager.h"
#include "AssetLoader.h" // Para los sonidos.
#include "Game.h" // Para el game time.
#include "Animations.h" // Para las explosiones.

#include <iostream>

namespace ObjManager {
	// Asteroids
	const int maxAsteroids = 50;
	Asteroid asteroids[maxAsteroids];
	int activeAsteroids;

	//Bullets
	const int maxBullets = 50;
	Bullet bullets[maxBullets];
	int activeBullets;
	
	void HandleCollision(int bulletID, int asteroidID);
	// Asteroids
	void DestroyAsteroid(int id, float angle);
	void PrintLog(AsteroidType type, bool creating);
	// Bullets
	void HandleBulletLifeTime(int id);

	// --
	
	void HandleCollision(int bulletID, int asteroidID) {
		float bulletAngle = bullets[bulletID].direction;
		DeActivateBullet(bulletID);
		DestroyAsteroid(asteroidID, bulletAngle);
	}

	// Asteroids
	void DestroyAsteroid(int id, float angle) {
		switch (asteroids[id].type)
		{
		case AsteroidType::BIG:
			ActivateAsteroid(asteroids[id].pos, AsteroidType::MEDIUM, 
				asteroids[id].direction - .25, Asteroids::GetSpeed(AsteroidType::MEDIUM));
			ActivateAsteroid(asteroids[id].pos, AsteroidType::MEDIUM,
				asteroids[id].direction + .25, Asteroids::GetSpeed(AsteroidType::MEDIUM));
			break;
		case AsteroidType::MEDIUM:
			ActivateAsteroid(asteroids[id].pos, AsteroidType::SMALL,
				angle - .25, Asteroids::GetSpeed(AsteroidType::SMALL));
			ActivateAsteroid(asteroids[id].pos, AsteroidType::SMALL,
				angle + .25, Asteroids::GetSpeed(AsteroidType::SMALL));
			break;
		default:
			break;
		}
		Animations::PlayAnimation(Anims::EXPLOSION, asteroids[id].pos, 
			Vector2{ (float)(Asteroids::GetSize(asteroids[id].type) * 6), (float)(Asteroids::GetSize(asteroids[id].type) * 6) });
		DeActivateAsteroid(id);
		Assets::PlayAudio((Audio)GetRandomValue((int)Audio::EXPLOSION_1, (int)Audio::EXPLOSION_3), .5);
	}

	void PrintLog(AsteroidType type, bool creating) {
		std::cout << ((creating) ?  "Created " : "Destroyed ") << 
			Asteroids::GetTypeString(type) << " Asteroid! (" << 
			activeAsteroids << " active)\n";
	}

	// Bullets
	void HandleBulletLifeTime(int id) {
		if (bullets[id].lifeTime < (Game::GetGameTime() - bullets[id].spawnTime))
			DeActivateBullet(id);
	}

	void PrintLog(bool creating) {
		std::cout << ((creating) ? "Created " : "Destroyed ") <<"Bullet! (" <<
			activeBullets << " active)\n";
	}

	// Global

	int GetMaxBullets() {
		return maxBullets;
	}

	int GetActiveBullets() {
		return activeBullets;
	}

	int GetMaxAsteroids() {
		return maxAsteroids;
	}

	int GetActiveAsteroids() {
		return activeAsteroids;
	}
	
	// Bullets
	void DeActivateBullet(int id) {
		if (id < activeBullets) {
			bullets[id] = bullets[activeBullets - 1];
			activeBullets--;
		}
	}

	void ActivateBullet(Vector2 pos, float size, float direction, float speed, float lifeTime) {
		if (activeBullets < maxBullets) {
			Bullets::Init(bullets[activeBullets], pos, size, direction, speed, lifeTime, Game::GetGameTime());
			activeBullets++;
		}
	}

	// Asteroids
	void DeActivateAsteroid(int id) {
		if (id < activeAsteroids) {
			AsteroidType type = asteroids[id].type; // Para el log
			asteroids[id] = asteroids[activeAsteroids - 1];
			activeAsteroids--;
		}
	}

	void ActivateAsteroid(AsteroidType type) {
		if (activeAsteroids < maxAsteroids) {
			Asteroids::Init(asteroids[activeAsteroids], type);
			activeAsteroids++;
		}
	}

	void ActivateAsteroid(Vector2 pos, AsteroidType type, float direction, float speed) {
		if (activeAsteroids < maxAsteroids) {
			Asteroids::Init(asteroids[activeAsteroids], pos, type, direction, speed);
			activeAsteroids++;
		}
	}

	// General
	void Draw() {
		// Bullets
		for (int i = 0; i < activeBullets; i++) {
			Bullets::Draw(bullets[i]);
		}
		// Asteroids
		for (int i = 0; i < activeAsteroids; i++) {
			Asteroids::Draw(asteroids[i]);
		}
	}

	void Update() {
		// Asteroids
		for (int i = 0; i < activeAsteroids; i++) {
			Asteroids::Update(asteroids[i], i);
			if (Collisions::CheckShipAsteroidCollision(asteroids[i])) {
				DeActivateAsteroid(i);
				Spaceship::ResetAcceleration(Game::GetPlayer());
				Game::SetHalted();
				Game::RemoveLive(1);
				Assets::PlayAudio(Audio::HURT, 1);
			}
		}
		// Bullets
		for (int i = 0; i < activeBullets; i++) {
			Bullets::Update(bullets[i]);
			HandleBulletLifeTime(i);
		}
		// Primero Updateamos todos, despues loopeamos nuevamente para checkear colisiones.
		for (int i = 0; i < activeBullets; i++) {
			for (int j = 0; j < activeAsteroids; j++) {
				if (Collisions::CheckBulletAsteroidCollision(bullets[i], asteroids[j]))
					HandleCollision(i, j);
			}
		}
	}

	void Init() {
		// Asteroids
		for (int i = 0; i < maxAsteroids; i++) {
			asteroids[i] = Asteroids::Create();
		}
		activeAsteroids = 0;

		// Bullets
		for (int i = 0; i < maxBullets; i++) {
			bullets[i] = Bullets::Create();
		}
		activeBullets = 0;
	}
}