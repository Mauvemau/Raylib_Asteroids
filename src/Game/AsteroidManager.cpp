#include "AsteroidManager.h"

#include <iostream>

namespace AstManager {
	const int maxBig = 20;
	const int maxMed = 40;
	const int maxSmall = 80;
	Asteroid bigAsteroids[maxBig];
	Asteroid medAsteroids[maxMed];
	Asteroid smallAsteroids[maxSmall];

	int activeBig;
	int activeMed;
	int activeSmall;

	void SortArray(Asteroid arr[], int id);

	// --

	void SortArray(Asteroid arr[], int id) {

	}

	// Global

	void DeActivateAsteroid(AsteroidType type, int id) {
		switch (type)
		{
		case AsteroidType::BIG:
			break;
		case AsteroidType::MEDIUM:
			break;
		case AsteroidType::SMALL:
			break;
		default:
			break;
		}
	}

	void ActivateAsteroid(AsteroidType type) {
		switch (type)
		{
		case AsteroidType::BIG:
			Asteroids::Init(bigAsteroids[activeBig], AsteroidType::BIG);
			activeBig++;
			break;
		case AsteroidType::MEDIUM:
			Asteroids::Init(medAsteroids[activeMed], AsteroidType::MEDIUM);
			activeMed++;
			break;
		case AsteroidType::SMALL:
			Asteroids::Init(smallAsteroids[activeSmall], AsteroidType::SMALL);
			activeSmall++;
			break;
		default:
			std::cout << "Invalid type! [AsteroidManager.cpp - ActivateAsteroid()]\n";
			break;
		}
	}

	void ActivateAsteroid(Asteroid& asteroid, Vector2 pos, AsteroidType type, float direction, float speed) {
		switch (type)
		{
		case AsteroidType::BIG:
			Asteroids::Init(bigAsteroids[activeBig], pos,  AsteroidType::BIG, direction, speed);
			activeBig++;
			break;
		case AsteroidType::MEDIUM:
			Asteroids::Init(medAsteroids[activeMed], pos, AsteroidType::MEDIUM, direction, speed);
			activeMed++;
			break;
		case AsteroidType::SMALL:
			Asteroids::Init(smallAsteroids[activeSmall], pos, AsteroidType::SMALL, direction, speed);
			activeSmall++;
			break;
		default:
			std::cout << "Invalid type! [AsteroidManager.cpp - ActivateAsteroid()]\n";
			break;
		}
	}

	void Update() {
		for (int i = 0; i < activeBig; i++) {

		}
		for (int i = 0; i < activeMed; i++) {

		}
		for (int i = 0; i < activeSmall; i++) {

		}
	}

	void Init() {
		for (int i = 0; i < maxBig; i++) {
			bigAsteroids[i] = Asteroids::Create();
			Asteroids::Init(bigAsteroids[i], AsteroidType::BIG);
		}
		for (int i = 0; i < maxMed; i++) {
			medAsteroids[i] = Asteroids::Create();
			Asteroids::Init(medAsteroids[i], AsteroidType::MEDIUM);
		}
		for (int i = 0; i < maxSmall; i++) {
			smallAsteroids[i] = Asteroids::Create();
			Asteroids::Init(smallAsteroids[i], AsteroidType::SMALL);
		}

		activeBig = 0;
		activeMed = 0;
		activeSmall = 0;
	}
}