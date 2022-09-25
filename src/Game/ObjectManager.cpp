#include "ObjectManager.h"

#include <algorithm>
#include <iostream>

namespace ObjManager {
	// Asteroids
	const int maxBig = 20;
	Asteroid bigAsteroids[maxBig];
	const int maxMed = 40;
	Asteroid medAsteroids[maxMed];
	const int maxSmall = 80;
	Asteroid smallAsteroids[maxSmall];

	int activeBig;
	int activeMed;
	int activeSmall;

	//Bullets
	const int maxBullets = 30;
	Bullet bullets[maxBullets];

	int activeBullets;

	// --

	// Bullets
	void DeActivateBullet(int id) {
		if (id < activeBullets) {
			bullets[id] = bullets[activeBullets - 1];
			activeBullets--;
			std::cout << "Destroyed Bullet! (" << activeBullets << " active)\n";
		}
	}

	void ActivateBullet(Vector2 pos, float size, float direction, float speed) {
		if (activeBullets < maxBullets) {
			Bullets::Init(bullets[activeBullets], pos, size, direction, speed);
			activeBullets++;
			std::cout << "Created Bullet! (" << activeBullets << " active)\n";
		}
	}

	// Global

	// Asteroids
	void DeActivateAsteroid(AsteroidType type, int id) {
		switch (type)
		{
		case AsteroidType::BIG:
			if (id < activeBig) {
				bigAsteroids[id] = bigAsteroids[activeBig - 1];
				activeBig--;
				std::cout << "Destroyed Big Asteroid! (" << activeBig << " active)\n";
			}
			break;
		case AsteroidType::MEDIUM:
			if (id < activeMed) {
				medAsteroids[id] = medAsteroids[activeMed - 1];
				activeMed--;
				std::cout << "Destroyed Medium Asteroid! (" << activeMed << " active)\n";
			}
			break;
		case AsteroidType::SMALL:
			if (id < activeSmall) {
				smallAsteroids[id] = smallAsteroids[activeSmall - 1];
				activeSmall--;
				std::cout << "Destroyed Small Asteroid! (" << activeSmall << " active)\n";
			}
			break;
		default:
			std::cout << "Invalid type! [AsteroidManager.cpp - DeActivateAsteroid()]\n";
			break;
		}
	}

	void ActivateAsteroid(AsteroidType type) {
		switch (type)
		{
		case AsteroidType::BIG:
			if (activeBig < maxBig) {
				Asteroids::Init(bigAsteroids[activeBig], AsteroidType::BIG);
				activeBig++;
				std::cout << "Created Big Asteroid! (" << activeBig << " active)\n";
			}
			break;
		case AsteroidType::MEDIUM:
			if (activeMed < maxMed) {
				Asteroids::Init(medAsteroids[activeMed], AsteroidType::MEDIUM);
				activeMed++;
				std::cout << "Created Medium Asteroid! (" << activeMed << " active)\n";
			}
			break;
		case AsteroidType::SMALL:
			if (activeSmall < maxSmall) {
				Asteroids::Init(smallAsteroids[activeSmall], AsteroidType::SMALL);
				activeSmall++;
				std::cout << "Created Small Asteroid! (" << activeSmall << " active)\n";;
			}
			break;
		default:
			std::cout << "Invalid type! [AsteroidManager.cpp - ActivateAsteroid()]\n";
			break;
		}
	}

	void ActivateAsteroid(Vector2 pos, AsteroidType type, float direction, float speed) {
		switch (type)
		{
		case AsteroidType::BIG:
			if (activeBig < maxBig) {
				Asteroids::Init(bigAsteroids[activeBig], pos, AsteroidType::BIG, direction, speed);
				activeBig++;
				std::cout << "Created Big Asteroid! (" << activeBig << " active)\n";
			}
			break;
		case AsteroidType::MEDIUM:
			if (activeMed < maxMed) {
				Asteroids::Init(medAsteroids[activeMed], pos, AsteroidType::MEDIUM, direction, speed);
				activeMed++;
				std::cout << "Created Medium Asteroid! (" << activeMed << " active)\n";
			}
			break;
		case AsteroidType::SMALL:
			if (activeSmall < maxSmall) {
				Asteroids::Init(smallAsteroids[activeSmall], pos, AsteroidType::SMALL, direction, speed);
				activeSmall++;
				std::cout << "Created Small Asteroid! (" << activeSmall << " active)\n";;
			}
			break;
		default:
			std::cout << "Invalid type! [AsteroidManager.cpp - ActivateAsteroid()]\n";
			break;
		}
	}

	// General
	void Draw() {
		// Bullets
		for (int i = 0; i < activeBullets; i++) {
			Bullets::Draw(bullets[i]);
		}
		// Asteroids
		for (int i = 0; i < activeBig; i++) {
			Asteroids::Draw(bigAsteroids[i]);
		}
		for (int i = 0; i < activeMed; i++) {
			Asteroids::Draw(medAsteroids[i]);
		}
		for (int i = 0; i < activeSmall; i++) {
			Asteroids::Draw(smallAsteroids[i]);
		}
	}

	void Update() {
		// Asteroids
		for (int i = 0; i < activeBig; i++) {
			Asteroids::Update(bigAsteroids[i], i);
		}
		for (int i = 0; i < activeMed; i++) {
			Asteroids::Update(medAsteroids[i], i);
		}
		for (int i = 0; i < activeSmall; i++) {
			Asteroids::Update(smallAsteroids[i], i);
		}
		// Bullets
		for (int i = 0; i < activeBullets; i++) {
			Bullets::Update(bullets[i], i);
		}
	}

	void Init() {
		// Asteroids
		for (int i = 0; i < maxBig; i++) {
			bigAsteroids[i] = Asteroids::Create();
		}
		for (int i = 0; i < maxMed; i++) {
			medAsteroids[i] = Asteroids::Create();
		}
		for (int i = 0; i < maxSmall; i++) {
			smallAsteroids[i] = Asteroids::Create();
		}
		
		activeBig = 0;
		activeMed = 0;
		activeSmall = 0;

		// Bullets
		for (int i = 0; i < maxBullets; i++) {
			bullets[i] = Bullets::Create();
		}
		activeBullets = 0;
	}
}