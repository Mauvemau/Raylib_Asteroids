#include "Spaceship.h"
#include "Utils.h"
#include "CollisionManager.h" // Para manejar las colisiones.

namespace Spaceship {
	void Move(Ship& ship);
	void LimitAcceleration(Ship& ship);

	// --

	void Move(Ship& ship) {
		ship.pos.x += (ship.acceleration.x * GetFrameTime()) * 380.0f;
		ship.pos.y += (ship.acceleration.y * GetFrameTime()) * 380.0f;
	}

	void LimitAcceleration(Ship& ship) {
		if (ship.acceleration.x > ship.maxAccel) {
			ship.acceleration.x = ship.maxAccel;
		}
		if (ship.acceleration.x < -ship.maxAccel) {
			ship.acceleration.x = -ship.maxAccel;
		}
		if (ship.acceleration.y > ship.maxAccel) {
			ship.acceleration.y = ship.maxAccel;
		}
		if (ship.acceleration.y < -ship.maxAccel) {
			ship.acceleration.y = -ship.maxAccel;
		}
	}

	// Global

	float GetCollisionRadius(Ship ship) {
		return (float)(ship.size.x * .5);
	}

	void Accelerate(Ship& ship, Vector2 target) {
		Vector2 vectorDir = Utils::GetTargetVector(ship.pos, target);
		Vector2 normalizedDir;
		normalizedDir.x = (vectorDir.x / Utils::Modulo(vectorDir));
		normalizedDir.y = (vectorDir.y / Utils::Modulo(vectorDir));

		ship.acceleration.x += normalizedDir.x * GetFrameTime();
		ship.acceleration.y += normalizedDir.y * GetFrameTime();
		LimitAcceleration(ship);
	}

	void Rotate(Ship& ship, float ang) {
		ship.rotation = ang;
	}

	void Draw(Ship ship) {
		DrawRectanglePro(
			{ ship.pos.x, ship.pos.y, ship.size.x, ship.size.y }, 
			{ (float)(ship.size.x  * .5), (float)(ship.size.y * .5) }, 
			ship.rotation, 
			RED);

		#ifdef _DEBUG
		DrawCircle(ship.pos.x, ship.pos.y, GetCollisionRadius(ship), Fade(GREEN, .5));
		#endif
	}

	void Update(Ship& ship) {
		Move(ship);
		Collisions::Update(ship);
	}

	Ship Create() {
		Ship ship;
		ship.pos = { 0, 0 };
		ship.size = { 0, 0 };
		ship.acceleration = { 0, 0 };
		ship.rotation = 0;
		ship.maxAccel = 0;
		return ship;
	}

	void Init(Ship& ship) {
		ship.pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .5) };
		ship.size = { (float)(GetScreenWidth() * .02), (float)(GetScreenHeight() * .08) };
		ship.maxAccel = 1.0f;
	}
	void Init(Ship& ship, Vector2 pos, float maxAccel) {
		ship.pos = pos;
		ship.maxAccel = maxAccel;
	}
}
