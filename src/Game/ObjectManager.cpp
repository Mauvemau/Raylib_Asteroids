#include "ObjectManager.h"

#include <algorithm>
#include <iostream>

namespace ObjManager {
	// Asteroids
	const int maxAsteroids = 60;
	Asteroid asteroids[maxAsteroids];
	int activeAsteroids;

	//Bullets
	const int maxBullets = 30;
	Bullet bullets[maxBullets];

	int activeBullets;
	
	// Asteroids
	void PrintLog(AsteroidType type, bool creating);
	// Bullets
	void PrintLog(bool creating);

	// --
	
	// Asteroids
	void PrintLog(AsteroidType type, bool creating) {
		std::cout << ((creating) ?  "Created " : "Destroyed ") << 
			Asteroids::GetTypeString(type) << " Asteroid! (" << 
			activeAsteroids << " active)\n";
	}

	// Bullets
	void PrintLog(bool creating) {
		std::cout << ((creating) ? "Created " : "Destroyed ") <<"Bullet! (" <<
			activeBullets << " active)\n";
	}

	// Global
	
	// Bullets
	void DeActivateBullet(int id) {
		if (id < activeBullets) {
			bullets[id] = bullets[activeBullets - 1];
			activeBullets--;
			PrintLog(false);
		}
	}

	void ActivateBullet(Vector2 pos, float size, float direction, float speed) {
		if (activeBullets < maxBullets) {
			Bullets::Init(bullets[activeBullets], pos, size, direction, speed);
			activeBullets++;
			PrintLog(true);
		}
	}

	// Asteroids
	void DeActivateAsteroid(int id) {
		if (id < activeAsteroids) {
			AsteroidType type = asteroids[id].type; // Para el log
			asteroids[id] = asteroids[activeAsteroids - 1];
			activeAsteroids--;
			PrintLog(type, false);
		}
	}

	void ActivateAsteroid(AsteroidType type) {
		if (activeAsteroids < maxAsteroids) {
			Asteroids::Init(asteroids[activeAsteroids], type);
			activeAsteroids++;
			PrintLog(type, true);
		}
	}

	void ActivateAsteroid(Vector2 pos, AsteroidType type, float direction, float speed) {
		if (activeAsteroids < maxAsteroids) {
			Asteroids::Init(asteroids[activeAsteroids], pos, type, direction, speed);
			activeAsteroids++;
			PrintLog(type, true);
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
		}
		// Bullets
		for (int i = 0; i < activeBullets; i++) {
			Bullets::Update(bullets[i], i);
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