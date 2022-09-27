#include "Spaceship.h"
#include "Utils.h"
#include "CollisionManager.h" // Para manejar las colisiones.
#include "ObjectManager.h" // Para disparar balas.
#include "Game.h" // Para el Gametime.
#include "Animations.h" // Para el blink.

namespace Spaceship {
	void Move(Ship& ship);
	void LimitAcceleration(Ship& ship);
	void InitCannon(Cannon& cannon);
	Cannon CreateCannon();

	// --

	void Move(Ship& ship) {
		ship.pos.x += (ship.acceleration.x * GetFrameTime()) * ship.speed;
		ship.pos.y += (ship.acceleration.y * GetFrameTime()) * ship.speed;
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

	void InitCannon(Cannon& cannon) {
		cannon.fireRate = .25f;
		cannon.power = 700.0f;
		cannon.range = .8f;
		cannon.caliber = (GetScreenWidth() * .005);
		cannon.lastShot = 0;
	}

	Cannon CreateCannon() {
		Cannon cannon;
		cannon.fireRate = 0;
		cannon.power = 0;
		cannon.range = 0;
		cannon.caliber = 0;
		cannon.lastShot = 0;
		return cannon;
	}

	// Global

	float GetCollisionRadius(Ship ship) {
		return (float)(ship.size.x * .5);
	}

	void Shoot(Ship& ship) {
		/* Falta:
		Arreglar offset.
		*/
		if (ship.cannon.fireRate < (Game::GetGameTime() - ship.cannon.lastShot)) {
			ship.cannon.lastShot = Game::GetGameTime();
			ObjManager::ActivateBullet(ship.pos,
				ship.cannon.caliber,
				Utils::DegreesToRadians(ship.rotation - 90.0f),
				ship.cannon.power,
				ship.cannon.range);
		}
	}

	void ResetAcceleration(Ship& ship) {
		ship.acceleration = { 0, 0 };
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
		if(Animations::Blink())
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
		if (!Game::GetIsHalted()) {
			Move(ship);
		}
		Collisions::Update(ship);
	}

	Ship Create() {
		Ship ship;
		ship.pos = { 0, 0 };
		ship.size = { 0, 0 };
		ship.acceleration = { 0, 0 };
		ship.rotation = 0;
		ship.maxAccel = 0;
		ship.cannon = CreateCannon();
		return ship;
	}

	void Init(Ship& ship) {
		ship.pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .5) };
		ship.size = { (float)(GetScreenWidth() * .02), (float)(GetScreenHeight() * .08) };
		ship.speed = 400.0f;
		ship.maxAccel = 1.0f;
		InitCannon(ship.cannon);
	}
	void Init(Ship& ship, Vector2 pos, float speed, float maxAccel) {
		ship.pos = pos;
		ship.size = { (float)(GetScreenWidth() * .02), (float)(GetScreenHeight() * .08) };
		ship.speed = speed;
		ship.maxAccel = maxAccel;
		InitCannon(ship.cannon);
	}
}
